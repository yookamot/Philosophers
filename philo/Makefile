# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yookamot <yookamot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 21:41:39 by yookamot          #+#    #+#              #
#    Updated: 2025/07/17 22:31:37 by yookamot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread
RM          = rm -f
SRCS        = cleanup.c \
				init_data.c \
				init_mutex.c \
				init_philos.c \
				main.c \
				monitor_func.c \
				philo_func.c \
				eat.c 
OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
