# cell-automaton
cell automaton simulator

Usage:
       
       life map_path [-z (!!!useful!!!)] [-s sleep in ms] [-m iteration min] [-e iteration max]
       
       Map must be a square, the first line contain only rules: format: birth/stay
       
       * -n n: number of neighbours cell to check (1 default)
       
       * -m n: first iteration to print
       
       * -e n: last iteration to print
       
         of course m must be < than e
       
       * -s s: m sleep in ms between generation (use '+' and '-' to modify on run-time).
       
       * -t t: path of table of rule for von Neumann's neighborhood (like langton's loops)
       
       * -p p: print map on each iteration in ascii
       
       * -w w: for wireworld's maps (can't be used with -t)
       
       * -ww ww: for personal rules of wireworld (one additional rule).
       
       * -q q: quit at the end (work only with -e)
       
       * -x x: map size (deprecated)
       
       * -z z: !!Useful!! adapt zoom
       
       * -1d 1d: one dimension Usage: life -1d rules starting_position
       
         rules on 8 bits, please see http://mathworld.wolfram.com/ElementaryCellularAutomaton.html
       
         starting_position with 0 or 1 (something like: 00010101000 or 00000100000)

for more information please contact me! :)
