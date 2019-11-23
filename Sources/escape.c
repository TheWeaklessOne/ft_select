/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:11:51 by wstygg            #+#    #+#             */
/*   Updated: 2019/11/13 16:11:53 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ft_select.h"

void				add_to_str(char **str_p, int *start, const char *add)
{
	register int	i;
	char			*str;

	str = *str_p;
	i = -1;
	while (add[++i])
		str[(*start)++] = add[i];
}

char				*remove_esc(char *str)
{
	const int		len = ft_strlen(str) - ft_strchr(str, 'm') - 6;
	register int	str_start;
	char			*ret;
	register int	i;

	if (!(ret = malloc(len + 1)))
		on_crash(MALLOC_ERR);
	str_start = ft_strchr(str, 'm');
	ret[len] = '\0';
	i = -1;
	while (++i < len)
		ret[i] = str[++str_start];
	free(str);
	return (ret);
}

char				*add_esc(char *str, char *colour, char *state, int to_free)
{
	char			*ret;
	const int		len = ft_strlen(str) + ft_strlen(state) + 11;
	int				i;

	if (!(ret = malloc(len + 1)))
		on_crash(MALLOC_ERR);
	ret[len] = '\0';
	i = 0;
	add_to_str(&ret, &i, ESCAPE);
	add_to_str(&ret, &i, colour);
	add_to_str(&ret, &i, state);
	add_to_str(&ret, &i, END_ESCAPE);
	add_to_str(&ret, &i, str);
	add_to_str(&ret, &i, RESET_ALL);
	(to_free) ? free(str) : 0;
	return (ret);
}

char				*remake_esc(char *str, char *colour, char *state)
{
	if (ft_strchr(str, '\033') != -1)
		return (add_esc(remove_esc(str), colour, state, 1));
	return (add_esc(str, colour, state, 1));
}
