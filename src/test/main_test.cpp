//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
using namespace ClassProject;

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

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
