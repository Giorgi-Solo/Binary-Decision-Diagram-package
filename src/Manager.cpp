#include "Manager.h"

using namespace ClassProject;

Manager::Manager()
{
    uniqueTable.push_back({"False", 0, 0, 0, 0});
    uniqueTable.push_back({"True", 1, 1, 1, 1});
}

Manager::~Manager()
{}

/*
* Adds new node to UniqueTable
* @param new node label
* @return id of new node
*/
BDD_ID Manager::createVar(const std::string &label)
{
    BDD_ID newVarId = uniqueTable.size();
    BDD_ID i;
    for(i = 0; i < newVarId; ++i)          // to check if we already have that variable
        if(uniqueTable.at(i).label == label)
            return i;
            
    uniqueTable.push_back({label,newVarId,1,0,newVarId});
    return newVarId; 
}

const BDD_ID& Manager::True()
{
    return uniqueTable.at(1).id;
}

const BDD_ID& Manager::False()
{
    return uniqueTable.at(0).id;
}

bool Manager::isConstant(BDD_ID f)
{
    if(f >= uniqueTableSize())
        return false;
        
    if(getNode(f).topVar < 2) 
        return true;
    else
        return false;
}

bool Manager::isVariable(BDD_ID x)
{}

BDD_ID Manager::topVar(BDD_ID f)
{}

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
{
    return uniqueTable.size();
}

TableEntry Manager::getNode(const BDD_ID id)
{
    if(id < uniqueTableSize())
        return uniqueTable.at(id); // think what to do if id >= size
}
