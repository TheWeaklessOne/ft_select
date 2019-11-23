/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:00:15 by wstygg            #+#    #+#             */
/*   Updated: 2019/10/25 19:00:16 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_select.h"

void				on_plus_minus_key(int is_plus)
{
	int				i;
	t_elem			*elem;
	t_list			*lst;

	lst = g_select.elem_lst;
	i = 0;
	while (lst)
	{
		i++;
		elem = lst->content;
		elem->selected = is_plus;
		if (is_plus)
			elem->name = remake_esc(elem->name, elem->colour,
					(i == g_select.pos) ? BOTH_STATE : REVERSE);
		else
			elem->name = remake_esc(elem->name, elem->colour,
					(i == g_select.pos) ? UNDERLINE : NORMAL_STATE);
		lst = lst->next;
	}
}

void				change_by_side(int side)
{
	if (side == SIDE_UP && g_select.rows > 1)
		g_select.pos -= g_select.cols;
	else if (side == SIDE_DOWN && g_select.rows > 1)
		g_select.pos += g_select.cols;
	else if (side == SIDE_LEFT)
		g_select.pos += ((g_select.pos % g_select.cols) == 1) ?
						(g_select.cols - 1) : -1;
	else if (side == SIDE_RIGHT)
		g_select.pos += (g_select.pos % g_select.cols) ? 1 :
						(-g_select.cols + 1);
}

void				change_pos(int side)
{
	int				old_pos;

	old_pos = g_select.pos;
	change_by_side(side);
	if (g_select.pos > g_select.elem_count)
	{
		if (side == SIDE_RIGHT && (g_select.pos = old_pos))
			while (g_select.pos % g_select.cols != 1)
				g_select.pos--;
		if (side == SIDE_LEFT)
			g_select.pos = g_select.elem_count;
		if (side == SIDE_LEFT || side == SIDE_RIGHT)
			return ;
		g_select.pos = old_pos % g_select.cols;
		if (!g_select.pos)
			g_select.pos = g_select.cols;
	}
	if (g_select.pos < 1)
	{
		g_select.pos = old_pos + g_select.cols * g_select.rows - g_select.cols;
		while (g_select.pos > g_select.elem_count)
			g_select.pos -= g_select.cols;
	}
}

void				ft_list_to_str(char str[])
{
	int				col_count;
	char			*name;
	register int	i;
	register int	j;
	t_list			*lst;

	lst = g_select.elem_lst;
	i = -1;
	col_count = 0;
	while (lst)
	{
		j = -1;
		name = ((t_elem*)lst->content)->name;
		while (name[++j])
			str[++i] = name[j];
		col_count++;
		j = ((t_elem*)lst->content)->escless_len;
		if (col_count != g_select.cols)
			while (j++ < g_select.max_len)
				str[++i] = ' ';
		else if (!(col_count = 0))
			str[++i] = '\n';
		lst = lst->next;
	}
	str[i] = '\0';
}

t_list				*ft_fill_elem_list(char *av[])
{
	int				i;
	t_list			*ret;
	t_elem			*elem;

	i = 0;
	ret = NULL;
	while (av[++i])
	{
		if (ft_strlen(av[i]) > g_select.max_len)
			g_select.max_len = ft_strlen(av[i]);
		ret = list_add_back(ret, init_elem(av[i]));
	}
	elem = (t_elem*)ret->content;
	elem->name = remake_esc(elem->name, elem->colour, UNDERLINE);
	g_select.max_len = (g_select.max_len / 8 + 1) * 8;
	return (ret);
}
