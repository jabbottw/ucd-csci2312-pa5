//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include "Game.h"
#include "Piece.h"
#include "Resource.h"

namespace Gaming {

    Resource::Resource(const Game &g, const Position &p, double __capacity) :
            Piece::Piece(g,p),
            __capacity(__capacity)
    {}

    Resource::~Resource(){

    }

    void Resource::age() {

    }

    double Resource::consume(){
        return 0;
    }


    ActionType Resource::takeTurn(const Surroundings &s) const {
        ActionType a = N;
        return a;
    }

    Piece &Resource::operator*(Piece &other)
    {
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