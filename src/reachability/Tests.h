//
// Created by tobias on 29.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#define STATE_SIZE 2

#include <gtest/gtest.h>
#include "Reachability.h"

using namespace std;
using namespace ClassProject;

TEST(Reachability, constructor)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    EXPECT_TRUE(STATE_SIZE == reachability.getStates().size()) << "state variables are not correctly stored" << reachability.getStates().size() << endl;

    std::vector<bool> tmp(STATE_SIZE, 0);
    EXPECT_TRUE(1 == reachability.isReachable(tmp)) << "Initial state is 00 and is reachable" << reachability.getStates().size() << endl;

    tmp = {1,1};
    EXPECT_TRUE(0 == reachability.isReachable(tmp)) << "state 11 is not reachable - fails" << reachability.getStates().size() << endl;
    
    tmp = {1,0};
    EXPECT_TRUE(0 == reachability.isReachable(tmp)) << "state 10 is not reachable - fails" << reachability.getStates().size() << endl;
    
    tmp = {0,1};
    EXPECT_TRUE(0 == reachability.isReachable(tmp)) << "state 01 is not reachable - fails" << reachability.getStates().size() << endl;
}

TEST(Reachability, getInitStates)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    EXPECT_TRUE(0 == reachability.getInitStates().at(0)) << "Initial State are incorrectly retrieved"  << endl;
    EXPECT_TRUE(0 == reachability.getInitStates().at(1)) << "Initial State are incorrectly retrieved"  << endl;
}

TEST(Reachability, getTransitionFunctions)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    EXPECT_TRUE(reachability.getStates().at(0) == reachability.getTransitionFunctions().at(0)) << "Transition Functions are incorrectly retrieved"  << endl;
    EXPECT_TRUE(reachability.getStates().at(1) == reachability.getTransitionFunctions().at(1)) << "Transition Functions are incorrectly retrieved"  << endl;
}

TEST(Reachability, setInitState)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    vector<bool> initialStates = {true,false};
    reachability.setInitState(initialStates);

    EXPECT_TRUE(1 == reachability.getInitStates().at(0)) << "Initial State are incorrectly retrieved"  << endl;
    EXPECT_TRUE(0 == reachability.getInitStates().at(1)) << "Initial State are incorrectly retrieved"  << endl;
}

TEST(Reachability, setTransitionFunctions)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    BDD_ID s0 = reachability.getStates().at(0);
    BDD_ID s1 = reachability.getStates().at(1);

    BDD_ID delta0 = reachability.and2(s0,s1);
    BDD_ID delta1 = reachability.xnor2(s0,s1);

    vector<BDD_ID> transactionFuns = {delta0, delta1};

    reachability.setTransitionFunctions(transactionFuns);

    EXPECT_TRUE( delta0 == reachability.getTransitionFunctions().at(0)) << "Transition Functions are incorrectly set"  << endl;
    EXPECT_TRUE( delta1 == reachability.getTransitionFunctions().at(1)) << "Transition Functions are incorrectly set"  << endl;

}

TEST(Reachability, isReachable)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    BDD_ID s0 = reachability.getStates().at(0);
    BDD_ID s1 = reachability.getStates().at(1);

    BDD_ID delta0 = reachability.neg(s0);
    BDD_ID delta1 = reachability.neg(s1);

    vector<BDD_ID> transactionFuns = {delta0, delta1};

    reachability.setTransitionFunctions(transactionFuns);

    std::vector<bool> tmp(STATE_SIZE, 0);
    EXPECT_TRUE(1 == reachability.isReachable(tmp)) << "state 00 should be reachable" << reachability.getStates().size() << endl;

    tmp = {1,1};
    EXPECT_TRUE(1 == reachability.isReachable(tmp)) << "state 11 should be reachable" << reachability.getStates().size() << endl;
    
    tmp = {1,0};
    EXPECT_TRUE(0 == reachability.isReachable(tmp)) << "state 10 should not be reachable" << reachability.getStates().size() << endl;
    
    tmp = {0,1};
    EXPECT_TRUE(0 == reachability.isReachable(tmp)) << "state 01 should not be reachable" << reachability.getStates().size() << endl;

}

TEST(Reachability, getStates)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    int uniqueTableSize = reachability.uniqueTableSize();

    BDD_ID s0 = uniqueTableSize - 2;
    BDD_ID s1 = uniqueTableSize - 1;
    cout << s0 << endl;
    EXPECT_TRUE(s0 == reachability.getStates().at(0)) << "state variables are not correctly retrieved " << reachability.getStates().at(0) << reachability.getStates().size() << endl;
    EXPECT_TRUE(s1 == reachability.getStates().at(1)) << "state variables are not correctly retrieved " << reachability.getStates().at(1) << reachability.getStates().size() << endl;

}





















TEST(Reachability, computeReachableStates)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    // EXPECT_TRUE(STATE_SIZE == reachability.getStates().size()) << "state variables are not correctly stored" << reachability.getStates().size() << endl;
}

TEST(Reachability, computeTransitionRelation)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    // EXPECT_TRUE(STATE_SIZE == reachability.getStates().size()) << "state variables are not correctly stored" << reachability.getStates().size() << endl;
}

TEST(Reachability, computeInitialCharacteristic)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    // EXPECT_TRUE(STATE_SIZE == reachability.getStates().size()) << "state variables are not correctly stored" << reachability.getStates().size() << endl;
}

#endif
