//
// Created by tom billard on 15/12/2016.
//

#include "libft.h"
#include <fcntl.h>



static int		ft_error(char * str)
{
    ft_putendl_fd(str, 2);
    exit (-1);
}

int main(int argc, char **argv)
{
    int         fd;
    char        *line;
    int         i = 0;
    int         nb;

    if (argc != 2)
    {
        ft_putendl_fd("one argument only", 2);
        return (0);
    }
    if ((fd = open(argv[1], O_RDONLY)) < 0)
        ft_error("open error");
    ft_putendl(".3/23");
    ft_putstr("0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n");
    ft_putstr("0 0 0 0 0 0 0 0 0 0 ");
    while (get_next_line(fd, &line))
    {
        if (!line)
            ft_error("read error");
        while (line[i])
        {
            if (line[i] == 'b')
            {
                ft_putnbr(0);
                ft_putchar(' ');
            }
            else if (line[i] == 'o')
            {
                ft_putnbr(1);
                ft_putchar(' ');
            }
            else if (line[i] == '$')
            {
                if (i > 0 && line[i - 1] == '$')
                {
                    ft_putchar('0');
                    ft_putchar(' ');
                }
                ft_putchar('\n');
                ft_putstr("0 0 0 0 0 0 0 0 0 0 ");
            }
            else
            {
                while (ft_isdigit(line[i]))
                {
                    nb += line[i] - 48;
                    nb *= 10;
                    i++;
                }
                nb /= 10;
                while (nb > 0)
                {
                    if (line[i] == 'b')
                        ft_putnbr(0);
                    else if (line[i] == 'o')
                        ft_putnbr(1);
                    else if (line[i] == '$')
                    {
                        ft_putchar('\n');
                        //if (nb / 10 > 0)
                            ft_putchar('0');
                    }
                    nb--;
                    ft_putchar(' ');
                }
                nb = 0;
            }
            i++;
        }
        i = 0;
        free(line);
    }
    ft_putstr("0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n");
    free(line);
    if ((close(fd)) != 0)
        ft_error("close fd error");
    return (1);
}