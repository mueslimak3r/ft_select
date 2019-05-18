/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 16:26:20 by calamber          #+#    #+#             */
/*   Updated: 2019/05/16 16:26:45 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void			print_selected(t_arg *args)
{
	while (args)
	{
		if (args->selected)
		{
			ft_putstr(args->name);
			ft_putchar(' ');
		}
		if (args->is_last)
			break ;
		args = args->next;
	}
	ft_putchar('\n');
}

static void		choose_color(t_arg *arg)
{
	struct stat	info;

	if (lstat(arg->name, &info) == -1)
		ft_putstr_fd(C_WHITE, STDERR_FILENO);
	else if (S_ISDIR(info.st_mode))
		ft_putstr_fd(C_BLUE, STDERR_FILENO);
	else if (S_ISLNK(info.st_mode))
		ft_putstr_fd(C_MAGENTA, STDERR_FILENO);
	else if (info.st_mode & S_IXUSR)
		ft_putstr_fd(C_RED, STDERR_FILENO);
}

void			printer(t_arg *arg)
{
	char		*underline;
	char		buf[2048];

	underline = buf;
	choose_color(arg);
	if (arg->underlined)
		ft_putstr_fd(tgetstr("us", &underline), STDERR_FILENO);
	if (arg->selected)
		ft_putstr_fd(tgetstr("so", &underline), STDERR_FILENO);
	ft_putstr_fd(arg->name, STDERR_FILENO);
	if (arg->underlined)
		ft_putstr_fd(tgetstr("ue", &underline), STDERR_FILENO);
	if (arg->selected)
		ft_putstr_fd(tgetstr("se", &underline), STDERR_FILENO);
	ft_putstr_fd(C_WHITE, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
}
