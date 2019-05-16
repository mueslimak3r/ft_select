#include "../includes/ft_select.h"

bool check_argsize(t_arg *head)
{
    int size;

    size = 0;
    while (head)
    {
        if ((int)ft_strlen(head->name) > size)
            size = (int)ft_strlen(head->name);
        if (head->is_last)
            break ;
        head = head->next;
    }
    if (size + 1 > window_size.ws_col)
    {
        CLEAR_SCREEN;
        ft_putstr_fd("check argside: please resize the screen!\n", STDERR_FILENO);
        return (false);
    }
    else
        return (true);
}

void    newcolumn(void)
{
    terms.rows++;
    if (terms.rows > window_size.ws_row)
    {
        CLEAR_SCREEN;
        ft_putstr_fd("new column invalid, please resize the window!\n", STDERR_FILENO);
    }
    else
        ft_putchar_fd('\n', STDERR_FILENO);
}

void    print_args(void)
{
    int rowlen;
    t_arg   *head;

    head = args.args;
    rowlen = 0;
    CLEAR_SCREEN;
    while (head)
    {
        rowlen += ft_strlen(head->name) + 1;
        if (rowlen > window_size.ws_col)
        {
            rowlen = ft_strlen(head->name) + 1;
            newcolumn();
        }
        if (terms.rows <= window_size.ws_row)
            printer(head);
        if (head->is_last)
            break ;
        head = head->next;
    }
}

static void    push(char *name, t_arg **tail)
{
    t_arg *new;

    if (!(new = ft_memalloc(sizeof(t_arg))))
        return ;
    if (!args.args)
        *tail = new;
    new->name = name;
    new->selected = false;
    new->underlined = false;
    new->is_last = false;
    new->last = args.args;
    if (args.args)
        args.args->next = new;
    args.args = new;
}

void    init_args(int ac, char **av)
{
    t_arg *tail;

    tail = NULL;
    args.args = NULL;
    args.deleted = NULL;
    while (ac && *av)
    {
        push(*av, &tail);
        av++;
    }
    args.args->is_last = true;
    args.args->next = tail;
    tail->last = args.args;
    args.args = args.args->next;
    args.args->underlined = true;
    args.args->selected = false;
}