#include "Manager.h"

using namespace ClassProject;

Manager::Manager()
{
    struct TableEntry Entry0 = {"False", 0, 0, 0, 0};
    UniqueTable.push_back(Entry0);

    struct TableEntry Entry1 = {"True", 1, 1, 1, 1};
    UniqueTable.push_back(Entry1);
    
}

Manager::~Manager()
{}

BDD_ID Manager::createVar(const std::string &label)
{
    BDD_ID newVarId = UniqueTable.size();
    UniqueTable.push_back({label,newVarId,1,0,newVarId});
    return newVarId;   
}

const BDD_ID& Manager::True()
{
    return UniqueTable.at(1).id;
}

const BDD_ID& Manager::False()
{
    return UniqueTable.at(0).id;
}

bool Manager::isConstant(BDD_ID f)
{
    if(f == 1 or f == 0)
        return true;
    else
        return false;
}

bool Manager::isVariable(BDD_ID x)
{
    if(x == 1 or x == 0)
        return false;
    else
        return true;
}

BDD_ID Manager::topVar(BDD_ID f)
{
    return UniqueTable.at(f).topVar;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e)
{}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x)
{}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x)
{}

BDD_ID Manager::coFactorTrue(BDD_ID f)
{}

BDD_ID Manager::coFactorFalse(BDD_ID f)
{}

BDD_ID Manager::neg(BDD_ID a)
{}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b)
{}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b)
{}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b)
{}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b)
{}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b)
{}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b)
{}

std::string Manager::getTopVarName(const BDD_ID &root)
{}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root)
{}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root)
{}

size_t Manager::uniqueTableSize()
{}

