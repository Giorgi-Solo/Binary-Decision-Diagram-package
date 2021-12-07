//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"


TEST(Manager, True)
{
    ClassProject::Manager *manager = new ClassProject::Manager;
    EXPECT_TRUE(1);
}


TEST(Manager, False)
{
    ClassProject::Manager *manager = new ClassProject::Manager;
    EXPECT_FALSE(1);
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
