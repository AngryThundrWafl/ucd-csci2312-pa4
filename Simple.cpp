//
// Created by Brian on 4/7/2016.
//
#include "Simple.h"
#include <ctime>
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
        std::default_random_engine gen(time(0));
        PositionRandomizer random;
        Position pos, This = this->getPosition();
        int location;
        for (int i = 0; i < 8; ++i) {
            if (s.array[i] == FOOD || s.array[i] == ADVANTAGE)
                ways.push_back(i);
        }
        if (ways.size() > 0)                                                       //if there are any resources neaar the piece and wll do the actio  requred move towards it
            location = ways[gen() % ways.size()];
        else {
            for (int i = 0; i < 8; ++i) {
                if (s.array[i] == EMPTY)
                    ways.push_back(i);
            }
            if (ways.size() > 0)                                                  //checks if theres a empty element in here
                 location = ways[gen() % ways.size()];
            else {                                                                  //since it is not moving p will be centered agian
                return STAY;
            }
        }
        switch (location) {
            case 0:
                pos.x = This.x - 1;
                pos.y = This.y - 1;
                break;
            case 1:
                pos.x = This.x - 1;
                pos.y = This.y;
                break;
            case 2:
                pos.x = This.x - 1;
                pos.y = This.y + 1;
                break;
            case 3:
                pos.x = This.x;
                pos.y = This.y - 1;
                break;
            case 4:
                pos.x = This.x;
                pos.y = This.y;
                break;
            case 5:
                pos.x = This.x;
                pos.y = This.y + 1;
                break;
            case 6:
                pos.x = This.x + 1;
                pos.y = This.y - 1;
                break;
            case 7:
                pos.x = This.x + 1;
                pos.y = This.y;
                break;
            case 8:
                pos.x = This.x + 1;
                pos.y = This.y + 1;
                break;
        }
        action = __game.reachSurroundings(This, pos);
        return action;
    }
}
