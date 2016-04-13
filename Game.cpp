//
// Created by Brian on 4/7/2016.
//

#include "Game.h"

namespace Gaming{
    //provided by ivo from PA4 read me
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    //used for populating grid (used in automatic random initialization of a Game)
    void Game::populate() {
    // simple pseudo-random number generator
    // sufficient for our casual purposes
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);
        //TODO need to calculate num of strategic and set it equal to num startegic of int

    // populate Strategic agents
        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic --;
            }
        }

    // populate Simple agents
    // ...

    // Note: you can reuse the generator
    }

//default constructor for game class
    Game::Game():__width(3), __height(3) {              //will make a __grid of 3 x 3
        for(int i = 0; i <(__width*__height);i++){
            __grid.push_back(nullptr);                  //will push null ptr to each element in the vector
        }
    }

// note: manual population by default
    Game::Game(unsigned width, unsigned height, bool manual):__width(width),__height(height) {
        for(int i = 0; i < __width * __height; i++) {
            __grid.push_back(nullptr);
        }
            if(!manual)
                populate();

    }

    //destructor for Game class
    Game::~Game() {

    }

    unsigned int Game::getNumPieces() const {
        return 0;
    }
}

