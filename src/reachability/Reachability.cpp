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

    for (int i = 0; i < stateSize; i++)
    {
        currentStateBits.push_back(createVar("s" + std::to_string(i)));
        nextStateBits.push_back(createVar("s'" + std::to_string(i)));
    }

    std::vector<bool> tmp(stateSize, 0);
    this->stateSize = stateSize;
    // setInitState(tmp);

    // setTransitionFunctions(currentStateBits);
    initStates = tmp;
    transitionFunction = currentStateBits;
    computeReachableStates();
}

void Reachability::setInitState(const std::vector<bool> &stateVector)
{
    if (stateSize != stateVector.size())
    {
        throw std::runtime_error("Reachability::setInitState: size does not match with number of state bits");
    }
    
    initStates = stateVector;
    computeReachableStates();
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions)
{
    if (stateSize != transitionFunctions.size())
    {
        throw std::runtime_error("Reachability::setTransitionFunctions: size does not match with number of state bits");
    }

    transitionFunction = transitionFunctions;
    computeReachableStates();
}

void Reachability::computeReachableStates()
{
    BDD_ID tau = computeTransitionRelation(nextStateBits,transitionFunction);

    // std::vector<BDD_ID> tmp(stateSize, 0);
    BDD_ID Cs0 = computeInitialCharacteristic(currentStateBits, initStates);
    
    // computeTransitionRelation(currentStateBits, tmp);

    BDD_ID Crit = Cs0;
    BDD_ID img;

    do{
        Cr = Crit;
        img = and2(Cr, tau);

        for(int i = 0; i < currentStateBits.size(); ++i)
        {
            img = or2(coFactorFalse(img, currentStateBits.at(i)), coFactorTrue(img, currentStateBits.at(i)));
        }

        for(int i = 0; i < nextStateBits.size(); ++i)
        {
            img = and2( img, xnor2(currentStateBits.at(i), nextStateBits.at(i)) );
        }

        for(int i = 0; i < nextStateBits.size(); ++i)
        {
            img = or2(coFactorFalse(img, nextStateBits.at(i)), coFactorTrue(img, nextStateBits.at(i)));
        }

        Crit = or2(Cr, img);

    }while (Cr != Crit);
}

BDD_ID Reachability::computeTransitionRelation(std::vector<BDD_ID>& nextStateBits, std::vector<BDD_ID>& transitionFunction)
{
    if (nextStateBits.size() != transitionFunction.size())
    {
        throw std::runtime_error("Reachability::setInitState: size does not match with number of state bits");
    }
    
    BDD_ID tau =  xnor2(nextStateBits.at(0), transitionFunction.at(0)); //,  and2(not(nextStateBits.at(0)), not(transitionFunction.at(0))));
    BDD_ID tmp;

    for(int i = 1; i < nextStateBits.size(); ++i)
    {
       tmp = xnor2(nextStateBits.at(i), transitionFunction.at(i));//or2(and2(nextStateBits.at(i), transitionFunction.at(i)),  and2(not(nextStateBits.at(i)), not(transitionFunction.at(i))));
       tau = and2(tmp,tau);
    }

    return tau;
}

BDD_ID Reachability::computeInitialCharacteristic(std::vector<BDD_ID> currentStateBits, std::vector<bool> initStates)
{
  
    BDD_ID Cs0 = xnor2(currentStateBits.at(0), initStates.at(0));
    BDD_ID tmp;
    for(int i = 1; i < initStates.size(); ++i)
    {
       tmp = xnor2(currentStateBits.at(i), initStates.at(i)); //TODO fix this
       Cs0 = and2(tmp, Cs0);
    }

    return Cs0;
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

    std::vector<BDD_ID> stateBits = getStates();
    BDD_ID tmp = Cr;

    for(int i = 0; i < stateVector.size(); ++i)
    {

        if(stateVector.at(i))
        {
            tmp = coFactorTrue(tmp,stateBits.at(i));
        }
        else
        {
            tmp = coFactorFalse(tmp,stateBits.at(i));
        }

        if(tmp <= 1)
        {
            return tmp;
        }
    }
}

const std::vector<bool> &Reachability::getInitStates() const
{
   return initStates;
}

const std::vector<BDD_ID> &Reachability::getTransitionFunctions() const
{
   return transitionFunction;
}