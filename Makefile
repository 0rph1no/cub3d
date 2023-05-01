NAME = cub3d
SRCS = main.c cub3d_utils1.c cub3d_utils2.c get_next_line.c get_next_line_utils.c #cub3d_utils3.c cub3d_utils4.c cub3d_utils5.c cub3d_utils6.c cub3d_utils7.c cub3d_utils8.c cub3d_utils9.c cub3d_utils10.c 
OBJS = $(SRCS:%.c=%.o)



all : $(NAME)

$(NAME) : $(OBJS)
	cc -fsanitize=address -g3 -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $(NAME)
$(OBJS) : $(SRCS)
	cc -Wall -Wextra   $(SRCS) -c

clean: 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re: fclean all

run:
	cc  -g3 -lmlx -framework OpenGL -framework AppKit cub3d_utils3.c get_next_line.c get_next_line_utils.c cub3d_utils4.c -o anas