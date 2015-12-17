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
        int i = 0;
        if (x >= 0 and y >= 0){
            i = (x*m) + y;
        } else if (x < 0){
            i = -1;
        } else if (y < 0){
            i = -1;
        }
        return i;
    }

    bool cellAccessible(int x, int y, const Game &g){
        if (x >= g.getWidth() or x < 0 or y >= g.getHeight() or y < 0){
            return false;
        } else {
            return true;
        }
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
        if (x > __height or y > __width) {
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

    //enum PieceType { SIMPLE=0, STRATEGIC=1, FOOD=2, ADVANTAGE=3, INACCESSIBLE=4, SELF=5, EMPTY=6 };
    PieceType Game::getPieceEncoding(char x){
        switch (x) {
            case 'S': return PieceType(SIMPLE);
            case 'T': return PieceType(STRATEGIC);
            case 'F': return PieceType(FOOD);
            case 'D': return PieceType(ADVANTAGE);
            case 'I': return PieceType(INACCESSIBLE);
            case 'X': return PieceType(SELF);
            case 'E': return PieceType(EMPTY);
            default: return PieceType(EMPTY);
        }
    }


    ActionType Game::get_sIndexDirection(int i) {
        //enum ActionType { N=0, NE, NW, E, W, SE, SW, S, STAY };
        switch (i) {
            case 0 :
                return ActionType::NW;
            case 1 :
                return ActionType::N;
            case 2 :
                return ActionType::NE;
            case 3 :
                return ActionType::W;
            case 4 :
                return ActionType::STAY;
            case 5 :
                return ActionType::E;
            case 6 :
                return ActionType::SW;
            case 7 :
                return ActionType::S;
            case 8 :
                return ActionType::SE;
            default:
                return ActionType::STAY;
        }
    }

    ActionType Game::findResource(const Surroundings &s) {
        for (int i = 0; i < 9; i++) {
            if (i != 4) {
                if (s.array[i] == PieceType::ADVANTAGE) {
                    return get_sIndexDirection(i);
                }
            }
        }
        for (int i = 0; i < 9; i++) {
            if (i != 4) {
                if (s.array[i] == PieceType::FOOD) {
                    return get_sIndexDirection(i);
                }
            }
        }
        return ActionType::STAY;
    }

    ActionType Game::findEmpty(const Surroundings &s) {
        for (int i = 0; i < 9; i++) {
            if (i != 4) {
                if (s.array[i] == PieceType::EMPTY) {
                    return get_sIndexDirection(i);
                }
            }
        }
        return ActionType::STAY;
    }




    const Surroundings Game::getSurroundings(const Position &pos) const{
        Surroundings surroundings;
        int sIndex = 0;
        int adjacentCellIndex = 0;
        for (int i = -1; i <= 1; i++){
            for (int j = -1; j <= 1; j++){
                if (i == 0 && j == 0)
                {
                    surroundings.array[sIndex++] = PieceType(SELF);
                } else {
                    adjacentCellIndex = xyToGridIndex(pos.x + i, pos.y + j, this->__width);
                    if (adjacentCellIndex < 0){
                        surroundings.array[sIndex++] = PieceType(INACCESSIBLE);
                    } else if (pos.x + i >= this->__height or pos.y + j >= this->__width){
                        surroundings.array[sIndex++] = PieceType(INACCESSIBLE);
                    } else if (__grid[adjacentCellIndex] == nullptr){
                        surroundings.array[sIndex++] = PieceType(EMPTY);
                    } else {
                        PieceType p = getPieceEncoding(__grid[adjacentCellIndex]->getTypeID());
                        surroundings.array[sIndex++] = p;
                    }
                }
            }
        }
        return surroundings;
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

    const ActionType Game::reachSurroundings(const Position &from, const Position &to){
        return ActionType::N;
    }


    bool Game::isLegal(const ActionType &ac, const Position &pos) const{
        switch (ac){
            case ActionType::N :
                return cellAccessible(pos.x - 1, pos.y, *this);
            case ActionType::NE :
                return cellAccessible(pos.x - 1, pos.y + 1, *this);
            case ActionType::NW :
                return cellAccessible(pos.x - 1, pos.y - 1, *this);
            case ActionType::W :
                return cellAccessible(pos.x, pos.y -1, *this);
            case ActionType::STAY :
                return cellAccessible(pos.x, pos.y, *this);
            case ActionType::E :
                return cellAccessible(pos.x, pos.y + 1, *this);
            case ActionType::SW :
                return cellAccessible(pos.x + 1, pos.y + 1, *this);
            case ActionType::SE :
                return cellAccessible(pos.x + 1, pos.y - 1, *this);
            case ActionType::S :
                return cellAccessible(pos.x + 1, pos.y, *this);
            default:
                return false;
        }
    }

    // note: assumes legal, use with isLegal()
    const Position Game::move(const Position &pos, const ActionType &ac) const{
        return pos;
    }

    // play a single round
    void Game::round(){

    }

    // play game until over
    void Game::play(bool verbose){

    }

}