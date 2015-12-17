//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include "Game.h"
#include "Agent.h"
#include "Strategy.h"
#include "DefaultAgentStrategy.h"
#include "Gaming.h"
#include "Strategic.h"

namespace Gaming {
    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) :
    Agent::Agent(g, p, energy),
    __strategy(s)
    {}

    Strategic::~Strategic()
    {
        delete __strategy;
    }

    void Strategic::print(std::ostream &os) const
    {
        os << STRATEGIC_ID << __id;
    }




    //enum PieceType { SIMPLE=0, STRATEGIC, FOOD, ADVANTAGE, INACCESSIBLE, SELF, EMPTY };
    ActionType Strategic::takeTurn(const Surroundings &s) const {

        if(Game::findResource(s) != ActionType::STAY){
            return Game::findResource(s);
        } else if (Game::findEmpty(s) != ActionType::STAY){
            return Game::findEmpty(s);
        } else {
            return ActionType::STAY;
        }
    }


    std::ostream &operator<<(std::ostream &os, const Strategic &s){
        os << s.getTypeID() << s.getID();
        return os;
    }

}