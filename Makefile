##
## EPITECH PROJECT, 2021
## my hunter
## File description:
## makefile
##

SRC	= 	lex.yy.c \
		hel.tab.c \
		src/variable.c \
		src/show.c \
		src/generic_list.c \
		src/generic_list_create_destroy.c \
		src/operators.c \
		src/tree.c \
		src/keywords.c \
		src/evaluators.c \

OBJ	=	$(SRC:.c=.o)

SMAIN	=	src/main.c

OMAIN	=	$(SMAIN:.c=.o)

NAME	=	hel

CFLAGS	+=

CPPFLAGS	=	-I ./include/

LDFLAGS	+= -lfl

TESTFILES	=

all: lex

$(NAME):	libs $(OBJ)
	clear
	gcc -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)

clean:
	$(RM) $(OBJ) $(OMAIN)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS	+=	-g3
debug: re

unit_test: CFLAGS	+=	-lcriterion
unit_test: $(OBJ)
	$(CC) -o unit_tests $(TESTFILES) $(OBJ) \
	$(CPPFLAGS) $(LDFLAGS) $(CFLAGS) --coverage
	./unit_tests
	gcovr -r .

libs:

lex:
	flex $(NAME).l
	bison -d -t $(NAME).y
	gcc $(SRC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)

.PHONY: $(NAME) all clean fclean re libs lex
