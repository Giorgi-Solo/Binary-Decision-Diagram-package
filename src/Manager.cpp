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
        
    if(uniqueTable.at(f).high == uniqueTable.at(f).low)
        return true;
    else
        return false;
}

bool Manager::isVariable(BDD_ID x)
{
    if(x >= uniqueTableSize())
        return false;
        
    if((uniqueTable.at(x).high == 1) && (uniqueTable.at(x).low == 0)) // cHECK IF BOOLEAN FUNCTION NODES SHOULD RETURN TRUE
        return true;
    else
        return false;
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
{
    return uniqueTable.at(f).high;
}

BDD_ID Manager::coFactorFalse(BDD_ID f)
{
    return uniqueTable.at(f).low;
}

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
    return getNode(uniqueTable.at(root).topVar).label;
}

void Manager::findNodes(const BDD_ID &root, set<BDD_ID> &nodes_of_root)
{
    if ((nodes_of_root.insert(root)).second == false)
    { 
        return; // root is already in set 
    }
    
    for (const auto &nextNode: {uniqueTable.at(root).high, uniqueTable.at(root).low})
    {

        if(nextNode > 1) // check if it is not terminal node (node.high != 0 && node.high != 1)
        {
            findNodes(nextNode, nodes_of_root);
        }
        else
        {
            nodes_of_root.insert(nextNode);
        }
    }
}

void Manager::findVars(const BDD_ID &root, set<BDD_ID> &vars_of_root)
{    
    set<BDD_ID> nodes_of_root;
    findNodes(root, nodes_of_root);

    //the True and False node should not be in vars_of_root
    nodes_of_root.erase(1);
    nodes_of_root.erase(0);

    for(const auto &i : nodes_of_root)
    {
        vars_of_root.insert(getNode(i).topVar);
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

BDD_ID Manager::add_node(TableEntry entry)
{
     uniqueTable.push_back(entry);
     return entry.id;
};

CashEntry Manager::getCashNode(const BDD_ID id)
{
    return computedTable.at(id);
};

size_t Manager::cashNodeSize()
{
    return computedTable.size();
};