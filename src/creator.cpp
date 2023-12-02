#include "../include/creator.hpp"
#include "../include/exception.hpp"

Creator::Creator(){
    this->c_table.emplace(_Int8,    &Creator::createInt8);
    this->c_table.emplace(_Int16,   &Creator::createInt16);
    this->c_table.emplace(_Int32,   &Creator::createInt32);
    this->c_table.emplace(_Double,  &Creator::createDouble);
    this->c_table.emplace(_Float,   &Creator::createFloat);
}

template <typename T>
void type_limit(std::string &value){

    try{
        if(std::stod(value) > std::numeric_limits<T>::max()) {
            throw(OverflowException());
        }else if(std::stod(value) < std::numeric_limits<T>::min()){
            throw(UnderflowException());
        }
    }catch(OverflowException &err){
        std::cout << err.what() << std::endl;
        exit(4);
    }catch(UnderflowException &err){
        std::cout << err.what() << std::endl;
        exit(4);
    }
}

Creator::Creator(Creator const &src){
    *this = src;
}

Creator const &Creator::operator=(Creator const &rhs){
    (void)rhs;
    return *this;
}

IOperand * Creator::createInt8(std::string &value){
    type_limit<int8_t>(value);
    IOperand *op = new Int8(value);
    return op;
}

IOperand * Creator::createInt16(std::string &value){
    type_limit<int16_t>(value);
    IOperand *op = new Int16(value);
    return op;
}

IOperand * Creator::createInt32(std::string &value){
    type_limit<int32_t>(value);
    IOperand *op = new Int32(value);
    return op;
}

IOperand * Creator::createFloat(std::string &value){
    type_limit<float>(value);
    IOperand *op = new Float(value);
    return op;
}

IOperand * Creator::createDouble(std::string &value)
{
    type_limit<double>(value);
    IOperand *op = new Double(value);
    return op;
}

IOperand * Creator::createOperand(eOperandType type, std::string &value)
{
    return (*this.*c_table.at(type))(value);
}