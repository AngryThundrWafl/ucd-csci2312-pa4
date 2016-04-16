//
// Created by Brian on 4/7/2016.
//
#include "Advantage.h"
#include <sstream>              //so we can use stringstream function for print function

namespace Gaming{
    //provided from PA4 readme
    const char Advantage::ADVANTAGE_ID = 'D';
   const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;


    Advantage::Advantage(const Game &g, const Position &p, double capacity):Resource(g,p,capacity *ADVANTAGE_MULT_FACTOR) {

    }

    Advantage::~Advantage() {
        //Todo maybe
    }

    void Advantage::print(std::ostream &os) const {
        //use the function from class
        std::stringstream s;
        s << ADVANTAGE_ID << Advantage::__id;
        os << s.str();          //inserrts string stream objec into ostream object
    }

    double Advantage::getCapacity() const {
        return Advantage::__capacity;
    }

    double Advantage::consume() {
        return __capacity;          //returns capacity since it will get cinsumed
    }
}
