/*
** EPITECH PROJECT, 2021
** EntryPoint
** File description:
** Arcade
*/

#include <iostream>
#include "Sdl.hpp"

Arcade::IGraphicals *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::Sdl;
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