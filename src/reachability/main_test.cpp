//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"


int main(int argc, char* argv[])
{
    ClassProject::Reachability a(static_cast<unsigned int>(10));
    a.False();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
