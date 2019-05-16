#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <signal.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <termios.h>
# include "../libft/libft.h"

# define SPACE 0x20
# define ENTER 0xA
# define ESCAPE 0x1B
# define LEFT 0x445B1B
# define RIGHT 0x435B1B
# define DELETE 0x7F
# define DELETE2 0x7E335B1B
# define CLEAR_SCREEN ft_putstr_fd(tgetstr("cl", NULL), STDERR_FILENO);

typedef struct          s_arg
{
    char                *name;
    bool                selected;
    bool                underlined;
    bool                is_last;
    struct s_arg        *next;
    struct s_arg        *last;
}                       t_arg;

typedef struct          s_args
{
    struct s_arg        *args;
    struct s_arg        *deleted;
    int                 count;
}                       t_args;

typedef struct          s_term
{
    struct termios      old_term;
    struct termios      new_term;
    int                 rows;
}                       t_term;

t_term                  terms;
t_args                  args;
struct winsize	        window_size;

void                    init_args(int ac, char **av);
void		            set_sighandle(void);
void                    reset_term(void);
void                    init_term(void);
void                    term_loop(int *status);
void                    print_args(void);
void                    printer(t_arg *arg);
bool                    check_argsize(t_arg *head);
void                    print_selected(t_arg *args);
#endif