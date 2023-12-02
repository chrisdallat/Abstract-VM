#include "../include/ioperand.hpp"
#include "../include/variables.hpp"
#include "../include/parser.hpp"
#include "../include/exception.hpp"

static int line_counter = 0;

Parser::Parser()
{
    //std::cout << "Parser constructor called" << std::endl;
}

Parser::Parser(Parser const &src){
    *this = src;
}

Parser const &Parser::operator=(Parser const &other){
    (void)other;
    return *this;
}

Parser::~Parser() 
{
    //std::cout << "Parser destructor called" << std::endl;   
    return;
}

void Parser::read_input()
{
    std::string input_line;

    while(input_line != ";;")
    {
        std::getline(std::cin, input_line);
        parse_table(input_line);
    }
    execute_table();
}

void Parser::read_file(std::string filename) 
{
    std::string     line;
    std::ifstream   input(filename);

    try{
        if(!input)
            throw InvalidFileException();
        if(input.peek() == std::ifstream::traits_type::eof())
            throw EmptyFileException();
    }catch(InvalidFileException &err){
        std::cerr << err.what() << std::endl;
        exit(1);
    }catch(EmptyFileException &err){
        std::cerr << err.what() << std::endl;
        exit(1);
    }
    //check if file is empty
    while (std::getline(input, line)) {
        parse_table(line);
    }
    input.close();
    execute_table();
}

void Parser::parse_table(std::string &line)
{
    line_counter++;

    try{
        if(line[0] != ';'){
            std::vector<std::string> parsed = parse_input(line);
            if(!parsed.empty()){
                exec_table.push_back(parsed);
            }else{
                throw(SyntaxException(line_counter));
            }
        }
    }catch(SyntaxException &err){
        std::cout << err.what() << std::endl;
        exit(2);
    }
}

std::vector<std::string> Parser::parse_input(std::string& input)
{
    std::vector<std::string> parsed;

    std::string splitted = split(input, " ");
    parsed.push_back(splitted);

    if(valid_command(splitted)){
        if(splitted.length() == input.length()){
            return parsed;
        }else if(check_comment(input,0) == true){
            return parsed;
        }
    }else if(splitted == "assert" || splitted == "push"){
        splitted = split(input, "(");
        if(valid_type(splitted))
        {
            parsed.push_back(splitted);
            splitted = split(input, ")");
            if(input.length() == 1 || (input.length() > 1 && check_comment(input,1) == true)){
                if(is_num(splitted, parsed.back())){
                    parsed.push_back(splitted);
                    return parsed;
                }
            }
        }
    }

    return {};
}

std::string Parser::split(std::string& str, std::string const& delim)
{
    size_t pos = str.find(delim); 
    std::string ret = str.substr(0, pos);
    if(delim == ")"){
        str.erase(0, pos); 
    }else{
        str.erase(0, pos+delim.length()); 
    }
    return ret;
}

bool Parser::valid_command(std::string const& cmd){

    for(auto &it : commands){
        if(cmd == it)
            return true;
    }
    return false;
}

bool Parser::valid_type(std::string const& type)
{
    for(auto &it : all_types){
        if(it == type)
            return true;
    }
    return false;
}

bool Parser::is_int(std::string const& str)
{
    int index = 0;

    if(str[index] == '-')
        index++;

    try{
        while(str[index]){
            if(!std::isdigit(str[index])){
                if(str[index] == '.'){
                    throw(PrecisionException(PRE_INT));
                }
                return false;
            }
            index++;
        }
    }catch(PrecisionException &err){
        std::cout << err.what() << std::endl;
        exit(0);
    }
    return true;
}

bool Parser::is_fractional(std::string const& type, std::string const& str)
{
    char dot = '.';
    int flag = 0, index = 0;

    while(str[index]){
        if(str[index] == dot && (index != 0 || str[index+1] != '\0')){
            if(flag == 0){
                flag = index;
                index++;
            }else{
                return false;
            }
        }

        if(!std::isdigit(str[index])){
            return false;
        }
        index++;
    }

    try{
        if(type == "double" && ((str.length() - flag) > PRE_DOUBLE )){
            throw(PrecisionException(PRE_DOUBLE));
        }else if(type == "float" && ((str.length() - flag) > PRE_FLOAT)){
            throw(PrecisionException(PRE_FLOAT));
        }
    }catch(PrecisionException &err){
        std::cout << err.what() << std::endl;
        exit(0);
    }
    return true;
}

bool Parser::is_num(std::string const& str, std::string const&type)
{
    if(type == "int8" || type == "int16" || type == "int32"){
        if(is_int(str)){
            return true;
        }
    }else{
        if(is_fractional(type, str)){
            return true;
        }
    }
    return false;
}

bool Parser::check_comment(std::string const& input, int index)
{
    while(input[index]){
        if(input[index] == ' '){
            index++;
        }else if(input[index] == ';' && input[index+1] != ';'){
            return true;
        }else{
            break;
        }
    }
    return false;
}

void Parser::execute_table()
{
    is_executable();

    auto it = exec_table.begin();
    for(; it != exec_table.end(); it++){
        handle_input(*it);
    }
}

void Parser::is_executable()
{
    auto it = exec_table.end();
    it--;
    try{
        if((*it)[0] != "exit"){
            throw(NoExitException());
        }

    }catch(NoExitException &err){
        std::cout << err.what() <<std::endl;
        exit(1);
    }
    exec_table.pop_back();
}