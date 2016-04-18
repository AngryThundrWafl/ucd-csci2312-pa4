//
// Created by Brian on 4/7/2016.
//
#include "Strategic.h"
#include <sstream>
namespace Gaming{
    //Provided from Pa4 read me
    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s):Agent(g,p,energy) {
        __strategy = s;         //will load the default strategy
    }

    Strategic::~Strategic() {
        delete __strategy;      //it has a array from surroundings
    }

    void Strategic::print(std::ostream &os) const {
        std::stringstream s;
        s << STRATEGIC_ID << Strategic::__id;
        os << s.str();
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const {
        //todo
        return (*__strategy)(s);
    }
}

