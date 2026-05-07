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
HOMEBREW_SFML2_PREFIX := $(shell brew --prefix sfml@2 2>/dev/null)
PKG_CONFIG = PKG_CONFIG_PATH="$(HOMEBREW_SFML2_PREFIX:%=%/lib/pkgconfig):$(PKG_CONFIG_PATH)" pkg-config
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
