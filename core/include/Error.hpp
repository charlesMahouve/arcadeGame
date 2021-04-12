/*
** EPITECH PROJECT, 2021
** Error
** File description:
** Arcade
*/

#pragma once

#include <exception>
#include <string>
#include <iostream>

namespace Arcade
{

    class ArcadeError: public std::exception {
    public:
        ArcadeError(const std::string &component, const std::string &message);
        const char *what() const noexcept override;
        const std::string &getComponent() const noexcept;

    private:
        std::string _component;
        std::string _message;
    };

    class Errors: public std::exception {
        public:
            Errors(std::ostream &, const std::string &) throw();
            virtual ~Errors(void) throw();

            const char *what(void) const throw();

        private:
            std::string _message;
            std::ostream &_os;
    };

    class DynamicLibraryLoaderError : public ArcadeError {
        public:
        DynamicLibraryLoaderError(const std::string &message);
    };

	class LibraryLoaderError: public Errors {
    	public:
            LibraryLoaderError(std::ostream &, const std::string &) throw();
            virtual ~LibraryLoaderError(void) throw();
	};

    class CoreError : public ArcadeError{
        public:
        CoreError(const std::string &message);
    };

}