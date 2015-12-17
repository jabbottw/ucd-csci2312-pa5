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

    ActionType get_sIndexDirection(int i){
        //enum ActionType { N=0, NE, NW, E, W, SE, SW, S, STAY };
        switch (i){
            case 0 : return ActionType::NE;
            case 1 : return ActionType::N;
            case 2 : return ActionType::NW;
            case 3 : return ActionType::W;
            case 4 : return ActionType::STAY;
            case 5 : return ActionType::E;
            case 6 : return ActionType::SW;
            case 7 : return ActionType::S;
            case 8 : return ActionType::SE;
            default: return ActionType::STAY;
        }
    }

    ActionType findResource(const Surroundings &s) {
        for (int i = 0; i < 9; i++){
            if (i != 4){
                if (s.array[i] == PieceType::FOOD or s.array[i] == PieceType::ADVANTAGE){
                    return get_sIndexDirection(i);
                } else {
                    return ActionType::STAY;
                }
            }
        }
    }

    ActionType findEmpty(const Surroundings &s) {
        for (int i = 0; i < 9; i++){
            if (i != 4){
                if (s.array[i] == PieceType::EMPTY){
                    return get_sIndexDirection(i);
                } else {
                    return ActionType::STAY;
                }
            }
        }
    }

    //enum PieceType { SIMPLE=0, STRATEGIC, FOOD, ADVANTAGE, INACCESSIBLE, SELF, EMPTY };
    ActionType Simple::takeTurn(const Surroundings &s) const {

        if(findResource(s) != ActionType::STAY){
            return findResource(s);
        } else if (findEmpty(s) != ActionType::STAY){
            return findEmpty(s);
        } else {
            return ActionType::STAY;
        }
    }


    std::ostream &operator<<(std::ostream &os, const Simple &s){
        os << s.getTypeID() << s.getID();
        return os;
    }

}