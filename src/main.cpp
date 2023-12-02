#include "../include/stack.hpp"
#include "../include/parser.hpp"
#include "../include/exception.hpp"


int main(int ac, const char** argv) 
{
    Parser Parser;

    try{
        if (ac == 1)
        {
            Parser.read_input();
        }
        else if (ac == 2) {   
            std::string     filename(argv[1]);
            Parser.read_file(filename);
        }
        else
        {
            throw(UsageException());
        }
    }
    catch(UsageException &err){
        std::cout << err.what() << std::endl;
        exit(1);
    }
    
    return 0;
}
