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

TEST(Reachability, constructor)
{
    ClassProject::Reachability reachability(STATE_SIZE);

    EXPECT_TRUE(STATE_SIZE == reachability.getStates().size()) << "Returened tate size" << reachability.getStates().size() << endl;

    std::vector<bool> tmp(STATE_SIZE, 0);
    EXPECT_TRUE(1 == reachability.isReachable(tmp)) << "Initial state is 00 and is reachable" << reachability.getStates().size() << endl;
    
}
#endif
