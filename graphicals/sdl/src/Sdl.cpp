/*
** EPITECH PROJECT, 2021
** Sdl
** File description:
** Arcade
*/

#include "Sdl.hpp"

Arcade::Sdl::Sdl()
{
}
Arcade::Sdl::~Sdl()
{
}

/*
void Arcade::Sdl::enterUsername(int g)
{
}
void Arcade::Sdl::checkChoices(std::map<int, Sdl::Text > &_gameText, std::map<int, Arcade::Sdl::Text > &_libText)
{
}
void Arcade::Sdl::displayListofChoices()
{
}
void Arcade::Sdl::playMenu()
{
}
void Arcade::Sdl::settingsMenu()
{
}
void Arcade::Sdl::howtoMenu()
{
}
void Arcade::Sdl::quit()
{
}
void Arcade::Sdl::checkText()
{
}

int Arcade::Sdl::checkClick(Sdl::Text &_pause)
{
}

void Arcade::Sdl::drawMenu()
{
    Sdl::Texture texture;
    Sdl::Sprite sprite;
    _wh = 4;
}
void Arcade::Sdl::pauseIn()
{
}
void Arcade::Sdl::gameIn()
{
}
Arcade::EventType Arcade::Sdl::
    Arcade::EventKey
    Arcade::Sdl::getKeyPressed()
{
}
Sdl:::Text Arcade::Sdl::getText(const std::string str, int size, int x, int y)
{
}
int Arcade::Sdl::checkRectPosition(Sdl:::RectangleShape rect)
{
}
int Arcade::Sdl::checkPosition(Sdl:::Text text)
{
}

Arcade::Sdl::~Sdl()
{
}

void Arcade::Sdl::display()
{
}

Arcade::EventType Arcade::Sdl::getEventType()
{
    return (NO_EVENT);
}

Arcade::EventKey Arcade::Sdl::getKeyPressed()
{
    return (NONE);
}

void Arcade::Sdl::setListGames(const std::vector<std::string> &games, const std::function<void(const std::string &)> &fct, int chosen)
{
}

void Arcade::Sdl::setListLibraries(const std::vector<std::string> &libraries, const std::function<void(const std::string &)> &fct, int chosen)
{
}

void Arcade::Sdl::setScores(const std::vector<std::pair<std::string, std::string>> &scores)
{
    _scores = scores;
}

void Arcade::Sdl::setScore(std::string score)
{
    _score = score;
}
void Arcade::Sdl::setControls(const std::map<std::pair<EventType, EventKey>, std::function<void()>> &controls)
{
    _controls = controls;
}

void Arcade::Sdl::setFunctionPlay(const std::function<void()> &function)
{
    _playFunction = function;
}

void Arcade::Sdl::setFunctionRestart(const std::function<void()> &function)
{
    _restartFunction = function;
}

void Arcade::Sdl::setFunctionMenu(const std::function<void()> &function)
{
    _menuFunc = function;
}

void Arcade::Sdl::setFunctionTogglePause(const std::function<void()> &function)
{
    _pauseFunction = function;
}

const std::string &Arcade::Sdl::getUserName()
{
    return (_username);
}

void Arcade::Sdl::setUserName(const std::string &username)
{
    _username = username;
}

Arcade::Sdl::Scene Arcade::Sdl::getScene() const
{
    return (*(new Arcade::Sdl::Scene));
}

void Arcade::Sdl::setScene(Scene scene)
{
    _scene = scene;
}

void Arcade::Sdl::setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info)
{
    _info = info;
}

void Arcade::Sdl::setGameStats(const std::vector<std::pair<std::string, std::string>> &info)
{
    _gameStats = info;
}

void Arcade::Sdl::updateGameInfo(const std::vector<std::shared_ptr<Thing>> &gameMap)
{
    _gameInfo = gameInfo;
}

void Arcade::Sdl::setMapSize(size_t height, size_t width)
{
    _height = height;
    _width = width;
}

void Arcade::Sdl::setGameTitle(const std::string &game)
{
    _title = game;
}

void Arcade::Sdl::setGamePause(bool pause)
{
    _isPaused = pause;
}

*/