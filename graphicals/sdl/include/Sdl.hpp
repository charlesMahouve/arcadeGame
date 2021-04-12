/*
** EPITECH PROJECT, 2021
** Sdl
** File description:
** Arcade
*/

#pragma once

#include <iostream>
#include "../../IGraphicals.hpp"
#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

namespace Arcade
{
    class Sdl : public IGraphicals
    {
    public:
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor
        ///
        Sdl();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        ///
        ~Sdl() override;

        /////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function must display the current scene. It is used in the game loop.
        /// @warning Warning Sirrr
        ///
        void display() override;

        /////////////////////////////////////////////////////////////////////////////////
        /// @brief This function must return the event type. It is called once per frame.
        /// @warning Warning Sirrr
        ///
        EventType getEventType() override;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function must returns the key pressed, if any. It is also called once per frame.
        /// @warning Warning Sirrr
        ///
        EventKey getKeyPressed() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The core provides a list of games to the user through this function. When a game is chosen from the list (first argument),
        /// it should be passed to the function (second argument). The third argument represents the currently chosen game, if any.
        /// If no game is chosen, it is set to -1.
        /// @warning Warning Sirrr
        /// @param games A list of games
        /// @param func A function to get the game from the list
        /// @param c A int that is set to -1 of no game is chosen
        ///
        void setListGames(const std::vector<std::string> &games, const std::function<void(const std::string &)> &fct, int chosen = -1) override;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The core provides a list of libraries to the user through this function. When a library is chosen from the list (first argument),
        /// it should be passed to the function (second argument). The third argument represents the currently chosen library, if any.
        /// If no library is chosen, it is set to -1.
        /// @warning Warning Sirrr
        /// @param libraries A list of lib
        /// @param func A function to get the lib from the list
        /// @param c A int that is set to -1 of no lib is chosen
        ///
        void setListLibraries(const std::vector<std::string> &libraries, const std::function<void(const std::string &)> &fct, int chosen = -1) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function sets the list of scores. First element of the pair is the username, the second is the score.
        /// @warning Warning Sirrr
        /// @param scores A vector of pair (username, score)
        ///
        void setScores(const std::vector<std::pair<std::string, std::string>> &scores) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function sets the controls for the game. They should be checked for only when the current scene is GAME.
        /// @warning Warning Sirrr
        /// @param Controls A map of pair (EnvenType, EventKey) and function linked to the state of scene
        ///
        void setControls(const std::map<std::pair<EventType, EventKey>, std::function<void()>> &controls) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This is the function that lets the game start. Should only be called when a game is chosen.
        /// @warning Warning Sirrr
        /// @param function A function linked to startGame
        ///
        void setFunctionPlay(const std::function<void()> &function) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function should be used in the GAME and END_GAME scenes. It restarts the game.
        /// @warning Warning Sirrr
        /// @param function A function linked to restart
        ///
        void setFunctionRestart(const std::function<void()> &function) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function should be used in the GAME and END_GAME scenes. It restarts the game.
        /// @warning Warning Sirrr
        /// @param function A function linked to menu
        ///
        void setFunctionMenu(const std::function<void()> &function) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function should be used to pause and unpause the game when it is running (GAME scene).
        /// @warning Warning Sirrr
        /// @param function A function linked to pause
        ///
        void setFunctionTogglePause(const std::function<void()> &function) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Should return the username entered by the player in the main menu scene.
        /// @warning Warning Sirrr
        /// @return The username
        ///
        const std::string &getUserName() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function is called to set the username of the player in case he entered one earlier.
        /// @warning Warning Sirrr
        /// @param username A string
        ///
        void setUserName(const std::string &username) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current scene.
        /// @warning Warning Sirrr
        /// @return The scene (MAIN_MENU, GAME, END_GAME), the step where we are
        ///
        Scene getScene() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the current scene.
        /// @warning Warning Sirrr
        /// @param scene The scene (MAIN_MENU, GAME, END_GAME)
        ///
        void setScene(Scene scene) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This is information for the player about the game controls. First element of the pair is the description of the action,
        /// the second is the key mapped to it.
        /// @warning Warning Sirrr
        /// @param info A vector of pair ("Step 1", "Choose a game")... It's the How to Play
        ///
        void setHowToPlay(const std::vector<std::pair<std::string, std::string>> &info) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This is called in a loop when the game is running. Sets the current game information. The first element of the pair
        /// is the category (e.g. Score), the second is the value (e.g. 200).
        /// @warning Warning Sirrr
        /// @param info A vector of pair ("Speed", "BAD X_X")... It's the Stats of Game
        ///
        void setGameStats(const std::vector<std::pair<std::string, std::string>> &info) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the current score.
        /// @warning Warning Sirrr
        /// @param score The score
        ///
        void setScore(std::string score) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This is called in a loop when the game is running. This vector contains entities that should be displayed in the game scene.
        /// @warning Warning Sirrr
        /// @param gameMap A vector of shared pointer that represent all the things to display. Ex : Map, Score, UserInfo, Button
        ///
        void updateGameInfo(const std::vector<std::shared_ptr<Thing>> &gameMap) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the size of the game map.
        /// @warning Warning Sirrr
        /// @param height The height of the map
        /// @param width The width of the map
        ///
        void setMapSize(size_t height, size_t width) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the title of the game.
        /// @warning Warning Sirrr
        /// @param game The title of the game
        ///
        void setGameTitle(const std::string &game) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Informs the game library whether the game is paused or not. It is called when the library is loaded and when there is a change.
        /// @warning Warning Sirrr
        /// @param pause A boolean to know if the game is pause or not
        ///
        void setGamePause(bool pause) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create a sdlText by a string, a size and positions
        /// @warning Warning Sirrr
        /// @param str String that will be transdlormed in sdlText
        /// @param size Size of the text
        /// @param x X coordinate of the new position
        /// @param y Y coordinate of the new position
        ///
        //Sdl::Text getText(const std::string str, int size, int x, int y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Check the click on mouse for text
        /// @warning Warning Sirrr
        /// @param text The sdl::Text
        ///
        //int checkPosition(Sdl::Text text);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Check the click on mouse for rect
        /// @warning Warning Sirrr
        /// @param text The sdl::Text
        ///
        //int checkRectPosition(Sdl::RectangleShape);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Display the start Menu
        /// @warning Warning Sirrr
        ///
        void drawMenu();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Check Menu Text Surround
        /// @warning Warning Sirrr
        ///
        void checkText();

        void playMenu();

        void settingsMenu();

        void howtoMenu();

        void quit();

        void gameIn();

        void displayListofChoices();

        //void checkChoices(std::map<int, Sdl::Text> &_gameText, std::map<int, Sdl::Text> &_libText);

        void enterUsername(int g);

        void pauseIn();

        //int checkClick(Sdl::Text &_pause);

        void displayEntities();

    protected:
    private:
        std::string _title = "Game";
        std::string _username = "Prince";
        std::string _libChosen = "";
        std::string _gameChosen = "";
        std::size_t _height;
        std::size_t _width;
        std::string _score;
        std::map<std::pair<Arcade::EventType, Arcade::EventKey>, std::function<void()>> _controls;
        std::vector<std::shared_ptr<Arcade::Thing>> _gameInfo;
        std::vector<std::pair<std::string, std::string>> _info;
        std::vector<std::pair<std::string, std::string>> _gameStats;
        std::vector<std::pair<std::string, std::string>> _scores;
        std::vector<std::string> _allLibs;
        std::function<void(const std::string &)> _getLibWithName;
        std::vector<std::string> _allGames;
        std::function<void(const std::string &)> _getGameWithName;
        Arcade::IGraphicals::Scene _scene;
        std::function<void()> _pauseFunction;
        std::function<void()> _menuFunction;
        std::function<void()> _restartFunction;
        std::function<void()> _playFunction;
        bool _isPaused;
        int _wh = 4;
        float _volume = 50;

        EventType _event = NO_EVENT;
        //Sdl::RenderWindow _window;
        //Sdl::Font _font;
        std::map<int, void (Arcade::Sdl::*)()> _sceneFunc;
        std::map<int, void (Arcade::Sdl::*)()> _menuFunc;
        //std::array< Sdl::Text, 4 > _menuText = {getText("PLAY", 20, 100, 284), getText("HOW TO PLAY", 20, 100, 324), getText("SETTINGS", 20, 100, 364), getText("QUIT", 20, 100, 408)};
    };
} // namespace Arcade