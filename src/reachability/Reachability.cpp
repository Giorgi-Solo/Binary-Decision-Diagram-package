//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"

using namespace ClassProject;

Reachability::Reachability(unsigned int stateSize):ReachabilityInterface(stateSize)
{
    if (stateSize == 0)
    {
        throw std::runtime_error ("Reachability::Reachability: initialized with null stateSize");
    }

    std::vector<bool> tmp(stateSize, 0);
    this->stateSize = stateSize;
    setInitState(tmp);

    for (int i = 0; i < stateSize; i++)
    {
        currentStateBits.push_back(createVar("s" + std::to_string(i)));
        nextStateBits.push_back(createVar("s'" + std::to_string(i)));
    }

}


const std::vector<BDD_ID> &Reachability::getStates() const
{
   return currentStateBits;
}

bool Reachability::isReachable(const std::vector<bool> &stateVector)
{
    if (stateSize != stateVector.size())
    {
        throw std::runtime_error("Reachability::isReachable: size does not match with number of state bits");
    }


    /*
    *
    */
   return false;
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions)
{

}

void Reachability::setInitState(const std::vector<bool> &stateVector)
{
    if (stateSize != stateVector.size())
    {
        throw std::runtime_error("Reachability::setInitState: size does not match with number of state bits");
    }
    
    reachableStates.push_back(stateVector);
}

void Reachability::computeReachableStates()
{
    std::vector<BDD_ID> tmp(stateSize, 0);

    BDD_ID tau = computeTransitionRelation(nextStateBits, transitionFunction);
    BDD_ID cs = computeTransitionRelation(currentStateBits, tmp);

    BDD_ID cr_it = cs;

}

BDD_ID Reachability::computeTransitionRelation(std::vector<BDD_ID>& stateBits, std::vector<BDD_ID>& transitionFunction)
{
    if (stateBits.size() != transitionFunction.size())
    {
        throw std::runtime_error("Reachability::setInitState: size does not match with number of state bits");
    }
    
    BDD_ID tau = 1; //1 = neutral element
    
    for (int i = 0; i < stateBits.size(); i++)
    {
        tau = and2(tau, xnor2(stateBits[i], transitionFunction[i]));

        // tau = and2(tau, or2(and2(nextStateBits[i], transitionFunction[i]),
        //                     and2(not2(nextStateBits[i]), not2(transitionFunction[i]))));
    }

    return tau;
}
