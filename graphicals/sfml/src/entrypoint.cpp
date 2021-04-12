/*
** EPITECH PROJECT, 2021
** EntryPoint
** File description:
** Arcade
*/

#include <iostream>
#include "Sfml.hpp"

extern "C" Arcade::IGraphicals *entryPoint()
{
	return new Arcade::Sfml;
}