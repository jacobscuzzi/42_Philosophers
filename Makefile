NAME 		=	philo

FLAGS		=	-Wall -Werror -Wextra  -pthread #-fsanitize=thread

FILES		=	main.c \
				philo.c	\
				parcing.c \
				philo_tools.c \
				philo_monitor.c \
				philo_actions.c

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
