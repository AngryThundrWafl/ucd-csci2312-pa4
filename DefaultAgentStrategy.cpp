//
// Created by Brian on 4/7/2016.
//
#include "DefaultAgentStrategy.h"
#include "Game.h"
#include <vector>

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
                surround[1] = true;     //checks if thers foodd
            }
            else if(s.array[i] == EMPTY){
                surround[2] = true;     //checks if its emoty
            }
            else if(s.array[i] == SIMPLE){
                surround[3] = true;     //checks if theres a simple piece
            }
        }
        //todo if statements for each instance of bool surround
        if (surround[0]) {
            //advatage is prioity
            for (int i = 0; i < 8; ++i) {
                if (s.array[i] == ADVANTAGE)
                    ways.push_back(i);
            }

            p = random(ways);
            return Game::reachSurroundings(mid, p);
        }
            //if there is not advantage it will check for food
        else if (surround[1]) {
            for (int i = 0; i < 8; ++i) {
                if (s.array[i] == FOOD)
                    ways.push_back(i);
            }

            p = random(ways);
            return Game::reachSurroundings(mid, p);
        }
            //if no food will check for Empty space to move to
        else if (surround[2]) {
            for (int i = 0; i < 8; ++i) {
                if (s.array[i] == EMPTY)
                    ways.push_back(i);
            }

            p = random(ways);
            return Game::reachSurroundings(mid, p);
        }
            //if there is no empty space will check for a simple agent to attack
        else if (surround[3]) {
            for (int i = 0; i < 8; ++i) {
                if (s.array[i] == SIMPLE)
                    ways.push_back(i);
            }

            p = random(ways);
            return Game::reachSurroundings(mid, p);
        }

        //if surround returns all false it is unable to remove so it will return stay
        return STAY;
        //todo include a switch statment for each movement case
    }

}