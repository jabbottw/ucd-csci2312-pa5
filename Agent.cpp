//
// Created by Julian Abbott-Whitley on 12/15/15.
//


#include "Piece.h"
#include "Agent.h"
#include "Resource.h"
#include "Advantage.h"


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

        Piece * p = &other;
        if (other.getType() == SIMPLE or other.getType() == STRATEGIC){
            Agent *a = dynamic_cast<Agent*>(p);
            return this->interact(a);
        } else if (other.getType() == FOOD or other.getType() == ADVANTAGE) {
            Resource *r = dynamic_cast<Resource *>(p);
            return this->interact(r);
        }
        return other;
    }

    Piece &Agent::interact(Agent * other)
    {
        if (this->__energy == other->__energy)
        {
            this->finish();
            other->finish();
        } else if (this->__energy > other->__energy){
            this->__energy -= other->__energy;
            other->finish();
        } else if (other->__energy > this->__energy){
            other->__energy -= this->__energy;
            this->finish();
        }
        return *this;
    }

    Piece &Agent::interact(Resource * r)
    {
        if(r->getType() == FOOD){
            this->__energy += r->getCapacity();
        } else if (r->getType() == ADVANTAGE){
            this->__energy += r->getCapacity() * Advantage::ADVANTAGE_MULT_FACTOR;
        }
        return *this;
    }

    void Agent::age(){
        __energy -= Agent::AGENT_FATIGUE_RATE;
    }
}
