# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 17:59:57 by mmourdal          #+#    #+#              #
#    Updated: 2023/04/02 19:54:49 by mmourdal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                  ASCII ART                                   #
################################################################################

RED_TWO = \033[1;31m
RED		= \033[5;31m
WHITE	= \033[1;37m
BLINK	= \033[5m
END		= \033[0m

ART_NAME_1 =  ██████ ██    ██ ██████  ██████  ██████  \n
ART_NAME_2 = ██      ██    ██ ██   ██      ██ ██   ██ \n
ART_NAME_3 = ██      ██    ██ ██████   █████  ██   ██ \n
ART_NAME_4 = ██      ██    ██ ██   ██      ██ ██   ██ \n
ART_NAME_5 =  ██████  ██████  ██████  ██████  ██████ \n

PRINT_NAME = @printf "\n$(RED)%19s$(ART_NAME_1)%18s$(ART_NAME_2)%18s$(ART_NAME_3)%18s$(ART_NAME_4)%19s$(ART_NAME_5)$(END)\n"

################################################################################
#                                  SOURCES                                     #
################################################################################

PARSE_DIR	= parse

SRC_FILES	=	$(addprefix parse/, \
				main.c) \

################################################################################
#                                  OBJETS                                      #
################################################################################

OBJS_DIR	= .objets
OBJS		= $(SRC_FILES:%.c=$(OBJS_DIR)/%.o)

################################################################################
#                               OTHER LIBRARY                                  #
################################################################################

LIB_DIR = libft

################################################################################
#                                COMPILATION                                   #
################################################################################

CC			= cc
MLX_FLAGS	= mlx/libmlx.a mlx/libmlx_Linux.a -L. -lXext -lX11
CFLAGS		= -g3 -Wall -Wextra -Werror
CIFLAGS		= -Iincludes -I$(LIB_DIR)/includes
CCLIED		= -L$(LIB_DIR) -lft
MAKE		= @make --no-print-directory

################################################################################
#                                  MAKEFILE                                    #
################################################################################

NAME = cub3D

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(CIFLAGS) $(OBJS) $(CCLIED) -o $(NAME)

$(OBJS_DIR) :
	@$(PRINT_NAME)
	@printf "$(RED_TWO)%20s Compilation de la librairie $(END)$(WHITE)$(LIB_DIR)...\n"
	$(MAKE) -C $(LIB_DIR)
	@printf "$(RED_TWO)%18s Compilation de la librairie $(END)$(BLINK)$(WHITE)$(LIB_DIR) terminée$(END)\n\n"
	@sleep 0.7
	@printf "$(RED_TWO)%20s Création des dossiers content les $(END)$(WHITE).o : \n"
	@sleep 0.2
	@printf "$(RED_TWO)%24s Création du dossier $(END)$(WHITE)$(OBJS_DIR)...\n"
	@mkdir $(OBJS_DIR)
	@sleep 0.2
	@printf "$(RED_TWO)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(PARSE_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(PARSE_DIR)
	@sleep 0.2
	@printf "$(RED_TWO)%20s Création des dossiers $(END)$(BLINK)$(WHITE)objets terminée$(END)\n\n"
	@sleep 0.9
	@printf "$(RED_TWO)%24s Compilation de $(END)$(WHITE)$(NAME)...\n"
	@sleep 0.2
	@printf "$(RED_TWO)%21s Compilation de $(END)$(BLINK)$(WHITE)$(NAME) terminée$(END)\n\n"

$(OBJS) : $(OBJS_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(CIFLAGS) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIB_DIR)
	@rm -rf $(OBJS_DIR)
	@printf "\n$(RED_TWO)Suppression des objets de la librairie : $(END)$(WHITE)$(LIB_DIR) [✅]$(END)\n"
	@printf "$(RED_TWO)%6s Suppression du dossier : $(END)$(WHITE)$(OBJS_DIR) [✅]$(END)\n\n"
	
fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	@rm -rf $(NAME)
	@printf "$(RED_TWO)%2s Suppression de l'exécutable : $(END)$(WHITE)$(NAME) [✅]$(END)\n\n"
	
re : fclean all

.PHONY: all clean fclean re