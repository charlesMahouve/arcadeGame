/*
** EPITECH PROJECT, 2021
** Ncurses
** File description:
** Arcade
*/

#include "Ncurses.hpp"

Arcade::Ncurses::Ncurses()
{
    initscr();
    _window = newwin(0, 0, 0, 0);
    box(_window, 0, 0);

    _menuFunc[0] = &Arcade::Ncurses::playMenu;
    _menuFunc[1] = &Arcade::Ncurses::howtoMenu;
    _menuFunc[2] = &Arcade::Ncurses::settingsMenu;
    _menuFunc[3] = &Arcade::Ncurses::quit;
    _menuFunc[4] = &Arcade::Ncurses::drawMenu;
    _menuFunc[5] = &Arcade::Ncurses::gameIn;
    _menuFunc[6] = &Arcade::Ncurses::pauseIn;
}

Arcade::Ncurses::~Ncurses()
{
    delwin(_window);
}

void Arcade::Ncurses::enterUsername(int g)
{
    char a[2] = "e";
    if (g >= 97 && g <= 122) {
        a[0] = g;
        _username += std::string(a);
    }
}

void Arcade::Ncurses::checkChoices()
{
}

void Arcade::Ncurses::displayListofChoices()
{
}

void Arcade::Ncurses::createBox(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, '*', x2-x1);
    mvhline(y2, x1, '*', x2-x1);
    mvvline(y1, x1, '*', y2-y1);
    mvvline(y1, x2, '*', y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

void Arcade::Ncurses::playMenu()
{
    int ch, i = 0;
    std::map<int, std::string> _gameStrings;
    std::map<int, std::string> _libStrings;
    _scene = Arcade::IGraphicals::Scene::PLAYMENU;
    _wh = 0;
    werase(_window);
//    createBox(5, 13, 10 + ((_allLibs.size()+1) * 5), 100);
    mvwprintw(_window, 10, 90, "CHOSEN GAME");
    mvwprintw(_window, 15, 90, _gameChosen.c_str());
    mvwprintw(_window, 10, 120, "CHOSEN LIBRARY");
    mvwprintw(_window, 15, 120, _libChosen.c_str());
    mvwprintw(_window, 30, 100, "USERNAME");
    mvwprintw(_window, 35, 100, _username.c_str());
    mvwprintw(_window, 10, 30, "GAMES");
    mvwprintw(_window, 10, 200, "LIBRARIES");
    wattron(_window, A_STANDOUT);
    mvwprintw(_window, 15, 30, _allGames[0].c_str());
    wattroff(_window, A_STANDOUT);
    for (int w = 1; w < _allGames.size(); w++)
        mvwprintw(_window, 10 + ((w+1) * 5), 30, _allGames[w].c_str());
    for (int w = 0; w < _allLibs.size(); w++)
        mvwprintw(_window, 10 + ((w+1) * 5), 200, _allLibs[w].c_str());
    for (int y = 0; (ch = wgetch(_window)) != 'q'; ) {
        mvwprintw(_window, 10 + ((i+1) * 5), 30 + (y * 170), (y == 0) ? _allGames[i].c_str() : _allLibs[i].c_str());
        if (ch == KEY_UP) {
            i--;
            i = (i<0) ? _allGames.size() - 1 : i;
        } else if (ch == KEY_DOWN) {
            i++;
            i = (i>=_allLibs.size()) ? 0 : i;
        } else if (ch == KEY_LEFT) {
            y = 0;
        } else if (ch == KEY_RIGHT) {
            y = 1;
        } else if (ch == '\n') {
            if (y == 0)
                _gameChosen = _allGames[i];
            else
                _libChosen = _allLibs[i];
/*            _wh = 4;
            werase(_window);
            (this->*_menuFunc[_wh])();*/
        } else if (ch == 83) {
            _wh = 5;
            werase(_window);
            (this->*_menuFunc[_wh])();
        } else if (ch >= 97 && ch <= 122)
            enterUsername(ch);
        else
            return;
        mvwprintw(_window, 10, 90, "CHOSEN GAME");
        mvwprintw(_window, 15, 90, _gameChosen.c_str());
        mvwprintw(_window, 10, 120, "CHOSEN LIBRARY");
        mvwprintw(_window, 15, 120, _libChosen.c_str());
        mvwprintw(_window, 30, 100, "USERNAME");
        mvwprintw(_window, 35, 100, _username.c_str());
        wattron(_window, A_STANDOUT);
        mvwprintw(_window, 10 + ((i+1) * 5), 30 + (y * 170), (y == 0) ? _allGames[i].c_str() : _allLibs[i].c_str());
        wattroff(_window, A_STANDOUT);
    }

}

void Arcade::Ncurses::settingsMenu()
{
    int ch, i = 0;
    std::array<std::string, 3> but = {"Low -", "High +", "Back"};
    werase(_window);
    wattron(_window, A_STANDOUT);
    mvwprintw(_window, 30, 30, but[0].c_str());
    wattroff(_window, A_STANDOUT);
    mvwprintw(_window, 30, 80, but[1].c_str());
    mvwprintw(_window, 50, 10, but[2].c_str());
    _scene = Arcade::IGraphicals::Scene::SETTINGSMENU;
    _wh = 2;
    mvwprintw(_window, 0, 100, "Welcome in Arcade");
    mvwprintw(_window, 30, 20, "Volume");
    while ((ch = wgetch(_window)) != 'q') {
        mvwprintw(_window, (i == 2) ? 50 : 30, (i == 2) ? 10 : (30 + (50 * i)), but[i].c_str());
        if (ch == KEY_LEFT) {
            i--;
            i = (i<0) ? 2 : i;
        } else if (ch == KEY_RIGHT) {
            i++;
            i = (i>2) ? 0 : i;
        } else if (ch == '\n' && i == 2) {
            _wh = 4;
            werase(_window);
            (this->*_menuFunc[_wh])();
        } else
            return;
        wattron(_window, A_STANDOUT);
        mvwprintw(_window, (i == 2) ? 50 : 30, (i == 2) ? 10 : (30 + (50 * i)), but[i].c_str());
        wattroff(_window, A_STANDOUT);
    }
}

void Arcade::Ncurses::howtoMenu()
{
    int ch;
    _wh = 1;
    werase(_window);
    wattron(_window, A_STANDOUT);
    mvwprintw(_window, 50, 10, "Back");
    wattroff(_window, A_STANDOUT);
    _scene = Arcade::IGraphicals::Scene::HOWTOMENU;
    wrefresh(_window);
    mvwprintw(_window, 0, 100, "Welcome in Arcade");
    mvwprintw(_window, 30, 15, "To Play --> Click on Play button on Menu then Choose a game and a graphical lib and enjoy !! ^ ^");
    while ((ch = wgetch(_window)) != 'q') {
        if (ch == '\n') {
            _wh = 4;
            werase(_window);
            (this->*_menuFunc[_wh])();
        } else
            return;
        wattron(_window, A_STANDOUT);
        mvwprintw(_window, 50, 10, "Back");
        wattroff(_window, A_STANDOUT);
    }
}

void Arcade::Ncurses::quit()
{
    endwin();
    _event = QUIT;
}

void Arcade::Ncurses::pauseIn()
{
}

void Arcade::Ncurses::displayEntities()
{
}

void Arcade::Ncurses::gameIn()
{
    _scene = Arcade::IGraphicals::Scene::GAMEIN;
    werase(_window);
}

void Arcade::Ncurses::checkButtons(int i)
{
    if (i == 0)
        playMenu();
    if (i == 1)
        howtoMenu();
    if (i == 2)
        settingsMenu();
    if (i == 3)
        quit();
}

void Arcade::Ncurses::drawMenu()
{
    int ch, i = 0, j = 0;
    _wh = 4;
    mvwprintw(_window, 0, 100, "          _____   _____          _____  ______ ");
    mvwprintw(_window, 1, 100, "    /\\   |  __ \\ / ____|   /\\   |  __ \\|  ____|");
    mvwprintw(_window, 2, 100, "   /  \\  | |__) | |       /  \\  | |  | | |__   ");
    mvwprintw(_window, 3, 100, "  / /\\ \\ |  _  /| |      / /\\ \\ | |  | |  __|  ");
    mvwprintw(_window, 4, 100, " / ____ \\| | \\ \\| |____ / ____ \\| |__| | |____ ");
    mvwprintw(_window, 5, 100, "/_/    \\_\\_|  \\_\\\\_____/_/    \\_\\_____/|______|");
    for (i = 0; i < 4; i++) {
        if (i == 0)
            wattron(_window, A_STANDOUT);
        else
            wattroff(_window, A_STANDOUT);
        mvwprintw(_window, 30+i+1, 15, "%s", _menuString[i].c_str());
    }
    wrefresh(_window);
    i = 0;
    noecho();
    keypad(_window, TRUE);
    curs_set(0);
    while ((ch = wgetch(_window)) != 'q') {
        j = 0;
        mvwprintw(_window, 30+i+1, 15, "%s", _menuString[i].c_str());
        switch (ch) {
            case KEY_UP:
                i--;
                i = (i<0) ? 3 : i;
                break;
            case KEY_DOWN:
                i++;
                i = (i>3) ? 0 : i;
                break;
            case '\n':
                j = 1;
                break;
            default:
                return;
        }
        if (j == 1)
            checkButtons(i);
        wattron(_window, A_STANDOUT);
        mvwprintw(_window, 30+i+1, 15, "%s", _menuString[i].c_str());
        wattroff(_window, A_STANDOUT);
    }
    _menuFunction();
}

void Arcade::Ncurses::display()
{
    (this->*_menuFunc[_wh])();
    refresh();
}

Arcade::EventType Arcade::Ncurses::getEventType()
{
    return (KEY_PRESSED);
}

Arcade::EventKey Arcade::Ncurses::getKeyPressed()
{
    return (_keysTemplate[wgetch(_window)]);
}

void Arcade::Ncurses::setListGames(const std::vector<std::string> &games, const std::function<void (const std::string &)> &fct, int chosen)
{
    _allGames = games;
    _getGameWithName = fct;
    if (chosen != -1)
        fct(games.at(chosen));
}

void Arcade::Ncurses::setListLibraries(const std::vector<std::string> &libraries, const std::function<void (const std::string &)> &fct, int chosen)
{
    _allLibs = libraries;
    _getLibWithName = fct;
    if (chosen != -1)
        fct(libraries.at(chosen));
}

void Arcade::Ncurses::setScores(const std::vector<std::pair<std::string, std::string>> &scores)
{
    _scores = scores;
}

void Arcade::Ncurses::setScore(std::string score)
{
    _score = score;
}

void Arcade::Ncurses::setControls(const std::map<std::pair<EventType, EventKey>, std::function<void ()>> &controls)
{
    _controls = controls;
}

void Arcade::Ncurses::setFunctionPlay(const std::function<void()> &function)
{
    _playFunction = function;
}

void Arcade::Ncurses::setFunctionRestart(const std::function<void()> &function)
{
    _restartFunction = function;
}

void Arcade::Ncurses::setFunctionMenu(const std::function<void()> &function)
{
    _menuFunction = function;
}

void Arcade::Ncurses::setFunctionTogglePause(const std::function<void()> &function)
{
    _pauseFunction = function;
}

const std::string &Arcade::Ncurses::getUserName()
{
    return (_username);
}

void Arcade::Ncurses::setUserName(const std::string &username)
{
    _username = username;
}

Arcade::Ncurses::Scene Arcade::Ncurses::getScene() const
{
    return (_scene);
}

void Arcade::Ncurses::setScene(Scene scene)
{
    _scene = scene;
}

void Arcade::Ncurses::setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info)
{
    _info = info;
}

void Arcade::Ncurses::setGameStats(const std::vector<std::pair<std::string, std::string>> &info)
{
    _gameStats = info;
}

void Arcade::Ncurses::updateGameInfo(const std::vector<std::shared_ptr<Thing>> &gameInfo)
{
    _gameInfo = gameInfo;
}

void Arcade::Ncurses::setMapSize(size_t height, size_t width)
{
    _height = height;
    _width = width;
}

void Arcade::Ncurses::setGameTitle(const std::string &game)
{
    _title = game;
}

void Arcade::Ncurses::setGamePause(bool pause)
{
    _isPaused = pause;
}