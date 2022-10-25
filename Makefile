CC = gcc
NAME = minishell
FLAGS = -g
LIBFT = libft/libft.a

SRCS = main.c				\
		tools.c				\
		create_node.c		\
		get.c				\
		print_node.c		\
		handler.c			\
		built-in.c			\
		env.c				\
		export.c			\
		unset.c				\
		echo.c				\
		clear_test.c		\
		signal.c			\
		builtin/ft_cd.c		\
		builtin/ft_pwd.c	\
		utlis.c				\
		convert_parssing.c	\
		redr.c				\
		exc.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	cd libft && make

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $@

clean:
	rm -rf $(OBJS)
	cd libft && make clean

fclean: clean
	rm -rf $(NAME)
	cd libft && make fclean

re: fclean all