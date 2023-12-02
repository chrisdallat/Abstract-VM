#include "../include/stack.hpp"
#include "../include/exception.hpp"

unsigned long needed[] = {1,2};

Stack::Stack(){
    this->table_dispatch.emplace(0 , &Stack::pop);
    this->table_dispatch.emplace(1 , &Stack::dump);
    this->table_dispatch.emplace(2 , &Stack::add);
    this->table_dispatch.emplace(3 , &Stack::sub);
    this->table_dispatch.emplace(4 , &Stack::mul);
    this->table_dispatch.emplace(5 , &Stack::div);
    this->table_dispatch.emplace(6 , &Stack::mod);
    this->table_dispatch.emplace(7 , &Stack::print);
};

Stack::Stack(Stack const &src){
    *this = src;
}

Stack &Stack::operator=(Stack const& other){
    this->_stack = other._stack; 
    return *this;
} 

Stack::~Stack(){};

void Stack::stack_caller(const int cmd){
    (*this.*table_dispatch.at(cmd))();
}

void Stack::stack_check(unsigned long const&valuesNeeded) const{

    try{
        if(_stack.empty()){
            throw(EmptyException());
        }
        else if( _stack.size() < valuesNeeded){
            throw(EnoughValuesException());
        }
    }catch(EnoughValuesException &err){
        std::cout << err.what() << std::endl;
        exit(3);
    }catch(EmptyException &err){
        std::cout << err.what() << std::endl;
        exit(3);
    }

}


void Stack::push(eOperandType const& type, std::string & value){

    Creator c;
    _stack.push_back(c.createOperand(type, value));
}

void Stack::assert_(eOperandType const& type,std::string const& value){

    stack_check(needed[0]);

    try{
        auto it = _stack.rbegin();
        if((*it)->getType() != type || (*it)->toString() != value){
            throw(AssertException());
        }
    }catch(AssertException &err){
        std::cout << err.what() << std::endl;
        exit(3);
    }
}

void Stack::pop(){


    stack_check(needed[0]);
    _stack.pop_back();

}

void Stack::dump(){

    stack_check(needed[0]);

    for(auto it = _stack.rbegin(); it != _stack.rend(); it++){
        std::cout << (*it)->toString() << std::endl;
    }
}

void Stack::add(){

    stack_check(needed[1]);

    Creator c;

    auto it = _stack.rbegin();
    const IOperand *first = *it;
    const IOperand *second = *(++it);
    const IOperand *third = (*first) + (*second); 

    _stack.pop_back();
    _stack.pop_back();

    _stack.push_back(third);

}
void Stack::sub(){   

    stack_check(needed[1]);

    Creator c;

    auto it = _stack.rbegin();
    const IOperand *first = *it;
    const IOperand *second = *(++it);
    const IOperand *third = (*second) - (*first); 

    _stack.pop_back();
    _stack.pop_back();

    _stack.push_back(third);
}
void Stack::mul(){      

    stack_check(needed[1]);

    Creator c;

    auto it = _stack.rbegin();
    const IOperand *first = *it;
    const IOperand *second = *(++it);
    const IOperand *third = (*first) * (*second);

    _stack.pop_back();
    _stack.pop_back();

    _stack.push_back(third);
}
void Stack::div(){   

    stack_check(needed[1]);

    Creator c;

    auto it = _stack.rbegin();
    const IOperand *first = *it;
    const IOperand *second = *(++it);
    const IOperand *third = (*second) / (*first); 

    _stack.pop_back();
    _stack.pop_back();

    _stack.push_back(third);
}

void Stack::mod(){


    stack_check(needed[1]);

    Creator c;

    auto it = _stack.rbegin();
    const IOperand *first = *it;
    const IOperand *second = *(++it);
    const IOperand *third = (*second) % (*first); 

    _stack.pop_back();
    _stack.pop_back();

    _stack.push_back(third);
}

void Stack::print(){
    
    stack_check(needed[0]);

    try{
        auto it = _stack.rbegin();
        if((*it)->getType() == _Int8){
            std::cout << char(stoi((*it)->toString())) << std::endl;
        }else{
            throw(PrintException());
        }
    }catch(PrintException &err){
        std::cout << err.what() << std::endl;
        exit(3);
    }
}
