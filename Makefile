# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 17:59:57 by mmourdal          #+#    #+#              #
#    Updated: 2023/05/18 16:43:57 by mmourdal         ###   ########.fr        #
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

ART_NAME_1_BONUS =  ██████   ██████  ███    ██ ██    ██ ███████  \n
ART_NAME_2_BONUS =  ██   ██ ██    ██ ████   ██ ██    ██ ██       \n
ART_NAME_3_BONUS =  ██████  ██    ██ ██ ██  ██ ██    ██ ███████  \n
ART_NAME_4_BONUS =  ██   ██ ██    ██ ██  ██ ██ ██    ██      ██  \n
ART_NAME_5_BONUS =  ██████   ██████  ██   ████  ██████  ███████  \n

PRINT_NAME = @printf "\n$(RED)%19s$(ART_NAME_1)%18s$(ART_NAME_2)%18s$(ART_NAME_3)%18s$(ART_NAME_4)%19s$(ART_NAME_5)$(END)\n"
PRINT_NAME_BONUS = @printf "\n$(RED)%19s$(ART_NAME_1_BONUS)%19s$(ART_NAME_2_BONUS)%19s$(ART_NAME_3_BONUS)%19s$(ART_NAME_4_BONUS)%19s$(ART_NAME_5_BONUS)$(END)\n"

################################################################################
#                                  SOURCES                                     #
################################################################################

SRC_FILES	=	$(addprefix parse/, \
				read_function.c	utils.c parsing_map.c parsing_map_info.c utils_parsing_map.c) \
				$(addprefix free/, \
				free.c) \
				$(addprefix game/, \
				mlx.c init.c raycast_utils.c raycasting.c texture.c \
				trash.c utils.c utils_mlx.c) \
				main.c \

SRC_FILES_BONUS = $(addprefix bonus/parse/, \
				read_function.c	utils.c parsing_map.c parsing_map_info.c utils_parsing_map.c) \
				$(addprefix bonus/free/, \
				free.c) \
				$(addprefix bonus/game/, \
				mlx.c  init.c brasenham.c brasenham2.c brasenham3.c draw_minimap.c raycast_utils.c raycasting.c texture.c \
				trash.c utils.c utils2_mlx.c utils_mlx.c) \
				bonus/main_bonus.c \

################################################################################
#                                  OBJETS                                      #
################################################################################

OBJS_DIR	= .objets
OBJS_DIR_BONUS	= .objets_bonus
OBJS		= $(SRC_FILES:%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS	= $(SRC_FILES_BONUS:%.c=$(OBJS_DIR_BONUS)/%.o)

################################################################################
#                               OTHER LIBRARY                                  #
################################################################################

LIB_DIR = libft

################################################################################
#                                COMPILATION                                   #
################################################################################

CC			= cc
MLX_FLAGS	= mlx/mlx/libmlx_Linux.a -L. -lXext -lX11
CFLAGS		= -g3 -Wall -Wextra -Werror
CIFLAGS		= -Iincludes -I$(LIB_DIR)/includes
CCLIED		= -L$(LIB_DIR) -lft
MAKE		= @make --no-print-directory

################################################################################
#                                  MAKEFILE                                    #
################################################################################

NAME = cub3D

NAME_BONUS = cub3D_bonus

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(CIFLAGS) $(OBJS) $(MLX_FLAGS) $(CCLIED) -lm -o $(NAME)

$(NAME_BONUS) : $(OBJS_DIR_BONUS) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(CIFLAGS) $(OBJS_BONUS) $(MLX_FLAGS) $(CCLIED) -lm -o $(NAME_BONUS) 
	
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
	@printf "$(RED_TWO)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/parse...\n"
	@mkdir $(OBJS_DIR)/parse
	@sleep 0.2
	@printf "$(RED_TWO)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/free...\n"
	@mkdir $(OBJS_DIR)/free
	@sleep 0.2
	@printf "$(RED_TWO)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/game...\n"
	@mkdir $(OBJS_DIR)/game
	@sleep 0.2
	@printf "$(RED_TWO)%20s Création des dossiers $(END)$(BLINK)$(WHITE)objets terminée$(END)\n\n"
	@sleep 0.9
	@printf "$(RED_TWO)%24s Compilation de $(END)$(WHITE)$(NAME)...\n"
	@sleep 0.2
	@printf "$(RED_TWO)%21s Compilation de $(END)$(BLINK)$(WHITE)$(NAME) terminée$(END)\n\n"

$(OBJS) : $(OBJS_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(CIFLAGS) -c $< -o $@

$(OBJS_DIR_BONUS) :
	@$(PRINT_NAME_BONUS)
	@printf "$(RED_TWO)%24s Création du dossier $(END)$(WHITE)$(OBJS_DIR_BONUS)...\n"
	@printf "$(RED_TWO)%20s Compilation de la librairie $(END)$(WHITE)$(LIB_DIR)...\n"
	$(MAKE) -C $(LIB_DIR)
	@mkdir $(OBJS_DIR_BONUS)
	@mkdir $(OBJS_DIR_BONUS)/bonus
	@sleep 0.2
	@printf "$(RED_TWO)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR_BONUS)/parse...\n"
	@mkdir $(OBJS_DIR_BONUS)/bonus/parse
	@sleep 0.2
	@printf "$(RED_TWO)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR_BONUS)/free...\n"
	@mkdir $(OBJS_DIR_BONUS)/bonus/free
	@sleep 0.2
	@printf "$(RED_TWO)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR_BONUS)/game...\n"
	@mkdir $(OBJS_DIR_BONUS)/bonus/game
	@sleep 0.2
	@printf "$(RED_TWO)%20s Création des dossiers $(END)$(BLINK)$(WHITE)objets_bonus terminée$(END)\n\n"
	@sleep 0.9
	@printf "$(RED_TWO)%24s Compilation de $(END)$(WHITE)$(NAME_BONUS)...\n"
	@sleep 0.2
	@printf "$(RED_TWO)%21s Compilation de $(END)$(BLINK)$(WHITE)$(NAME_BONUS) terminée$(END)\n\n"

$(OBJS_BONUS) : $(OBJS_DIR_BONUS)/%.o : %.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(CIFLAGS) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIB_DIR)
	@rm -rf $(OBJS_DIR)
	@printf "\n$(RED_TWO)Suppression des objets de la librairie : $(END)$(WHITE)$(LIB_DIR) [✅]$(END)\n"
	@printf "$(RED_TWO)%2s Suppression des objets : $(END)$(WHITE)$(OBJS_DIR) [✅]$(END)\n\n"
	@if [ -d $(OBJS_DIR_BONUS) ]; then \
		rm -rf $(OBJS_DIR_BONUS); \
		printf "$(RED_TWO)%2s Suppression des objets : $(END)$(WHITE)$(OBJS_DIR_BONUS) [✅]$(END)\n\n"; \
	fi
	
bonus : $(NAME_BONUS)

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	@rm -rf $(NAME)
	@printf "$(RED_TWO)%2s Suppression de l'exécutable : $(END)$(WHITE)$(NAME) [✅]$(END)\n\n"
	@if [ -f $(NAME_BONUS) ]; then \
		rm -rf $(NAME_BONUS); \
		printf "$(RED_TWO)%2s Suppression de l'exécutable : $(END)$(WHITE)$(NAME_BONUS) [✅]$(END)\n\n"; \
	fi

re : fclean all

.PHONY: all clean fclean bonus re