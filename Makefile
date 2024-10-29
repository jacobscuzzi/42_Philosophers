NAME 		=	philo

FLAGS		=	-Wall -Werror -Wextra

FILES		=	main.c \
				basic_tools.c \
				philo_tools.c

SOURCES_DIR	=	./sources/

SOURCES		=	$(addprefix $(SOURCES_DIR), $(FILES))

OBJECTS		= 	$(SOURCES:.c=.o)

%.o : %.c
				@gcc $(CFLAGS) -c $< -o $@

all:			$(NAME)

$(NAME): $(OBJECTS)
		@gcc $(FLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
