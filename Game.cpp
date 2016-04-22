//
// Created by Brian on 4/7/2016.
//
#include "Gaming.h"
#include "Game.h"
#include "Simple.h"     //to find simple agents etc...
#include "Strategic.h"  //to find the strategic agents
#include "Food.h"
#include "Piece.h"
#include "Exceptions.h"
#include "Advantage.h"
#include<set>
#include<iomanip>

namespace Gaming{
    //provided by ivo from PA4 read me
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    PositionRandomizer Game::__posRandomizer = PositionRandomizer();


    //used for populating grid (used in automatic random initialization of a Game)
    void Game::populate() {
        // simple pseudo-random number generator
        // sufficient for our casual purposes
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height-1);

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
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);     //used strategic
                numStrategic --;
            }
        }
        //creates a variable called num simle
        //populate simple agents
        while(numSimple >0){
            int i = d(gen);                                                             //random index from the grid vector
            if(__grid[i] == nullptr){                                                   //is emptry equals nullptr
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);        //used simple
                numSimple--;
            }
        }
        // Note: you can reuse the generator

        while(numFood > 0){
            int i = d(gen);
            if(__grid[i] == nullptr){
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos,Game::STARTING_RESOURCE_CAPACITY);     //used food
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
    Game::Game() {
        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;
        __status = NOT_STARTED;
       // __verbose = false;
        //__round =0;
        //will make a __grid of 3 x 3
        for(int i = 0; i <(__width*__height);i++){
            __grid.push_back(nullptr);                                                  //will push null ptr to each element in the vector
        }
    }

// note: manual population by default
    Game::Game(unsigned width, unsigned height, bool manual) {
        if (width < MIN_WIDTH || height < MIN_HEIGHT)
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);

        __width = width;
        __height = height;
        __status = NOT_STARTED;
        //__verbose = false;
       // __round = 0;
        for(int i = 0; i < __width * __height; i++) {
            __grid.push_back(nullptr);
        }
        if(!manual)
            populate();

    }

    //destructor for Game class
    Game::~Game() {
        for(auto it = __grid.begin(); it != __grid.end();it++)
        {
            if(*it != nullptr)
                delete *it;
        }
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
        int location = y +(x* __width);         //will look for this location on the grid
        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[location] == nullptr)
            throw PositionEmptyEx(x, y);

        return __grid[location];                //returns the location on the grid
    }

    void Game::addSimple(const Position &position) {
        //exception for out of bounds
        int location = position.y + (position.x * __width);
        if(position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width){
            throw OutOfBoundsEx(__width,__height,position.x,position.y);
        }
        if(__grid[location])
            throw PositionNonemptyEx(position.x,position.y);
        __grid[location] = new Simple(*this, position,STARTING_AGENT_ENERGY);

    }

    void Game::addSimple(const Position &position, double energy) {
        //exception for out of bounds
        int location = position.y + (position.x * __width);
        if(position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width){
            throw OutOfBoundsEx(__width,__height,position.x,position.y);
        }
        if(__grid[location])
            throw PositionNonemptyEx(position.x,position.y);
        __grid[location] = new Simple(*this, position,energy);
    }

    void Game::addSimple(unsigned x, unsigned y) {
        //exception for out of bounds
        int location = y + (x * __width);
        if(x < 0 || x >= __width || y < 0 || y >= __height){
            throw OutOfBoundsEx(__width,__height,x,y);
        }
        if (__grid[location])
            throw PositionNonemptyEx(x, y);
        Position pos(x,y);
        __grid[location] = new Simple(*this, pos,STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy) {
        //exception for out of bounds

        Position pos(x,y);
        int location = y + (x * __width);
        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[location])
            throw PositionNonemptyEx(x, y);
        __grid[location] = new Simple(*this, pos,energy);
    }

    void Game::addStrategic(const Position &position, Strategy *s) {
        int location = position.y + (position.x * __width);
        if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
        throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[location])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[location] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        Position pos(x,y);
        int location = y + (x * __width);
        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[location])
            throw PositionNonemptyEx(x, y);
        __grid[location] = new Strategic(*this, pos, STARTING_AGENT_ENERGY,s);
    }

    void Game::addFood(const Position &position) {
        int location = position.y + (position.x * __width);
        if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[location])
            throw PositionNonemptyEx(position.x, position.y);
        __grid[location] = new Food(*this, position,STARTING_RESOURCE_CAPACITY);
    }

    void Game::addFood(unsigned x, unsigned y) {
        Position pos(x,y);
        int location = y + (x * __width);
        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[location])
            throw PositionNonemptyEx(x, y);
        __grid[location] = new Food(*this, pos,STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(const Position &position) {
        int location = position.y + (position.x * __width);
        if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[location])
            throw PositionNonemptyEx(position.x, position.y);
        __grid[location] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned x, unsigned y) {
        Position pos(x,y);
        int location = y +(x *__width);
        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[location])
            throw PositionNonemptyEx(x, y);
        __grid[location] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const {
        if(pos.x < 0 || pos.x >= __height || pos.y >= __width)
            throw OutOfBoundsEx(__width,__height,pos.x,pos.y);
        //todo  check why surround has no been initialized
        Surroundings surround;              // a array of class Surroundings

        //Todo Fill the array with empty members except for self whivh is at 4
        for(int i = 0; i < 9; i++){     //i is less than nine since theres only 8 elements
            if(i == 4){
                surround.array[i] = SELF;
            }
            else
                surround.array[i] = EMPTY;  //sets all elements to enum Empty
        }
        //Position search;                    //will search for a postion
        PieceType p;                            //what piece we will find
        int pos1, pos2, counter =0;
        //search.x = pos.x - 1;               // x and y that are passe into the function as pos
        //search.y = pos.y -1;
        for(int i = -1; i < 2;i++){          //will traverse the i colms and j the rows of the grid
            pos1 = pos.x + i;   //finds the x cordinate
            for(int j = -1; j < 2; j++) {
                pos2 = pos.y + j;       //will find the y cordinate
                //base condtion where the position is outside the grid
                if (pos1 < 0 || pos1 >= __height || pos2 < 0 || pos2 >= __width) {
                    surround.array[counter] = INACCESSIBLE;        //will set that position as inaccesible
                }
                else {
                    if (__grid[pos2 + (pos1 * __width)] && counter !=4) {
                        //base condition where it checks if that part of the grid has a object in it
                        p = __grid[pos2 + (pos1 * __width)]->getType();             //will get the type of piece or object that is at that part of the grid and will set that equal to our piece type variable p
                        surround.array[counter] = p;
                    }
                }
                counter++;      //will increment counter since the task did not find a move
            }
        }

        //todo check if this works
        return surround;                    //will return the Surroundings
    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        //base condition
        //if(from.x == to.x && from.y == to.y){
        if(from.x == to.x && from.y == to.y){
            return  STAY;       //means that the piece stayed
        }
        //WHERE THE PIECE MOVES (N,S,E,W,NE,NW,SE,SW)//////////////////
        //todo check which one works for N
        //if(to.x == from.x && to.y == from.y == to.y -1)
        //return N
        if(to.x == from.x -1 && to.y == from.y)
            return N;            //moved up one on grid
        else if(to.x == from.x+1 && to.y == from.y)
            return S;           //moved down one on grid
        else if(to.x == from.x && to.y == from.y+1)
            return E;           //moved right on the grid
        else if(to.x == from.x + 1 && to.y == from.y + 1)
            return SE;          //moved down one and right one on the grid
        else if(to.x == from.x-1 && to.y == from.y +1)
            return NE;          //moved up one and right one on the grid
        else if(to.x == from.x && to.y == from.y-1)
            return W;           //moved left one on the grid
        else if(to.x == from.x -1 && to.y == from.y - 1)
            return NW;           //moved up one and left one
        else if(to.x == from.x +1 && to.y == from.y -1)
            return SW;          //moved down one and left one on the grid
        ///////////END OF WHERE THE PiECE MOVES ON THE GRID////////////////
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        //exceptiond
        if (pos.x < 0 || pos.x >= __height || pos.y < 0 || pos.y >= __width)
            throw OutOfBoundsEx(__width, __height, pos.x, pos.y);
        Surroundings surround;
        surround = getSurroundings(pos);        //surround will be qual to the surroudings recieved from whats passed into th function pos
        bool isLeg = false;     //or maybe false IDK
        //todo switch statments or if statments where we will make each case in tha surrounds either true or false
        //PASS action type into the switch
        switch(ac){
            case N:
                if (surround.array[1] != INACCESSIBLE)
                    isLeg = true;
                break;
            case NE:
                if (surround.array[2] != INACCESSIBLE)
                    isLeg = true;
                break;
            case NW:
                if (surround.array[0] != INACCESSIBLE)
                    isLeg = true;
                break;
            case E:
                if (surround.array[5] != INACCESSIBLE)
                    isLeg = true;
                break;
            case W:
                if (surround.array[3] != INACCESSIBLE)
                    isLeg = true;
                break;
            case SE:
                if (surround.array[8] != INACCESSIBLE)
                    isLeg = true;
                break;
            case SW:
                if (surround.array[6] != INACCESSIBLE)
                    isLeg = true;
                break;
            case S:
                if (surround.array[7] != INACCESSIBLE)
                    isLeg = true;
                break;
            case STAY:
                isLeg = true;
                break;
        }
        //each case will be for what direction it moves in the switch statement
        //todo////
        return isLeg;                 //if its true or false
    }
    //we assume legal and use isLegal
    const Position Game::move(const Position &pos, const ActionType &ac) const {
        Position shino(pos.x, pos.y);
        if(isLegal(ac,pos)){
            switch(ac){
                //when it goes left its ++ and right its -- for x
                //y goes down when its ++ and goes up when --
                case N:
                    shino.x--;      //y goes up one
                    break;
                case NE:
                    shino.x--;      //y goes up one and right one
                    shino.y++;
                    break;
                case NW:
                    shino.y--;       //y goes up one and left one
                    shino.x--;
                    break;
                case W:
                    shino.y--;      //x gors lrft onr
                    break;
                case E:
                    shino.y++;      //x goes right one
                    break;
                case S:
                    shino.x++;      //y goes down one
                    break;
                case SE:
                    shino.y++;      //y goes down one and x goes righ one
                    shino.x++;
                    break;
                case SW:
                    shino.x++;      //y goes down and x goes left one
                    shino.y--;
                    break;
                case STAY:          //we leave STAY blank since the piece does not move ta all

                    break;

            }
        }
        return  shino; // dont forget to down throw
    }

    void Game::round() {
        //using the set example algorithm from the read me
        std::set<Piece*> board;
        Position pos, Newpos;
        ActionType action;
        Piece* pptr;
        int location;
        for (auto it = __grid.begin(); it < __grid.end(); ++it) {
            if (*it != nullptr) {
                board.insert(board.end(),*it);
                (*it)->setTurned(false);                                            //resets the pieces so that they can take a turn this will reset after each round
            }
        }
        for (auto it = board.begin(); it != board.end(); ++it) {
            if ((*it)->isViable()&& (*it)->getTurned()) {
                (*it)->age();
                (*it)->setTurned(true);
                pos = (*it)->getPosition();                                          //will pass a pieces position or location in
                action = (*it)->takeTurn(getSurroundings(pos));                     //piece takes a turn for each
                Newpos = this->move(pos, action);                                   //passes the new location into the new variabale
                location = Newpos.y + (Newpos.x * __width);
                pptr = __grid[location];
                if(pos.x != Newpos.x && pos.y != Newpos.y){                         //checks if new pos and the current pos arent n the same location
                    if (pptr != nullptr) {                                                  //this happens if the piece wants to move to annother spot hwere there is another piece in it soit will challnege or cosume if its a resource
                        (*(*it)* *pptr);                                            //this means that the pieces interact and we will pass some if statmnts
                     if ((*it)->isViable()) {                                    //if it didn't get consumed we pass it set new position
                        (*it)->setPosition(Newpos);
                        __grid[Newpos.y + (Newpos.x * __width)] = *it;                //will change the grid and set equal to it and also set it equal to nullptr
                        __grid[pos.y + (pos.x * __width)] = nullptr;
                    }
                    else {                                                      //when a resource gets consumed you set that location = to null ptr
                        __grid[pos.y + (pos.x * __width)] = nullptr;
                    }
                }
                }
                else {
                    __grid[Newpos.y + (Newpos.x * __width)] = *it;              //else to the other staments if the position is emoyty
                }
            }
        }
        for (int i = 0; i < __grid.size(); ++i) {
            //if (!__grid[i]->isViable() && __grid[i] != nullptr) {
            if(__grid[i] != nullptr && !__grid[i]->isViable()){
                delete __grid[i];
                __grid[i] = nullptr;
            }
        }
        if (getNumResources() == 0)
            this->__status = OVER;
        //we need to increment the round after it is over
        __round++;
    }

    void Game::play(bool verbose) {
        __status = PLAYING;             //returns the stauts that the game is playing
        __verbose = verbose;            //returns verbose when its verbose lol
        if(__verbose) {
            std::cout << this;          //will print out the location of the piece from the grid
        }
        while (__status != OVER) {
            round();                    //if the status of the game is not over the game will comtimue to play through
            if (__verbose)              //this will show what was going on the game when the game eas not over
                std::cout << *this;
        }
        if (__verbose)
            std::cout << this;          //this will print out the location aka the cordinates of the pieces when the game is finished
    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        //todo work on print
        int x = game.__width, y = game.__height;

        os << "Round: " << game.__round << std::endl;
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                if (game.__grid[j + (i * (game.__width - 1))] == nullptr)
                    os << "[     ]";
                else
                    os << std::setw(5) << game.__grid[j + (i * (game.__width - 1))] << "]";
            }
            os << std::endl;
        }
        os << "Status: " << game.getStatus() << std::endl;

        return os;
    }
}
