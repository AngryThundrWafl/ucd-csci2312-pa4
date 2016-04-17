//
// Created by Brian on 4/7/2016.
//
#include "Simple.h"
#include <sstream>
namespace Gaming{
    //Provided from PA4 read me
    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy):Agent(g,p,energy) {

    }

    Simple::~Simple() {

    }

    void Simple::print(std::ostream &os) const {
        std::stringstream s;
        s << SIMPLE_ID << Simple::__id;
        os << s.str();
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {
        //should be the same as other take turns

    }
}
