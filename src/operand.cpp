#include "../include/operand.hpp"
#include "../include/exception.hpp"
#include "../include/creator.hpp"

// const IOperand 
template <typename T>
eOperandType get_bigger(eOperandType &type, std::string &value)
{
    try{
        if(type == _Double){
            if(stoi(value) > std::numeric_limits<T>::max()){
                throw(OverflowException());
            }else if(stoi(value) < std::numeric_limits<T>::min())
                throw(UnderflowException());
        }
    }catch(OverflowException &err){
        std::cout << err.what() << std::endl;
        exit(5);
    }catch(UnderflowException &err){
        std::cout << err.what() << std::endl;
        exit(5);
    }

    if(stoi(value) > std::numeric_limits<T>::max() || stoi(value) < std::numeric_limits<T>::min()){
        return static_cast<eOperandType>(static_cast<int>(type)+1);
    }

    return type;

}
void get_perfect_type(eOperandType &type, std::string &value)
{
    if(type == _Int8){
        type = get_bigger<int8_t>(type, value);
    }else if(type == _Int16){
        type = get_bigger<int16_t>(type, value);
    }else if(type == _Int32){
        type = get_bigger<int32_t>(type, value);
    }else if(type == _Float){
        type = get_bigger<float>(type, value);
    }else if(type == _Double){
        type = get_bigger<double>(type, value);
    }

}

IOperand* Operand::operator+(const IOperand &rhs) const{

    Creator c;
    std::string value; 
    eOperandType type = std::max(this->getType(), rhs.getType());
    if(type <= 2){
        value = std::to_string(stoi(this->toString())+stoi(rhs.toString()));
    }else{
        value = std::to_string(stod(this->toString())+stod(rhs.toString()));
    }

    get_perfect_type(type, value);
    return c.createOperand(type, value);
}

IOperand* Operand::operator-(const IOperand &rhs) const
{
    Creator c;
    std::string value; 
    eOperandType type = std::max(this->getType(), rhs.getType());
    if(type <= 2){
        value = std::to_string(stoi(this->toString())-stoi(rhs.toString()));
    }else{
        value = std::to_string(stod(this->toString())-stod(rhs.toString()));
    }

    get_perfect_type(type, value);
    return c.createOperand(type, value);
}

IOperand* Operand::operator*(const IOperand &rhs) const
{
    Creator c;
    std::string value; 
    eOperandType type = std::max(this->getType(), rhs.getType());
    if(type <= 2){
        value = std::to_string(stoi(this->toString())*stoi(rhs.toString()));
    }else{
        value = std::to_string(stod(this->toString())*stod(rhs.toString()));
    }

    get_perfect_type(type, value);
    return c.createOperand(type, value);
}

IOperand* Operand::operator/(const IOperand &rhs) const
{
    try{
        if(stoi(rhs.toString()) == 0){
            throw(DivisByZeroException());
        }
    }catch(DivisByZeroException &err){
        std::cout << err.what() << std::endl;
        exit(5);
    }

    Creator c;
    std::string value; 
    eOperandType type = std::max(this->getType(), rhs.getType());
    if(type <= 2){
        value = std::to_string(stoi(this->toString())/stoi(rhs.toString()));
    }else{
        value = std::to_string(stod(this->toString())/stod(rhs.toString()));
    }

    get_perfect_type(type, value);
    return c.createOperand(type, value);
}

IOperand* Operand::operator%(const IOperand &rhs) const
{
    try{
        if(stoi(rhs.toString()) == 0){
            throw(ModByZeroException());
        }
    }catch(ModByZeroException &err){
        std::cout << err.what() << std::endl;
        exit(5);
    }
    Creator c;
    std::string value; 
    eOperandType type = std::max(this->getType(), rhs.getType());
    value = std::to_string(stoi(this->toString())%stoi(rhs.toString()));

    get_perfect_type(type, value);
    return c.createOperand(type, value);
}