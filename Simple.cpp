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
        ActionType action;
        std::vector<int> ways;
        PositionRandomizer random;
        Position pos;
        for (int i = 0; i < 8; ++i) {
            if (s.array[i] == FOOD || s.array[i] == ADVANTAGE)
                ways.push_back(i);
        }
        if (ways.size() != 0)                                                       //if there are any resources neaar the piece and wll do the actio  requred move towards it
            pos = random(ways);
        else {
            ways.clear();
            for (int i = 0; i < 8; ++i) {
                if (s.array[i] == EMPTY)
                    ways.push_back(i);
            }
            if (ways.size() != 0)                                                  //checks if theres a empty element in here
                pos = random(ways);
            else {                                                                  //since it is not moving p will be centered agian
                pos.x = 1;
                pos.y = 1;
            }
        }
        action=__game.reachSurroundings(this->getPosition(), pos);
        return action;
    }
}
