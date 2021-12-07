#include"Tests.h"
#include"../Manager.h"
// using ::testing::Return;
typedef size_t BDD_ID;

TEST(Manager,createVar){

    ClassProject::Manager *manager = new ClassProject::Manager;
    BDD_ID id = 1;
    std::string label = "a";
    for(id = 2; id < 7; ++id){
        label[0] = label[0] + id - (BDD_ID)2;
        EXPECT_EQ(manager->createVar(label),id);
    }
}

TEST(Manager, True)
{
    ClassProject::Manager *manager = new ClassProject::Manager;
    BDD_ID id = 1;
    EXPECT_EQ(manager->True(),id);
}

TEST(Manager, False)
{
    ClassProject::Manager *manager = new ClassProject::Manager;
    BDD_ID id = 0;
    EXPECT_EQ(manager->False(),id);
}

TEST(Manager, isConstant)
{
    ClassProject::Manager *manager = new ClassProject::Manager;
    
    BDD_ID id;
    for(id=0;id<3;++id){
    if(id<2)
        EXPECT_TRUE(manager->isConstant(id));
    else
        EXPECT_FALSE(manager->isConstant(id));
    }
}

TEST(Manager, isVariable)
{
    ClassProject::Manager *manager = new ClassProject::Manager;
    
    BDD_ID id;
    for(id=0;id<3;++id){
    if(id==2)
        EXPECT_TRUE(manager->isVariable(id));
    else
        EXPECT_FALSE(manager->isVariable(id));
    }
}

TEST(Manager, topVar){
    ClassProject::Manager *manager = new ClassProject::Manager;
    
    BDD_ID id;
    manager->createVar("a");
    for(id = 0; id < 3; id++){
        EXPECT_EQ(manager->topVar(id),id);
    }
}