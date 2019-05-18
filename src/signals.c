/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 16:25:17 by calamber          #+#    #+#             */
/*   Updated: 2019/05/16 16:25:57 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void		sig_resume(int nb)
{
	if (nb)
	{
		init_term();
		set_sighandle();
		CLEAR_SCREEN;
		if (check_argsize(args.args))
			print_args();
	}
}

static void		sig_suspend(int nb)
{
	if (nb)
	{
		reset_term();
		CLEAR_SCREEN;
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	}
}

static void		sig_resize(int nb)
{
	if (nb)
	{
		CLEAR_SCREEN;
		GET_SCREENSIZE;
		if (check_argsize(args.args))
			print_args();
	}
}

static void		sig_stop(int nb)
{
	if (nb)
	{
		reset_term();
		exit(0);
	}
}

void			set_sighandle(void)
{
	signal(SIGFPE, sig_stop);
	signal(SIGILL, sig_stop);
	signal(SIGINT, sig_stop);
	signal(SIGSEGV, sig_stop);
	signal(SIGTERM, sig_stop);
	signal(SIGWINCH, sig_resize);
	signal(SIGCONT, sig_resume);
	signal(SIGTSTP, sig_suspend);
	signal(SIGINT, sig_stop);
	signal(SIGABRT, sig_stop);
}
