##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## to make project
##

all: core games graphicals

core:
	@ls lib/ > /dev/null || mkdir lib
	@make --no-print-directory -C core

games:
	@ls lib/ > /dev/null || mkdir lib
	@make --no-print-directory -C games

graphicals:
	@ls lib/ > /dev/null || mkdir lib
	@make --no-print-directory -C graphicals

clean:
	@make clean  --no-print-directory -C core
	@make clean  --no-print-directory -C games
	@make clean  --no-print-directory -C graphicals
	@rm -rf lib

fclean:
	@make fclean  --no-print-directory -C core
	@make fclean  --no-print-directory -C games
	@make fclean  --no-print-directory -C graphicals
	@rm -rf lib

re:
	@rm -rf lib
	@mkdir lib
	@make re  --no-print-directory -C core
	@make re  --no-print-directory -C games
	@make re  --no-print-directory -C graphicals

.PHONY: core games graphicals