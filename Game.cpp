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

namespace Gaming {
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    PositionRandomizer Game::__posRandomizer = PositionRandomizer();

    void Game::populate() {

        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;
        //random number generator
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height -1);

        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        while (numSimple > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        while (numAdvantages > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        while (numFoods > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }


    }

    Game::Game() {
        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;
        __status = NOT_STARTED;

        int size = __width * __height;
        for (int i = 0; i < size; ++i)
            __grid.push_back(nullptr);

    }

    Game::Game(unsigned width, unsigned height, bool manual) {
        if (width < MIN_WIDTH || height < MIN_HEIGHT)
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);

        __width = width;
        __height = height;
        __status = NOT_STARTED;

        int size = __width * __height;
        for (int i = 0; i < size; ++i)
            __grid.push_back(nullptr);

        if (!manual)
            populate();
    }

    Game::~Game() {
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
            if (*it != nullptr)
                delete *it;
    }

    unsigned int Game::getNumPieces() const {
        int num = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
            if (*it != nullptr)
                ++num;

        return num;
    }

    unsigned int Game::getNumAgents() const {
        int num = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Agent *agent = dynamic_cast<Agent*>(*it);

            if (agent) ++num;
        }

        return num;
    }

    unsigned int Game::getNumSimple() const {
        int num = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Simple *simple = dynamic_cast<Simple*>(*it);

            if (simple) ++num;
        }

        return num;
    }

    unsigned int Game::getNumStrategic() const {
        int num = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Strategic *strategic = dynamic_cast<Strategic*>(*it);

            if (strategic) ++num;
        }

        return num;
    }

    unsigned int Game::getNumResources() const {
        int num = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Resource *resource = dynamic_cast<Resource*>(*it);

            if (resource) ++num;
        }

        return num;
    }

    const Piece* Game::getPiece(unsigned int x, unsigned int y) const {
        int place = y + (x * __width);

        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[place] == nullptr)
            throw PositionEmptyEx(x, y);

        return __grid[place];
    }

    // grid population methods
    void Game::addSimple(const Position& position) {
        int place = position.y + (position.x * __width);

        if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        if (__grid[place])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[place] = new Simple(*this, position, STARTING_AGENT_ENERGY);

    }

    void Game::addSimple(const Position& position, double energy) {
        int place = position.y + (position.x * __width);

        if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        if (__grid[place])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[place] = new Simple(*this, position, energy);
    }

    void Game::addSimple(unsigned x, unsigned y) {
        Position p(x, y);
        int place = y + (x * __width);

        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[place])
            throw PositionNonemptyEx(x, y);

        __grid[place] = new Simple(*this, p, STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy) {
        Position p(x, y);
        int place = y + (x * __width);

        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[place])
            throw PositionNonemptyEx(x, y);

        __grid[place] = new Simple(*this, p, energy);
    }

    void Game::addStrategic(const Position& position, Strategy* s) {
        int place = position.y + (position.x * __width);

        if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        if (__grid[place])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[place] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy* s) {
        Position p(x, y);
        int place = y + (x * __width);

        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[place])
            throw PositionNonemptyEx(x, y);

        __grid[place] = new Strategic(*this, p, STARTING_AGENT_ENERGY, s);
    }

    void Game::addFood(const Position& position) {
        int place = position.y + (position.x * __width);

        if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        if (__grid[place])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[place] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addFood(unsigned x, unsigned y) {
        Position p(x, y);
        int place = y + (x * __width);

        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[place])
            throw PositionNonemptyEx(x, y);

        __grid[place] = new Food(*this, p, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(const Position& position) {
        int place = position.y + (position.x * __width);

        if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        if (__grid[place])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[place] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned x, unsigned y) {
        Position p(x, y);
        int place = y + (x * __width);

        if (x < 0 || x >= __height || y < 0 || y >= __width)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[place])
            throw PositionNonemptyEx(x, y);

        __grid[place] = new Advantage(*this, p, STARTING_RESOURCE_CAPACITY);
    }

    const Surroundings Game::getSurroundings(const Position& pos) const {
        if (pos.x < 0 || pos.x >= __height || pos.y < 0 || pos.y >= __width)
            throw OutOfBoundsEx(__width, __height, pos.x, pos.y);

        Surroundings s; //makes an array

        for (int i = 0; i < 9; ++i) { //fill array
            if (i == 4)
                s.array[4] = SELF; //puts self in the middle
            else
                s.array[i] = EMPTY;
        }

        int x, y, i = 0;
        PieceType type;

        for (int row = -1; row < 2; ++row) {//position x
            x = pos.x + row;
            for (int col = -1; col < 2; ++col) {//position y
                y = pos.y + col;

                if (x < 0 || x >= __height || y < 0 || y >= __width)
                    s.array[i] = INACCESSIBLE;
                else {
                    if (__grid[y + (x * __width)] && i != 4) {
                        type = __grid[y + (x * __width)]->getType();
                        s.array[i] = type;
                    }
                }

                ++i;
            }
        }

        return s;
    }

    const ActionType Game::reachSurroundings(const Position& from, const Position& to) {
        if (from.x == to.x && from.y == from.x)
            return STAY;

        if (to.x == from.x - 1 && to.y == from.y - 1)
            return NW;
        else if (to.x == from.x -1 && to.y == from.y)
            return N;
        else if (to.x == from.x - 1 && to.y == from.y + 1)
            return NE;
        else if (to.x == from.x && to.y == from.y-1)
            return W;
        else if (to.x == from.x && to.y == from.y + 1)
            return E;
        else if (to.x == from.x + 1 && to.y == from.y - 1)
            return SW;
        else if (to.x == from.x + 1 && to.y == from.y)
            return S;
        else if (to.x == from.x + 1 && to.y == from.y + 1)
            return SE;
    }

    bool Game::isLegal(const ActionType& ac, const Position& pos) const {
        if (pos.x < 0 || pos.x >= __height || pos.y < 0 || pos.y >= __width)
            throw OutOfBoundsEx(__width, __height, pos.x, pos.y);

        Surroundings s;
        s = getSurroundings(pos);
        bool legal = false;

        switch (ac) {
            case N:
                if (s.array[1] != INACCESSIBLE) legal = true;
                break;
            case NE:
                if (s.array[2] != INACCESSIBLE) legal = true;
                break;
            case NW:
                if (s.array[0] != INACCESSIBLE) legal = true;
                break;
            case E:
                if (s.array[5] != INACCESSIBLE) legal = true;
                break;
            case W:
                if (s.array[3] != INACCESSIBLE) legal = true;
                break;
            case SE:
                if (s.array[8] != INACCESSIBLE) legal = true;
                break;
            case SW:
                if (s.array[6] != INACCESSIBLE) legal = true;
                break;
            case S:
                if (s.array[7] != INACCESSIBLE) legal = true;
                break;
            case STAY:
                legal = true;
                break;
        }

        return legal;
    }

    const Position Game::move(const Position& pos, const ActionType& ac) const {

        Position p(pos.x, pos.y);

        if (isLegal(ac, pos)) {

            switch (ac) {
                case N:
                    p.x--;
                    break;
                case NE:
                    p.x--;
                    p.y++;
                    break;
                case NW:
                    p.x--;
                    p.y--;
                    break;
                case W:
                    p.y--;
                    break;
                case E:
                    p.y++;
                    break;
                case S:
                    p.x++;
                    break;
                case SE:
                    p.x++;
                    p.y++;
                    break;
                case SW:
                    p.x++;
                    p.y--;
                    break;
                case STAY:
                    //nothing because we are staying
                    break;

            }

        }


        return p;
    }

    void Game::round() {
        std::set<Piece*> board;
        Position pos, New;
        ActionType move;
        Piece* pptr;
        int place;

        for (auto it = __grid.begin(); it < __grid.end(); ++it) {
            if (*it != nullptr) {
                board.insert(board.end(), *it);
                (*it)->setTurned(false);//resets the pieces of not doing turn yet
            }
        }

        for (auto it = board.begin(); it != board.end(); ++it) {

            if ((*it)->isViable() && (*it)->getTurned()) {
                (*it)->age();
                (*it)->setTurned(true);

                pos = (*it)->getPosition();//puts pieces position in a variable
                move = (*it)->takeTurn(getSurroundings(pos)); //takes the pieces turn

                New = this->move(pos, move);//get's the new position of the piece
                place = New.y + (New.x * __width);

                pptr = __grid[place];
                if (pos.x != New.x && pos.y != New.y) {
                    if (pptr != nullptr) {//there is a piece at position it wants to move

                        (*(*it) * *pptr);//the pieces interact

                        if ((*it)->isViable()) {//didn't get consumed
                            (*it)->setPosition(New);

                            //change the board
                            __grid[New.y + (New.x * __width)] = *it;
                            __grid[pos.y + (pos.x * __width)] = nullptr;
                        }
                        else {//piece got consumed
                            __grid[pos.y + (pos.x * __width)] = nullptr;
                        }
                    }
                    else {//space is empty
                        __grid[New.y + (New.x * __width)] = *it;
                    }
                }
            }
        }//end of the loop

        for (int i = 0; i < __grid.size(); ++i) {
            if (__grid[i] != nullptr && !__grid[i]->isViable()) {
                delete __grid[i];
                __grid[i] = nullptr;
            }
        }

        if (getNumResources() == 0)
            this->__status = OVER;

        ++__round;
    }

    void Game::play(bool verbose) {
        __status = PLAYING;
        //verbose means to show what's going on
        __verbose = verbose;

        //print starting corridants of pieces
        if(__verbose)
            std::cout << this;

        while (__status != OVER) {//start the game!!!
            round();

            if (__verbose)//if true shows the host what is going on in the game
                std::cout << *this;
        }

        //print final corrdinants of piecs
        if (__verbose)
            std::cout << this;
    }

    std::ostream& operator<<(std::ostream& os, const Game& game) {
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