#include "command.hpp"

int main(int argc, char* argv[]){

    if (argc != 2){
        std::cout << "Usage: " << argv[0] << " <num_commands>" << std::endl;
        return 1; }

    int numCommands;
    std::istringstream(argv[1]) >> numCommands;

    CommandInvoker invoker(numCommands);

    std::string commandLine;

    while(std::getline(std::cin, commandLine)){

        ConcreteCommand* command = new ConcreteCommand(commandLine);
        invoker.setBlock(command);
        invoker.executeBlock(command);
    }

    //if EOF is received  
    invoker.executeBlock(new ConcreteCommand("EOF"));
}
 