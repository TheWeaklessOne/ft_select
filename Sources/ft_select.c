/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:44:51 by wstygg            #+#    #+#             */
/*   Updated: 2019/11/23 20:06:57 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_select.h"

int					print_list(void)
{
	char			str[BUFF_SIZE];
	char			*clear;

	if (!(clear = tgetstr("cl", NULL)))
		on_crash(ENV_ERR);
	tputs(clear, 1, ft_putchar_select);
	if (ioctl(0, TIOCGWINSZ, &g_select.winsize) == -1)
		on_crash(ENV_ERR);
	if (!((g_select.cols = g_select.winsize.ws_col / (g_select.max_len + 1))))
		return (write(2, "Not enough space on screen.\n", 27));
	if ((g_select.rows = g_select.elem_count / g_select.cols +
			(g_select.elem_count % g_select.cols)) >
			g_select.winsize.ws_row - 1)
		return (write(2, "Not enough space on screen.\n", 27));
	ft_list_to_str(str);
	ft_putstr_fd(str, 2, 1);
	return (0);
}

int					ft_putchar_select(int c)
{
	write(2, &c, 1);
	return (0);
}

int					ft_is_empty_input(char *av[])
{
	int				space_count;
	int				char_count;
	int				i;
	int				j;

	i = 0;
	space_count = 0;
	char_count = 0;
	while (av[++i] && (j = -1))
	{
		while (av[i][++j])
		{
			if ((av[i][j] >= 9 && av[i][j] <= 13) || av[i][j] == ' ')
				space_count++;
			char_count++;
		}
	}
	return (space_count == char_count);
}

int					main(int ac, char *av[])
{
	if (ac < 2)
		return (!write(1, "usage: ./ft_select [-r] [arguments]\n", 36));
	g_select.del = (av[1][0] == '-' && av[1][1] == 'r');
	if (ft_is_empty_input(av + g_select.del))	
		return (!write(1, "usage: ./ft_select [-r] [arguments]\n", 36));
	if (g_select.del)
		init_select(ac - 1, av + 1);
	else
		init_select(ac, av);
	init_term();
	sig_set();
	read_input();
	exit(0);
}
