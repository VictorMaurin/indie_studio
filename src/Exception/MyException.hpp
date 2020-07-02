/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MyException
*/

#ifndef MYEXCEPTION_HPP_
#define MYEXCEPTION_HPP_

#include <exception>

class MyException : public std::exception {
    public:
        MyException(const char *msg, const char *file_, int line_, const char *func_);
        ~MyException();

        const char *get_file(void) const;
        int get_line(void) const;
		const char *get_func(void) const;
        const char *what() const throw ();


    private:
        const char *_msg;
        const char *_file;
        int _line;
        const char *_func;

};

#endif /* !MYEXCEPTION_HPP_ */
