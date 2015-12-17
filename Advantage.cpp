//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include <iostream>
#include "Piece.h"
#include "Resource.h"
#include "Advantage.h"

namespace Gaming {

    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 0.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity) :
            Resource::Resource(g, p, capacity)
    {}

    Advantage::~Advantage(){

    }

    void Advantage::print(std::ostream &os) const{

    }

    double Advantage::getCapacity() const{
        return 0;
    }


    double Advantage::consume() {
        return 0;
    }


    std::ostream &operator<<(std::ostream &os, const Advantage &a){
        os << a.getTypeID() << a.getID();
        return os;
    }

}