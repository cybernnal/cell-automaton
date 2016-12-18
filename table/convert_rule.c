//
// Created by tom billard on 15/12/2016.
//

#include "libft.h"
#include <fcntl.h>

typedef struct      s_lst
{
    int             len;
    char            tab[11];
    char            *var;
    struct s_lst   *next;
}                   t_lst;


static int		ft_error(char * str)
{
    ft_putendl_fd(str, 2);
    exit (-1);
}

static void     get_nb(char *line, t_lst **lst, t_lst **f)
{
    int i = 4;
    int j = 0;
    if (!(*lst))
    {
        (*lst) = (t_lst*)ft_memalloc((sizeof(t_list)));
        *(f) = (*lst);
        (*lst)->next = NULL;
    }
    else
    {
        (*lst)->next = (t_lst*)ft_memalloc((sizeof(t_list)));
        (*lst) = (*lst)->next;
        (*lst)->next = NULL;
    }
    (*lst)->var = ft_strrevchr(line + 4, '=');
    while (line[i] != '{')
        i++;
    ft_bzero((*lst)->tab, 10);
    while (line[i])
    {
        if (ft_isdigit(line[i]))
            (*lst)->tab[j++] = line[i];
        i++;
    }
    (*lst)->len = (int) ft_strlen((*lst)->tab);
}

static void      get_mail(t_lst **lst, t_lst *f, char *str)
{
    if (ft_strcmp((*lst)->var, str))
        (*lst) = f;
    while ((*lst) && ft_strcmp((*lst)->var, str))
        (*lst) = (*lst)->next;
}

static void     stabilize(int *tab, char **name)
{
    int i = 0;
    int tmp = 1;
    int s[3][2];
    int c = 0;

    while (i < 6)
    {
        while (tmp + i < 6)
        {
            if (ft_isalpha(name[i][0]) && !ft_strcmp(name[i], name[i + tmp]))
            {
                s[c][0] = i;
                s[c][1] = i + tmp;
                c++;
            }
            tmp++;
        }
        tmp = 1;
        i++;
    }
    if (c == 0)
        return;
    while (c >= 0)
    {
        tab[s[c][0]] = tab[s[c][1]];
        c--;
    }
}

static int     print_lettre(t_lst *lst,t_lst *f, char **name, int *tab, int j)
{
    int i = 0;
    int c = 0;
    int fi = -1;
    int s = 0;

    get_mail(&lst, f, name[j]);
    if (!lst)
        ft_error("bat file");
    if (tab[j] == -1)
        tab[j] = 0;
    while (name[i])
    {
        if (ft_isalpha(name[i][0]))
        {
            c = i;
            if (fi == -1)
                fi = i;
        }
        i++;
    }
    ft_putchar(lst->tab[tab[j]]);
    if (c == j)
    {
        i = j;
        while (i >= 0)
        {
            if (ft_isalpha(name[i][0]))
            {
                tab[i] +=1;
                get_mail(&lst, f, name[i]);
                if (tab[i] < lst->len)
                    break ;
                else if (i == fi && (s = 1))
                    break ;
                else
                    tab[i] = 0;
            }
            i--;
        }
        if (s == 1)
            return (-1);
        return (1);
    }
    return (1);
}

static void     print_rules(t_lst *lst, t_lst *f, char *line)
{
    char    **tab;
    int     i[6] = {-1, -1, -1, -1, -1, -1};
    int     j = 0;
    int s = 1;

    tab = ft_strsplit(line, ',');
    while (s != 0)
    {
        s = 0;
        while (tab[j])
        {
            if (ft_isdigit(tab[j][0]))
                ft_putchar(tab[j][0]);
            else
            {
                s++;
                if (print_lettre(lst, f, tab, i, j) <= 0)
                    s = 0;
                stabilize(i, tab);
            }
            j++;
        }
        j = 0;
        ft_putendl("");
    }
}

int main(int argc, char **argv)
{
    t_lst       *lst;
    t_lst       *f;
    int         fd;
    char        *line;

    if (argc != 2)
    {
        ft_putendl_fd("one argument only", 2);
        return (0);
    }
    if ((fd = open(argv[1], O_RDONLY)) < 0)
        ft_error("open error");
    while (get_next_line(fd, &line))
    {
        if (!line)
            ft_error("read error");
        if (line[0] == 'v')
            break ;
        free(line);
    }
    get_nb(line, &lst, &f);
    free(line);
    while (get_next_line(fd, &line))
    {
        if (!line)
            ft_error("read error");
        if (line[0] == '$')
           break ;
        get_nb(line, &lst, &f);
        free(line);
    }
    free(line);
    while (get_next_line(fd, &line))
    {
        lst = f;
        if (!line)
            ft_error("read error");
        if (!ft_isalnum(line[0]))
            break ;
        print_rules(lst, f, line);
        free (line);
     }
    free(line);
    if ((close(fd)) != 0)
        ft_error("close fd error");
    return (1);
}