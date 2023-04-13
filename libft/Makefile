SRCS	= ft_isalpha.c ft_isdigit.c ft_atoi.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
		ft_strdup.c ft_toupper.c ft_tolower.c ft_strchr.c ft_memset.c ft_bzero.c ft_strncmp.c \
		ft_strrchr.c ft_strlcpy.c ft_calloc.c ft_memcmp.c ft_memcpy.c ft_memchr.c ft_memmove.c \
		ft_strlcat.c ft_strnstr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_substr.c ft_strmapi.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_striteri.c ft_strcmp.c get_next_line.c get_next_line_utils.c\
		ft_printf.c ft_printf_inc.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \

NAME	= libft.a
 
OBJS		= ${SRCS:.c=.o} ${ADDED:.c=.o} 
 
OBJS_BONUS	= ${BONUS:.c=.o}
 
HEADERS	= ./
 
.c.o	:
		@cc -Wall -g3 -Wextra -Werror -I ${HEADERS} -c $< -o ${<:.c=.o}
 
all : ${NAME}
 
${NAME} : ${OBJS}
		ar rcs ${NAME} ${OBJS}
 
clean :
		rm -f ${OBJS} ${OBJS_BONUS} $(OBJS_GNL) $(OBJS_PRINTF)
 
fclean : clean
		rm -f ${NAME}
 
re : fclean all
 
.PHONY : all clean fclean re

