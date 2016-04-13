//
// Created by Brian on 4/7/2016.
//

#include "Game.h"
#include "Simple.h"     //to find simple agents etc...
#include "Strategic.h"  //to find the strategic agents
#include "Food.h"
#include "Advantage.h"

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
        int numStrategic = (int)((__width * __height) / NUM_INIT_AGENT_FACTOR / 2.0);   //calculates num strategic agents

    // populate Strategic agents
        while (numStrategic > 0) {
            int i = d(gen);                                                             // random index in the grid vector
            if (__grid[i] == nullptr) {                                                 // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);     //used strategic
                numStrategic --;
            }
        }
        int numSimple = numStrategic;                                                   //creates a variable called num simle
    //populate simple agents
        while(numSimple >0){
            int i = d(gen);                                                             //random index from the grid vector
            if(__grid[i] == nullptr){                                                   //is emptry equals nullptr
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);        //used simple
                numSimple--;
            }
        }
    // Note: you can reuse the generator
        int numFood = ((__width * __height) / NUM_INIT_RESOURCE_FACTOR / 2);
        while(numFood > 0){
            int i = d(gen);
            if(__grid[i] == nullptr){
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos,STARTING_RESOURCE_CAPACITY);     //used food
                numFood--;
            }
        }
        int numAdvantage = numFood;
        while(numAdvantage > 0){
            int i = d(gen);
            if(__grid[i] == nullptr){
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY); //used Resource
                numAdvantage--;
            }
        }
    }
//shiek
//default constructor for game class
    Game::Game():__width(3), __height(3) {                                               //will make a __grid of 3 x 3
        for(int i = 0; i <(__width*__height);i++){
            __grid.push_back(nullptr);                                                  //will push null ptr to each element in the vector
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

    //will search the whole board of pieces
    unsigned int Game::getNumPieces() const {
        //used the num grt simple function but instead used if statment to for spots that arent nullptr
          unsigned int numPieces = 0;                                                   //will kepp count of how many pieces we have

            for (auto it = __grid.begin(); it != __grid.end(); ++it) {
                if(*it != nullptr){                                                     //if *it is not equal to nullptr then we increment numPieces since thats populated by a piece
                    numPieces++;                                                        //increment
                }
            }
            return numPieces;                                                           //after all ietrations we return the number of pieces
        }

    //will get the amoutn of agents on the board
    unsigned int Game::getNumAgents() const {
       unsigned int numAgents = 0;

        for(auto it = __grid.begin(); it != __grid.end(); it++){
            Agent *agent = dynamic_cast<Agent*>(*it);
            if(agent) numAgents++;
        }
        return numAgents;
    }

    //gets the amounnt of simple agents on the board
    unsigned int Game::getNumSimple() const {
        // dynamic_cast returns a pointer of the argument type
// or NULL if the derived type of the object is not of
// the argument type

        unsigned int numSimple = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Simple *simple = dynamic_cast<Simple*>(*it);
            if (simple) numSimple ++;
        }

        return numSimple;

    }


    unsigned int Game::getNumStrategic() const {
        unsigned int numStrategic = 0;
        for(auto it = __grid.begin(); it != __grid.end(); ++it){
            Strategic *strategic = dynamic_cast<Strategic*>(*it);
            if(strategic) numStrategic++;
        }
        return numStrategic;
    }

    unsigned int Game::getNumResources() const {
        unsigned int numResource = 0;
        for(auto it = __grid.begin(); it != __grid.end(); it++){
            Resource *resource = dynamic_cast<Resource*>(*it);
            if(resource) numResource++;
        }
        return numResource;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const {
        //TODO would i return the piece that is at that location??
    }
}

