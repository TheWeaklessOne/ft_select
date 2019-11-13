NAME = ft_select

SRC  =	Sources/data_structures.c		\
		Sources/list.c					\
		Sources/list_2.c				\
		Sources/ft_select.c				\
		Sources/ft.c					\
		Sources/ft_2.c					\
		Sources/init.c					\
		Sources/input.c					\
		Sources/escape.c				\

OBJ  = $(SRC:.c=.o)

FLAGS = -g

RED= \033[1;31m
GREEN= \033[1;32m
YELLOW= \033[1;33m
BLUE= \033[1;34m
VIOLET= \033[1;35m
RESET= \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME) -ltermcap
	rm -rf $(OBJ)
	@echo "$(GREEN)Project is successfully compiled$(RESET)"

%.o : %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	@echo "$(RED)Suspending library files$(VIOLET)"
	rm -rf *.o

fclean: clean
	@echo "$(RED)Suspending project files$(VIOLET)"
	rm -rf $(OBJ)
	rm -rf $(NAME)
	@echo "$(RED)All files is deleted$(RESET)"

re: fclean all
