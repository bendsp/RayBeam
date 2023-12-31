##
## EPITECH PROJECT, 2022
## bootstrapRaytracer
## File description:
## Makefile
##

SRC =	src/main.cpp \
		src/scene.cpp \
		src/parser/file_parser.cpp \
		src/parser/parse_primitives.cpp \
		src/parser/parse_lights.cpp \
		src/parser/parse_transformations.cpp \

OBJ = $(SRC:.cpp=.o)

NAME = RayBeam

CPPFLAGS = -I./includes/

all: $(NAME)

$(NAME): $(OBJ)
		g++ -o $(NAME) $(OBJ) $(CPPFLAGS) -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system


clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
