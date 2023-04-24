##
## EPITECH PROJECT, 2022
## bootstrapRaytracer
## File description:
## Makefile
##

SRC =	src/main.cpp \

OBJ = $(SRC:.cpp=.o)

NAME = raytracer

CPPFLAGS = -I./includes/

all: $(NAME)

$(NAME): $(OBJ)
		g++ -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
