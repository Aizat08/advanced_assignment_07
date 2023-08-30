#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Command Interface
class Command{
public:
   virtual void execute() = 0;
};
 
// Receiver Class
class Receiver{
public:
    Receiver(int numCommands) : numCommands{numCommands},
    						    isDynamic_{false},
    						    counter{0}{}
    						      
    //utility methods
    void setCommand(std::string com){command = com;}
    std::string getCommand(){return command;}
    int getNumCommands(){return numCommands;}
    void increaseCounter(){counter++;}
    void decreaseCounter(){counter--;}
    int getCounter(){return counter;}
    void setDynamic(bool dynamic){isDynamic_ = dynamic;}
    bool isDynamic(){return isDynamic_;}
    size_t size(){return static_block.size();} //only for static

    //actual commands to be received
    void write(std::string blockType){
    	if(blockType == "static"){static_block.push_back(command);}
    	if(blockType == "dynamic"){dynamic_block.push_back(command);}
    }

    void read(std::string blockType){
    	if(blockType == "static"){read(static_block);}
    	if(blockType == "dynamic"){read(dynamic_block);}
    }

private:
    std::string command;
    int numCommands;
    int counter;
    bool isDynamic_;
    std::vector<std::string> static_block;
    std::vector<std::string> dynamic_block;
    void read(std::vector<std::string>& vec){
    	if(!vec.empty()){
           std::cout << "bulk: ";
           for(auto it = vec.begin(); it != vec.end(); ++it){
               if(it != vec.begin()){ std::cout << ", "; }
               std::cout << *it; }
           std::cout << std::endl;
           vec.clear();}
    }
}; 

// Command for writing the bulk command
class WriteCommand : public Command{
public:
    WriteCommand(Receiver* receiver) : receiver{receiver} {}

    void execute() override{
    	//static block
    	if(receiver->getCommand() != "{" && receiver->isDynamic() == false){
    	   receiver->write("static");}

    	//dynamic block
    	if(receiver->getCommand() == "{" || receiver->isDynamic() == true){
           receiver->read("static");
           receiver->setDynamic(true);
           if(receiver->getCommand() == "{"){receiver->increaseCounter();}
           if(receiver->getCommand() != "{" && receiver->getCommand() != "}"){
              receiver->write("dynamic"); }
    	}

    	if(receiver->getCommand() == "}"){
    	   receiver->decreaseCounter();}
    }

private:
    Receiver* receiver;
};
 
// Command for reading commands from containers
class ReadCommand : public Command{
public:
    ReadCommand(Receiver* receiver) : receiver{receiver} {}

    void execute() override {
    	//static block
    	if(receiver->getCommand() != "{" && receiver->isDynamic() == false){
    	   if(receiver->getNumCommands() == receiver->size()){
    	      receiver->read("static");} 
    	}

    	//static block if EOF is received
    	if(receiver->getCommand() == "EOF"){receiver->read("static");}

    	//dynamic block
    	if(receiver->getCommand() == "}"){
    	   if(receiver->getCounter() == 0){
    	      receiver->read("dynamic");
    	      receiver->setDynamic(false);}
    	}
    }

private:
    Receiver* receiver;
};

// Invoker 
// Stores the ConcreteCommand object 
class Invoker{
public:
    void setBlock(Command *com) {mCmd = com;}
    void executeBlock() {mCmd->execute();} 

private:
     Command *mCmd;
};
 