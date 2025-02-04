##
## EPITECH PROJECT, 2024
## B-MUL-100-LIL-1-1-myradar-mathys1.dupont
## File description:
## Makefile
##

SRC 	=	main.c 							\
			src/render_window.c				\
			src/tower.c 					\
			src/init.c						\
			src/towerinfo.c 				\
			src/plane.c 					\
			src/plane_info.c 				\
			src/time.c

LIB 	= 	-L./lib/ -lmy -lm

OBJ	=	$(SRC:.c=.o)

NAME	=	my_radar

CSFML	=	-lcsfml-graphics -lcsfml-system -lcsfml-window -lcsfml-audio

CFLAGS	=	-Wall -Wextra -I./include

debug:	CFLAGS += -g
debug:	$(OBJ)
	make -C lib/my
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LIB) $(CSFML)

all:	$(NAME)

$(NAME):	$(OBJ)
		make -C lib/my
		gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LIB) $(CSFML)

clean:
		rm -f $(OBJ)
		make -C lib/my clean

fclean:	clean
		rm -f $(NAME)
		make -C lib/my fclean

re:	fclean all
