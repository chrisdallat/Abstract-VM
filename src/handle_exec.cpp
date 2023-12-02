#include "../include/stack.hpp"
#include "../include/parser.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
static Stack stack_;

eOperandType Parser::get_type(std::string const &type)
{

    for (int i = 0; i < TYPES_SIZE; i++)
    {
        if (all_types[i] == type)
        {
            return eOperandType(i);
        }
    }

    return _Double;
}

void Parser::handle_input(std::vector<std::string> const &input)
{

    auto index = input.begin();
    std::string cmd = *index, value;
    eOperandType type;

   if(cmd == "push" || cmd == "assert"){
        index++;
        type = get_type(*index);
        index++;
        value = *index;

        if (cmd == "push")
        {
            stack_.push(type, value);
        }
        else
        {
            stack_.assert_(type, value);
        }
    }else{
        size_t index = 0;
        for( ; index < commands.size(); index++){
            if(commands[index] == cmd)
                break;
        }
        stack_.stack_caller((int)index);
    }
}
