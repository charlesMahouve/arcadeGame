/*
** EPITECH PROJECT, 2021
** LibraryLoader
** File description:
** Arcade
*/

#pragma once

#include <string>
#include <dlfcn.h>
#include "Error.hpp"

namespace Arcade
{
    template <typename T>
    class LibraryLoader {
        public:
            LibraryLoader() = default;
            LibraryLoader(const LibraryLoader<T> &) = default;

            LibraryLoader(const char *libPath) :
                _libPath(libPath), _handle(nullptr), _sym(nullptr)
            {}
            LibraryLoader(std::string const &libPath) :
                _libPath(libPath), _handle(nullptr), _sym(nullptr)
            {}

            ~LibraryLoader() noexcept(false)
            {
                if (this->_handle && dlclose(this->_handle))
                    throw LibraryLoaderError(std::cerr, "Dlclose fail.");
            }

            T *load(const std::string &symbol, std::string str = "")
            {
                if (!str.empty()) {
                    this->_libPath = str;
                }
                if (this->_handle && (dlclose(this->_handle) != 0))
                    throw LibraryLoaderError(std::cerr, std::string("Could not dlclose : ") + std::string(dlerror()));
                this->_handle = dlopen(this->_libPath.c_str(), RTLD_LAZY);
                if (!this->_handle)
                    throw LibraryLoaderError(std::cerr, std::string("Could not open file : ") + std::string(dlerror()));
                void *ptr = dlsym(this->_handle, symbol.c_str());
                this->_sym = reinterpret_cast<T *(*)()>(ptr);
                if (!this->_sym)
                    throw LibraryLoaderError(std::cerr, "Dlsym fail.");
                return this->_sym();
            }

            T *getInstance(std::string symbol, std::string lib) {
                return (load(symbol, lib));
            }

        private:
            std::string _libPath;
            void *_handle;
            T *(*_sym)();
            void (*_sm)();
    };
}