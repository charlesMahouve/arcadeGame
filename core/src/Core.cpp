/*
** EPITECH PROJECT, 2021
** Core
** File description:
** Arcade
*/

#include "Core.hpp"
#include "LibraryLoader.hpp"
#include <filesystem>

Arcade::Core::Core(const std::string &graphicalLib):
    _game(nullptr), _quitGame(false), _isPaused(false),
    _scene(IGraphicals::Scene::MAIN_MENU), _changeLib(false),
    _startTime(std::chrono::system_clock::now())
{
    _graphical = nullptr;
    initGeneralControl();
    refreshLibrarieLists();
    loadGraphicalLibrary(getDynamicLibraryName(graphicalLib), graphicalLib);
}

Arcade::Core::~Core()
{
    _graphical.reset();
    _game.reset();
}

std::string tolow(std::string str)
{
    str[0] += 32;
    return (str);
}

void Arcade::Core::loadGameLibrary(const std::string &gamePath)
{
    if (!_gameLoaders.count(gamePath))
        throw CoreError("Game library couldn't be found in ./games");

    std::shared_ptr<IGames> newGame(_gameLoaders[gamePath]->getInstance("entryPoint", GAME_DIR + "arcade_" + tolow(gamePath) + ".so"));

    _game.swap(newGame);
    _oldGame.swap(newGame);
    _currentGame = gamePath;
    _graphical->setControls(_game->getControls());
    _graphical->setHowToPlay(getControls());
    _graphical->setGameStats(_game->getGameStats());
    _game->getEntities();
    _graphical->setMapSize(_game->getMapHeight(), _game->getMapWidth());
    _graphical->setGameTitle(_game->getTitle());
}

std::vector<std::pair<std::string, std::string>> Arcade::Core::getControls() const
{
    std::vector<std::pair<std::string, std::string>> controls;

    controls.emplace_back("Previous library", "9");
    controls.emplace_back("Next library", "0");
    controls.emplace_back("Previous game", "7");
    controls.emplace_back("Next game", "8");
    controls.emplace_back("Restart game", "R");
    controls.emplace_back("Pause game", "P");
    controls.emplace_back("Quit Arcade", "Escape");
    controls.emplace_back("Return to Menu", "M");
    if (_game != nullptr) {
        controls.insert(controls.end(), _game->getGameControls().begin(),
                        _game->getGameControls().end());
    }
    return (controls);
}

void Arcade::Core::loadGraphicalLibrary(const std::string &libPath, const std::string &lib)
{
    Arcade::IGraphicals *ptr;
    if (!_graphicalLoaders.count(libPath))
        throw CoreError("Graphical libraries should be located in " + libPath);
    if (libPath != _currentGraphicalLib)
        _currentGraphicalLib = libPath;
    _graphical.reset();
    ptr = reinterpret_cast<Arcade::IGraphicals *>(_graphicalLoaders[libPath]->getInstance("entryPoint", lib));
    std::shared_ptr<Arcade::IGraphicals> newLib(ptr);
    _changeLib = false;
    _graphical.swap(newLib);
    _currentGraphicalLib = libPath;
    _graphical->setScene(_scene);
    setGraphicalLibFunctions();
    _graphical->setHowToPlay(getControls());
    _graphical->setGamePause(_isPaused);
    _graphical->setUserName(_username);
    if (_game != nullptr) {
        _graphical->setControls(_game->getControls());
        _graphical->setMapSize(_game->getMapHeight(), _game->getMapWidth());
        _graphical->setGameTitle(_game->getTitle());
        _graphical->setHowToPlay(getControls());
        _graphical->setGameStats(_game->getGameStats());
    }
    sendListsToGraphicalLib();

    if (_currentGame != "") {
        getBestScoresGame();
        _graphical->setScores(_bestScoresGame);
    }
}

void Arcade::Core::sendListsToGraphicalLib()
{
    int currentGame = -1, currentLib = -1;

    for (size_t i = 0; i < _graphicalList.size(); i++)
        if (_currentGraphicalLib == _graphicalList[i]) {
            currentLib = i;
            break;
        }
    for (size_t i = 0; i < _gameList.size(); i++)
        if (_currentGame == _gameList[i]) {
            currentGame = i;
            break;
        }

    if (_graphical != nullptr) {
        _graphical->setListGames(_gameList, [this] (const std::string &game) {setCurrentGame(game);}, currentGame);
        _graphical->setListLibraries(_graphicalList, [this] (const std::string &lib) {setCurrentLib(lib);}, currentLib);
    }
}

void Arcade::Core::refreshLibrarieLists()
{
    _gameList.clear();
    _graphicalList.clear();
    _gameLoaders.clear();
    _graphicalLoaders.clear();

    try {
        std::filesystem::directory_iterator gameDir(GAME_DIR);
        std::filesystem::directory_iterator graphicalLibDir(GRAPHICAL_DIR);

        for (auto &file: gameDir)
            if (file.path().filename().extension() == ".so") {
                try {
                    std::string libname = getDynamicLibraryName(file.path());
                    _gameLoaders[libname] = std::make_unique<LibraryLoader<IGames>>(file.path());
                    _gameList.push_back(libname);
                } catch (LibraryLoaderError &) {}
            }

        for (auto &file: graphicalLibDir)
            if (file.path().filename().extension() == ".so") {
                try {
                    std::string libname = getDynamicLibraryName(file.path());
                    _graphicalLoaders[libname] = std::make_unique<LibraryLoader<IGraphicals>>(file.path());
                    _graphicalList.push_back(libname);
                } catch (LibraryLoaderError &) {}
            }

    } catch (std::exception &error) {
        throw CoreError(error.what());
    }
    if (_graphical != nullptr)
        sendListsToGraphicalLib();
}

void Arcade::Core::setCurrentGame(const std::string &game)
{
    try {
        _currentGame = game;
        getBestScoresGame();
        _graphical->setScores(_bestScoresGame);
    } catch (ArcadeError &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Arcade::Core::setCurrentLib(const std::string &lib)
{
    _changeLib = false;
    _currentGraphicalLib = lib;
}

void Arcade::Core::startGame()
{
    try {
        loadGameLibrary(_currentGame);
        _scene = IGraphicals::GAME;
        _graphical->setScene(_scene);
        _graphical->setGamePause(false);
        _isPaused = false;
    } catch (ArcadeError &e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
    }
}

void Arcade::Core::setGraphicalLibFunctions()
{
    _graphical->setFunctionPlay([this] () {startGame();});
    _graphical->setFunctionMenu(_generalControls[std::make_pair(KEY_PRESSED, MENU_KEY)]);
    _graphical->setFunctionRestart(_generalControls[std::make_pair(KEY_PRESSED, RESTART_KEY)]);
    _graphical->setFunctionTogglePause(_generalControls[std::make_pair(KEY_PRESSED, PAUSE_GAME_KEY)]);
}

const std::vector<std::string> &Arcade::Core::getGameList() const
{
    return (_gameList);
}

const std::vector<std::string> &Arcade::Core::getGraphicalList() const
{
    return (_graphicalList);
}

void Arcade::Core::run()
{
    while (_graphical->getEventType() != QUIT && !_quitGame) {
        this->coreClock();
        if (_changeLib == true)
            loadGraphicalLibrary(_currentGraphicalLib, GRAPHICAL_DIR + "arcade_" + tolow(_currentGraphicalLib) + ".so");
        _graphical->display();
        if (_scene == IGraphicals::GAME && _game != nullptr) {
            if (!_isPaused)
                _game->updateGame(((int)_graphical->getEventType()) * 100 + (int)_graphical->getKeyPressed());
            if (endGame() == true || _game->isGameOver() == true) {
                break;
            }
            _graphical->setScore(_game->getScore());
            _graphical->updateGameInfo(_game->getEntities());
            _graphical->setGameStats(_game->getGameStats());
        }
        try {
            _generalControls.at(std::pair<EventType, EventKey>(_graphical->getEventType(), _graphical->getKeyPressed()))();
        } catch (std::out_of_range) {
        }
        if (_graphical->getUserName() != _username)
            _username = _graphical->getUserName();
    }
}

std::string Arcade::Core::getDynamicLibraryName(const std::string &path)
{
    std::string prefix = "/arcade_";
    size_t pos = path.find(prefix);

    if (pos != std::string::npos) {
        std::string name = path.substr(pos + prefix.size(), path.size() - 3 - pos - prefix.size());

        if (name[0] >= 'a' && name[0] <= 'z')
            name[0] -= 32;
        return (name);
    }
    return (path);
}

void Arcade::Core::initGeneralControl()
{
    _generalControls[std::make_pair(KEY_PRESSED, RESTART_KEY)] = // restart
        [this](){
            if (_game != nullptr && _scene != IGraphicals::MAIN_MENU) {
                _game->restart();
                _graphical->setGamePause(false);
                _graphical->setScene(IGraphicals::GAME);
                _isPaused = false;
            }
        };
    _generalControls[std::make_pair(KEY_PRESSED, QUIT_KEY)] = // quit
        [this](){
            _quitGame = true;
        };
    _generalControls[std::make_pair(KEY_PRESSED, MENU_KEY)] = // return to menu
        [this](){
            if (_scene == IGraphicals::MAIN_MENU)
                return;
            _scene = IGraphicals::MAIN_MENU;
            _graphical->setScene(_scene);
            _game = nullptr;
            _graphical->setHowToPlay(getControls());
        };
    _generalControls[std::make_pair(KEY_PRESSED, PREV_LIB_KEY)] = // previous lib
        [this](){
            auto it = std::find(_graphicalList.begin(), _graphicalList.end(), _currentGraphicalLib);
            if (it == _graphicalList.begin())
                return;
            auto prevLib = std::prev(it);
            setCurrentLib(*prevLib);
        };
    _generalControls[std::make_pair(KEY_PRESSED, NEXT_LIB_KEY)] = // next lib
        [this](){
            auto it = std::find(_graphicalList.begin(), _graphicalList.end(), _currentGraphicalLib);
            auto nextLib = std::next(it);
            if (nextLib == _graphicalList.end())
                return;
            setCurrentLib(*nextLib);
        };
    _generalControls[std::make_pair(KEY_PRESSED, NEXT_GAME_KEY)] = // next game
        [this](){
            if (_currentGame.empty()) {
                setCurrentGame(_gameList.front());
                startGame();
            }
            auto it = std::find(_gameList.begin(), _gameList.end(), _currentGame);
            auto nextGame = std::next(it);
            if (nextGame == _gameList.end())
                return;
            setCurrentGame(*nextGame);
            startGame();
        };
    _generalControls[std::make_pair(KEY_PRESSED, PREV_GAME_KEY)] = // prev game
        [this](){
            if (_currentGame.empty()) {
                setCurrentGame(_gameList.front());
                startGame();
            }
            auto it = std::find(_gameList.begin(), _gameList.end(), _currentGame);
            if (it == _gameList.begin())
                return;
            auto prevGame = std::prev(it);
            setCurrentGame(*prevGame);
            startGame();
        };
    _generalControls[std::make_pair(KEY_PRESSED, PAUSE_GAME_KEY)] =
        [this](){
            if (_scene != IGraphicals::GAME)
                return;
            _isPaused = !_isPaused;
            _graphical->setGamePause(_isPaused);
        };
}

void Arcade::Core::getBestScoresGame()
{
    std::string dirBestScores(".scores/");
    std::string path(dirBestScores + _currentGame);
    std::ifstream fileScores(path);
    std::string line;
    _bestScoresGame.clear();
    if (!fileScores.good())
        return;
    while (std::getline(fileScores, line)) {
        std::istringstream lineParse(line);
        std::pair<std::string, std::string> score;
        lineParse >> score.first;
        lineParse >> score.second;
        if (score.first != "" && score.second != "")
            _bestScoresGame.emplace_back(score);
    }
    std::sort(_bestScoresGame.begin(), _bestScoresGame.end(), [](const auto &a, const auto &b){
        return std::stoi(a.second.c_str()) >= std::stoi(b.second.c_str());
    });
    if (_bestScoresGame.size() > 10)
        _bestScoresGame.erase(_bestScoresGame.begin() + 10, _bestScoresGame.end());
    fileScores.close();
}

bool Arcade::Core::endGame()
{
    if (_graphical->getScene() != IGraphicals::GAME)
        return false;
    if (_game->isGameOver() == false)
        return false;
    _graphical->setScene(IGraphicals::END_GAME);
    saveBestScore();
    _graphical->setScores(_bestScoresGame);
    _graphical->setGameStats(_game->getGameStats());
    return true;
}

void Arcade::Core::saveBestScore()
{
    _bestScoresGame.emplace_back(std::make_pair((_username.empty() ? "Unknown" : _username), _game->getScore()));
    std::sort(_bestScoresGame.begin(), _bestScoresGame.end(), [](const auto &a, const auto &b){
        return std::stoi(a.second.c_str()) >= std::stoi(b.second.c_str());
    });
    if (_bestScoresGame.size() > 10)
        _bestScoresGame.erase(_bestScoresGame.begin() + 10, _bestScoresGame.end());

    std::string dirBestScores(".scores/");
    std::string path(dirBestScores + _currentGame);
    std::ofstream fileScores(path);
    if (!fileScores.good())
        return;
    for (const auto &score : _bestScoresGame)
        fileScores << (score.first.empty() ? "Unknown" : score.first) << " " << score.second << std::endl;
    fileScores.close();
}

 void Arcade::Core::coreClock()
 {
    _endTime = std::chrono::system_clock::now();
    int elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>
        (_endTime - _startTime).count();

    if (elapsed_milliseconds < LOOP_DELAY)
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_DELAY - elapsed_milliseconds));

    _startTime = std::chrono::system_clock::now();
 }