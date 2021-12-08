//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
using namespace ClassProject;

/*
    During testing, we had to create unique table with several variable nodes. That is why we 
    wrote a function that does that.

    @param pointer to Manager object, number of variable numVars
    the function adds numVars nodes to unique table
*/

void addNodes(Manager *manager, size_t numVars)
{
    BDD_ID id;
    std::string label = "a";
    label[0] = label[0] - 1; // subtract 1 so that in loop first variable is "a"

    for(id = 2; id < (numVars + 2); ++id) // id 2 because we already have 2 nodes in uniqueTable
    {
        label[0] = label[0] + 1; // add 1 to simulate different variables starting with "a"
        manager->createVar(label);
    }
}


TEST(Manager, Constructor)
{
    Manager manager;
    TableEntry falseNode =  {"False", 0, 0, 0, 0};
    TableEntry trueNode =  {"True", 1, 1, 1, 1};
    EXPECT_TRUE(manager.getNode(0) == falseNode);
    EXPECT_TRUE(manager.getNode(1) == trueNode);
}

TEST(Manager,createVar)
{    
    Manager manager;
    BDD_ID id;
    std::string label = "a";
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
    addNodes(&manager,size - 2); // we add size-2 nodes because we already have 2 nodes
    EXPECT_TRUE(size == manager.uniqueTableSize()) << "Method not implemented";
    
}

TEST(Manager, isConstant)
{
    Manager manager;
    size_t size = 10;
    addNodes(&manager,size - 2); // we add size-2 nodes because we already have 2 nodes
    
    BDD_ID id;
    for(id=0;id<size;++id)
    {
        if(manager.getNode(id).topVar < 2) // the first two nodes are leaf nodes
            EXPECT_TRUE(manager.isConstant(id) == true) << "Method not implemented";
        else
            EXPECT_TRUE(manager.isConstant(id) == false) << "Method not implemented";
    }
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
