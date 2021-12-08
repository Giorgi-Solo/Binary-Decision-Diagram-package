//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"


TEST(Manager, Constructor)
{
    ClassProject::Manager manager;
    ClassProject::TableEntry falseNode =  {"False", 0, 0, 0, 0};
    ClassProject::TableEntry trueNode =  {"True", 1, 1, 1, 1};
    EXPECT_TRUE(manager.getNode(0) == falseNode);
    EXPECT_TRUE(manager.getNode(1) == trueNode);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
