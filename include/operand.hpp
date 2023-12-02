#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "ioperand.hpp"

#include <iostream>

class Operand : public IOperand{

    public:
        virtual std::string const & toString() const = 0;

        virtual int           getPrecision() const = 0;
        virtual eOperandType  getType() const = 0;

        virtual IOperand *  operator+(const IOperand &rhs) const;
        virtual IOperand *  operator-(const IOperand &rhs) const;
        virtual IOperand *  operator*(const IOperand &rhs) const;
        virtual IOperand *  operator/(const IOperand &rhs) const;
        IOperand *  operator%(const IOperand &rhs) const;

        virtual ~Operand() {}
};

#endif