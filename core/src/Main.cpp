/*
** EPITECH PROJECT, 2021
** Main
** File description:
** Arcade
*/

#include <fstream>
#include <iostream>
#include "../include/Core.hpp"
#include "../include/Error.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    try {
        Arcade::Core core(av[1]);
        core.run();
    } catch (Arcade::ArcadeError &error) {
        std::cerr << error.getComponent() << ": " << error.what() << std::endl;
        return (84);
    }
    return (0);
}