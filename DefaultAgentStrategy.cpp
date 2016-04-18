//
// Created by Brian on 4/7/2016.
//
#include "DefaultAgentStrategy.h
#include "DefaultAgentStrategy.h"

namespace Gaming{


    DefaultAgentStrategy::DefaultAgentStrategy() {

    }

    DefaultAgentStrategy::~DefaultAgentStrategy() {

    }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        bool surround[4] ={false,false,false,false};        //all locations return false
        PositionRandomizer random;
        Position p, mid(1,1);
        std::vector<int> ways;

        //loop to check if theres any pieces
        for(int i = 0; i < 8; i++){
            if(s.array[i] == ADVANTAGE){
                surround[0] = true; //checks if there is an advantage
            }
            else if(s.array[i] == FOOD){
                surround[0] = true;     //checks if thers foodd
            }
            else if(s.array[i] == EMPTY){
                surround[0] = true;     //checks if its emoty
            }
            else if(s.array[i] == SIMPLE){
                surround[0] = true;     //checks if theres a simple piece
            }
        }
        //todo if statements for each instance of bool surround
    }
}