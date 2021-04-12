/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

Arcade::Nibbler::Nibbler()
{
	initGameInfos();
	std::srand (time(NULL));
}

Arcade::Nibbler::~Nibbler()
{
}

void Arcade::Nibbler::loadMapFile()
{
    std::ifstream map("assets/nibbler/map.txt");
    std::string line;
    if (map.is_open()) {
        for (size_t i = 0; getline(map, line); i++)
            _map[i] = line;
        map.close();
    } else
        throw std::invalid_argument("Unable to open Nibbler map file");
}

void Arcade::Nibbler::initGameInfos()
{
	loadMapFile();
	initControls();
	initEntities();
	initStats();
	setGameControls();
}

void Arcade::Nibbler::initControls()
{
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(NO_EVENT, NONE), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(NO_EVENT, UNKNOWN), [this](){&Arcade::Nibbler::noEvent;}) );

	for (Arcade::EventKey l = NONE; l <= Z; l = (Arcade::EventKey)((int)l + 1))
		_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, l), [this](){&Arcade::Nibbler::noEvent;}) );

	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(QUIT, RETURN), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, BACKSPACE), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, TAB), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, ESCAPE), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, ENTER), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, DELETE), [this](){&Arcade::Nibbler::noEvent;}) );

	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, UP), [this](){&Arcade::Nibbler::goNorth;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, DOWN), [this](){&Arcade::Nibbler::goSouth;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, LEFT), [this](){&Arcade::Nibbler::goWest;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, RIGHT), [this](){&Arcade::Nibbler::goEast;}) );

	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, Z), [this](){&Arcade::Nibbler::goNorth;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, S), [this](){&Arcade::Nibbler::goSouth;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, Q), [this](){&Arcade::Nibbler::goWest;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, D), [this](){&Arcade::Nibbler::goEast;}) );

	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(MOUSE_PRESSED, MOUSE_1), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(MOUSE_PRESSED, MOUSE_2), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(MOUSE_PRESSED, MOUSE_3), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, MENU_KEY), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, RESTART_KEY), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, PAUSE_GAME_KEY), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, PREV_GAME_KEY), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, NEXT_GAME_KEY), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, PREV_LIB_KEY), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, NEXT_LIB_KEY), [this](){&Arcade::Nibbler::noEvent;}) );
	_controls.insert( std::pair<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>>(std::pair<Arcade::EventType, Arcade::EventKey>(KEY_PRESSED, QUIT_KEY), [this](){&Arcade::Nibbler::noEvent;}) );
}

void Arcade::Nibbler::initEntities()
{
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::GameMap)));
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::Apple)));
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::SnakeHead)));
	_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::SnakeBody)));
}

void Arcade::Nibbler::initStats()
{
	_gameStats.push_back(std::pair<std::string, std::string>("Apple", "0"));
}

void Arcade::Nibbler::setGameControls()
{
	_gameControls.push_back(std::pair<std::string, std::string>("MOVE DOWN", "KEY DOWN OR KEY S"));
	_gameControls.push_back(std::pair<std::string, std::string>("MOVE UP", "KEY UP OR KEY Z"));
	_gameControls.push_back(std::pair<std::string, std::string>("MOVE LEFT", "KEY LEFT OR KEY Q"));
	_gameControls.push_back(std::pair<std::string, std::string>("MOVE RIGHT", "KEY RIGHT OR KEY D"));
}

void Arcade::Nibbler::noEvent()
{}

int Arcade::Nibbler::goNorth(int t)
{
	int y = 0, x = 0;
	std::stringstream ss;

	x = _entities[2]->_x;
	y = _entities[2]->_y;
	_entities[2]->_y -= 45;
	m_score += 2;
	ss << m_score;
	_score = ss.str();
	for (int i = 3, s = 0, k = 0; i < _entities.size(); i++) {
		s = _entities[i]->_x;
		k = _entities[i]->_y;
		if (_entities[i]->_x == x)
			_entities[i]->_y += (y > _entities[i]->_y) ? 45 : -45;
		else if (y == _entities[i]->_y)
			_entities[i]->_x += (x > _entities[i]->_x) ? 45 : -45;
		else {
			_entities[i]->_y = y;
			_entities[i]->_x = x;
		}
		x = s;
		y = k;
	}
	return (0);
}

int Arcade::Nibbler::goSouth(int t)
{
	int y = 0, x = 0;
	std::stringstream ss;

	x = _entities[2]->_x;
	y = _entities[2]->_y;
	_entities[2]->_y += 45;
	m_score += 2;
	ss << m_score;
	_score = ss.str();
	for (int i = 3, s = 0, k = 0; i < _entities.size(); i++) {
		s = _entities[i]->_x;
		k = _entities[i]->_y;
		if (_entities[i]->_x == x)
			_entities[i]->_y += (y > _entities[i]->_y) ? 45 : -45;
		else if (y == _entities[i]->_y)
			_entities[i]->_x += (x > _entities[i]->_x) ? 45 : -45;
		else {
			_entities[i]->_y = y;
			_entities[i]->_x = x;
		}
	x = s;
		y = k;
	}
	return (0);
}

int Arcade::Nibbler::goWest(int t)
{
	int y = 0, x = 0;
	std::stringstream ss;

	x = _entities[2]->_x;
	y = _entities[2]->_y;
	_entities[2]->_x -= 45;
	m_score += 2;
	ss << m_score;
	_score = ss.str();
	for (int i = 3, s = 0, k = 0; i < _entities.size(); i++) {
		s = _entities[i]->_x;
		k = _entities[i]->_y;
		if (_entities[i]->_x == x)
			_entities[i]->_y += (y > _entities[i]->_y) ? 45 : -45;
		else if (y == _entities[i]->_y)
			_entities[i]->_x += (x > _entities[i]->_x) ? 45 : -45;
		else {
			_entities[i]->_y = y;
			_entities[i]->_x = x;
		}
		x = s;
		y = k;
	}
	return (0);
}

int Arcade::Nibbler::goEast(int t)
{
	int y = 0, x = 0;
	std::stringstream ss;

	x = _entities[2]->_x;
	y = _entities[2]->_y;
	_entities[2]->_x += 45;
	m_score += 2;
	ss << m_score;
	_score = ss.str();
	for (int i = 3, s = 0, k = 0; i < _entities.size(); i++) {
		s = _entities[i]->_x;
		k = _entities[i]->_y;
		if (_entities[i]->_x == x)
			_entities[i]->_y += (y > _entities[i]->_y) ? 45 : -45;
		else if (_entities[i - 1]->_y == _entities[i]->_y)
			_entities[i]->_x += (x > _entities[i]->_x) ? 45 : -45;
		else {
			_entities[i]->_y = y;
			_entities[i]->_x = x;
		}
		x = s;
		y = k;
	}
	return (0);

}

size_t Arcade::Nibbler::getMapHeight() const
{
	return (_height);
}

size_t Arcade::Nibbler::getMapWidth() const
{
	return (_width);
}

const std::string &Arcade::Nibbler::getMusic() const
{
	return (_music);
}

const std::string &Arcade::Nibbler::getSound() const
{
	return (_sound);
}

const std::string &Arcade::Nibbler::getScore() const
{
	return (_score);
}

const std::map<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>> &Arcade::Nibbler::getControls() const
{
	return (_controls);
}

const std::vector<std::shared_ptr<Arcade::Thing>> &Arcade::Nibbler::getEntities() const
{
	return (_entities);
}

const std::vector<std::pair<std::string, std::string>> &Arcade::Nibbler::getGameControls() const
{
	return (_gameControls);
}

const std::vector<std::pair<std::string, std::string>> &Arcade::Nibbler::getGameStats() const
{
	return (_gameStats);
}

void Arcade::Nibbler::restart()
{
	_gameOver = false;
	_controls.clear();
	_entities.clear();
	_gameControls.clear();
	_gameStats.clear();
	_map.clear();
	initGameInfos();
}

void Arcade::Nibbler::updateGame(int dir)
{
	static int t = 0;
	std::stringstream ss;
	for (int i = 3, s = 0; i < _entities.size(); i++, s = 0) {
		s += (_entities[2]->_currentCase == 1 && _entities[i]->_y == _entities[2]->_y && abs(_entities[i]->_x - _entities[2]->_x) == 0) ? 1 : 0;
		s += (_entities[2]->_currentCase == 3 && _entities[i]->_y == _entities[2]->_y && abs(_entities[i]->_x - _entities[2]->_x) == 0) ? 1 : 0;
		s += (_entities[2]->_currentCase == 2 && _entities[i]->_x == _entities[2]->_x && abs(_entities[i]->_y - _entities[2]->_y) == 0) ? 1 : 0;
		s += (_entities[2]->_currentCase == 4 && _entities[i]->_x == _entities[2]->_x && abs(_entities[i]->_y - _entities[2]->_y) == 0) ? 1 : 0;
		if (s != 0) {
			_gameOver = true;
			return;
		}
	}
	if (((dir == 434 || dir == 427) && _ldir != 435 && _ldir != 428) || (_ldir == 434 || _ldir == 427)) {
		if ((t % 16) == 0)
			goNorth(t);
		_entities[2]->_currentCase = 1;
		_ldir = (dir == 434 || dir == 427) ? dir : _ldir;
	}
	if (((dir == 435 || dir == 428) && _ldir != 434 && _ldir != 427) || (_ldir == 435 || _ldir == 428)) {
		if ((t % 16) == 0)
			goSouth(t);
		_entities[2]->_currentCase = 3;
		_ldir = (dir == 435 || dir == 428) ? dir : _ldir;
	}
	if (((dir == 436 || dir == 429) && _ldir != 437 && _ldir != 430) || (_ldir == 436 || _ldir == 429)) {
		if ((t % 16) == 0)
			goWest(t);
		_entities[2]->_currentCase = 2;
		_ldir = (dir == 436 || dir == 429) ? dir : _ldir;
	}
	if (((dir == 437 || dir == 430) && _ldir != 436 && _ldir != 429) || (_ldir == 437 || _ldir == 430)) {
		if ((t % 16) == 0)
			goEast(t);
		_entities[2]->_currentCase = 4;
		_ldir = (dir == 437 || dir == 430) ? dir : _ldir;
	}
	t += 1;
	if (abs(_entities[1]->_x - _entities[2]->_x) <= 25 && abs(_entities[1]->_y - _entities[2]->_y) <= 25) {
		_apple += 1;
		_entities.push_back(std::make_shared<Arcade::Thing>(*(new Arcade::SnakeBody)));
		_entities[1]->_x = std::rand() % (475 - 124) + 125;
		_entities[1]->_y = std::rand() % (475 - 124) + 125;
			if (_entities[2]->_currentCase == 1) {
				_entities[_entities.size() - 1]->_y = _entities[_entities.size() - 2]->_y + 45;
				_entities[_entities.size() - 1]->_x = _entities[_entities.size() - 2]->_x;
			}
			if (_entities[2]->_currentCase == 3) {
				_entities[_entities.size() - 1]->_y = _entities[_entities.size() - 2]->_y - 45;
				_entities[_entities.size() - 1]->_x = _entities[_entities.size() - 2]->_x;
			}
			if (_entities[2]->_currentCase == 2) {
				_entities[_entities.size() - 1]->_x = _entities[_entities.size() - 2]->_x + 45;
				_entities[_entities.size() - 1]->_y = _entities[_entities.size() - 2]->_y;
			}
			if (_entities[2]->_currentCase == 4) {
				_entities[_entities.size() - 1]->_x = _entities[_entities.size() - 2]->_x - 45;
				_entities[_entities.size() - 1]->_y = _entities[_entities.size() - 2]->_y;
			}
	}
	ss << _apple;
	_gameStats.clear();
	_gameStats.push_back(std::pair<std::string, std::string>("Apple", ss.str()));
	if (_entities[2]->_x < 100 || _entities[2]->_y <= 100 || _entities[2]->_x > 600 || _entities[2]->_y >= 600) {
		_gameOver = true;
	}
}

bool Arcade::Nibbler::isGameOver() const
{
	return (_gameOver);
}

const std::string &Arcade::Nibbler::getTitle() const
{
	return (_title);
}