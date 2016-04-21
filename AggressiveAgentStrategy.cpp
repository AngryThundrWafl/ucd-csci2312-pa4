//
// Created by Brian on 4/7/2016.
//
#include "Game.h"                   //for Game::Starting.....
#include "AggressiveAgentStrategy.h"
#include <ctime>

namespace  Gaming{
    //Provided from PA4 read me
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
        __agentEnergy = agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() {
        //Todo maybe
    }
    //strategy for agrressive agent
    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        //TODO implement so that the agent finds any means of play using if sttments
        std::vector<int> ways;
        PositionRandomizer random;      //our random generator
        Position p, mid(1,1);
        int location;
        std::default_random_engine gen(time(0));
        bool surround[4] = { false, false, false, false };
        for (int i = 0; i < 8; ++i) {
            if ((s.array[i] == SIMPLE || s.array[i] == STRATEGIC) && __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)                              //checks if theres any agents in the vicinity
                surround[0] = true;
            else if (s.array[i] == ADVANTAGE)                                               //checks for advantage on the grid and dos that if there arent any agents
                surround[1] = true;
            else if (s.array[i] == FOOD)                                                    //3rd optiom if agents or advantage was not found and cchecks for food
                surround[2] = true;
            else if (s.array[i] == EMPTY)                                                   //last option if none of the other was found
                surround[3] = true;
        }
        if (surround[0]) {                                                                  //if agent was found we will move towards the agent and interact maybe
            for (int i = 0; i < 8; ++i) {
                if (s.array[i] == SIMPLE || s.array[i] == STRATEGIC)
                    ways.push_back(i);
            }
            location = ways[gen() % ways.size()];
        }
        else if (surround[1]) {                                                             //moves to advantage if no agents were true
            for (int i = 0; i < 8; ++i) {
                if (s.array[i] == ADVANTAGE)
                    ways.push_back(i);
            }
            location = ways[gen() % ways.size()];
        }
        else if (surround[2]) {                                                             //moves to food if that point in the array is true
            for (int i = 0; i < 8; ++i) {
                if (s.array[i] == FOOD)
                    ways.push_back(i);
            }

            location = ways[gen() % ways.size()];
        }
        else if (surround[3]) {                                                             //moves to empty space if true
            for (int i = 0; i < 8; ++i) {
                if (s.array[i] == EMPTY)
                    ways.push_back(i);
            }
            location = ways[gen() % ways.size()];
        }
        else//if all the elements = false then noconditions are met for the agent to move
            return STAY;

        switch(location){       //each case will be for each part of the surroundings in the array
            case 0:
                p.x = mid.x -1;
                p.y = mid.y -1;
                break;
            case 1:
                p.x = mid.x-1;
                p.y = mid.y;
                break;
            case 2:
                p.x = mid.x-1;
                p.y = mid.y+1;
                break;
            case 3:
                p.x = mid.x;
                p.y = mid.y-1;
                break;
            case 4:
                p.x = mid.x;
                p.y = mid.y;
                break;
            case 5:
                p.x = mid.x;
                p.y = mid.y+1;
                break;
            case 6:
                p.x = mid.x+1;
                p.y = mid.y-1;
                break;
            case 7:
                p.x = mid.x+1;
                p.y = mid.y;
                break;
            case 8:
                p.x = mid.x+1;
                p.y = mid.y+1;
                break;
        }
        return Game::reachSurroundings(mid, p);
    }
}

