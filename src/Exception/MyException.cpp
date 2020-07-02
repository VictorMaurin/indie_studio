/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MyException
*/

#include "MyException.hpp"
#include <iostream>

MyException::MyException(const char *msg, const char *file, int line, const char *func) : std::exception()
{
    _file = file;
    _line = line;
    _msg = msg;
    _func = func;
}

MyException::~MyException()
{
}

const char *MyException::get_file(void) const
{
    return (_file);
}

int MyException::get_line(void) const
{
    return (_line);
}

const char *MyException::get_func(void) const
{
    return (_func);
}

const char *MyException::what() const throw () 
{
    return _msg;
}