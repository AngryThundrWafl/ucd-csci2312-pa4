//
// Created by Brian on 4/7/2016.
//
#include "Resource.h"
#include "Agent.h"
namespace Gaming{
    //Provided from pa4 read me
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity):Piece(g,p) {
        __capacity = capacity;
    }

    Resource::~Resource() {

    }

    double Resource::consume() {
        this->finish();
        return __capacity;
    }

    ActionType Resource::takeTurn(const Surroundings &s) const {
        return STAY;        //returns stay since resources cant move muahhah
    }

    Piece &Resource::operator*(Piece &other) {
        return other.interact(this);
    }

    void Resource::age() {
        __capacity /= RESOURCE_SPOIL_FACTOR;
    }

    Piece &Resource::interact(Agent *agent) {
       // agent->addEnergy()
        //todo
        return *this;
    }

    Piece &Resource::interact(Resource *resource) {
        return *this;
    }
}

