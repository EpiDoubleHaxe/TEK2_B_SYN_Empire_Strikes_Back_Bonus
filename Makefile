##
## EPITECH PROJECT, 2021
## cpoolday10 task01
## File description:
## Makefile
##

SRC =			src/empire.c			\
     			src/change_state.c		\
     			src/init.c				\
     			src/my_rand.c			\
     			src/mutex.c				\

TEST_SRC =		tests/test_general.c	\

MAIN =		src/main.c

OBJ =		$(SRC:.c=.o)

MAIN_OBJ =		$(MAIN:.c=.o)

TEST_OBJ =		$(TEST_SRC:.c=.o)

NAME =		empire

CXXFLAGS = -I ./include
CPPFLAGS = -I ./include
LDFLAGS = -L. -lempire -lpthread

all:	$(NAME)

$(NAME):	$(OBJ) $(MAIN_OBJ)
		gcc $(LDFLAGS) $(OBJ) $(MAIN_OBJ) -Wall -Wextra -Werror -o $(NAME)

tests_run:   LDFLAGS += -lcriterion -lgcov --coverage
tests_run:		CFLAGS 	+= -lgcov --coverage
tests_run:		CXXFLAGS += -lgcov --coverage
tests_run:		$(TEST_OBJ) $(OBJ)
		gcc -o unit_tests $(CXXFLAGS) $(LDFLAGS) $(TEST_OBJ) $(OBJ) -g

clean:
	rm -f $(OBJ)
	rm -f $(MAIN_OBJ)
	rm -f $(TEST_OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

debug: CPPFLAGS += -g
debug: $(NAME)

.PHONY:	all clean fclean re debug
