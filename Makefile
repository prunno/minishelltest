SRC = main.c

NAME = test

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra $(SRC) -o $(NAME) -lreadline
	gcc -o dummy dummy.c

clean:
	rm -f $(NAME)

re: clean all
