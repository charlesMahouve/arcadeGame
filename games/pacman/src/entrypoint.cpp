/*
** EPITECH PROJECT, 2021
** EntryPoint
** File description:
** Arcade
*/

#include <iostream>
#include "Pacman.hpp"

extern "C" Arcade::IGames *entryPoint()
{
	return new Arcade::Pacman;
}