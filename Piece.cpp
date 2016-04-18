//
// Created by Brian on 4/7/2016.
//
#include "Piece.h"
namespace Gaming {
    unsigned int Piece::__idGen = 1000; //sets __idgen to 1000

    //constructor for Piece class
    Piece::Piece(const Game &g, const Position &p) :__game(g), __position(p){           //puts g into game and p into position
        __finished = false;             //game will be initialized to false since it isnt ovr when its constructed LOL
        __turned = false;
        __id = __idGen++;                 //id will be intialized to the current id in idGen
    }
    //destructor for piece class
    Piece::~Piece() {
                                        //TODO
    }
    //Friend Function for piece class
    std::ostream &operator<<(std::ostream &os, const Piece &piece) {
           piece.print(os);                        //TODO need to return os and use inheritance for this function
            return os;
    }
}