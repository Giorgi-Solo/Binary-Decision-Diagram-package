//
// Created by tobias on 29.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#define STATE_SIZE 16 // If one wants to test FSM with different bit size, he/she should change STATE_SIZE  

#include <gtest/gtest.h>
#include "Reachability.h"

using namespace std;
using namespace ClassProject;

std::vector<bool> decToBinVct(int number, int size)
{
    
    // std::cout << "Number: " << number << "\nBitVector:"; 

    std::vector<bool> binVector(size,0);
    for(int i=0; i < size; i++)    
    {    
        binVector[i]=number%2;    
        number= number/2;  
    }    
// 
    // std::cout << "Number: " << number << "\nBitVector:"; 
    // for(int i = 0; i < binVector.size(); ++i) std::cout << binVector.at(i) << ",";
    //  std::cout << std::endl;
    return binVector;
}

TEST(Reachability, constructor)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    std::vector<bool> tmp(STATE_SIZE, 0);

    EXPECT_TRUE(STATE_SIZE == reachability.getStates().size()) << "state variables are not correctly stored" << reachability.getStates().size() << endl;

    EXPECT_TRUE(1 == reachability.isReachable(tmp)) << "Initial state is 00 and is reachable" << reachability.getStates().size() << endl;

    for(int i = 1; i < pow(2,STATE_SIZE); ++i)
    {
        tmp = decToBinVct(i,STATE_SIZE);
        EXPECT_TRUE(0 == reachability.isReachable(tmp)) << "Initial state is 00 and is reachable" << reachability.getStates().size() << endl;
    }

    // std::vector<bool> tmp(STATE_SIZE, 0);
    // EXPECT_TRUE(1 == reachability.isReachable(tmp)) << "Initial state is 00 and is reachable" << reachability.getStates().size() << endl;

}

TEST(Reachability, getInitStates)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    std::vector<bool> tmp(STATE_SIZE, 0);

    EXPECT_TRUE(tmp == reachability.getInitStates()) << "Initial State are incorrectly retrieved"  << endl;
}

TEST(Reachability, getTransitionFunctions)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    EXPECT_TRUE(reachability.getStates() == reachability.getTransitionFunctions()) << "Transition Functions are incorrectly retrieved"  << endl;
}

TEST(Reachability, setInitState)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    vector<bool> initialStates;
    
    for (int i = 0; i< STATE_SIZE; i++)
    {
        initialStates.push_back(i%2);
    }
    reachability.setInitState(initialStates);

    EXPECT_TRUE(initialStates == reachability.getInitStates()) << "Initial State are incorrectly retrieved"  << endl;
}

TEST(Reachability, setTransitionFunctions)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    vector<BDD_ID> s = reachability.getStates();

    vector<BDD_ID> delta;
    
    for(int i = 0; i < STATE_SIZE; ++i)
    {
        delta.push_back(reachability.neg(s.at(i)));
    }
    
    reachability.setTransitionFunctions(delta);

    EXPECT_TRUE( delta == reachability.getTransitionFunctions()) << "Transition Functions are incorrectly set"  << endl;
}

TEST(Reachability, isReachable)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    vector<BDD_ID> s = reachability.getStates();

    vector<BDD_ID> delta;
    
    for(int i = 0; i < STATE_SIZE; ++i)
    {
        delta.push_back(reachability.neg(s.at(i)));
    }
    
    reachability.setTransitionFunctions(delta);

    std::vector<bool> tmp(STATE_SIZE, 0);
    EXPECT_TRUE(1 == reachability.isReachable(tmp)) << "state 00 should be reachable" << reachability.getStates().size() << endl;

    tmp = std::vector<bool>(STATE_SIZE,1);
    EXPECT_TRUE(1 == reachability.isReachable(tmp)) << "state 11 should be reachable" << reachability.getStates().size() << endl;
    vector<bool> boolVector;
    for (int i = 1 ; i < pow(2,STATE_SIZE)-1; i++)
    {
        boolVector = decToBinVct(i, STATE_SIZE);
        EXPECT_TRUE(0 == reachability.isReachable(boolVector)) << "state should not be reachable" << endl;
    }
}

TEST(Reachability, getStates)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    vector<BDD_ID> stateVarIds;


    for(int i=2; i <= 2 * STATE_SIZE; i = i + 2)
    {
        stateVarIds.push_back(i);
    }
    EXPECT_TRUE(stateVarIds == reachability.getStates()) << "state variables are not correctly retrieved " << reachability.getStates().at(0) << endl;

}

TEST(Reachability, computeReachableStates)
{   // This checks computeREachableStates, GetCR, computeTransitionRelation, and computeInitialCharacteristic methods
    ClassProject::Reachability reachability(STATE_SIZE);

    vector<BDD_ID> s = reachability.getStates();

    vector<BDD_ID> delta;
    
    for(int i = 0; i < STATE_SIZE; ++i)
    {
        delta.push_back(reachability.neg(s.at(i)));
    }
    
    reachability.setTransitionFunctions(delta);

    BDD_ID minTerm1 = reachability.or2(s.at(0), s.at(1));
    BDD_ID minTerm2 = reachability.and2(s.at(0), s.at(1));

    BDD_ID charachteristicFunction;// = reachability.xnor2(s.at(0), s.at(1));

    for(int i = 2; i < STATE_SIZE; ++i)
    {
        minTerm1 =  reachability.or2(minTerm1, s.at(i));
        minTerm2 =  reachability.and2(minTerm2, s.at(i));
    }

    charachteristicFunction = reachability.or2(reachability.neg(minTerm1), minTerm2);

    EXPECT_TRUE(charachteristicFunction == reachability.getCr()) << "Characteristic Function calculation fails - " << reachability.getCr() << endl;

}

#endif
