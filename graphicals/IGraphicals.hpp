/*
** EPITECH PROJECT, 2021
** Interface for graphicals
** File description:
** Arcade
*/

#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <fstream>
#include <memory>
#include <utility>
#include "../games/Thing.hpp"


namespace Arcade
{
    enum EventKey {
        NONE, UNKNOWN, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        RETURN, BACKSPACE, TAB, ESCAPE, ENTER, DELETE, UP, DOWN, LEFT, RIGHT, MOUSE_1, MOUSE_2, MOUSE_3,
        MENU_KEY, RESTART_KEY, PAUSE_GAME_KEY, PREV_GAME_KEY, NEXT_GAME_KEY, NEXT_LIB_KEY, PREV_LIB_KEY, QUIT_KEY
    };

    enum EventType {
        NO_EVENT,
        MOUSE_PRESSED,
        MOUSE_RELEASED,
        MOUSE_WHEEL,
        KEY_PRESSED,
        KEY_RELEASED,
        QUIT,
        RESIZE,
    };

	class IGraphicals {
        public:


        enum Scene {
            /// You enter this scene when launching the arcade, it should display the scores of the chosen game,
            /// let you choose between graphical libraries and games, play the chosen game and exit the arcade.
            /// It is also possible to display the arcade controls in this scene. The player must be able to set
            /// and change his username in this scene
            MAIN_MENU,
            /// This is the game scene, it should display the game. It can display game information, buttons
            /// (restart, go to main menu, pause game) and the arcade and game controls.
            GAME,
            PLAYMENU,
            HOWTOMENU,
            SETTINGSMENU,
            DRAWMENU,
            GAMEIN,
            PAUSEIN,
            /// This scene is not mandatory, it can display the current score, previous high scores and give the option to the player to
            /// restart the game or return to the main menu.
            END_GAME,
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        ///
        virtual ~IGraphicals() = default;

        /////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function must display the current scene. It is used in the game loop.
        /// @warning Warning Sirrr
        ///
        virtual void display() = 0;

        /////////////////////////////////////////////////////////////////////////////////
        /// @brief This function must return the event type. It is called once per frame.
        /// @warning Warning Sirrr
        ///
        virtual EventType getEventType() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function must returns the key pressed, if any. It is also called once per frame.
        /// @warning Warning Sirrr
        ///
        virtual EventKey getKeyPressed() = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The core provides a list of games to the user through this function. When a game is chosen from the list (first argument),
        /// it should be passed to the function (second argument). The third argument represents the currently chosen game, if any.
        /// If no game is chosen, it is set to -1.
        /// @warning Warning Sirrr
        /// @param games A list of games
        /// @param func A function to get the game from the list
        /// @param c A int that is set to -1 of no game is chosen
        ///
        virtual void setListGames(const std::vector<std::string> &games, const std::function<void (const std::string &)> &fct, int chosen = -1) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The core provides a list of libraries to the user through this function. When a library is chosen from the list (first argument),
        /// it should be passed to the function (second argument). The third argument represents the currently chosen library, if any.
        /// If no library is chosen, it is set to -1.
        /// @warning Warning Sirrr
        /// @param libraries A list of lib
        /// @param func A function to get the lib from the list
        /// @param c A int that is set to -1 of no lib is chosen
        ///
        virtual void setListLibraries(const std::vector<std::string> &libraries, const std::function<void (const std::string &)> &fct, int chosen = -1) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function sets the list of scores. First element of the pair is the username, the second is the score.
        /// @warning Warning Sirrr
        /// @param scores A vector of pair (username, score)
        ///
        virtual void setScores(const std::vector<std::pair<std::string, std::string > > &scores) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function sets the controls for the game. They should be checked for only when the current scene is GAME.
        /// @warning Warning Sirrr
        /// @param Controls A map of pair (EnvenType, EventKey) and function linked to the state of scene
        ///
        virtual void setControls(const std::map<std::pair<EventType, EventKey>, std::function<void () > > &controls) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This is the function that lets the game start. Should only be called when a game is chosen.
        /// @warning Warning Sirrr
        /// @param function A function linked to startGame
        ///
        virtual void setFunctionPlay(const std::function<void()> &function) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function should be used in the GAME and END_GAME scenes. It restarts the game.
        /// @warning Warning Sirrr
        /// @param function A function linked to restart
        ///
        virtual void setFunctionRestart(const std::function<void()> &function) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function should be used in the GAME and END_GAME scenes. It restarts the game.
        /// @warning Warning Sirrr
        /// @param function A function linked to menu
        ///
        virtual void setFunctionMenu(const std::function<void()> &function) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function should be used to pause and unpause the game when it is running (GAME scene).
        /// @warning Warning Sirrr
        /// @param function A function linked to pause
        ///
        virtual void setFunctionTogglePause(const std::function<void()> &function) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Should return the username entered by the player in the main menu scene.
        /// @warning Warning Sirrr
        /// @return The username
        ///
        virtual const std::string &getUserName() = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function is called to set the username of the player in case he entered one earlier.
        /// @warning Warning Sirrr
        /// @param username A string
        ///
        virtual void setUserName(const std::string &username) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current scene.
        /// @warning Warning Sirrr
        /// @return The scene (MAIN_MENU, GAME, END_GAME), the step where we are
        ///
        virtual Scene getScene() const = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the current scene.
        /// @warning Warning Sirrr
        /// @param scene The scene (MAIN_MENU, GAME, END_GAME)
        ///
        virtual void setScene(Scene scene) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This is information for the player about the game controls. First element of the pair is the description of the action,
        /// the second is the key mapped to it.
        /// @warning Warning Sirrr
        /// @param info A vector of pair ("Step 1", "Choose a game")... It's the How to Play
        ///
        virtual void setHowToPlay(const std::vector<std::pair<std::string, std::string > > &info) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This is called in a loop when the game is running. Sets the current game information. The first element of the pair
        /// is the category (e.g. Score), the second is the value (e.g. 200).
        /// @warning Warning Sirrr
        /// @param info A vector of pair ("Speed", "BAD X_X")... It's the Stats of Game
        ///
        virtual void setGameStats(const std::vector<std::pair<std::string, std::string > > &info) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This is called in a loop when the game is running. This vector contains entities that should be displayed in the game scene.
        /// @warning Warning Sirrr
        /// @param gameMap A vector of shared pointer that represent all the things to display. Ex : Map, Score, UserInfo, Button
        ///
        virtual void updateGameInfo(const std::vector<std::shared_ptr<Thing > > &gameMap) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the size of the game map.
        /// @warning Warning Sirrr
        /// @param height The height of the map
        /// @param width The width of the map
        ///
        virtual void setMapSize(size_t height, size_t width) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the title of the game.
        /// @warning Warning Sirrr
        /// @param game The title of the game
        ///
        virtual void setGameTitle(const std::string &game) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Informs the game library whether the game is paused or not. It is called when the library is loaded and when there is a change.
        /// @warning Warning Sirrr
        /// @param pause A boolean to know if the game is pause or not
        ///
        virtual void setGamePause(bool pause) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the current score.
        /// @warning Warning Sirrr
        /// @param score The score
        ///
        virtual void setScore(std::string score) = 0;
	};
}