//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"

using namespace std;
using namespace ClassProject;

/*
    During testing, we had to create unique table with several variable nodes. That is why we 
    wrote a function that does that.

    @param pointer to Manager object, number of variable numVars
    the function adds numVars nodes to unique table

    Since this function uses createVar method, we do not use this functin in Test for createVar
*/

void addNodes(Manager *manager, size_t size)
{
    BDD_ID id;
    string label = "a";
    label[0] = label[0] - 1; // subtract 1 so that in loop first variable is "a"

    for(id = 2; id < (size); ++id) // id 2 because we already have 2 nodes in uniqueTable
    {
        label[0] = label[0] + 1; // add 1 to simulate different variables, starting with "a"
        manager->createVar(label);
    }
}


TEST(Manager, Constructor)
{
    Manager manager;
    TableEntry falseNode = NODE_FALSE;
    TableEntry trueNode =  NODE_TRUE;
    EXPECT_TRUE(manager.getNode(0) == falseNode);
    EXPECT_TRUE(manager.getNode(1) == trueNode);
}

TEST(Manager, ConstructorWithParameter)
{
    const std::vector<TableEntry> tmp {SAMPLE_TABLE};
    Manager manager(SAMPLE_TABLE);
    
    EXPECT_TRUE(manager.uniqueTableSize() == tmp.size());
    
    for(int i = 0; i < tmp.size(); i++)
    {
        EXPECT_TRUE(manager.getNode(i) == tmp.at(i));
    }
}

TEST(Manager,createVar)
{    
    Manager manager;
    BDD_ID id;
    string label = "a";
    label[0] = label[0] - 1; // subtract 1 so that in loop first variable is "a"
    TableEntry tmp; 
    for(id = 2; id < 7; ++id) // id 2 because we already have 2 nodes in uniqueTable
    {
        label[0] = label[0] + 1; // add 1 to simulate different variables starting with "a"
        tmp = manager.getNode(manager.createVar(label));
        EXPECT_TRUE(tmp == manager.getNode(id));
    }
    EXPECT_TRUE(manager.createVar("False") == 0) << "Same variable added twice";
}

TEST(Manager, True)
{
    Manager manager;
    EXPECT_TRUE(manager.True() == (BDD_ID)1) << "Method not implemented";
}

TEST(Manager, False)
{
    Manager manager;
    EXPECT_TRUE(manager.False() == (BDD_ID)0) << "Method not implemented";
}

TEST(Manager, uniqueTableSize)
{
    Manager manager;
    size_t size = 10;
    addNodes(&manager, size);
    EXPECT_TRUE(size == manager.uniqueTableSize()) << "Method not implemented";
}

TEST(Manager, isConstant)
{
    Manager manager;
    size_t size = 10;
    addNodes(&manager, size);
    
    BDD_ID id;
    for(id=0; id<size; ++id)
    {
        if(manager.getNode(id).topVar < 2) // the first two nodes are leaf nodes
            EXPECT_TRUE(manager.isConstant(id) == true) << "Method not implemented";
        else
            EXPECT_TRUE(manager.isConstant(id) == false) << "Method not implemented";
    }
    EXPECT_TRUE(manager.isConstant(size) == false) << " Method not implemented"; // case when requested node is not in unique table
}

TEST(Manager, isVariable)
{
    Manager manager;
    size_t size = 10;
    addNodes(&manager, size);
    
    BDD_ID id;
    for(id=0; id<size; ++id)
    {
        if(manager.getNode(id).topVar >= 2) // the first two nodes are leaf nodes
            EXPECT_TRUE(manager.isVariable(id) == true) << "Method not implemented";
        else
            EXPECT_TRUE(manager.isVariable(id) == false) << "Method not implemented";
    }
    EXPECT_TRUE(manager.isVariable(size) == false) << " Method not implemented"; // case when requested node is not in unique table
}

TEST(Manager, topVar)
{
    Manager manager;
    size_t size = 10;
    addNodes(&manager, size);
    
    BDD_ID id;
    for(id=0; id<size; ++id)
    {
        EXPECT_TRUE(manager.getNode(id).topVar == manager.topVar(id)) << " Method not implemented"; 
    }
}

TEST(Manager, getTopVarName)
{
    const std::vector<TableEntry> tmp {SAMPLE_TABLE};
    Manager manager(SAMPLE_TABLE);

    for (int i = 0; i < tmp.size(); i++)
    {
        BDD_ID topVarId = tmp.at(i).topVar;
        std::string topVarName = tmp.at(topVarId).label;

        EXPECT_TRUE(manager.getTopVarName(i) == topVarName);
    }
}

TEST(Manager, findNodes)
{
    Manager manager(SAMPLE_TABLE);
    set<BDD_ID> nodes_of_root;
    manager.findNodes(9, nodes_of_root);

    //this expectedResult has been calculated beforehand based on the SAMPLE_TABLE (TODO:check if it is correct)
    set<BDD_ID> expectedResult;
    expectedResult.insert(9);
    expectedResult.insert(7);
    expectedResult.insert(5);
    expectedResult.insert(8);
    
    EXPECT_TRUE(nodes_of_root == expectedResult);
}

TEST(Manager, findVars)
{
    Manager manager(SAMPLE_TABLE);
    set<BDD_ID> nodes_of_vars;
    manager.findVars(9, nodes_of_vars);

    //this expectedResult has been calculated beforehand based on the SAMPLE_TABLE (TODO:check if it is correct)
    set<BDD_ID> expectedResult;
    expectedResult.insert(2);
    expectedResult.insert(4);
    expectedResult.insert(3);
    expectedResult.insert(5);
    
    EXPECT_TRUE(nodes_of_vars == expectedResult);
}

TEST(Manager, getNode)
{
    Manager manager;

    TableEntry falseNode = NODE_FALSE;
    TableEntry trueNode  = NODE_TRUE;

//  the values for the false and true node are inserted in the vector in the constructor
    EXPECT_TRUE(manager.getNode(0) == falseNode) << "Method not implemented";
    EXPECT_TRUE(manager.getNode(1) == trueNode) << "Method not implemented";

    TableEntry testVar{"testGetNodeVar", 2, 1, 0, 2};
    manager.createVar("testGetNodeVar");
    EXPECT_TRUE(manager.getNode(2) == testVar) << "Method not implemented"; 
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
