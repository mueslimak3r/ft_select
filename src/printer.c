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

void		print_selected(t_arg *args)
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

void		printer(t_arg *arg)
{
	char	*underline;
	char	buf[2048];

	underline = buf;
	if (arg->underlined)
		ft_putstr_fd(tgetstr("us", &underline), STDERR_FILENO);
	if (arg->selected)
		ft_putstr_fd(tgetstr("so", &underline), STDERR_FILENO);
	ft_putstr_fd(arg->name, STDERR_FILENO);
	if (arg->underlined)
		ft_putstr_fd(tgetstr("ue", &underline), STDERR_FILENO);
	if (arg->selected)
		ft_putstr_fd(tgetstr("se", &underline), STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
}
