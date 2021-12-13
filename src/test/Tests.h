//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

#define SAMPLE_TABLE \
{   \
{"False", 0, 0, 0, 0}, \
{ "True", 1, 1, 1, 1}, \
{    "a", 2, 1, 0, 2}, \
{    "b", 3, 1, 0, 3}, \
{    "c", 4, 1, 0, 4}, \
{    "d", 5, 1, 0, 5}, \
{  "a+b", 6, 1, 3, 2}, \
{  "c*d", 7, 5, 0, 4}, \
{"b*c*d", 8, 7, 0, 3}, \
{    "f", 9, 7, 8, 2}, \
} \


using namespace std;
using namespace ClassProject;

void prTable(Manager manager){  // we used this function for debugging.
    BDD_ID id; 
    for(id = 0; id < manager.uniqueTableSize(); ++id)
    {
        cout << manager.getNode(id).id << " | " << manager.getNode(id).high << " | " << manager.getNode(id).low << " | " << manager.getNode(id).topVar << " | " << manager.getNode(id).label << endl;
    }
}

struct ManagerTest : testing::Test
{
    Manager manager; 
    
    BDD_ID false_node = manager.False();
    BDD_ID true_node = manager.True();

    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");
    BDD_ID c_id = manager.createVar("c");
    BDD_ID d_id = manager.createVar("d");

    BDD_ID a_or_b_id    = manager.add_node({"a+b",   6, 1, 3, 2});
    BDD_ID c_and_d_id   = manager.add_node({"c*d",   7, 5, 0, 4}); 
    BDD_ID b_c_and_d_id = manager.add_node({"b*c*d", 8, 7, 0, 3}); 
    BDD_ID f_id         = manager.add_node({"f",     9, 7, 8, 2}); 
};

TEST_F(ManagerTest, coFactorTrue)
{  // decision variable is top variable
    BDD_ID id;

    for(id = 0; id < manager.uniqueTableSize(); ++id)
    {
        EXPECT_EQ(manager.coFactorTrue(id), manager.getNode(id).high) << "Method not implemented" << endl;
    } 
}

TEST_F(ManagerTest, coFactorFalse)
{  // decision variable is top variable
    BDD_ID id;

    for(id = 0; id < manager.uniqueTableSize(); ++id)
    {
        EXPECT_EQ(manager.coFactorFalse(id), manager.getNode(id).low) << "Method not implemented" << endl;
    } 
}


#endif
