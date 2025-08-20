NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c \
       ft_isascii.c ft_isprint.c ft_strlen.c \
       ft_memset.c ft_bzero.c ft_memcpy.c \
       ft_memmove.c ft_strlcpy.c ft_strlcat.c \
       ft_toupper.c ft_tolower.c \
       ft_strchr.c ft_strrchr.c ft_strncmp.c \
       ft_memchr.c ft_memcmp.c ft_strnstr.c \
       ft_atoi.c ft_strdup.c ft_calloc.c \
       ft_substr.c ft_strjoin.c ft_strtrim.c \
       ft_split.c ft_itoa.c ft_strmapi.c \
       ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
       ft_putendl_fd.c ft_putnbr_fd.c \
       get_next_line.c ft_printf.c \
       ft_putptr.c ft_puthex.c ft_putuns.c ft_strcmp.c

OBJ = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# для швидкого тесту
test: re
	$(CC) -Wall -Wextra -Werror -g main.c libft.a -o test

.PHONY: all clean fclean re test
