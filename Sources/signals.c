/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:22:06 by wstygg            #+#    #+#             */
/*   Updated: 2019/11/20 17:22:07 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_select.h"

void		restore_term(void)
{
	char	*curs_end;
	char	*show_curs;

	if (!(curs_end = tgetstr("te", NULL)))
		on_crash(ENV_ERR);
	if (!(show_curs = tgetstr("ve", NULL)))
		on_crash(ENV_ERR);
	if ((tcsetattr(2, TCSANOW, &(g_select.term_save))) == -1)
		on_crash(ENV_ERR);
	tputs(curs_end, 1, &ft_putchar_select);
	tputs(show_curs, 1, &ft_putchar_select);
}

void		suspend_signal_handler(void)
{
	restore_term();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
}

void		stop_signal_handler(void)
{
	restore_term();
	exit(0);
}

void		signal_handler(int signo)
{
	if (signo == SIGTSTP)
		suspend_signal_handler();
	else if (signo == SIGINT || signo == SIGABRT || signo == SIGSTOP
		|| signo == SIGKILL || signo == SIGQUIT)
		stop_signal_handler();
	else if (signo == SIGCONT)
	{
		init_term();
		sig_set();
		print_list();
	}
	else if (signo == SIGWINCH)
		print_list();
}

void		sig_set(void)
{
	signal(SIGWINCH, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGSTOP, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGQUIT, signal_handler);
}
