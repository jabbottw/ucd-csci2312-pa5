//
// Created by Julian Abbott-Whitley on 12/15/15.
//


#include "Piece.h"
#include "Agent.h"


namespace Gaming {
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy):
            Piece::Piece(g,p),
            __energy(energy)
    {}

    Agent::~Agent()
    {

    }

    Piece &Agent::operator*(Piece &other)
    {
        return other;
    }

    Piece &Agent::interact(Agent *other)
    {
        return *this;
    }

    Piece &Agent::interact(Resource *)
    {
        return *this;
    }

    void Agent::age(){
        __energy -= Agent::AGENT_FATIGUE_RATE;
    }
}
