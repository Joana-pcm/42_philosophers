NAME = philo

SRC = $(addprefix srcs/, main.c init.c time_set.c routine.c parse.c utils.c)

OBJS = ${SRC:.c=.o}

CC = cc
RM = rm -fr
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -include ./t_incs/philo.h
MAKE = make -C

%.o: %.c
	@${CC} ${CFLAGS} ${INCLUDE} -o $@ -c $<

all:	${NAME}

$(NAME):	${OBJS}
	@${CC} ${OBJS} -o ${NAME}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME} 
	@echo "all clean"

re: fclean all

.PHONY: all clean fclean re
