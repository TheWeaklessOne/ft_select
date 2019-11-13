#ifndef FT_SELECT_FT_SELECT_H
# define FT_SELECT_FT_SELECT_H

# define CLEAR_SCREEN				"\033[?1049h\033[H"

# define ESCAPE						"\033["
# define DEFAULT					"39;"
# define RED						"31;"
# define GREEN						"32;"
# define YELLOW						"33;"
# define BLUE						"34;"
# define PURPLE						"35;"
# define CYAN						"36;"
# define WHITE						"97;"
# define UNDERLINE					"4;"
# define REVERSE					"7;"
# define BOTH_STATE					"4;7;"
# define NORMAL_STATE				"24;27;"

# define END_ESCAPE					"m"
# define RESET_ALL					"\033[0;m"

# define ENTER_K					10
# define ESC_K						27
# define SPACE_K					32
# define BACK_SPACE_K				127
# define LEFT_K						4479771
# define UP_K						4283163
# define RIGHT_K					4414235
# define DOWN_K						4348699
# define DEL_K						2117294875L

# include <stdlib.h>
# include <termcap.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <sys/stat.h>
# include <ftw.h>
# include <unistd.h>
# include <sys/param.h>
# include <fcntl.h>

# include "data_structures.h"

typedef struct		s_elem
{
	int				selected;
	char			*name;
	char			*state;
	char			*colour;
}					t_elem;

typedef struct		s_select
{
	int				fd;
	int				pos;
	int				elem_count;
	t_list			*elem_lst;
	struct termios	term_new;
	struct termios	term_save;
}					t_select;

enum				e_side
{
	SIDE_LEFT = 1,
	SIDE_UP,
	SIDE_RIGHT,
	SIDE_DOWN
};

t_select			*act_select(t_select *select);

char 				*remake_esc(char *str, char *colour, char *state);
char				*add_esc(char *str, char *colour, char *state, int to_free);
char				*remove_esc(char *str);

void				init_select(int ac, char *av[], t_select *select);
void				init_term(t_select *select);
t_elem				*init_elem(char *av);

void				print_list(t_select *select);
void				change_pos(int side, t_select *select);

int					read_input(t_select *select);

int 				ft_strchr(const char *s, int c);
int					ft_putchar_select(int c);
int					ft_strcmp(const char *s11, const char *s22);
char				*ft_strjoin(char const *s1, char const *s2, int to_free);
char				*ft_strrenew(char **s_ptr, const char *new_str, int to_free);
int					ft_strlen(const char *src);
void				ft_putstr_fd(char const *str, int fd, int new_str);
char				*ft_list_to_str(t_list *lst);
char				*ft_state_to_escape(int state);
t_list				*ft_fill_elem_list(char *av[]);

#endif
