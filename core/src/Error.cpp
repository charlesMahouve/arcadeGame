/*
** EPITECH PROJECT, 2021
** Error
** File description:
** Arcade
*/

#include "Error.hpp"
#include "LibraryLoader.hpp"

using namespace Arcade;

ArcadeError::ArcadeError(const std::string &component, const std::string &message):
    _component(component), _message(message)
{}

const char *ArcadeError::what() const noexcept
{
    return (_message.c_str());
}

const std::string &ArcadeError::getComponent() const noexcept
{
    return (_component);
}

DynamicLibraryLoaderError::DynamicLibraryLoaderError(const std::string &message):
    ArcadeError("Library Loader", message)
{}

CoreError::CoreError(const std::string &message):
    ArcadeError("Core", message)
{}

LibraryLoaderError::LibraryLoaderError(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

LibraryLoaderError::~LibraryLoaderError(void) throw()
{}

Errors::Errors(std::ostream &os, const std::string &message) throw()
	: _os(os)
{
	_message = message;
}

Errors::~Errors(void) throw()
{}

const char *Errors::what(void) const throw()
{
	return _message.c_str();
}
