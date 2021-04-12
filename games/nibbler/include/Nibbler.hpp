/*
** EPITECH PROJECT, 2021
** Aracde
** File description:
** Nibbler
*/

#pragma once

#include <iostream>
#include "../../IGames.hpp"

namespace Arcade
{
	class Nibbler : public IGames {
        public:
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor
        ///
        Nibbler();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        ///
        ~Nibbler();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Init Map Infos (attributes of class Nibbler)
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
        const std::map<std::pair<EventType, EventKey>, std::function<void ()>> &getControls() const override;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Getter for the entities.
        /// @return return all the game's entities to display.
        ///
        const std::vector<std::shared_ptr<Thing>> &getEntities() const override;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Getter for the game controls indication.
        /// @return all the controls indication (e.g. first is MOVE DOWN, second is : KEY_DOWN).
        ///
        const std::vector<std::pair<std::string, std::string>> &getGameControls() const override;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Getter for the game stats (score, other stats).
        /// @return all the stats (Name + value) in string.
        ///
        const std::vector<std::pair<std::string, std::string>> &getGameStats() const override;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Call this function to restart the entire game. The game must reset himself.
        ///
        void restart() override;

        ////////////override/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

    private:
        std::string _title = "Nibbler";
        std::string _sound = "assets/nibbler/sound.ogg";
        std::string _music = "assets/nibbler/music.ogg";
        std::size_t _height = 500;
        std::size_t _width = 500;
        std::string _score = "0";
        std::size_t m_score = 0;
        bool _gameOver = false;
        std::map<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void ()>> _controls;
        std::vector<std::shared_ptr<Arcade::Thing>> _entities;
        std::vector<std::pair<std::string, std::string>> _gameControls;
        std::vector<std::pair<std::string, std::string>> _gameStats;
        std::map<std::size_t, std::string> _map;
        int _ldir;
        int _apple = 0;
    };

    class GameMap : public Thing {
        public:
            GameMap () {
                _type = "map";
                _assetTxt = "assets/nibbler/map.txt";
                _assetGfx = "assets/nibbler/map.png";
                _totalCase = 1;
                _x = 100;
                _y = 100;
            }
    };
    class Apple : public Thing {
        public:
            Apple () {
                _type = "map";
                _assetTxt = "x";
                _assetGfx = "assets/nibbler/apple.png";
                _x = 400;
                _y = 150;
                _l = 50;
                _wid = 50;
                _leng = 50;
                _currentH = 0;
                _currentCase = 1;
                _totalCase = 1;
            }
    };
    class SnakeHead : public Thing {
        public:
            SnakeHead () {
                _type = "map";
                _assetTxt = "O";
                _assetGfx = "assets/nibbler/snake.png";
                _x = 350;
                _y = 400;
                _l = 50;
                _wid = 50;
                _leng = 200;
                _currentH = 0;
                _currentCase = 1;
                _totalCase = 4;
            }
    };
    class SnakeBody : public Thing {
        public:
            SnakeBody () {
                _type = "map";
                _assetTxt = "o";
                _assetGfx = "assets/nibbler/snakeBody.png";
                _x = 350;
                _y = 445;
                _l = 50;
                _wid = 50;
                _leng = 50;
                _currentH = 0;
                _currentCase = 1;
                _totalCase = 1;
            }
    };

}