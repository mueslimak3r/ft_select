#include "../includes/ft_select.h"

static void        select_arg(t_arg *args)
{
    while (args)
    {
        if (args->underlined)
            args->selected = args->selected ? false : true;
        if (args->is_last)
            break ;
        args = args->next;
    }
}

static void move_arg(unsigned long *c, t_arg *args)
{
    while (args)
    {
        if (args->underlined)
        {
            args->underlined = false;
            if (*c == LEFT)
                args->last->underlined = true;
            else
                args->next->underlined = true;
            break ;
        }
        if (args->is_last)
            break ;
        args = args->next;
    }
}

static bool del(int *status)
{
    t_arg   *temp;

    temp = args.args;
    while (temp)
    {
        if (temp->underlined)
        {
            if (!args.args->last)
            {
                *status = 0;
                return(false);
            }
            args.args = args.args->last;
            args.args->underlined = true;
            args.args->next = temp->next;
            temp->next->last = args.args;
            temp->next = args.deleted;
            temp->last = NULL;
            args.deleted = temp;
        }
        if (temp->is_last)
            break ;
        temp = temp->next;
    }
    return (true);
}

void        term_loop(int *status)
{
    unsigned long		c;

    ioctl(STDERR_FILENO, TIOCGWINSZ, &window_size);
    if (check_argsize(args.args))
        print_args();
    while (1)
    {
        c = 0;
		read(STDERR_FILENO, &c, 6);
        if (c == ENTER)
            break ;
        else if (c == ESCAPE)
		{
			*status = 0;
			break ;
		}
        else if (c == SPACE)
            select_arg(args.args);
        else if (c == RIGHT || c == LEFT)
            move_arg(&c, args.args);
        else if ((c == DELETE || c == DELETE2) && !del(status))
            break ;
        print_args();
    }
}