/*
** EPITECH PROJECT, 2021
** Pacman
** File description:
** Arcade
*/

#pragma once

#include <math.h>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <utility>
#include <functional>
#include "../../IGames.hpp"
#include "../../../graphicals/IGraphicals.hpp"

namespace Arcade
{
    class Pacman : public IGames {
        public:
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor
            ///
            Pacman();

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Destructor
            ///
            ~Pacman();

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Init Map Infos (attributes of class Pacman)
            ///
            void initGameInfos();

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Load Map File txt
            ///
            void loadMapFile();

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Getter for the height of the map
            /// @return Height of the map
            ///
            size_t getMapHeight() const override;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Init Controls
            /// A control is a pair of Event::Type (e.g. KEY_PRESSED) and the Event::Key (e.g. B) associated with a function to call when the event comes.
            ///
            void initControls();

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Init Stats
            ///
            void initStats();

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Init Entities
            ///
            void initEntities();

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Fix Game Controls
            /// All the controls indication (e.g. first is MOVE DOWN, second is : KEY_DOWN).
            ///
            void setGameControls();

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Getter for the width of the map
            /// @return Width of the map
            ///
            size_t getMapWidth() const override;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Getter for the music
            /// @return Path of the music file
            ///
            const std::string &getMusic() const override;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Getter for the sound
            /// @return Path of the sound file, or empty string if no sound should be played at the moment
            ///
            const std::string &getSound() const override;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Getter for the score
            /// @return Score of the current game in string
            ///
            const std::string &getScore() const override;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Getter for the controls of the game.
            /// A control is a pair of Event::Type (e.g. KEY_PRESSED) and the Event::Key (e.g. B) associated with a function to call when the event comes.
            ///
            const std::map<std::pair<EventType, EventKey>, std::function<void () > >  &getControls() const override;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Getter for the entities.
            /// @return return all the game's entities to display.
            ///
            const std::vector<std::shared_ptr<Thing > >  &getEntities() const override;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Getter for the game controls indication.
            /// @return all the controls indication (e.g. first is MOVE DOWN, second is : KEY_DOWN).
            ///
            const std::vector<std::pair<std::string, std::string > >  &getGameControls() const override;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Getter for the game stats (score, other stats).
            /// @return all the stats (Name + value) in string.
            ///
            const std::vector<std::pair<std::string, std::string > >  &getGameStats() const override;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Call this function to restart the entire game. The game must reset himself.
            ///
            void restart() override;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief updateGame function should be called in a loop. It's used to advance the game and update all logic.
            /// @brief The game must manage time on it's own.
            /// @param dir A int represents th direction of pacman
            ///
            void updateGame(int dir) override;

            ///////////////override//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Check if the game is over
            /// @return bool which indicate if the game is over
            ///
            bool isGameOver() const override;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get the name of the game
            /// @return Name of the game
            ///
            const std::string &getTitle() const override;

            void noEvent();
            int goNorth(int t);
            int goSouth(int t);
            int goEast(int t);
            int goWest(int t);
            void moveGhost(int t);
            void goTo(int x, int y, int t);
            void dontGoTo(int x, int y, int t);

        private:
            std::string _title = "Pacman";
            std::string _sound = "assets/pacman/sound.ogg";
            std::string _music = "assets/pacman/music.ogg";
            std::size_t _height = 496;
            std::size_t _width = 452;
            std::string _score = "0";
            std::size_t m_score = 0;
            bool _gameOver = false;
            std::map<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void () > >  _controls;
            std::vector<std::shared_ptr<Arcade::Thing > >  _entities;
            std::vector<std::pair<std::string, std::string > >  _gameControls;
            std::vector<std::pair<std::string, std::string > >  _gameStats;
            std::map<std::size_t, std::string> _map;
            int _ldir = 0, s = 0;
    };

    class GameMap : public Thing {
        public:
            GameMap() {
                _x = 124;
                _y = 102;
                _totalCase = 1;
                _type = "map";
                _assetTxt = "assets/pacman/map.txt";
                _assetGfx = "assets/pacman/map.png";
            };
//            ~GameMap() override;
    };

    class PacChar : public Thing {
        public:
            PacChar() {
                _x = 126 + 202;
                _y = 102 + 458;
                _l = 30;
//                _x = 210 + 124;
//                _y = 359 + 102;
                _currentCase = 1;
                _currentH = 0;
                _totalCase = 2;
                _wid = 30;
                _leng = 60;
                _type = "character";
                _assetTxt = "X";
                _assetGfx = "assets/pacman/pac/pacpac.png";
            };
//            ~PacChar() override;
            int m_x = 210;
            int m_y = 359;
    };

    class GhostRed : public Thing {
        public:
            GhostRed() {
                _x = 124 + 230;
                _y = 102 + 212;
                _l = 32;
                _wid = 32;
                _leng = 510;
                _currentH = 0;
                _currentCase = 1;
                _totalCase = 16;
                _type = "ghost";
                _assetTxt = "M";
                _assetGfx = "assets/pacman/ghosts/red.png";
            };
//            ~GhostRed() override;
    };

    class GhostBlue : public Thing {
        public:
            GhostBlue() {
                _x = 124 + 184;
                _y = 102 + 212;
                _l = 32;
                _wid = 32;
                _leng = 510;
                _currentH = 0;
                _currentCase = 1;
                _totalCase = 16;
                _type = "ghost";
                _assetTxt = "M";
                _assetGfx = "assets/pacman/ghosts/blue.png";
            };
//            ~GhostBlue() override;
    };


    class GhostPurple : public Thing {
        public:
            GhostPurple() {
                _x = 124 + 202;
                _y = 102 + 222;
                _l = 32;
                _wid = 32;
                _leng = 510;
                _currentH = 0;
                _currentCase = 1;
                _totalCase = 16;
                _type = "ghost";
                _assetTxt = "M";
                _assetGfx = "assets/pacman/ghosts/purple.png";
            };
//            ~GhostPurple() override;
    };

    class GhostOrange : public Thing {
        public:
            GhostOrange() {
                _x = 124 + 222;
                _y = 102 + 222;
                _l = 32;
                _wid = 32;
                _leng = 510;
                _currentH = 0;
                _currentCase = 1;
                _totalCase = 16;
                _type = "ghost";
                _assetTxt = "M";
                _assetGfx = "assets/pacman/ghosts/orange.png";
            };
//            ~GhostOrange() override;
    };

    class Fruits : public Thing {
        public:
            Fruits() {
                _x = 124 + 500;
                _y = 102 + 496;
                _l = 32;
                _wid = 32;
                _leng = 256;
                _currentH = 0;
                _currentCase = 1;
                _totalCase = 8;
                _type = "fruits";
                _assetTxt = "*";
                _assetGfx = "assets/pacman/ghosts/fruits.png";
            };
//            ~Fruits() override;
    };

    class Gum : public Thing {
        public:
            Gum() {
                _x = 124 + 11;
                _y = 102 + 11;
                _l = 25;
                _wid = 25;
                _leng = 25;
                _currentH = 0;
                _currentCase = 1;
                _totalCase = 1;
                _type = "gum";
                _assetTxt = ".";
                _assetGfx = "assets/pacman/gum.png";
            };
//            ~Fruits() override;
    };
}