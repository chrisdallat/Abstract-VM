#ifndef STACK_HPP
#define STACK_HPP

#include "creator.hpp"

#include <list>
#include <iostream>
#include <vector>
#include <map>

#define TYPES_SIZE 4
class Stack{

        public:
        void push(eOperandType const&, std::string &);
        void pop();
        void dump();
        void assert_(eOperandType const&,std::string const&);
        void add();
        void sub();
        void mul();
        void div();
        void mod();
        void print();
        void stack_check(unsigned long const&) const;
        void handle_commands(std::string &);
        void stack_caller(const int);

        Stack();
        Stack(Stack const &src);
        Stack & operator=(Stack const& other);
        ~Stack();
        

     private:
        std::list<const IOperand *> _stack;
        std::map < const int , void (Stack::*)()> table_dispatch;
};

#endif