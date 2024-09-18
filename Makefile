NAME_M = fractol
NAME_B = fractol_bonus
HEADER_M  = mandatory/fractol.h
HEADER_B = bonus/fractol_bonus.h

SRCS_M = $(wildcard mandatory/*.c)
SRCS_B = $(wildcard bonus/*.c)
M_OBJS := $(SRCS_M:.c=.o)
B_OBJS := $(SRCS_B:.c=.o)

RM = rm -rf
FLAGS = -Werror -Wextra -Wall

$(NAME_M): $(M_OBJS) $(HEADER_M)
	gcc $(M_OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME_M)
$(NAME_B): $(B_OBJS) $(HEADER_B)
	gcc $(B_OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME_B)
%.o : %.c
	gcc $(FLAGS) -Imlx -c $< -o $@


all : $(NAME_M) $(NAME_B)

bonus: $(NAME_B)

clean :
	$(RM) $(M_OBJS) $(B_OBJS)

fclean: clean
	$(RM) $(NAME_M) $(NAME_B)

re: fclean clean all
.PHONY: all bonus fclean clean re
