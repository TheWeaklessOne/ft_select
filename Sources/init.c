/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:49:52 by wstygg            #+#    #+#             */
/*   Updated: 2019/11/20 16:49:53 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_select.h"

void			init_select(int ac, char *av[])
{
	g_select.max_len = 0;
	g_select.elem_lst = ft_fill_elem_list(av);
	g_select.pos = 1;
	g_select.elem_count = ac - 1;
}

char			*elem_colour(char *av)
{
	struct stat	buf;

	if ((lstat(av, &buf)) == 0)
	{
		if (S_ISBLK(buf.st_mode))
			return (BLUE);
		else if (S_ISCHR(buf.st_mode))
			return (GREEN);
		else if (S_ISDIR(buf.st_mode))
			return (CYAN);
		else if (S_ISLNK(buf.st_mode))
			return (PURPLE);
		else if (S_ISSOCK(buf.st_mode))
			return (YELLOW);
		else if (S_ISFIFO(buf.st_mode))
			return (RED);
		else
			return (DEFAULT);
	}
	else
		return (WHITE);
}

t_elem			*init_elem(char *av)
{
	t_elem		*ret;

	if (!(ret = malloc(sizeof(t_elem))))
		on_crash(MALLOC_ERR);
	ret->colour = elem_colour(av);
	ret->state = NORMAL_STATE;
	ret->selected = 0;
	ret->name = add_esc(av, ret->colour, ret->state, 0);
	ret->escless_len = ft_strlen(av);
	return (ret);
}

void			init_term(void)
{
	char		*name;
	char		*cursor_hide;
	char		*cursor_move;

	if (!(name = getenv("TERM")))
		on_crash(ENV_ERR);
	if ((tgetent(NULL, name)) < 1)
		on_crash(ENV_ERR);
	if ((tcgetattr(2, &(g_select.term_save))) == -1 ||
		tcgetattr(2, &(g_select.term_new)) == -1)
		on_crash(ENV_ERR);
	g_select.term_new.c_lflag &= ~(ICANON | ECHO);
	g_select.term_new.c_cc[VMIN] = 1;
	g_select.term_new.c_cc[VTIME] = 0;
	if ((tcsetattr(2, TCSANOW, &g_select.term_new)) == -1)
		on_crash(ENV_ERR);
	if (!(cursor_hide = tgetstr("vi", NULL)))
		on_crash(ENV_ERR);
	if (!(cursor_move = tgetstr("ti", NULL)))
		on_crash(ENV_ERR);
	tputs(cursor_hide, 1, ft_putchar_select);
	tputs(cursor_move, 1, ft_putchar_select);
}
