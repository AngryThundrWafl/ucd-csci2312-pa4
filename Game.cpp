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
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantage = __numInitResources / 4;
        unsigned int numFood = __numInitResources - numAdvantage;

    // populate Strategic agents
        while (numStrategic > 0) {
            int i = d(gen);                                                             // random index in the grid vector
            if (__grid[i] == nullptr) {                                                 // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);     //used strategic
                numStrategic --;
            }
        }
                                                          //creates a variable called num simle
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

        while(numFood > 0){
            int i = d(gen);
            if(__grid[i] == nullptr){
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos,STARTING_RESOURCE_CAPACITY);     //used food
                numFood--;
            }
        }

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
        int location = x +(y* __width);         //will look for this location on the grid
        return __grid[location];                //returns the location on the grid
    }

    void Game::addSimple(const Position &position) {
        //exception for out of bounds
        if((position.x < 0 && position.x > getWidth()) || (position.y < 0 && position.y > getHeight())){
            throw OutOfBoundsEx(getWidth(),getHeight(),position.x,position.y);
        }
        int location = position.x + (position.y * __width);
        __grid[location] = new Simple(*this, position,STARTING_AGENT_ENERGY);

    }

    void Game::addSimple(const Position &position, double energy) {
        //exception for out of bounds
        if((position.x < 0 && position.x > getWidth()) || (position.y < 0 && position.y > getHeight())){
            throw OutOfBoundsEx(getWidth(),getHeight(),position.x,position.y);
        }
        int location = position.x + (position.y * __width);
        __grid[location] = new Simple(*this, position,energy);
    }

    void Game::addSimple(unsigned x, unsigned y) {
        //exception for out of bounds
        if((x < 0 && x > getWidth()) || (y < 0 && y > getHeight())){
            throw OutOfBoundsEx(getWidth(),getHeight(),x,y);
        }
        Position pos(x,y);
        int location = x + (y * __width);
        __grid[location] = new Simple(*this, pos,STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy) {
        //exception for out of bounds
        if((x < 0 && x > getWidth()) || (y < 0 && y > getHeight())){
            throw OutOfBoundsEx(getWidth(),getHeight(),x,y);
        }
        Position pos(x,y);
        int location = x + (y * __width);
        __grid[location] = new Simple(*this, pos,energy);
    }

    void Game::addStrategic(const Position &position, Strategy *s) {
        int location = position.x + (position.y * __width);
        __grid[location] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        Position pos(x,y);
        int location = x + (y * __width);
        __grid[location] = new Strategic(*this, pos, STARTING_AGENT_ENERGY,s);
    }

    void Game::addFood(const Position &position) {
        int location = position.x + (position.y * __width);
        __grid[location] = new Food(*this, position,STARTING_RESOURCE_CAPACITY);
    }

    void Game::addFood(unsigned x, unsigned y) {
        Position pos(x,y);
        int location = x + (y * __width);
        __grid[location] = new Food(*this, pos,STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(const Position &position) {
        int location = position.x + (position.y * __width);
        __grid[location] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned x, unsigned y) {
        Position pos(x,y);
        int location = x +(y *__width);
        __grid[location] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const {
        Surroundings surround;              // a array of class Surroundings
        //Todo implement Surroundings
        //Todo Fill the array with empty members except for self whivh is at 4

        return surround;                    //will return the Surroundings
    }
}

