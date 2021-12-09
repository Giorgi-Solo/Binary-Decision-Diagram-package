#include "Manager.h"

using namespace std;
using namespace ClassProject;

Manager::Manager()
{
    uniqueTable.push_back(NODE_FALSE);
    uniqueTable.push_back(NODE_TRUE);
}

Manager::Manager(vector<TableEntry> uniqueTable)
{
    // TODO: Check for incorrect uniqueTable?
    this->uniqueTable = uniqueTable;
}

Manager::~Manager()
{}

/*
* Adds new node to UniqueTable
* @param new node label
* @return id of new node
*/
BDD_ID Manager::createVar(const string &label)
{
    BDD_ID newVarId = uniqueTable.size();
    BDD_ID i;
    for(i = 0; i < newVarId; ++i)          // to check if we already have that variable
        if(uniqueTable.at(i).label == label)
            return i;
            
    uniqueTable.push_back({label, newVarId, 1, 0, static_cast<uint16_t>(newVarId)});
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
{
    if(x >= uniqueTableSize())
        return false;
        
    if(getNode(x).topVar < 2) // cHECK IF BOOLEAN FUNCTION NODES SHOULD RETURN TRUE
        return false;
    else
        return true;
}

BDD_ID Manager::topVar(BDD_ID f)
{
    return uniqueTable.at(f).topVar;
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

string Manager::getTopVarName(const BDD_ID &root)
{
    return getNode(uniqueTable.at(root).id).label;
}

void Manager::findNodes(const BDD_ID &root, set<BDD_ID> &nodes_of_root)
{
    nodes_of_root.clear();
    findNodesHigh(root, nodes_of_root);
    findNodesLow(root, nodes_of_root);
}

void Manager::findNodesHigh(const BDD_ID &root, set<BDD_ID> &nodes_of_root_high)
{
    BDD_ID id = root;
    uint16_t high = getNode(id).high;

    while(1)
    {
        if (high == 1) // 1 is not a node (TODO: check if this is true)
        {
            return;
        }

        high = getNode(id).high;
        nodes_of_root_high.insert(id);
        id = high; //  high points to next id
    }
}

void Manager::findNodesLow(const BDD_ID &root, set<BDD_ID> &nodes_of_root_low)
{
    BDD_ID id = root;
    uint16_t low = getNode(id).low;
    while(1)
    {
        if (low == 0) // 0 is not a node (TODO: check if this is true)
        {
            return;
        }

        low = getNode(id).low;
        nodes_of_root_low.insert(id);
        id = low; //  low points to next id
    }
}

void Manager::findVars(const BDD_ID &root, set<BDD_ID> &vars_of_root)
{    
    set<BDD_ID> nodes_of_root;
    findNodes(root, nodes_of_root);

    vars_of_root.clear();

    for(set<BDD_ID>::const_iterator i = nodes_of_root.cbegin(); i != nodes_of_root.cend(); i++)
    {
        vars_of_root.insert(getNode((*i)).topVar);
    }
}

size_t Manager::uniqueTableSize()
{
    return uniqueTable.size();
}

TableEntry Manager::getNode(const BDD_ID id)
{
    return uniqueTable.at(id); 
}
