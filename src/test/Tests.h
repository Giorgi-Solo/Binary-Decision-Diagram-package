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

TEST_F(ManagerTest, addNode)
{  
    BDD_ID new_node_id = manager.uniqueTableSize();
    TableEntry testNode = {"testNode", new_node_id, 9, 8, 7};
    manager.add_node(testNode);
   
    EXPECT_TRUE(testNode == manager.getNode(new_node_id)) << "Method not implemented" << endl;
}

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

// ite(BDD_ID i,BDD_ID t,BDD_ID e) coFactorTrue(BDD_ID f,BDD_ID x), coFactorFalse(BDD_ID f,BDD_ID x) are tested
// together, because they are depenednt on each other

TEST_F(ManagerTest, coFactorTrue_specifying_variabel) // //TODO: incomplete, last two checks are not implemented
{  
    BDD_ID id = 9;
    BDD_ID x  = 5;
    TableEntry entry10 = {"placeHodler",   10, 4, 0, 3};
    TableEntry entry11 = {"placeHodler",   11, 4, 10, 2};
   
    EXPECT_EQ(manager.coFactorTrue(id,x), 11) << "case, when table doesn't contain the cofactor and variable isn't TV, fails" << endl; // f, d = 1; result is (a+b)*c
    EXPECT_TRUE(entry10 == manager.getNode(10)) << "case, when table doesn't contain the cofactor and variable isn't TV, fails" << endl;
    EXPECT_TRUE(entry11 == manager.getNode(11)) << "case, when table doesn't contain the cofactor and variable isn't TV, fails" << endl;

    id = 2;
    x;
    EXPECT_EQ(manager.coFactorTrue(id,manager.topVar(id)), manager.getNode(id).high) << "case, when variable it TV, fails" << endl;
    
    id = 1;
    x  = 3;
    EXPECT_EQ(manager.coFactorTrue(id,x), id) << "case, when f is terminal 1, fails" << endl;

    id = 0;
    x  = 3;
    EXPECT_EQ(manager.coFactorTrue(id,x), id) << "case, when f is terminal 0, fails" << endl;

    id = 3;
    x  = 2;
    EXPECT_EQ(manager.coFactorTrue(id,x), id) << "case, when function of node f does not depend on variable, fails" << endl;

    id = 7;
    x  = 5;
    EXPECT_EQ(manager.coFactorTrue(id,x), 4) << "case, when table already contains the cofactor and variable isn't TV, fails" << endl; // c*d, d = 1; result is c
}

TEST_F(ManagerTest, coFactorFalse_specifying_variabel) //TODO: incomplete, last two checks are not implemented
{
    BDD_ID id = 2;
    BDD_ID x;
    EXPECT_EQ(manager.coFactorFalse(id,manager.topVar(id)), manager.getNode(id).low) << "case, when variable it TV, fails" << endl;
    
    id = 1;
    x  = 3;
    EXPECT_EQ(manager.coFactorFalse(id,x), id) << "case, when f is terminal 1, fails" << endl;

    id = 0;
    x  = 3;
    EXPECT_EQ(manager.coFactorFalse(id,x), id) << "case, when f is terminal 0, fails" << endl;

    id = 3;
    x  = 2;
    EXPECT_EQ(manager.coFactorFalse(id,x), id) << "case, when function of node f does not depend on variable, fails" << endl;

    id = 6;
    x  = 3;
    EXPECT_EQ(manager.coFactorFalse(id,x), 2) << "case, when table already contains the cofactor and variable isn't TV, fails" << endl; // a+b, b = 1; result is a

    id = 9;
    x  = 3;
    TableEntry entry10 = {"placeHodler",   10, 7, 0, 2};
    EXPECT_EQ(manager.coFactorFalse(id,x), 10) << "case, when table doesn't contain the cofactor and variable isn't TV, fails" << endl; // f, d = 1; result is (a+b)*c
    EXPECT_TRUE(entry10 == manager.getNode(10)) << "case, when table doesn't contain the cofactor and variable isn't TV, fails" << endl;
}


TEST_F(ManagerTest, ite) //
{  
    BDD_ID i = 1, t = 3, e = 4;
    EXPECT_EQ(manager.ite(i,t,e), t) << "case, when i is 1, fails";

    i = 0, t = 3, e = 4;
    EXPECT_EQ(manager.ite(i,t,e), e) << "case, when i is 0, fails";

    i = 0, t = 6, e = 6;
    EXPECT_EQ(manager.ite(i,t,e), t) << "case, when t = e, fails";

    i = 7, t = 1, e = 0;
    EXPECT_EQ(manager.ite(i,t,e), i) << "case, when {t,e} = {1,0}, fails";
   
    i = 2, t = 1, e = 3;

    size_t cashSizeChange = manager.cashNodeSize(); // intially cash is empty

    BDD_ID r = manager.ite(i,t,e);

    cashSizeChange = manager.cashNodeSize() - cashSizeChange; // ite updated cash and increased number of entries by 1.
    // CashEntry expectedEntry = {i, t, e, r};
    // CashEntry actualEntry = manager.getCashNode(0);

    // // The following three check proves that ite works correctly and cash is correctly updated
    // EXPECT_EQ(cashSizeChange, 1) << "cash was not updated"; 
    // EXPECT_TRUE(r == manager.getCashNode(0).r) << "case when cash is not correctly updated. r is incorectly stored";
    // EXPECT_TRUE(manager.getCashNode(0) == expectedEntry) << "case when cash is not correctly updated. i,t,e are incorrect";

    // cashSizeChange = manager.cashNodeSize() - cashSizeChange; // since we call the same ite, cash size should not change. if cashsizeChange is 0, result was read from cahs

    // r = manager.ite(i,t,e);
    // EXPECT_EQ(cashSizeChange, 0);
    // EXPECT_EQ(r,expectedEntry.r); // prove that result, read from cash, is correct
}

TEST_F(ManagerTest, getCashNode)
{  
    BDD_ID f = 4, g = 3, h = 0;
    BDD_ID r = manager.ite(f, g, h);
    CashEntry expectedEntry = {f, g, h};
   
    // EXPECT_TRUE(expectedEntry == manager.getCashNode(0)) << "f, g, h are not correctly retrieved" << endl;
    // EXPECT_TRUE(r == manager.getCashNode(0).r) << "r is not correctly retrieved";
    // EXPECT_TRUE(r == manager.getCashNode1(f,g,h)) << "r is not correctly retrieved";

}

TEST_F(ManagerTest, cashNodeSize)
{  
    BDD_ID f = 4, g = 3, h = 0;
    manager.ite(f, g, h);
   
    EXPECT_TRUE(manager.cashNodeSize() == 1) << "can't read cash size" << endl;
}

TEST(Manager, logicalOperations)
{
    Manager manager;

    manager.createVar("a");
    manager.createVar("b");

    EXPECT_TRUE(manager.or2(2,3)   == manager.ite(2,1,3)) << "or fails";
    EXPECT_TRUE(manager.or2(1,3)   == 1) << "or fails (1,3)";
    EXPECT_TRUE(manager.or2(3,1)   == 1) << "or fails (3,1)";
    EXPECT_TRUE(manager.or2(0,3)   == 3) << "or fails (0,3)";
    EXPECT_TRUE(manager.or2(3,0)   == 3) << "or fails (3,0)";
    EXPECT_TRUE(manager.or2(0,0)   == 0) << "or fails (3,0)";
    EXPECT_TRUE(manager.or2(1,1)   == 1) << "or fails (3,0)";

    EXPECT_TRUE(manager.and2(2,3)  == manager.ite(2,3,0)) << "and fails";
    EXPECT_TRUE(manager.and2(1,3)  == 3) << "and fails (1,3)";
    EXPECT_TRUE(manager.and2(3,1)  == 3) << "and fails (3,1)";
    EXPECT_TRUE(manager.and2(0,3)  == 0) << "and fails (0,3)";
    EXPECT_TRUE(manager.and2(3,0)  == 0) << "and fails (3,0)";
    EXPECT_TRUE(manager.and2(1,1)  == 1) << "and fails (3,0)";
    EXPECT_TRUE(manager.and2(0,0)  == 0) << "and fails (3,0)";
    

    EXPECT_TRUE(manager.neg(2)     == manager.ite(2,0,1)) << "neg fails";
    EXPECT_TRUE(manager.neg(0)     == 1) << "neg fails";
    EXPECT_TRUE(manager.neg(1)     == 0) << "neg fails";

    EXPECT_TRUE(manager.xor2(2,3)  == manager.ite(2,manager.neg(3),3)) << "xor  fails";
    EXPECT_TRUE(manager.xor2(1,0)  == 1) << "xor  fails";
    EXPECT_TRUE(manager.xor2(0,1)  == 1) << "xor  fails";
    EXPECT_TRUE(manager.xor2(1,3)  == manager.neg(3)) << "xor  fails";
    EXPECT_TRUE(manager.xor2(3,3)  == 0) << "xor  fails";
    EXPECT_TRUE(manager.xor2(1,1)  == 0) << "xor  fails";
    EXPECT_TRUE(manager.xor2(0,0)  == 0) << "xor  fails";

    EXPECT_TRUE(manager.nand2(2,3) == manager.neg(manager.and2(2,3)))  << "nand fails";
    EXPECT_TRUE(manager.nand2(1,1) == 0)  << "nand fails";
    EXPECT_TRUE(manager.nand2(1,0) == 1)  << "nand fails";
    EXPECT_TRUE(manager.nand2(0,1) == 1)  << "nand fails";
    EXPECT_TRUE(manager.nand2(0,0) == 1)  << "nand fails";

    EXPECT_TRUE(manager.nor2(2,3)  == manager.neg(manager.or2(2,3)))   << "nor  fails";
    EXPECT_TRUE(manager.nor2(0,0)  == 1)   << "nor  fails";
    EXPECT_TRUE(manager.nor2(1,0)  == 0)   << "nor  fails";
    EXPECT_TRUE(manager.nor2(0,1)  == 0)   << "nor  fails";
    EXPECT_TRUE(manager.nor2(1,1)  == 0)   << "nor  fails";

    EXPECT_TRUE(manager.xnor2(2,3) == manager.neg(manager.xor2(2,3)))  << "xnor  fails";
    EXPECT_TRUE(manager.xnor2(1,0)  == 0) << "xnor  fails";
    EXPECT_TRUE(manager.xnor2(0,1)  == 0) << "xnor  fails";
    EXPECT_TRUE(manager.xnor2(0,0)  == 1) << "xnor  fails";
    EXPECT_TRUE(manager.xnor2(1,1)  == 1) << "xnor  fails";
    // EXPECT_TRUE(manager.xnor2(1,3)  == 3) << "xnor  fails";
    // EXPECT_TRUE(manager.xnor2(3,1)  == 3) << "xnor  fails";
    EXPECT_TRUE(manager.xnor2(3,3)  == 1) << "xnor  fails";
}


#endif
