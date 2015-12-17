//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include <string>

#include "Game.h"
#include "Piece.h"

namespace Gaming {
    unsigned int Piece::__idGen = 0;

    Piece::Piece(const Game &g, const Position &p) :
            __game(g),
            __id(__idGen++),
            __finished(false)
    {}


    Piece::~Piece(){

    }


    std::ostream &operator<<(std::ostream &os, const Piece &p){
        os << p.getTypeID() << p.getID();
        return os;
    }

}