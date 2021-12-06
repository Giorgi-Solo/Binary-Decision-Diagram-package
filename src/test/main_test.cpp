//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
// #include "tst_testManager.cpp"

TEST(Manager, True)
{
    ClassProject::Manager *manager = new ClassProject::Manager;
    
    EXPECT_TRUE(manager->True());
}

TEST(Manager, False)
{
    ClassProject::Manager *manager = new ClassProject::Manager;
    EXPECT_TRUE(0);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
