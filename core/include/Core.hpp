/*
** EPITECH PROJECT, 2021
** Core
** File description:
** Arcade
*/

#pragma once

#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <istream>
#include <algorithm>
#include <dirent.h>
//#include <asm-generic/errno-base.h>
#include "LibraryLoader.hpp"
#include "../../games/IGames.hpp"
#include "../../graphicals/IGraphicals.hpp"

namespace Arcade
{
    class Core {
    public:
        Core(const std::string &graphicalLib);
        ~Core();

        void loadGraphicalLibrary(const std::string &libPath, const std::string &lib);
        void loadGameLibrary(const std::string &path);

        void run();

        std::vector<std::pair<std::string, std::string>> getControls() const;

    private:
        void refreshLibrarieLists();
        const std::vector<std::string> &getGameList() const;
        const std::vector<std::string> &getGraphicalList() const;

        void setGraphicalLibFunctions();
        void startGame();

        static std::string getDynamicLibraryName(const std::string &path);

        void setCurrentLib(const std::string &lib);
        void setCurrentGame(const std::string &game);

        void sendListsToGraphicalLib();

        void initGeneralControl();

        void getBestScoresGame();
        void saveBestScore();

        bool endGame();

        void coreClock();

        std::shared_ptr<IGraphicals> _graphical;
        std::shared_ptr<IGames> _game;
        std::shared_ptr<IGames> _oldGame;

        std::string _currentGame;
        std::vector<std::string> _gameList;
        std::map<std::string, std::shared_ptr<LibraryLoader<Arcade::IGames>>> _gameLoaders;

        std::string _currentGraphicalLib;
        std::vector<std::string> _graphicalList;
        std::map<std::string, std::shared_ptr<LibraryLoader<Arcade::IGraphicals>>> _graphicalLoaders;

        bool _quitGame = false;
        bool _isPaused = false;

        IGraphicals::Scene _scene;

        std::map<std::pair<EventType, EventKey>, std::function<void ()>> _generalControls;

        std::vector<std::pair<std::string, std::string>> _bestScoresGame;

        int LOOP_DELAY = 16;

        std::string _username;

        bool _changeLib = false;

        std::chrono::system_clock::time_point _startTime;
        std::chrono::system_clock::time_point _endTime;
        std::string GAME_DIR = "lib/";
        std::string GRAPHICAL_DIR = "lib/";
    };
}