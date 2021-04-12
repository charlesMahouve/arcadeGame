/*
** EPITECH PROJECT, 2021
** Sfml
** File description:
** Arcade
*/

#include "Sfml.hpp"

Arcade::Sfml::Sfml() : _window(sf::VideoMode(1366, 768, 32), "ARCADE", sf::Style::Titlebar | sf::Style::Close)
{
    if (!_font.loadFromFile("assets/font.ttf"))
        throw std::invalid_argument("Asset font not found");
    _window.clear(sf::Color::Black);
//    _window.setFramerateLimit(20);
    _menuFunc[0] = &Arcade::Sfml::playMenu;
    _menuFunc[1] = &Arcade::Sfml::howtoMenu;
    _menuFunc[2] = &Arcade::Sfml::settingsMenu;
    _menuFunc[3] = &Arcade::Sfml::quit;
    _menuFunc[4] = &Arcade::Sfml::drawMenu;
    _menuFunc[5] = &Arcade::Sfml::gameIn;
    _menuFunc[6] = &Arcade::Sfml::pauseIn;
}

Arcade::Sfml::~Sfml()
{
}

void Arcade::Sfml::enterUsername(int g)
{
    sf::Event event;
    sf::Text text = getText("<\\ START />", 20, 550, 670);
    if (g == 1) {
        _window.pollEvent(event);
        if (event.type == sf::Event::TextEntered) {
            if ((event.text.unicode == 8 && _username.length() > 0))
                _username.pop_back();
            else if (event.text.unicode < 128 && _username.length() < 17)
                _username.push_back(static_cast<char>(event.text.unicode));
        }
    }
    if (checkPosition(text)) {
        text.setFillColor(sf::Color::Blue);
        if ((_gameChosen.length() > 0 && _libChosen.length() > 0 && _username.length() > 0 ) && (getEventType() == MOUSE_PRESSED || (getEventType() == KEY_PRESSED && getKeyPressed() == ENTER))) {
            gameIn();
            _getGameWithName(_gameChosen);
            _getLibWithName(_libChosen);
            _playFunction();
        }
    } else
        text.setFillColor(sf::Color::White);
    _window.draw(text);
    _window.draw(getText(_username, 20, 510, 480));
}

void Arcade::Sfml::checkChoices(std::map<int, sf::Text> &_gameText, std::map<int, sf::Text> &_libText)
{
    int i = 0;
    for (std::map<int, sf::Text>::iterator it = _gameText.begin(); it != _gameText.end(); ++it) {
        if (checkPosition(_gameText[i])) {
            _gameText[i].setFillColor(sf::Color::Yellow);
            if (getEventType() == MOUSE_PRESSED || (getEventType() == KEY_PRESSED && getKeyPressed() == ENTER))
                _gameChosen = _gameText[i].getString();
        } else
            _gameText[i].setFillColor(sf::Color::White);

        if (checkPosition(_libText[i])) {
            _libText[i].setFillColor(sf::Color::Magenta);
            if (getEventType() == MOUSE_PRESSED || (getEventType() == KEY_PRESSED && getKeyPressed() == ENTER))
                _libChosen = _libText[i].getString();
        } else
            _libText[i].setFillColor(sf::Color::White);
        i++;
    }
}

void Arcade::Sfml::displayListofChoices()
{
    float x = 170, y = 130;
    int i = 0;
    static int g = 0;
    std::map<int, sf::Text> _gameText;
    std::map<int, sf::Text> _libText;
    sf::RectangleShape rectGame;
    sf::RectangleShape rectLib;
    sf::RectangleShape rectName;
    const sf::Color DarkGray(0xA9, 0xA9, 0xA9);
    rectGame.move(sf::Vector2f(500, 180));
    rectGame.setSize(sf::Vector2f(350, 30));
    rectGame.setFillColor(DarkGray);
    rectLib = rectGame;
    rectName = rectGame;
    rectLib.move(sf::Vector2f(0, 150));
    rectName.move(sf::Vector2f(0, 300));
    for (std::string elem : _allGames) {
        _gameText[i] = getText(elem, 20, x, y);
        y += 100; i++;
    }
    y = 130; x = 970; i = 0;
    for (std::string elem : _allLibs) {
        _libText[i] = getText(elem, 20, x, y);
        y += 100; i++;
    }
    checkChoices(_gameText, _libText);
    for (int o = 0; o < i; o++) {
        _window.draw(_gameText[o]);
        _window.draw(_libText[o]);
    }
    _window.draw(getText("<\\ CHOSEN GAME />", 20, 500, 130));
    _window.draw(getText("<\\ CHOSEN LIBRARY />", 20, 470, 280));
    _window.draw(getText("<\\ USERNAME />", 20, 530, 420));
    _window.draw(rectName);
    _window.draw(rectGame);
    _window.draw(rectLib);
    _window.draw(getText("GAMES", 20, 220, 70));
    _window.draw(getText("LIBRARIES", 20, 1000, 70));
    sf::Text _gC = getText(_gameChosen, 20, 510, 180);
    sf::Text _lC = getText(_libChosen, 20, 510, 330);
    _gC.setFillColor(sf::Color::Yellow);
    _lC.setFillColor(sf::Color::Magenta);
    _window.draw(_gC);
    _window.draw(_lC);
    if (getEventType() == MOUSE_PRESSED)
        g = (checkRectPosition(rectName)) ? 1 : 0;
    enterUsername(g);
}

void Arcade::Sfml::playMenu()
{
    sf::Text _back = getText("Back", 20, 20, 700);
    sf::RectangleShape rectGame;
    sf::RectangleShape rectLib;
    const sf::Color DarkGray(0xA9, 0xA9, 0xA9);
    _scene = Arcade::IGraphicals::Scene::PLAYMENU;
    rectGame.move(sf::Vector2f(100, 100));
    rectGame.setSize(sf::Vector2f(350, 550));
    rectGame.setFillColor(DarkGray);
    rectLib = rectGame;
    rectLib.move(sf::Vector2f(800, 0));
    _wh = 0;
    _window.clear(sf::Color::Black);
    _window.draw(rectGame);
    _window.draw(rectLib);
    if (checkPosition(_back)) {
        _back.setFillColor(sf::Color::Blue);
        _window.draw(_back);
        if (getEventType() == MOUSE_PRESSED || (getEventType() == KEY_PRESSED && getKeyPressed() == ENTER)) {
            _wh = 4;
            _window.clear(sf::Color::Black);
            (this->*_menuFunc[_wh])();
        }
    } else {
        _window.draw(_back);
        _back.setFillColor(sf::Color::White);
    }
    displayListofChoices();
}

void Arcade::Sfml::settingsMenu()
{
    sf::Text _volM = getText("Low -", 20, 300, 284);
    sf::Text _volP = getText("High +", 20, 950, 284);
    sf::Text _back = getText("Back", 20, 20, 700);
    sf::RectangleShape rectangle;
    _scene = Arcade::IGraphicals::Scene::SETTINGSMENU;
    rectangle.move(sf::Vector2f(430, 284));
    _wh = 2;
    _window.clear(sf::Color::Black);
    _window.draw(getText("Welcome in Arcade", 30, 400, 10));
    _window.draw(getText("Volume", 20, 100, 284));

    if (checkPosition(_volM)) {
        _volM.setFillColor(sf::Color::Red);
        if (getEventType() == MOUSE_PRESSED || (getEventType() == KEY_PRESSED && getKeyPressed() == ENTER))
        _volume -= (_volume > 0) ? 1 : 0;
    } else
        _volM.setFillColor(sf::Color::White);
    if (checkPosition(_volP)) {
        _volP.setFillColor(sf::Color::Green);
        if (getEventType() == MOUSE_PRESSED || (getEventType() == KEY_PRESSED && getKeyPressed() == ENTER))
        _volume += (_volume < 100) ? 1 : 0;
    } else
        _volP.setFillColor(sf::Color::White);

    _window.draw(_volM);
    _window.draw(_volP);

    rectangle.setSize(sf::Vector2f(_volume * 5, 20));
    _window.draw(rectangle);
    _window.draw(_back);
    if (checkPosition(_back)) {
        _back.setFillColor(sf::Color::Blue);
        _window.draw(_back);
        if (getEventType() == MOUSE_PRESSED || (getEventType() == KEY_PRESSED && getKeyPressed() == ENTER)) {
            _wh = 4;
            _window.clear(sf::Color::Black);
            (this->*_menuFunc[_wh])();
        }
    } else
        _back.setFillColor(sf::Color::White);
}

void Arcade::Sfml::howtoMenu()
{
    sf::Text _back = getText("Back", 20, 20, 700);
    _wh = 1;
    _scene = Arcade::IGraphicals::Scene::HOWTOMENU;
    _window.clear(sf::Color::Black);
    _window.draw(getText("Welcome in Arcade", 30, 400, 10));
    _window.draw(getText("To Play -->\nClick on Play button on Menu\nChoose a game and a graphical lib and enjoy !! ^ ^", 20, 100, 284));
    _window.draw(_back);
    if (checkPosition(_back)) {
        _back.setFillColor(sf::Color::Blue);
        _window.draw(_back);
        if (getEventType() == MOUSE_PRESSED || (getEventType() == KEY_PRESSED && getKeyPressed() == ENTER)) {
            _wh = 4;
            _window.clear(sf::Color::Black);
            (this->*_menuFunc[_wh])();
        }
    } else
        _back.setFillColor(sf::Color::White);
}

void Arcade::Sfml::quit()
{
    _event = QUIT;
    _window.close();
}

void Arcade::Sfml::checkText()
{
    for (int i = 0; i < 4; i++) {
        if (checkPosition(_menuText[i])) {
            _menuText[i].setFillColor(sf::Color::Blue);
            if (getEventType() == MOUSE_PRESSED || (getEventType() == KEY_PRESSED && getKeyPressed() == ENTER))
                (this->*_menuFunc[i])();
        } else
            _menuText[i].setFillColor(sf::Color::White);
    }
}

int Arcade::Sfml::checkClick(sf::Text &_pause)
{
    if (checkPosition(_pause)) {
        _pause.setFillColor(sf::Color::Cyan);
        if (getEventType() == MOUSE_PRESSED || (getEventType() == KEY_PRESSED && getKeyPressed() == ENTER)) {
            return (1);
        }
    } else
        _pause.setFillColor(sf::Color::White);
    return (0);
}

void Arcade::Sfml::drawMenu()
{
    sf::Texture texture;
    sf::Sprite sprite;
    _wh = 4;
    _scene = Arcade::IGraphicals::Scene::DRAWMENU;
    _window.clear(sf::Color::Black);
    _window.draw(getText("ARCADE", 30, 630, 10));
    _window.draw(_menuText[0]);
    _window.draw(_menuText[1]);
    _window.draw(_menuText[2]);
    _window.draw(_menuText[3]);/*
    if (!texture.loadFromFile("assets/menu.png")) {
        throw std::invalid_argument("menu.png not found");
    }
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(500, 300));
    _window.draw(sprite);*/
    checkText();
    _menuFunction();
}

void Arcade::Sfml::pauseIn()
{
    sf::Text _continue = getText("Continue", 20, 100, 300);
    sf::Text _quit = getText("Quit", 20, 100, 370);
    sf::Text _restart = getText("Restart", 20, 100, 440);
    sf::RectangleShape rectHowto;
    const sf::Color DarkGray(0xA9, 0xA9, 0xA9);
    _scene = Arcade::IGraphicals::Scene::PAUSEIN;
    rectHowto.move(sf::Vector2f(600, 200));
    rectHowto.setSize(sf::Vector2f(700, 400));
    rectHowto.setFillColor(DarkGray);
    _wh = 6;
    _window.clear(sf::Color::Black);
    _window.draw(getText(_title, 30, 630, 10));
    if (checkClick(_restart)) {
        _wh = 5;
        _restartFunction();
    }
    if (checkClick(_continue)) {
        _wh = 5;
        _pauseFunction();
    }
    if (checkClick(_quit)) {
        _wh = 2;
        drawMenu();
    }
    _window.draw(_restart);
    _window.draw(_continue);
    _window.draw(_quit);
    _window.draw(rectHowto);
    for (size_t i = 0, y = 210, x = 610; i < _info.size(); i++, y += 30) {
        if (y < 390) {
            _window.draw(getText(_info[i].first, 20, x, y));
            _window.draw(getText(_info[i].second, 20, x + 30 + (_info[i].first.length() * 20), y));
        }
    }
}

void Arcade::Sfml::displayEntities()
{
    for (size_t i = 0; i < _gameInfo.size(); i++) {
        sf::Texture texture;
        sf::Sprite sprite;
        if (!texture.loadFromFile(_gameInfo[i]->_assetGfx)) {
            throw std::invalid_argument(_gameInfo[i]->_assetGfx + std::string("not found"));
        }
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(_gameInfo[i]->_x, _gameInfo[i]->_y));
        if (_gameInfo[i]->_totalCase > 1)
            sprite.setTextureRect(sf::IntRect((_gameInfo[i]->_currentCase - 1) * _gameInfo[i]->_l, _gameInfo[i]->_currentH * _gameInfo[i]->_wid, _gameInfo[i]->_wid, _gameInfo[i]->_l));
        if (_gameInfo[i]->_wid + _gameInfo[i]->_leng != 0)
            _window.draw(sprite);
    }
}

void Arcade::Sfml::gameIn()
{
    sf::RectangleShape rectGame;
    sf::RectangleShape rectBestScore;
    sf::RectangleShape rectGameStats;
    sf::RectangleShape rectPause;
    sf::Text _pause = getText("||", 20, 10, 10);
    const sf::Color DarkGray(0xA9, 0xA9, 0xA9);
    _scene = Arcade::IGraphicals::Scene::GAMEIN;
    rectGame.move(sf::Vector2f(100, 100));
    rectGame.setSize(sf::Vector2f(500, 500));
    rectGame.setFillColor(DarkGray);
    rectBestScore.move(sf::Vector2f(900, 500));
    rectBestScore.setSize(sf::Vector2f(400, 200));
    rectBestScore.setFillColor(DarkGray);
    rectGameStats.move(sf::Vector2f(900, 200));
    rectGameStats.setSize(sf::Vector2f(400, 200));
    rectGameStats.setFillColor(DarkGray);
    rectPause.move(sf::Vector2f(10, 10));
    rectPause.setSize(sf::Vector2f(40, 30));
    rectPause.setFillColor(sf::Color::Black);
    _wh = 5;
    _window.clear(sf::Color::Black);
    _window.draw(rectGame);
    _window.draw(rectBestScore);
    _window.draw(rectGameStats);
    _window.draw(rectPause);
    _window.draw(getText("Game Stats", 20, 920, 170));
    for (size_t i = 0, y = 210, x = 920; i < _gameStats.size(); i++, y += 30) {
        if (y < 390) {
            _window.draw(getText(_gameStats[i].first, 20, x, y));
            _window.draw(getText(_gameStats[i].second, 20, x + 60 + (_gameStats[i].first.length() * 20), y));
        }
    }
    for (size_t i = 0, y = 510, x = 920; i < _scores.size(); i++, y += 30) {
        if (y < 690) {
            _window.draw(getText(_scores[i].first, 20, x, y));
            _window.draw(getText(_scores[i].second, 20, x + 60 + (_scores[i].first.length() * 20), y));
        }
    }
    if (checkClick(_pause)) {
        _pauseFunction();
        pauseIn();
    }
    _window.draw(_pause);
    _window.draw(getText("Bests Scores", 20, 920, 470));
    _window.draw(getText("Username : " + _username, 20, 920, 80));
    _window.draw(getText("Score : " + _score, 20, 920, 110));
    _window.draw(getText(_gameChosen, 20, 300, 70));
    displayEntities();
}

void Arcade::Sfml::display()
{
//    if (_window.isOpen()) {
//        _window.clear(sf::Color::Blue);
    (this->*_menuFunc[_wh])();
    _window.display();
//    }
}

Arcade::EventType Arcade::Sfml::getEventType()
{
    sf::Event event;
//    _window.pollEvent(event);
//    while (_window.isOpen()) {
//        while (_window.pollEvent(event)) {
    if (_event == QUIT)
        return (QUIT);
    if (_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::MouseButtonPressed:
                _event = MOUSE_PRESSED;
                break;
            case sf::Event::Closed:
                _event = QUIT;
                break;
            case sf::Event::KeyPressed:
                _event = KEY_PRESSED;
                break;
            default:
                _event = NO_EVENT;
                break;
        }
    }
//    }
    return (_event);
}

Arcade::EventKey Arcade::Sfml::getKeyPressed()
{
//    sf::Event event;
//    _window.pollEvent(event);
//    while (_window.isOpen()) {
//        while (_window.pollEvent(event)) {
//    if (_window.pollEvent(event)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            return (LEFT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            return (RIGHT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            return (UP);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            return (DOWN);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Unknown))
            return (UNKNOWN);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            return (PAUSE_GAME_KEY);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            return (RESTART_KEY);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            return (MENU_KEY);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
            return (PREV_GAME_KEY);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
            return (NEXT_GAME_KEY);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
            return (PREV_LIB_KEY);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
            return (NEXT_LIB_KEY);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            return (ENTER);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return (QUIT_KEY);
//    }
//    }
    return (NONE);
}

sf::Text Arcade::Sfml::getText(const std::string str, int size, int x, int y)
{
    sf::Text text(str, _font, size);
    text.setPosition(x, y);
    return (text);
}

int Arcade::Sfml::checkRectPosition(sf::RectangleShape rect)
{
    sf::FloatRect bound = rect.getGlobalBounds();
    sf::Vector2i click_position;

    click_position = sf::Mouse::getPosition(_window);
    if ((rect.getPosition().x <= click_position.x && click_position.x <= rect.getPosition().x + bound.width)
&& (rect.getPosition().y <= click_position.y && click_position.y <= rect.getPosition().y + bound.height))
        return (1);
    return (0);
}

int Arcade::Sfml::checkPosition(sf::Text text)
{
    sf::FloatRect bound = text.getGlobalBounds();
    sf::Vector2i click_position;

    click_position = sf::Mouse::getPosition(_window);
    if ((text.getPosition().x <= click_position.x && click_position.x <= text.getPosition().x + bound.width)
&& (text.getPosition().y <= click_position.y && click_position.y <= text.getPosition().y + bound.height))
        return (1);
    return (0);
}

void Arcade::Sfml::setListGames(const std::vector<std::string> &games, const std::function<void (const std::string &)> &fct, int chosen)
{
    _allGames = games;
    _getGameWithName = fct;
    if (chosen != -1)
        fct(games.at(chosen));
}

void Arcade::Sfml::setListLibraries(const std::vector<std::string> &libraries, const std::function<void (const std::string &)> &fct, int chosen)
{
    _allLibs = libraries;
    _getLibWithName = fct;
    if (chosen != -1)
        fct(libraries.at(chosen));
}

void Arcade::Sfml::setScores(const std::vector<std::pair<std::string, std::string>> &scores)
{
    _scores = scores;
}

void Arcade::Sfml::setScore(std::string score)
{
    _score = score;
}

void Arcade::Sfml::setControls(const std::map<std::pair<EventType, EventKey>, std::function<void ()>> &controls)
{
    _controls = controls;
}

void Arcade::Sfml::setFunctionPlay(const std::function<void()> &function)
{
    _playFunction = function;
}

void Arcade::Sfml::setFunctionRestart(const std::function<void()> &function)
{
    _restartFunction = function;
}

void Arcade::Sfml::setFunctionMenu(const std::function<void()> &function)
{
    _menuFunction = function;
}

void Arcade::Sfml::setFunctionTogglePause(const std::function<void()> &function)
{
    _pauseFunction = function;
}

const std::string &Arcade::Sfml::getUserName()
{
    return (_username);
}

void Arcade::Sfml::setUserName(const std::string &username)
{
    _username = username;
}

Arcade::Sfml::Scene Arcade::Sfml::getScene() const
{
    return (_scene);
}

void Arcade::Sfml::setScene(Scene scene)
{
    _scene = scene;
}

void Arcade::Sfml::setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info)
{
    _info = info;
}

void Arcade::Sfml::setGameStats(const std::vector<std::pair<std::string, std::string>> &info)
{
    _gameStats = info;
}

void Arcade::Sfml::updateGameInfo(const std::vector<std::shared_ptr<Thing>> &gameInfo)
{
    _gameInfo = gameInfo;
}

void Arcade::Sfml::setMapSize(size_t height, size_t width)
{
    _height = height;
    _width = width;
}

void Arcade::Sfml::setGameTitle(const std::string &game)
{
    _title = game;
}

void Arcade::Sfml::setGamePause(bool pause)
{
    _isPaused = pause;
}