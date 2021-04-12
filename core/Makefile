##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## to make project
##

CC	=	g++
ECHO	=	echo

COLOR	=   31
LIGHT   =   \e[0m
BOLD    =   \e[1m
BLACK   =   \e[30m
RED     =   \e[31m
GREEN   =   \e[32m
YELLOW  =   \e[33m
BLUE    =   \e[34m
PURPLE  =   \e[35m
CYAN    =   \e[36m
WHITE   =   \e[37m
DEFAULT =   \e[0;37m

INFO    =   $(BOLD)$(GREEN)[INFO]\t$(WHITE)
WARNING =   $(BOLD)$(YELLOW)[WARNING]\t$(WHITE)
ERROR   =   $(BOLD)$(RED)[ERROR]\t$(WHITE)

SRC	=	$(wildcard $(SRC_DIR)src/*.cpp)

OBJ	=	$(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRC))

INC_DIR =	-I./include/

CFLAGS	=	$(INC_DIR) -ldl -std=c++17

NAME	=	arcade

NOM =	Christian MIYIGBENA aka PrinceIsGod

$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(BIN_DIR)$(NAME)
	@$(ECHO) "$(INFO)Compilation terminée !$(DEFAULT)"
	@echo "\033[01m\033[05m\033[31m\033[03m[${NAME}]\033[00m"
	@echo "\033[01m\033[05m\033[31m\033[03m[${NOM}]\033[00m"
	@cp $(BIN_DIR)$(NAME) ../

$(OBJ): $(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -g -c $< -o $@

all:	$(NAME)

clean:
	@rm -f $(OBJ)
	@rm -f $(BIN_DIR)$(NAME)
	@$(ECHO) "$(INFO)Fichiers supprimées !$(DEFAULT)"
	@rm -f $(OBJ)
	@rm -f ../$(BIN_DIR)$(NAME)

fclean:	clean
	@rm -f $(NAME) $(NAMETEST)

re:	fclean all