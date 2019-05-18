/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 16:28:59 by calamber          #+#    #+#             */
/*   Updated: 2019/05/16 16:30:19 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			select_arg(t_arg *args)
{
	while (args)
	{
		if (args->underlined)
		{
			args->selected = args->selected ? false : true;
			if (args->next)
			{
				args->underlined = false;
				args->next->underlined = true;
				break ;
			}
		}
		if (args->is_last)
			break ;
		args = args->next;
	}
}

static void			move_arg(unsigned long *c, t_arg *args)
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

static void			rm_arg(void)
{
	t_arg			*temp;

	temp = args.args;
	args.args = args.args->last;
	args.args->is_last = temp->is_last ? true : args.args->is_last;
	args.args->underlined = true;
	args.args->next = temp->next;
	temp->next->last = args.args;
	temp->next = args.deleted;
	temp->last = NULL;
	args.deleted = temp;
	while (args.args)
	{
		if (args.args->is_last)
			break ;
		args.args = args.args->next;
	}
}

static bool			del(int *status)
{
	while (args.args)
	{
		if (args.args->underlined)
		{
			if (args.args == args.args->last)
			{
				*status = 0;
				return (false);
			}
			rm_arg();
			break ;
		}
		if (args.args->is_last)
			break ;
		args.args = args.args->next;
	}
	args.args = args.args->next;
	return (true);
}

void				term_loop(int *status)
{
	unsigned long	c;

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
		if (check_argsize(args.args))
			print_args();
	}
}
