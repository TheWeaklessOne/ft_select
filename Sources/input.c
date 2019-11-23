/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:17:49 by wstygg            #+#    #+#             */
/*   Updated: 2019/11/13 16:17:50 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_select.h"

int					on_arrow_keys(long c)
{
	t_elem			*old_elem;
	t_elem			*new_elem;

	old_elem = list_at(g_select.elem_lst, g_select.pos)->content;
	if (c == DOWN_K)
		change_pos(SIDE_DOWN);
	else if (c == UP_K)
		change_pos(SIDE_UP);
	else if (c == LEFT_K)
		change_pos(SIDE_LEFT);
	else if (c == RIGHT_K)
		change_pos(SIDE_RIGHT);
	else
		return (0);
	new_elem = list_at(g_select.elem_lst, g_select.pos)->content;
	old_elem->name = remake_esc(old_elem->name, old_elem->colour,
			(old_elem->selected) ? REVERSE : NORMAL_STATE);
	new_elem->name = remake_esc(new_elem->name, new_elem->colour,
			(new_elem->selected) ? BOTH_STATE : UNDERLINE);
	return (0);
}

int					on_space_key(void)
{
	t_elem			*elem;

	elem = (t_elem*)list_at(g_select.elem_lst, g_select.pos)->content;
	elem->selected = !elem->selected;
	elem->name = remake_esc(elem->name, elem->colour,
			(elem->selected) ? BOTH_STATE : UNDERLINE);
	return (0);
}

int					on_enter_key(void)
{
	t_list			*elem_list;
	t_list			*output_list;
	t_list			*output_head;
	t_elem			*elem;

	restore_term();
	output_list = NULL;
	elem_list = g_select.elem_lst;
	while (elem_list)
	{
		elem = (t_elem*)elem_list->content;
		if (elem->selected)
			output_list = list_add_back(output_list, remove_esc(elem->name));
		elem_list = elem_list->next;
	}
	output_head = output_list;
	while (output_list)
	{
		ft_putstr_fd(output_list->content, 1, 0);
		if (output_list->next)
			ft_putstr_fd(" ", 1, 0);
		output_list = output_list->next;
	}
	list_remove_all(output_head, 1);
	exit(0);
}

int					on_del_key(void)
{
	t_elem			*elem;

	if (g_select.elem_count == 1)
	{
		if (g_select.del)
			remove(remove_esc(((t_elem*)g_select.elem_lst->content)->name));
		stop_signal_handler();
	}
	elem = list_at(g_select.elem_lst, g_select.pos)->content;
	if (g_select.del)
		remove((elem->name = remove_esc(elem->name)));
	free(elem->name);
	g_select.elem_lst = list_remove_at(g_select.elem_lst, g_select.pos, 1);
	g_select.elem_count--;
	(g_select.pos > g_select.elem_count) ? g_select.pos-- : 0;
	elem = list_at(g_select.elem_lst, g_select.pos)->content;
	elem->name = remake_esc(elem->name, elem->colour,
							(elem->selected) ? BOTH_STATE : UNDERLINE);
	return (0);
}

int					read_input(void)
{
	long			c;
	int				space_error;

	while (!(c = 0))
	{
		space_error = print_list(select);
		read(2, &c, 8);
		if (c == ESC_K)
			stop_signal_handler();
		else if (!space_error)
		{
			if (c == ENTER_K)
				on_enter_key();
			else if (c == SPACE_K)
				on_space_key();
			else if (c == PLUS_KEY || c == MINUS_K)
				on_plus_minus_key(c == PLUS_KEY);
			else if (c == BACK_SPACE_K || c == DEL_K)
				on_del_key();
			else
				on_arrow_keys(c);
		}
	}
	return (0);
}
