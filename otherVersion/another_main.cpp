#include "anotherCommand.hpp"

// The client
int main(int argc, char* argv[]){

    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " <num_commands>" << std::endl;
        return 1; }

    int numCommands;
    std::istringstream(argv[1]) >> numCommands;

    Receiver* receiver = new Receiver(numCommands);
    WriteCommand* write;
    ReadCommand* read;
    Invoker* invoker = new Invoker();

    std::string commandLine;

    while(std::getline(std::cin, commandLine)){
 
        // Receiver 
        receiver->setCommand(commandLine);

        // concrete Command objects 
        write = new WriteCommand(receiver);
        read = new ReadCommand(receiver);

        // execute
        invoker->setBlock(write);
        invoker->executeBlock();
        invoker->setBlock(read); 
        invoker->executeBlock();
    }

    //EOF goes here
    receiver->setCommand("EOF");
    read = new ReadCommand(receiver);
    invoker->setBlock(read);
    invoker->executeBlock();
}

