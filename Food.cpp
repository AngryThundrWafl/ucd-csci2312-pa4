//
// Created by Brian on 4/7/2016.
//
#include "Food.h"
#include<sstream>
namespace Gaming{
    //Provided from Pa4 read me
   const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity):Resource(g,p,capacity) {

    }

    Food::~Food() {

    }

    void Food::print(std::ostream &os) const {
       std::stringstream s;
       s << FOOD_ID << Food::__id;
       os << s.str();
    }
}

