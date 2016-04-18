//
// Created by Brian on 4/7/2016.
//

#include "Agent.h"
#include "Resource.h"

namespace Gaming{
    //provided from Pa4 read me
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy):Piece(g,p) {
        __energy = energy;
    }

    Agent::~Agent() {
            //Todo maybe
    }

    void Agent::age() {
        __energy -= AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other) {
        return other.interact(this);
    }
    //Agent interraction with other agents
    Piece &Agent::interact(Agent *agent) {
        if(__energy == agent->getEnergy()){
            this->finish();     //this will be finished
            agent->finish();    //agent will also be finished
            //nothing happens
        }
        else if(__energy > agent->getEnergy()){
            __energy -= agent->getEnergy();     //if the energy is greater than the agent its facing
            agent->finish();

        }
        else{
            agent->addEnergy(__energy* -1);
            this->finish();         //if the agent its facing has greater energy
        }
        return *this;       //return the correct agent strategy
    }
    //agent interaction with resources
    Piece &Agent::interact(Resource *resource) {
        addEnergy(resource->consume());
        return *this;
    }
}

