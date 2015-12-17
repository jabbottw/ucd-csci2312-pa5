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

    ActionType Simple::takeTurn(const Surroundings &s) const {

        ActionType action;

        return action;
    }

    std::ostream &operator<<(std::ostream &os, const Simple &s){
        os << s.getTypeID() << s.getID();
        return os;
    }

}