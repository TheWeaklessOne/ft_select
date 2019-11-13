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

int					on_arrow_keys(long c, t_select *select)
{
	t_elem			*old_elem;
	t_elem			*new_elem;

	old_elem = list_at(select->elem_lst, select->pos)->content;
	if (c == DOWN_K)
		change_pos(SIDE_DOWN, select);
	else if (c == UP_K)
		change_pos(SIDE_UP, select);
	else
		return (0);
	new_elem = list_at(select->elem_lst, select->pos)->content;
	old_elem->name = remake_esc(old_elem->name, old_elem->colour,
			(old_elem->selected) ? REVERSE : NORMAL_STATE);
	new_elem->name = remake_esc(new_elem->name, new_elem->colour,
			(new_elem->selected) ? BOTH_STATE : UNDERLINE);
	return (0);
}

int					on_del_key(t_select *select)
{
	t_elem			*elem;
	t_list			*to_free;

	to_free =  select->elem_lst;
	select->elem_lst = select->elem_lst->next;
	elem = (t_elem*)to_free->content;
	free(elem->name);
	free(to_free->content);
	free(to_free);
	select->elem_count--;
	elem = (t_elem*)select->elem_lst->content;
	elem->name = remake_esc(elem->name, elem->colour,
			(elem->selected) ? BOTH_STATE : UNDERLINE);
	return (0);
}

int					on_space_key(t_select *select)
{
	t_elem			*elem;

	elem = (t_elem*)list_at(select->elem_lst, select->pos)->content;
	elem->selected = !elem->selected;
	elem->name = remake_esc(elem->name, elem->colour,
			(elem->selected) ? BOTH_STATE : UNDERLINE);
	return (0);
}

int 				on_enter_key(t_select *select)
{
	t_list			*elem_list;
	t_list			*output_list;
	t_list			*output_head;
	t_elem			*elem;

	output_list = NULL;
	elem_list = select->elem_lst;
	while (elem_list)
	{
		elem = (t_elem*)elem_list->content;
		if (elem->selected)
			output_list = list_add_back(output_list, remove_esc(elem->name));
		elem_list = elem_list->next;
	}
	ft_putstr_fd(CLEAR_SCREEN, select->fd, 0);
	output_head = output_list;
	while (output_list)
	{
		ft_putstr_fd(output_list->content, select->fd, 0);
		if (output_list->next)
			ft_putstr_fd(" ", select->fd, 0);
		output_list = output_list->next;
	}
	list_remove_all(output_head, 1);
	return (0);
}

int					on_esc_key(t_select *select)
{
	return (0);
}

int					read_input(t_select *select)
{
	long			c;

	while (!(c = 0))
	{
		print_list(select);
		read(0, &c, 8);
		if (c == ENTER_K)
			return (on_enter_key(select));
		else if (c == SPACE_K)
			on_space_key(select);
		else if (c == ESC_K)
			return (on_esc_key(select));
		else if (c == BACK_SPACE_K || c == DEL_K)
			on_del_key(select);
		else
			on_arrow_keys(c, select);
	}
	return (0);
}
