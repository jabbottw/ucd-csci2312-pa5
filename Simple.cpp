//
// Created by Julian Abbott-Whitley on 12/15/15.
//


#include "Game.h"
#include "Agent.h"
#include "Simple.h"

namespace Gaming {
    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy) :
            Agent::Agent(g, p, energy)
    {}


    Simple::~Simple(){

    }



    void Simple::print(std::ostream &os) const{

    }


    //enum PieceType { SIMPLE=0, STRATEGIC, FOOD, ADVANTAGE, INACCESSIBLE, SELF, EMPTY };
    ActionType Simple::takeTurn(const Surroundings &s) const {
        if(Game::findResource(s) != ActionType::STAY){
            return Game::findResource(s);
        } else if (Game::findEmpty(s) != ActionType::STAY){
            return Game::findEmpty(s);
        } else {
            return ActionType::STAY;
        }
    }


    std::ostream &operator<<(std::ostream &os, const Simple &s){
        os << s.getTypeID() << s.getID();
        return os;
    }

}