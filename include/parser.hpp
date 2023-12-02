#ifndef PARSER_HPP
#define PARSER_HPP

#include "ioperand.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>

class Parser
{

public:
    Parser();
    Parser(Parser const &src);
    Parser const &operator=(Parser const &other);
    virtual ~Parser();

    void read_input();
    void read_file(std::string);
    void parse_table(std::string &line);
    std::vector<std::string> parse_input(std::string &input);
    std::string split(std::string &str, std::string const &delim);
    bool valid_command(std::string const &cmd);
    bool valid_type(std::string const &type);
    bool is_int(std::string const &str);
    bool is_fractional(std::string const &type, std::string const &str);
    bool is_num(std::string const &str, std::string const &type);
    bool check_comment(std::string const &input, int index);
    void execute_table();
    void is_executable();
    void handle_input(std::vector<std::string> const& input);
    eOperandType get_type(std::string const& type);

private:    
    std::vector<std::vector<std::string>> exec_table;
    std::vector<std::string> all_types = {"int8", "int16", "int32", "float", "double"};
    std::vector<std::string> commands = {"pop", "dump", "add", "sub", "mul", "div", "mod", "print", "exit"};
};

#endif
