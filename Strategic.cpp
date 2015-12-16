//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include "Game.h"
#include "Agent.h"
#include "Strategy.h"
#include "DefaultAgentStrategy.h"
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

    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        ActionType action;

        return action;
    }
}