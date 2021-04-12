/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Pacman
*/

#include "Pacman.hpp"

Arcade::Pacman::Pacman()
{
	initGameInfos();
}

Arcade::Pacman::~Pacman()
{
}

void Arcade::Pacman::loadMapFile()
{
    std::ifstream map("assets/pacman/map.txt");
    std::string line;
    if (map.is_open()) {
        for (size_t i = 0; getline(map, line); i++)
            _map[i] = line;
        map.close();
    } else
        throw std::invalid_argument("Unable to open pacman map file");
}

void Arcade::Pacman::initGameInfos()
{
	loadMapFile();
	initControls();
	initEntities();
	initStats();
	setGameControls();
}

void Arcade::Pacman::initControls()
{
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(NO_EVENT, NONE), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(NO_EVENT, UNKNOWN), [this](){&Arcade::Pacman::noEvent;}) );

	for (Arcade::EventKey l = NONE; l <= Z; l = (Arcade::EventKey)((int)l + 1))
		_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, l), [this](){&Arcade::Pacman::noEvent;}) );

	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(QUIT, RETURN), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, BACKSPACE), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, TAB), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, ESCAPE), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, ENTER), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, DELETE), [this](){&Arcade::Pacman::noEvent;}) );

	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, UP), [this](){&Arcade::Pacman::goNorth;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, DOWN), [this](){&Arcade::Pacman::goSouth;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, LEFT), [this](){&Arcade::Pacman::goWest;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, RIGHT), [this](){&Arcade::Pacman::goEast;}) );

	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, Z), [this](){&Arcade::Pacman::goNorth;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, S), [this](){&Arcade::Pacman::goSouth;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, Q), [this](){&Arcade::Pacman::goWest;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, D), [this](){&Arcade::Pacman::goEast;}) );

	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(MOUSE_PRESSED, MOUSE_1), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(MOUSE_PRESSED, MOUSE_2), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(MOUSE_PRESSED, MOUSE_3), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, MENU_KEY), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, RESTART_KEY), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, PAUSE_GAME_KEY), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, PREV_GAME_KEY), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, NEXT_GAME_KEY), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, PREV_LIB_KEY), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, NEXT_LIB_KEY), [this](){&Arcade::Pacman::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, QUIT_KEY), [this](){&Arcade::Pacman::noEvent;}) );
}

void Arcade::Pacman::initEntities()
{
	int i = 7, a = 126 + 11, b = 102 + 11;
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::GameMap)));
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::PacChar)));
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::GhostBlue)));
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::GhostOrange)));
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::GhostPurple)));
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::GhostRed)));
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Fruits)));

	for (; a <= 126 + 188; i += 4, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = a;
		_entities[i + 1]->_y = b + 64;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 2]->_x = a;
		_entities[i + 2]->_y = 316 + 102;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 3]->_x = a;
		_entities[i + 3]->_y = 458 + 102;
	}
	for (a = 126 + 235; a <= (126 + 411); i += 4, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = a;
		_entities[i + 1]->_y = b + 64;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 2]->_x = a;
		_entities[i + 2]->_y = 316 + 102;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 3]->_x = a;
		_entities[i + 3]->_y = 458 + 102;
	}

	for (a = 126 + 11, b = 102 + 27; b <= (102 + 60); i += 6, b += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = 126 + 91;
		_entities[i + 1]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 2]->_x = 126 + 187;
		_entities[i + 2]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 3]->_x = 126 + 235;
		_entities[i + 3]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 4]->_x = 126 + 331;
		_entities[i + 4]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 5]->_x = 126 + 411;
		_entities[i + 5]->_y = b;
	}

	for (a = 126 + 11, b = 102 + 92; b <= (102 + 108); i += 6, b += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = 126 + 91;
		_entities[i + 1]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 2]->_x = 126 + 139;
		_entities[i + 2]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 3]->_x = 126 + 283;
		_entities[i + 3]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 4]->_x = 126 + 331;
		_entities[i + 4]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 5]->_x = 126 + 411;
		_entities[i + 5]->_y = b;
	}

	for (a = 126 + 11, b = 102 + 124; a <= (126 + 91); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 139, b = 102 + 124; a <= (126 + 188); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 235, b = 102 + 124; a <= (126 + 284); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 332, b = 102 + 124; a <= (126 + 412); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = (a >= (126 + 411)) ? 126 + 411 : a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 11, b = 102 + 427; b <= (102 + 427 + 16); i += 8, b += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = 126 + 187;
		_entities[i + 1]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 2]->_x = 126 + 235;
		_entities[i + 2]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 3]->_x = 126 + 411;
		_entities[i + 3]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 4]->_x = a;
		_entities[i + 4]->_y = b - 75 - 16;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 5]->_x = 126 + 187;
		_entities[i + 5]->_y = b - 75 - 16;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 6]->_x = 126 + 235;
		_entities[i + 6]->_y = b - 75 - 16;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 7]->_x = 126 + 411;
		_entities[i + 7]->_y = b - 75 - 16;
	}

	for (a = 126 + 11, b = 102 + 411; a <= (126 + 91); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 139, b = 102 + 411; a <= (126 + 188); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 235, b = 102 + 411; a <= (126 + 284); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 331, b = 102 + 411; a <= (126 + 412); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = (a >= (126 + 411)) ? 126 + 411 : a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 11, b = 102 + 368; a <= (126 + 43); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 91, b = 102 + 368; a <= (126 + 188); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 235, b = 102 + 368; a <= (126 + 332); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
	}

	for (a = 126 + 380, b = 102 + 368; a <= (126 + 412); i++, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = (a >= (126 + 411)) ? 126 + 411 : a;
		_entities[i]->_y = b;
	}

	for (a = 126, b = 102 + 381; b <= (102 + 381 + 16); i += 6, b += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a + 43;
		_entities[i]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = a + 91;
		_entities[i + 1]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 2]->_x = a + 139;
		_entities[i + 2]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 3]->_x = a + 283;
		_entities[i + 3]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 4]->_x = a + 331;
		_entities[i + 4]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 5]->_x = a + 379;
		_entities[i + 5]->_y = b;
	}

	for (a = 126 + 202, b = 102 + 456; a <= (126 + 202 + 16); i += 3, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b + 2;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = a;
		_entities[i + 1]->_y = 102 + 75;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 2]->_x = a;
		_entities[i + 2]->_y = 102 + 369;
		_entities[i + 2]->_leng = 0;
		_entities[i + 2]->_wid = 0;
	}

	for (a = 126 + 91, b = 102 + 140; b <= (102 + 140 + 160); i += 2, b += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = 126 + 332;
		_entities[i + 1]->_y = b;
	}

	for (a = 126 + 91, b = 102 + 335; b <= (102 + 335 + 16); i += 2, b += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = 126 + 332;
		_entities[i + 1]->_y = b;
	}

	for (a = 126 + 0, b = 102 + 220; a < (126 + 91); i += 2, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
		_entities[i]->_leng = 0;
		_entities[i]->_wid = 0;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = a + 337 + 11;
		_entities[i + 1]->_y = b;
		_entities[i + 1]->_leng = 0;
		_entities[i + 1]->_wid = 0;
	}

	for (a = 126 + 139, b = 102 + 169; b <= (102 + 297); i += 2, b += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
		_entities[i]->_leng = 0;
		_entities[i]->_wid = 0;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = 126 + 283;
		_entities[i + 1]->_y = b;
		_entities[i + 1]->_leng = 0;
		_entities[i + 1]->_wid = 0;
	}

	for (a = 126 + 155, b = 102 + 169; a < (126 + 283); i += 2, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a;
		_entities[i]->_y = b;
		_entities[i]->_leng = 0;
		_entities[i]->_wid = 0;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = a;
		_entities[i + 1]->_y = 102 + 265;
		_entities[i + 1]->_leng = 0;
		_entities[i + 1]->_wid = 0;
	}

	for (a = 126 + 11, b = 102 + 220; a <= (126 + 27); i += 2, a += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a + 99;
		_entities[i]->_y = b;
		_entities[i]->_leng = 0;
		_entities[i]->_wid = 0;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = a + 290;
		_entities[i + 1]->_y = b;
		_entities[i + 1]->_leng = 0;
		_entities[i + 1]->_wid = 0;
	}
	for (a = 126 + 11, b = 102 + 135; b <= (102 + 135 + 16); i += 2, b += 16) {
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i]->_x = a + 175;
		_entities[i]->_y = b;
		_entities[i]->_leng = 0;
		_entities[i]->_wid = 0;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Gum)));
		_entities[i + 1]->_x = a + 225;
		_entities[i + 1]->_y = b;
		_entities[i + 1]->_leng = 0;
		_entities[i + 1]->_wid = 0;
	}
}

void Arcade::Pacman::initStats()
{
	_gameStats.push_back(std::pair<std::string, std::string>("Cerise", "0"));
	_gameStats.push_back(std::pair<std::string, std::string>("Fraise", "0"));
	_gameStats.push_back(std::pair<std::string, std::string>("Orange", "0"));
	_gameStats.push_back(std::pair<std::string, std::string>("Pomme", "0"));
	_gameStats.push_back(std::pair<std::string, std::string>("Melon", "0"));
	_gameStats.push_back(std::pair<std::string, std::string>("Galboss", "0"));
	_gameStats.push_back(std::pair<std::string, std::string>("Cloche", "0"));
	_gameStats.push_back(std::pair<std::string, std::string>("Clé", "0"));
	_gameStats.push_back(std::pair<std::string, std::string>("Fantômes", "0"));
}

void Arcade::Pacman::setGameControls()
{
	_gameControls.push_back(std::pair<std::string, std::string>("MOVE DOWN", "KEY DOWN OR KEY S"));
	_gameControls.push_back(std::pair<std::string, std::string>("MOVE UP", "KEY UP OR KEY Z"));
	_gameControls.push_back(std::pair<std::string, std::string>("MOVE LEFT", "KEY LEFT OR KEY Q"));
	_gameControls.push_back(std::pair<std::string, std::string>("MOVE RIGHT", "KEY RIGHT OR KEY D"));
}

void Arcade::Pacman::noEvent()
{
	std::cout << "No Event" << std::endl;
}

int Arcade::Pacman::goNorth(int t)
{
	int y = 0, x = 0;
	std::stringstream ss;

	if (t != 1)
		_entities[s]->_currentH = 2;
	for (int i = 7; i < _entities.size(); i++) {
		if ((abs(_entities[i]->_x - _entities[s]->_x) <= 5) && (abs(_entities[i]->_x - _entities[s]->_x) >= 0) && (_entities[i]->_y - _entities[s]->_y >= -19) && (_entities[i]->_y - _entities[s]->_y <= 0)) {
			_entities[s]->_y -= 1;
			if (t != 1) {
				m_score += 1 * _entities[i]->_leng;
				_entities[i]->_wid = 0;
				_entities[i]->_leng = 0;
				ss << m_score;
				_score = ss.str();
			}
			if ((t % 100) == 0) {
				_entities[s]->_currentCase = (_entities[s]->_currentCase == 3) ? 1 : _entities[s]->_currentCase + 1;
			}
			return (0);
		}
	}
	return (1);
}

int Arcade::Pacman::goSouth(int t)
{
	std::stringstream ss;

	if (t != 1)
		_entities[s]->_currentH = 3;
	for (int i = 7; i < _entities.size(); i++)
		if ((abs(_entities[i]->_x - _entities[s]->_x) <= 5) && (abs(_entities[i]->_x - _entities[s]->_x) >= 0) && (_entities[i]->_y - _entities[s]->_y <= 19) && (_entities[i]->_y - _entities[s]->_y >= 0)) {
			_entities[s]->_y += 1;
			if (t != 1) {
				m_score += 1 * _entities[i]->_leng;
				_entities[i]->_wid = 0;
				_entities[i]->_leng = 0;
				ss << m_score;
				_score = ss.str();
			}
			if ((t % 100) == 0) {
				_entities[s]->_currentCase = (_entities[s]->_currentCase == 3) ? 1 : _entities[s]->_currentCase + 1;
			}
			return (0);
		}
	return (1);
}

int Arcade::Pacman::goWest(int t)
{
	std::stringstream ss;

	if (t != 1) {
		_entities[s]->_currentH = 1;
		if (_entities[s]->_x <= 130) {
			_entities[s]->_x = 126 + 420;
			return (0);
		}
	}
	for (int i = 7; i < _entities.size(); i++)
		if ((abs(_entities[i]->_y - _entities[s]->_y) <= 5) && (abs(_entities[i]->_y - _entities[s]->_y) >= 0) && (_entities[i]->_x - _entities[s]->_x >= -18) && (_entities[i]->_x - _entities[s]->_x <= 0)) {
			_entities[s]->_x -= 1;
			if (t != 1) {
				m_score += 1 * _entities[i]->_leng;
				_entities[i]->_wid = 0;
				_entities[i]->_leng = 0;
				ss << m_score;
				_score = ss.str();
			}
			if ((t % 100) == 0) {
				_entities[s]->_currentCase = (_entities[s]->_currentCase == 3) ? 1 : _entities[s]->_currentCase + 1;
			}
			return (0);
		}
	return (1);
}

int Arcade::Pacman::goEast(int t)
{
	std::stringstream ss;

	if (t != 1)
		_entities[s]->_currentH = 0;
	if (_entities[s]->_x >= 126 + 420) {
		_entities[s]->_x = 130;
		return (0);
	}
	for (int i = 7; i < _entities.size(); i++)
		if ((abs(_entities[i]->_y - _entities[s]->_y) <= 5) && (abs(_entities[i]->_y - _entities[s]->_y) >= 0) && (_entities[i]->_x - _entities[s]->_x <= 18) && (_entities[i]->_x - _entities[s]->_x >= 0)) {
			_entities[s]->_x += 1;
			if (t != 1) {
				m_score += 1 * _entities[i]->_leng;
				_entities[i]->_wid = 0;
				_entities[i]->_leng = 0;
				ss << m_score;
				_score = ss.str();
			}
			if ((t % 100) == 0) {
				_entities[s]->_currentCase = (_entities[s]->_currentCase == 3) ? 1 : _entities[s]->_currentCase + 1;
			}
			return (0);
		}
	return (1);
}

size_t Arcade::Pacman::getMapHeight() const
{
	return (_height);
}

size_t Arcade::Pacman::getMapWidth() const
{
	return (_width);
}

const std::string &Arcade::Pacman::getMusic() const
{
	return (_music);
}

const std::string &Arcade::Pacman::getSound() const
{
	return (_sound);
}

const std::string &Arcade::Pacman::getScore() const
{
	return (_score);
}

const std::map<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>> &Arcade::Pacman::getControls() const
{
	return (_controls);
}

const std::vector<std::shared_ptr<Arcade::Thing>> &Arcade::Pacman::getEntities() const
{
	return (_entities);
}

const std::vector<std::pair<std::string, std::string>> &Arcade::Pacman::getGameControls() const
{
	return (_gameControls);
}

const std::vector<std::pair<std::string, std::string>> &Arcade::Pacman::getGameStats() const
{
	return (_gameStats);
}

void Arcade::Pacman::restart()
{
	_gameOver = false;
	_controls.clear();
	_entities.clear();
	_gameControls.clear();
	_gameStats.clear();
	_map.clear();
	initGameInfos();
}

void Arcade::Pacman::goTo(int x, int y, int t)
{
	int c = 1;
	if (c == 1 && _entities[s]->_x < x) {
		c = goEast(1);
		if ((t % 100) == 0)
			_entities[s]->_currentCase = (_entities[s]->_currentCase == 2) ? 1 : 2;
	}
	if (c == 1 && _entities[s]->_x > x) {
		c = goWest(1);
		if ((t % 100) == 0)
			_entities[s]->_currentCase = (_entities[s]->_currentCase == 4) ? 3 : 4;
	}
	if (c == 1 && _entities[s]->_y < y) {
		c = goSouth(1);
		if ((t % 100) == 0)
			_entities[s]->_currentCase = (_entities[s]->_currentCase == 8) ? 7 : 8;
	}
	if (c == 1 && _entities[s]->_y > y) {
		c = goNorth(1);
		if ((t % 100) == 0)
			_entities[s]->_currentCase = (_entities[s]->_currentCase == 6) ? 5 : 6;
	}
}

void Arcade::Pacman::dontGoTo(int x, int y, int t)
{
	int c = 1;
	if (c == 1 && _entities[s]->_x > _entities[1]->_x) {
		c = goEast(1);
		if ((t % 100) == 0)
			_entities[s]->_currentCase = (_entities[s]->_currentCase == 2) ? 1 : 2;
	}
	if (c == 1 && _entities[s]->_x < _entities[1]->_x && _entities[s]->_x) {
		c = goWest(1);
		if ((t % 100) == 0)
			_entities[s]->_currentCase = (_entities[s]->_currentCase == 4) ? 3 : 4;
	}
	if (c == 1 && _entities[s]->_y > _entities[1]->_y) {
		c = goSouth(1);
		if ((t % 100) == 0)
			_entities[s]->_currentCase = (_entities[s]->_currentCase == 8) ? 7 : 8;
	}
	if (c == 1 && _entities[s]->_y < _entities[1]->_y) {
		c = goNorth(1);
		if ((t % 100) == 0)
			_entities[s]->_currentCase = (_entities[s]->_currentCase == 6) ? 5 : 6;
	}
}

void Arcade::Pacman::moveGhost(int t)
{
	static int o = 2;
	static int q_x = 126 + 329;
	static int q_y = 102 + 11;
	static int s_x = 126 + 408;
	static int s_y = 102 + 11;
	static int t_x = 126 + 11;
	static int t_y = 102 + 456;
	int x, y;
	if (o < 6 && (t % 500) == 0) {
		_entities[o]->_x = 126 + 208;
		_entities[o]->_y = 102 + 170;
		o++;
	}
	if (o > 2) {
		s = 2;
		if ((s_x - _entities[1]->_x + s_y - _entities[1]->_y) > (t_x - _entities[1]->_x + t_y - _entities[1]->_y))
			goTo(t_x, t_y, t);
		else
			dontGoTo(s_x, s_y, t);
	}
	if (o > 3) {
		s = 3;
		q_y = (q_y >= 102 + 408) ? 0 : q_y + 2;
		goTo(q_x, q_y, t);
	}
	if (o > 4) {
		s = 4;
		goTo(126 + 89, q_y, t);
	}
	if (o > 5) {
		s = 5;
		goTo(_entities[1]->_x, _entities[1]->_y, t);
	}
}

void Arcade::Pacman::updateGame(int dir)
{
	static int t = 0;
	if ((dir == 434 || dir == 427) || (_ldir == 434 || _ldir == 427)) {
		_ldir = (dir == 434 || dir == 427) ? dir : _ldir;
		s = 1;
		goNorth(t);
	}
	if ((dir == 435 || dir == 428) || (_ldir == 435 || _ldir == 428)) {
		_ldir = (dir == 435 || dir == 428) ? dir : _ldir;
		s = 1;
		goSouth(t);
	}
	if ((dir == 436 || dir == 429) || (_ldir == 436 || _ldir == 429)) {
		_ldir = (dir == 436 || dir == 429) ? dir : _ldir;
		s = 1;
		goWest(t);
	}
	if ((dir == 437 || dir == 430) || (_ldir == 437 || _ldir == 430)) {
		_ldir = (dir == 437 || dir == 430) ? dir : _ldir;
		s = 1;
		goEast(t);
	}
	t += 20;
	moveGhost(t);
	for (int i = 2; i < 6; i++) {
		if (abs(_entities[i]->_x - _entities[1]->_x) < 5 && abs(_entities[i]->_y - _entities[1]->_y) < 5)
			_gameOver = true;
		else
			_gameOver = false;
	}
}

bool Arcade::Pacman::isGameOver() const
{
	return (_gameOver);
}

const std::string &Arcade::Pacman::getTitle() const
{
	return (_title);
}