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

void				change_pos(int side, t_select *select)
{
	if (side == SIDE_UP)
	{
		if (select->pos == 1)
			select->pos = select->elem_count;
		else
			select->pos--;
	}
	else if (side == SIDE_DOWN)
	{
		if (select->pos == select->elem_count)
			select->pos = 1;
		else
			select->pos++;
	}
}

char				*ft_list_to_str(t_list *lst)
{
	char 			*ret;
	char			*str;
	register int	len;
	register int	i;
	t_list			*head;

	head = lst;
	len = 0;
	if (!lst)
		return (NULL);
	while (lst)
	{
		len += ft_strlen(((t_elem*)lst->content)->name) + 1;
		lst = lst->next;
	}
	if (!(ret = malloc(len + 1)))
		on_crash(MALLOC_ERR);
	len = -1;
	while (head)
	{
		str = ((t_elem*)head->content)->name;
		i = -1;
		while (str[++i])
			ret[++len] = str[i];
		ret[++len] = '\n';
		head = head->next;
	}
	ret[len + 1] = '\0';
	return (ret);
}

t_list				*ft_fill_elem_list(char *av[])
{
	int				i;
	t_list			*ret;
	t_elem			*elem;

	i = 0;
	ret = NULL;
	while (av[++i])
		ret = list_add_back(ret, init_elem(av[i]));
	elem = (t_elem*)ret->content;
	elem->name = remake_esc(elem->name, elem->colour, UNDERLINE);
	return (ret);
}
