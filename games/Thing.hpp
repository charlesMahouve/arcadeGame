/*
** EPITECH PROJECT, 2021
** Entity
** File description:
** Arcade
*/

#pragma once

#include <iostream>
#include "../graphicals/IGraphicals.hpp"

namespace Arcade
{
    class Thing {
        public:
            virtual ~Thing() = default;
            float _x;
            float _y;
            int _l;
            int _wid;
            int _leng;
            int _currentCase;
            int _currentH;
            int _totalCase;
            std::string _type;
            std::string _assetTxt;
            std::string _assetGfx;
    };
}