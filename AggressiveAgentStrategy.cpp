//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include <iostream>
#include "Strategy.h"
#include "Advantage.h"
#include "AggressiveAgentStrategy.h"


namespace Gaming{

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) :
        __agentEnergy(agentEnergy)
    {}

    AggressiveAgentStrategy::~AggressiveAgentStrategy(){

    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        // If the Agent's energy >= aggressiveness threshold AND there are any adjacent Agent-s, challenge one of them.
        if (__agentEnergy >= AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD) {
            if (Game::findAgent(s) != ActionType::STAY) {
                return Game::findAgent(s);
            }
        } else if(Game::findAdvantage(s) != ActionType::STAY){
            return Game::findAdvantage(s);
        } else if (Game::findFood(s) != ActionType::STAY) {
            return Game::findFood(s);
        } else if (Game::findEmpty(s) != ActionType::STAY) {
            return Game::findEmpty(s);
        } else {
            return ActionType::STAY;
        }
    }

}