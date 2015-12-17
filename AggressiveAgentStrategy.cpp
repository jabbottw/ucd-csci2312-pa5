//
// Created by Julian Abbott-Whitley on 12/15/15.
//

#include <iostream>
#include "Strategy.h"
#include "Advantage.h"
#include "AggressiveAgentStrategy.h"


namespace Gaming{

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = 0;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) :
        __agentEnergy(agentEnergy)
    {}

    AggressiveAgentStrategy::~AggressiveAgentStrategy(){

    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {

    }

}