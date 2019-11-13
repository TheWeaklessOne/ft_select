#include "../Includes/ft_select.h"

void			init_select(int ac, char *av[], t_select *select)
{
	if ((select->fd = open(ttyname(0), O_RDWR | O_NDELAY) < 0))
		on_crash(ENV_ERR);
	select->elem_lst = ft_fill_elem_list(av);
	select->pos = 1;
	select->elem_count = ac - 1;
	act_select(select);
}

t_elem			*init_elem(char *av)
{
	struct stat	buf;
	t_elem		*ret;
	if (!(ret = malloc(sizeof(t_elem))))
		on_crash(MALLOC_ERR);
	if ((lstat(av, &buf)) == 0)
	{
		if (S_ISBLK(buf.st_mode))
			ret->colour = BLUE;
		else if (S_ISCHR(buf.st_mode))
			ret->colour = GREEN;
		else if (S_ISDIR(buf.st_mode))
			ret->colour = CYAN;
		else if (S_ISLNK(buf.st_mode))
			ret->colour = PURPLE;
		else if (S_ISSOCK(buf.st_mode))
			ret->colour = YELLOW;
		else if (S_ISFIFO(buf.st_mode))
			ret->colour = RED;
		else
			ret->colour = DEFAULT;
	}
	else
		ret->colour = WHITE;
	ret->state = NORMAL_STATE;
	ret->selected = 0;
	ret->name = add_esc(av, ret->colour, ret->state, 0);
	return (ret);
}

void			init_term(t_select *select)
{
	char 		*name;

	if (!(name = getenv("TERM")))
		on_crash(ENV_ERR);
	if ((tgetent(NULL, name)) == -1)
		on_crash(ENV_ERR);
	if ((tcgetattr(0, &(select->term_save))) == -1 ||
		tcgetattr(0, &(select->term_new)) == -1)
		on_crash(ENV_ERR);
	select->term_new.c_lflag &= ~(ICANON | ECHO);
	select->term_new.c_cc[VMIN] = 1;
	select->term_new.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSANOW, &select->term_new)) == -1)
		on_crash(ENV_ERR);
	tputs(tgetstr("vi", NULL), select->fd, ft_putchar_select);
	tputs(tgetstr("cl", NULL), select->fd, ft_putchar_select);
}
