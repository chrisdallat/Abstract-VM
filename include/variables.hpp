#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include "operand.hpp"

#define PRE_INT 0
#define PRE_FLOAT 6
#define PRE_DOUBLE 15

class Int8 : public Operand{

    private: 
        std::string str_value;

    public:
        Int8(){};
        Int8(std::string const& str_value){this->str_value = str_value;};

        ~Int8(){};
        const std::string & toString() const override {return str_value;};
        eOperandType getType() const override {return eOperandType::_Int8;};
        int getPrecision() const override {return PRE_INT;}
};

class Int16 : public Operand{

    private: 
        std::string str_value;

    public:
        Int16(){};
        Int16(std::string const& str_value){this->str_value = str_value;};
        const std::string & toString() const override {return str_value;};
        eOperandType getType() const override {return eOperandType::_Int16;};
        int getPrecision() const override {return PRE_INT;}
};

class Int32 : public Operand{

    private: 
        std::string str_value;

    public:
        Int32(){};
        Int32(std::string const& str_value){this->str_value = str_value;};
        const std::string & toString() const override {return str_value;};
        eOperandType getType() const override {return eOperandType::_Int32;};
        int getPrecision() const override {return PRE_INT;}
};

class Double : public Operand{

    private: 
        std::string str_value;

    public:
        Double(){};
        Double(std::string const& str_value){this->str_value = str_value;};
        const std::string & toString() const override {return str_value;};
        eOperandType getType() const override {return eOperandType::_Double;};
        int getPrecision() const override {return PRE_DOUBLE;}
};

class Float : public Operand{

    private: 
        std::string str_value;

    public:
        Float(){};
        Float(std::string const& str_value){this->str_value = str_value;};
        const std::string & toString() const override {return str_value;};
        eOperandType getType() const override {return eOperandType::_Float;};
        int getPrecision() const override {return PRE_FLOAT;}
};

#endif