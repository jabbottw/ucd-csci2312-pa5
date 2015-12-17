//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include <iostream>
#include "Strategy.h"
#include "DefaultAgentStrategy.h"
#include "Game.h"


namespace Gaming {

    DefaultAgentStrategy::DefaultAgentStrategy() {}
    DefaultAgentStrategy::~DefaultAgentStrategy() {}
    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        if (Game::findSimple(s) != ActionType::STAY) {
            return Game::findSimple(s);
        } else if(Game::findAdvantage(s) != ActionType::STAY){
            return Game::findAdvantage(s);
        } else if (Game::findFood(s) != ActionType::STAY) {
            return Game::findFood(s);
        } else if (Game::findEmpty(s) != ActionType::STAY) {
            return Game::findEmpty(s);
        } else if (Game::findSimple(s) != ActionType::STAY){
            return Game::findSimple(s);
        } else {
            return ActionType::STAY;
        }
    }
}