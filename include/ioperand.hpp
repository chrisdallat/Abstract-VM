#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <iostream>
#include <cassert>

enum eOperandType{
    _Int8,
    _Int16,
    _Int32,
    _Float,
    _Double,
};

class IOperand{
    public:
        virtual std::string const & toString() const = 0;

        virtual int           getPrecision() const = 0;
        virtual eOperandType  getType() const = 0;

        virtual IOperand *  operator+(const IOperand &rhs) const = 0;
        virtual IOperand *  operator-(const IOperand &rhs) const = 0;
        virtual IOperand *  operator*(const IOperand &rhs) const = 0;
        virtual IOperand *  operator/(const IOperand &rhs) const = 0;
        virtual IOperand *  operator%(const IOperand &rhs) const = 0;

        IOperand(){};
        virtual ~IOperand() {}
};

#endif