//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include <iostream>
#include <vector>
#include <array>

#include "Gaming.h"
#include "Game.h"
#include "Exceptions.h"
#include "Strategic.h"
#include "Simple.h"
#include "Food.h"
#include "Advantage.h"
#include "DefaultAgentStrategy.h"

namespace Gaming {

    // Static Member variables
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;


    // Static Class Variables
    const unsigned Game::MIN_WIDTH = 3, Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    Game::Game() :
        __width(Game::MIN_WIDTH),
        __height(Game::MIN_HEIGHT),
        __grid(__width*__height, nullptr),
        __verbose(true),
        __round(0)
    {}

    Game::Game(unsigned width, unsigned height, bool manual) : __grid(width*height, nullptr) {
        if (width < Game::MIN_WIDTH or height < MIN_HEIGHT){
            throw InsufficientDimensionsEx(Game::MIN_WIDTH, Game::MIN_HEIGHT, width, height);
        } else {
            __width = width;
            __height = height;
            __verbose = manual;
            __round = 0;
            if (!manual){
                populate();
            }
        }
    }

    Game::Game(const Game &another) :
            __grid(another.getWidth() * another.getHeight(), nullptr),
            __width(another.getWidth()),
            __height(another.getHeight()),
            __round(another.getRound())
    {}

    Game::~Game(){

    }

    // X = Rows, Y = Columns
    int xyToGridIndex(int x, int y, int m){
        int i = (x*m) + y;
        return i;
    }


    void Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);

        // populate Strategic agents
        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position position(i / __width, i % __width);
                __grid[i] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        // populate Simple agents
        while (numSimple > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position position(i / __width, i % __width);
                __grid[i] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        // populate Advantages agents
        while (numAdvantages > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position position(i / __width, i % __width);
                __grid[i] = new Advantage(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        // populate Food agents
        while (numFoods > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position position(i / __width, i % __width);
                __grid[i] = new Food(*this, position, Game::STARTING_AGENT_ENERGY);
                numFoods--;
            }
        }
    }

    unsigned int Game::getNumPieces() const {
        int count = 0;
        for (int i = 0; i < this->__grid.size(); i++)    {
            if (__grid[i] != nullptr){
                count++;
            }
        }
        return count;
    }
    unsigned int Game::getNumAgents() const {
        int count = 0;
        for (int i = 0; i < this->__grid.size(); i++)    {
            if (__grid[i] != nullptr){
                if (__grid[i]->getTypeID() == 'S' or __grid[i]->getTypeID() == 'T') {
                    count++;
                }
            }
        }
        return count;
    }
    unsigned int Game::getNumSimple() const {
        int count = 0;
        for (int i = 0; i < this->__grid.size(); i++) {
            if (__grid[i] != nullptr) {
                if (__grid[i]->getTypeID() == 'S') {
                    count++;
                }
            }
        }
        return count;
    }

    unsigned int Game::getNumStrategic() const {
        int count = 0;
        for (int i = 0; i < this->__grid.size(); i++) {
            if (__grid[i] != nullptr) {
                if (__grid[i]->getTypeID() == 'T') {
                    count++;
                }
            }
        }
        return count;
    }

    unsigned int Game::getNumResources() {
        int count = 0;
        for (int i = 0; i < this->__grid.size(); i++)    {
            if (__grid[i] != nullptr){
                if (__grid[i]->getTypeID() == 'F' or __grid[i]->getTypeID() == 'D') {
                    count++;
                }
            }
        }
        return count;
    }


    bool Game::addSimple(const Position &position){
        int i = xyToGridIndex(position.x, position.y, this->__width);
        if (__grid[i] == nullptr) {
            __grid[i] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
            return true;
        } else {
            return false;
        }
    }
    bool Game::addSimple(unsigned x, unsigned y) {
        int i = xyToGridIndex(x, y, this->__width);
        if (__grid[i] == nullptr) {
            Position position(x, y);
            __grid[i] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
            return true;
        } else {
            return false;
        }
    }

    bool Game::addStrategic(const Position &position, Strategy *s){
        if (position.x > MIN_HEIGHT or position.y > Game::MIN_WIDTH) {
            throw OutOfBoundsEx(Game::MIN_WIDTH, Game::MIN_HEIGHT, position.y, position.x);
        } else {
            int i = xyToGridIndex(position.x, position.y, this->__width);
            if (__grid[i] == nullptr) {
                __grid[i] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);
                return true;
            } else {
                return false;
            }
        }
    }

    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s ){
        if (x > MIN_HEIGHT or y > Game::MIN_WIDTH) {
            throw OutOfBoundsEx(Game::MIN_WIDTH, Game::MIN_HEIGHT, y, x);
        } else {
            int i = xyToGridIndex(x, y, this->__width);
            if (__grid[i] == nullptr) {
                Position position(x, y);
                __grid[i] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);
                return true;
            } else {
                return false;
            }
        }
        return false;
    }
    bool Game::addFood(const Position &position){
        int i = xyToGridIndex(position.x, position.y, this->__width);
        if (__grid[i] == nullptr) {
            __grid[i] = new Food(*this, position, Game::STARTING_AGENT_ENERGY);
            return true;
        } else {
            return false;
        }
    }

    bool Game::addFood(unsigned x, unsigned y){
        int i = xyToGridIndex(x, y, this->__width);
        if (__grid[i] == nullptr) {
            Position position(x, y);
            __grid[i] = new Food(*this, position, Game::STARTING_AGENT_ENERGY);
            return true;
        } else {
            return false;
        }
    }

    bool Game::addAdvantage(const Position &position){
        int i = xyToGridIndex(position.x, position.y, this->__width);
        if (position.x > MIN_HEIGHT or position.y > Game::MIN_WIDTH) {
            throw OutOfBoundsEx(Game::MIN_WIDTH, Game::MIN_HEIGHT, position.y, position.x);
        } else {
            if (__grid[i] == nullptr) {
                __grid[i] = new Advantage(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                return true;
            } else {
                return false;
            }
        }
    }

    bool Game::addAdvantage(unsigned x, unsigned y){
        if (x > MIN_HEIGHT or y > Game::MIN_WIDTH) {
            throw OutOfBoundsEx(Game::MIN_WIDTH, Game::MIN_HEIGHT, y, x);
        } else {
            int i = xyToGridIndex(x, y, this->__width);
            if (__grid[i] == nullptr) {
                Position position(x, y);
                __grid[i] = new Advantage(*this, position, Game::STARTING_RESOURCE_CAPACITY);
                return true;
            } else {
                return false;
            }
        }
    }

    const Surroundings Game::getSurroundings(const Position &pos) const{
        Surroundings s;
        return s;
    }

    // Print as follows the state of the game after the last round:
    //
    // Round 1:
    // [F0   ][     ][T1   ]
    // [W2   ][     ][F3   ]
    // [     ][S4   ][     ]
    // Status: Playing...
    //
    // Round 5:
    // [     ][     ][     ]
    // [     ][T1   ][     ]
    // [     ][     ][     ]
    // Status: Over!
    //
    std::ostream &operator<<(std::ostream &os, const Game &game){
        auto gridXY = game.__grid.begin();
        os << "Round " << game.getRound();
        for (int i = 0; i < game.getHeight(); i++){
            os << std::endl;
            for (int j = 0; j < game.getWidth(); j++){
                if (*gridXY == nullptr){
                    os << "[     ]";
                } else {
                    int x = (*gridXY)->getType();
                    os << "[" << (*gridXY)->getTypeID() << (*gridXY)->getID() << "]";
                }
                gridXY++;
            }
        }
        os << std::endl << "Status:";
        return os;
    }

}