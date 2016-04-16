//
// Created by Brian on 4/7/2016.
//
#include "Game.h"                   //for Game::Starting.....
#include "AggressiveAgentStrategy.h"

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



        return STAY;        // done last if no condtitioins meet the agressive agents startegy
    }
}

