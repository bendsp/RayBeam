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

CXXFLAGS = -std=c++17 -Wall -Wextra
PKG_CONFIG = PKG_CONFIG_PATH=/opt/homebrew/opt/sfml@2/lib/pkgconfig pkg-config
CPPFLAGS = -I./includes/ $(shell $(PKG_CONFIG) --cflags libconfig++ sfml-graphics sfml-window sfml-system)
LDLIBS = $(shell $(PKG_CONFIG) --libs libconfig++ sfml-graphics sfml-window sfml-system)

all: $(NAME)

$(NAME): $(OBJ)
		g++ -o $(NAME) $(OBJ) $(LDLIBS)


clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
