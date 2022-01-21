#include "Manager.h"

using namespace std;
using namespace ClassProject;

Manager::Manager()
{
    uniqueTable.push_back(NODE_FALSE);
    uniqueTable.push_back(NODE_TRUE);
    // reverseUniqueTable[NODE_FALSE] = 0;
    // reverseUniqueTable[NODE_TRUE] = 1;

    reverseUniqueTable[{to_string(0)+'|'+to_string(0)+'|'+to_string(0)}] = 0;
    reverseUniqueTable[{to_string(1)+'|'+to_string(1)+'|'+to_string(1)}] = 1;
}

Manager::Manager(vector<TableEntry> uniqueTable)
{
    // TODO: Check for incorrect uniqueTable?
    this->uniqueTable = uniqueTable;
    int i;
    for (i = 0; i < uniqueTable.size(); i++)
    {
        // reverseUniqueTable[uniqueTable.at(i)] = uniqueTable.at(i).id;
        reverseUniqueTable[{to_string(uniqueTable.at(i).high)+'|'+to_string(uniqueTable.at(i).low)+'|'+to_string(uniqueTable.at(i).topVar)}] = uniqueTable.at(i).id;
    }
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
    // reverseUniqueTable[{label, newVarId, 1, 0, static_cast<uint16_t>(newVarId)}] = newVarId;
    reverseUniqueTable[{to_string(1)+'|'+to_string(0)+'|'+to_string(newVarId)}] = newVarId;

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

// TODO: add comments for the following 5 methods

bool Manager::findComputedIte(const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID &r)
{
    BDD_ID id;
    CashEntry tmp = {i, t, e};

    // if (reverseComputedTable.count({to_string(i)+'|'+to_string(t)+'|'+to_string(e)}))
    if (reverseComputedTable.count({to_string(i)+'|'+to_string(t)+'|'+to_string(e)}))
    {
        // r = reverseComputedTable[tmp];
        r = reverseComputedTable[{to_string(i)+'|'+to_string(t)+'|'+to_string(e)}];
        return true;
    }
    // for(id = 0; id < computedTable.size(); ++id)
    // {
    //     if(tmp == computedTable.at(id)){
    //         r = computedTable.at(id).r;
    //         return true;
    //     }
    // }

    return false;
}

BDD_ID Manager::find_or_add_unique_table(const BDD_ID topVar, const BDD_ID r_low, const BDD_ID r_high)
{
    TableEntry tmp = {"placeHolder", 0, r_high, r_low, topVar};

    BDD_ID id;
    // for(id = 0; id < uniqueTableSize(); ++id){
    //     tmp.label = uniqueTable.at(id).label;
    //     tmp.id = uniqueTable.at(id).id;

    //     if(tmp == uniqueTable.at(id))
    //         return uniqueTable.at(id).id;
    // }
    //TODO aici e o problema mare partea de sus merge dar if ul de jos nu 
    // if (reverseUniqueTable.count(tmp))
    if (reverseUniqueTable.count({to_string(r_high)+'|'+to_string(r_low)+'|'+to_string(topVar)}))
    {
        // return static_cast<BDD_ID>(reverseUniqueTable[tmp]);
            return static_cast<BDD_ID>(reverseUniqueTable[{to_string(r_high)+'|'+to_string(r_low)+'|'+to_string(topVar)}]);

    }
    
    id = uniqueTableSize();
    uniqueTable.push_back({"ITE Result", id, r_high, r_low, topVar}); // when loop breaks, id = uniqueTableSize, which is id of the next entry
    // reverseUniqueTable[{"ITE Result", id, r_high, r_low, topVar}] = id;
    reverseUniqueTable[{to_string(r_high)+'|'+to_string(r_low)+'|'+to_string(topVar)}] = id;

    return id;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e)
{
    BDD_ID r;
    BDD_ID r_high;
    BDD_ID r_low;
    
    BDD_ID topVar;
    set<BDD_ID> topVars;
    
    // 4 Terminal Cases
    if(i == static_cast<BDD_ID>(1))
        return t;
    else if(i == static_cast<BDD_ID>(0))
        return e;
    else if(t == e)
        return t;   
    else if((t == static_cast<BDD_ID>(1))&&( e == static_cast<BDD_ID>(0)))
        return i;
    else if(/*!computedTable.empty()*/ !reverseComputedTable.empty() && findComputedIte(i,t,e,r)) // We check computedTable if it is not empty
        return r;
    else
    {
        topVars = {uniqueTable.at(i).topVar, uniqueTable.at(t).topVar, uniqueTable.at(e).topVar}; // TODO:: maybe adding 0,1 is not necessary
        topVars.erase(0);
        topVars.erase(1);
        topVar = *(--topVars.rend()); // topvar has is the variable with lowest id,  because that is the highest variable
       
        r_high = ite(coFactorTrue(i,topVar), coFactorTrue(t,topVar), coFactorTrue(e,topVar));
        r_low = ite(coFactorFalse(i,topVar), coFactorFalse(t,topVar), coFactorFalse(e,topVar));

        if(r_high == r_low)
            return r_high;
        
        r = find_or_add_unique_table(topVar, r_low, r_high);

        // computedTable.push_back({i, t, e});
        reverseComputedTable[{to_string(i)+'|'+to_string(t)+'|'+to_string(e)}] = r;
        return r;
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x)
{
    BDD_ID T, F;
    BDD_ID TpV = topVar(f);
    if(TpV == x)
        return uniqueTable.at(f).high;
    else if(isConstant(f) || uniqueTable.at(f).topVar > x) // checks 2 cases when f does not depend on x
        return f;
    else
    {
        T = coFactorTrue(uniqueTable.at(f).high, x);
        F = coFactorTrue(uniqueTable.at(f).low, x);

        return ite(TpV, T, F); // TODO, this case is not complete
    }
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x)
{
    BDD_ID T, F;
    
    if(uniqueTable.at(f).topVar == x)
        return uniqueTable.at(f).low;
    else if(isConstant(f) || uniqueTable.at(f).topVar > x) // checks 3 cases when f does not depend on x
        return f;
    else
    {
        T = coFactorFalse(uniqueTable.at(f).high, x);
        F = coFactorFalse(uniqueTable.at(f).low, x);
        return ite(uniqueTable.at(f).topVar, T, F);
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f)
{
    return uniqueTable.at(f).high;
}

BDD_ID Manager::coFactorFalse(BDD_ID f)
{
    return uniqueTable.at(f).low;
}

BDD_ID Manager::neg(BDD_ID a)
{
   return ite(a, 0, 1);
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b)
{
    return ite(a,b,0);
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b)
{
    return ite(a, 1, b);
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b)
{
    return ite(a, neg(b), b);
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b)
{
    return neg(and2(a,b)); // or ite(a, neg(b), 1) think whichever is simpler
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b)
{
    return neg(or2(a,b)); // Maybe ite(a,0,neg(b)) is simpler
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b)
{
    return neg(xor2(a,b)); 
}

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
    //  reverseUniqueTable[entry] = entry.id;
    // reverseUniqueTable[entry] = entry.id;
    reverseUniqueTable[{to_string(entry.high)+'|'+to_string(entry.low)+'|'+to_string(entry.topVar)}] = entry.id;
     return entry.id;
};

BDD_ID Manager::getCashNode(const string key)
{
    return reverseComputedTable.at(key);
};


size_t Manager::cashNodeSize()
{
    return reverseComputedTable.size();
};