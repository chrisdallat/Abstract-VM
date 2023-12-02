#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <iostream>
#include <limits>

class UsageException : public std::exception{

    public:
        virtual const char *what() const throw(){
            return ("Usage: [./avm] or [./avm] [filename]");
        }
};

class SyntaxException : public std::exception{

    public:
        std::string message;
        SyntaxException(int line_number){
            std::string line = std::to_string(line_number);
            message = std::string("Syntax error happened at line ") + line + ", Terminating.\n";
        }

        virtual const char* what() const throw(){
            return (message.c_str()); 
        }

        virtual ~SyntaxException(){};
};

class InvalidFileException : public std::exception{

    public:
        virtual const char *what() const throw(){
            return ("File could not be opened, Terminating.");
        }
};

class EmptyFileException : public std::exception{

    public:
        virtual const char *what() const throw(){
            return ("File is empty, Terminating.");
        }
};


class OverflowException : public std::exception{

    public:
        virtual const char *what() const throw(){
            return ("Overflow happened, Terminating.");
        }
};

class UnderflowException : public std::exception{

    public:
        virtual const char *what() const throw(){
            return ("Underflow happened, Terminating.");
        }
};

class EmptyException : public std::exception{

    public:
        virtual const char* what() const throw(){
            return ("Pop from an empty stack, Terminating.");
        }
};

class DivisByZeroException : public std::exception{

    public:
        virtual const char *what() const throw(){
            return ("Trying to divide by zero, Terminating.");
        }
};

class ModByZeroException : public std::exception{

    public:
        virtual const char *what() const throw(){
            return ("Trying to module by zero, Terminating.");
        }
};

class NoExitException : public std::exception{

    public:
        virtual const char *what() const throw(){
            return("No exit found, Terminating.");
        }
};

class AssertException : public std::exception{

    public:
        virtual const char* what() const throw(){
            return ("Assert for value and type not found, Terminating.");
        }
};

class PrintException : public std::exception{

public:
        virtual const char* what() const throw(){
            return ("Invalid type for print [int8 only], Terminating.");
        }
};

class EnoughValuesException : public std::exception{

    public:
        virtual const char* what() const throw(){
            return ("Not enough on stack to calculate, Terminating.");
        }
};

class PrecisionException : public std::exception{

    public:
        std::string message;
        PrecisionException(int const&pre){
            message = ("Incorrect precision for type: max ") + std::to_string(pre) + (" decimal places, Terminating.");
        }
        virtual const char* what() const throw(){
            return (message.c_str());
        }
};

#endif