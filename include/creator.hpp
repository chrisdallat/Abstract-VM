#ifndef CREATOR_HPP
#define CREATOR_HPP

#include "variables.hpp"
#include <map>
#include <iostream>
#include <utility>

class Creator{

    private:
        IOperand * createInt8(std::string & value);
        IOperand * createInt16(std::string & value);
        IOperand * createInt32(std::string & value);
        IOperand * createFloat(std::string & value);
        IOperand * createDouble(std::string & value);
        std::map<eOperandType, IOperand *(Creator::*)(std::string & value)> c_table;

    public:
        Creator();
        Creator(Creator const &src);
        Creator const &operator=(Creator const &rhs);
        virtual ~Creator(){};

        IOperand * createOperand(const eOperandType, std::string  &value);
};

#endif