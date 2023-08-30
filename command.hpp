#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "file.hpp"

// Concrete command
class ConcreteCommand{
public:
    ConcreteCommand(const std::string& cmd) : command(cmd) {}

    void execute(std::ofstream& file){
        std::cout << command;
        file << command;}

    std::string getCommand(){return command;}

private:
    std::string command;
};

// Receiver-Invoker (kinda wrapper)
class CommandInvoker{
public:

    CommandInvoker(int numCommands) : numCommands{numCommands},
                                      isDynamic{false}, counter_dynamic{0},
                                      counter_static{0} {}

    void setBlock(ConcreteCommand* cmd){

        std::string command = cmd->getCommand();

        //static block
        if(command != "{" && isDynamic == false){
            if(counter_static == 0){
                fileName_ = fileName();
                counter_static++;}
            static_vec.push_back(cmd);}

        //dynamic block
        if(command == "{" || isDynamic == true){
            executeBlock(static_vec, fileName_);
            counter_static = 0;
            isDynamic = true;
            if(command == "{"){
               if(counter_dynamic == 0){fileName_ = fileName();}
                  counter_dynamic++;}
            if(command != "{" && command != "}"){
                dynamic_vec.push_back(cmd); }
        }
    }

    void executeBlock(ConcreteCommand* cmd){

        std::string command = cmd->getCommand();

        //static block
        if(command != "{" && isDynamic == false){
           if(numCommands == static_vec.size()){
              executeBlock(static_vec, fileName_);
              counter_static = 0; }
        }

        //dynamic block
        if(command == "}"){ 
            counter_dynamic--;
            if(counter_dynamic == 0){
               executeBlock(dynamic_vec, fileName_);
               isDynamic = false; }
        }

        //EOF signal handling
        if(command == "EOF"){
           executeBlock(static_vec, fileName_); }
    }

private:
    std::vector<ConcreteCommand*> static_vec;
    std::vector<ConcreteCommand*> dynamic_vec;

    int numCommands;
    bool isDynamic;
    int counter_dynamic;
    int counter_static;
    std::string fileName_;

    void executeBlock(std::vector<ConcreteCommand*>& vec_, std::string name){
        if(!vec_.empty()){
            std::ofstream file(name);
            std::cout << "bulk: ";
            file << "bulk: ";
            for(auto it = vec_.begin(); it != vec_.end(); ++it){
                if(it != vec_.begin()){ 
                    std::cout << ", ";
                    file << ", "; }
                (*it)->execute(file); }
            std::cout << std::endl; 
            file << std::endl;
            vec_.clear();
            file.close();}
    }
};
