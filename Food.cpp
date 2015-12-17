//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include "Game.h"
#include "Resource.h"
#include "Food.h"

namespace Gaming {
    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) :
        Resource::Resource(g, p, capacity)
    {}

    Food::~Food(){

    }

    void Food::print(std::ostream &os) const {

    }

    double Food::consume(){
        return 0;
    }


    std::ostream &operator<<(std::ostream &os, const Food &f){
        os << f.getTypeID() << f.getID();
        return os;
    }

}
