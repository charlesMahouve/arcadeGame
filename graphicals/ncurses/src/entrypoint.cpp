/*
** EPITECH PROJECT, 2021
** EntryPoint
** File description:
** Arcade
*/

#include <iostream>
#include "Ncurses.hpp"

Arcade::IGraphicals *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::Ncurses;
}

__attribute__((destructor))
void out()
{
	delete ret;
}

extern "C" Arcade::IGraphicals *entryPoint()
{
	return ret;
}