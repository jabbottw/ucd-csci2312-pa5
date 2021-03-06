//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include "Game.h"
#include "Piece.h"
#include "Resource.h"

namespace Gaming {

    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double __capacity) :
            Piece::Piece(g,p),
            __capacity(__capacity)
    {}

    Resource::~Resource(){

    }

    void Resource::age() {
        __capacity /= Resource::RESOURCE_SPOIL_FACTOR;
        if (__capacity < 0.0001){
            __capacity = 0;
        }
    }

    double Resource::consume(){
        return 0;
    }

    //enum PieceType { SIMPLE=0, STRATEGIC, FOOD, ADVANTAGE, INACCESSIBLE, SELF, EMPTY };
    ActionType Resource::takeTurn(const Surroundings &s) const {
        return ActionType::STAY;;
    }

    Piece &Resource::operator*(Piece &other)
    {
        Piece * p = &other;
        if (other.getType() == FOOD or other.getType() == ADVANTAGE){
            Resource *r = dynamic_cast<Resource*>(p);
            return this->interact(r);
        }
        return other;
    }

    Piece &Resource::interact(Agent *other)
    {
        return *this;
    }

    Piece &Resource::interact(Resource *)
    {
        return *this;
    }
}