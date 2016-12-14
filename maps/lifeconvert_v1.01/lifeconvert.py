#!/usr/bin/env python
#
# Game of Life file converter script
# Version 1.01 - December 3, 2010
#
# Written by Adam Wolf and Matthew Beckler of Wayne and Layne, LLC
# For more details, check out: http://lifeconvert.wayneandlayne.com/

import os
from PIL import Image

class Pattern:
    def __init__(self, name):
        self.name = name
        self.init_field()

    def init_field(self):
        self.field = []
        for y in range(64):
            self.field.append([])
            for x in range(104):
                self.field[y].append(False)

    def __str__(self):
        output = "//"

        if self.name:
            output += self.name
            output += "\n"

        for row in range(64):
            line = "//"
            for col in range(104):
                if self.field[row][col]:
                        line += "X"
                else:
                        line += " "
            output += line 
            output += "\\\\\n"

        return output


    def pack(self):
        packed_field = []

        for y in range(64):
            packed_row = []
            for packed_x in range(104/8):
                packed_cell = 0
                for cell in range(8):
                    if self.field[y][packed_x*8+(7-cell)]: #if the cell is alive...
                        packed_cell += 1 << cell
                packed_row.append(packed_cell)
            packed_field.append(packed_row)
        return packed_field


    def set_alive(self, x, y):
        self.field[y][x] = True

    def set_dead(self, x, y):
        self.field[y][x] = False

    def get_struct(self):
        packed_field = self.pack()
        output = "const Pattern %s PROGMEM = {\n\"%s\",\n{" % (self.name.lower().replace(".", "_"), self.name) #need to make the first name be a "safe" name... something like only alphanumerics and _ or something.
        for y in range(64):
            output += "{"
            for packed_x in range(104/8):
                output += "0x%02X, " % packed_field[y][packed_x]
            #remove the ", " from the last one
            output = output[:-2]
            output += "},\n"
        #remove the ",\n from the last one
        output = output[:-2]
        output += "}\n};"
        return output 

    def get_image(self):
        """ Returns a PIL Image object, the visual representation of the pattern. """
        width = 104 * 5 + 104 + 1 + 10
        height = 64 * 5 + 64 + 1 + 10
        img = Image.new("RGB", (width, height), (127, 127, 127))

        # The background is already grey, now just iterate over each cell, filling black or white
        for y in range(64):
            for x in range(104):
                boxx = 6 * x + 1 + 5
                boxy = 6 * y + 1 + 5
                if self.field[y][x]:
                    img.paste((0, 0, 0), (boxx, boxy, boxx + 5, boxy + 5))
                else:
                    img.paste((255, 255, 255), (boxx, boxy, boxx + 5, boxy + 5))

        return img

    def adjust_coordinates(self, coords, x, y):
        adjusted_coordinates = []
        for pair in coords:
            adjusted_coordinates.append( (pair[0] + x, pair[1] + y))
        return adjusted_coordinates

    def parse_file(self, filename, center=True):
        self.parse_data(file(filename).readlines(), center)

    def parse_data(self, data, center=True):
        import operator
        self.init_field()
        coords = [ line.split() for line in data if not line.startswith("#") ]
        coords = [ (int(line[0]), int(line[1])) for line in coords]

        #we need to shift so all coords are positive
        #get largest x value
        largest_x = sorted(coords, key=operator.itemgetter(0))[0][0]
        largest_y = sorted(coords, key=operator.itemgetter(1))[0][1]
        largest_x *= -1
        largest_y *= -1

        adjusted_coords = self.adjust_coordinates(coords, largest_x, largest_y) 

        #find the bounding box
        xmax = sorted(adjusted_coords, key=operator.itemgetter(0), reverse=True)[0][0]
        ymax = sorted(adjusted_coords, key=operator.itemgetter(1), reverse=True)[0][1]
        #print "Bounding box: (", xmax, ",", ymax, ")"

        if center:
            width = 104
            height = 64
            assert xmax <= width
            assert ymax <= height
            x_offset = (width-xmax)/2
            y_offset = (height-ymax)/2
            adjusted_coords = self.adjust_coordinates(adjusted_coords, x_offset, y_offset)

        for x, y in adjusted_coords:
            self.set_alive(x, y)


def process_file(filename):
    p = Pattern(os.path.basename(filename))
    p.parse_file(filename)
    print p
    print p.get_struct()
    
def process_dir(dir):
    input_files = [os.path.join(dir, file) for file in os.listdir(dir) if file.endswith(".lif")]
    for input_file in input_files:
        process_file(input_file)

def make_random_pattern(density):
    #why was this so hard? this can't be the right way to do it
    #density should be *inside* the range of 0 to 1
    import random

    p = Pattern(name="random_%s" % density)

    for x in range(104):
        for y in range(64):
            if random.random() <= density:
                p.set_alive(x, y)

    return p

def main():
    import sys

    if len(sys.argv) < 2:
        print "Usage: %s input_filename" % sys.argv[0]
        sys.exit(1)

    input_filename = sys.argv[1]

    p = Pattern(os.path.basename(input_filename))
    p.parse_file(input_filename)
    print p
    print p.get_struct()
#    img = p.get_image()
#    img.show()

    # If you want to make some random fields:
    #for i in range(10):
    #    print make_random_pattern(i/10.0).get_struct()

if __name__ == "__main__":
    main()

