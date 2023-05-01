##
## EPITECH PROJECT, 2022
## bootstrapRaytracer
## File description:
## Makefile
##

SRC =	src/main.cpp \
		src/file_parser.cpp \

OBJ = $(SRC:.cpp=.o)

NAME = raytracer

CPPFLAGS = -I./includes/

all: $(NAME)

$(NAME): $(OBJ)
		g++ -o $(NAME) $(OBJ) $(CPPFLAGS) -lconfig++

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
