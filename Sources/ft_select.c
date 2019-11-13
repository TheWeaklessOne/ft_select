#include "../Includes/ft_select.h"

void				print_list(t_select *select)
{
	char			*str;

	ft_putstr_fd(CLEAR_SCREEN, select->fd, 0);
	str = ft_list_to_str(select->elem_lst);
	ft_putstr_fd(CLEAR_SCREEN, select->fd, 0);
	ft_putstr_fd(str, select->fd, 0);
	free(str);
}

t_select			*act_select(t_select *select)
{
	static t_select	*ret;

	if (select)
		ret = select;
	else
		return (select);
	return (NULL);
}

int					ft_putchar_select(int c)
{
	t_select	*select;

	select = act_select(NULL);
	write(2, &c, 1);
	return		(0);
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
	t_select		select;

	if (ac < 2 || ft_is_empty_input(av))
		return (!write(1, "usage: ./ft_select [arguments]\n", 31));
	init_select(ac, av, &select);
	init_term(&select);
	read_input(&select);
	tputs(tgetstr("ve", NULL), select.fd, ft_putchar_select);
	exit(0);
}