// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <iostream>
#include <vector>

/*NODE Structure {label, id, high, low, topVar}*/
#define NODE_FALSE {"False", 0, 0, 0, 0}
#define NODE_TRUE  {"True",  1 , 1, 1, 1}

using namespace std;

namespace ClassProject 
{

    struct TableEntry
    {
        string label;
        BDD_ID id;
        uint16_t high;
        uint16_t low;
        uint16_t topVar;
        
        bool operator == (TableEntry c2) 
        {
            return (label == c2.label) &&
                    (id == c2.id) &&
                    (high == c2.high) &&
                    (low == c2.low) &&
                    (topVar == c2.topVar);
        }
    };

class Manager: public ManagerInterface
{
public:
    Manager();
    Manager(vector<TableEntry> uniqueTable);
    ~Manager();

    BDD_ID createVar(const string &label);

    const BDD_ID &True();

    const BDD_ID &False();

    bool isConstant(BDD_ID f);

    bool isVariable(BDD_ID x);

    BDD_ID topVar(BDD_ID f);

    BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e);

    BDD_ID coFactorTrue(BDD_ID f, BDD_ID x);

    BDD_ID coFactorFalse(BDD_ID f, BDD_ID x);

    BDD_ID coFactorTrue(BDD_ID f);

    BDD_ID coFactorFalse(BDD_ID f);

    BDD_ID neg(BDD_ID a);

    BDD_ID and2(BDD_ID a, BDD_ID b);

    BDD_ID or2(BDD_ID a, BDD_ID b);

    BDD_ID xor2(BDD_ID a, BDD_ID b);

    BDD_ID nand2(BDD_ID a, BDD_ID b);

    BDD_ID nor2(BDD_ID a, BDD_ID b);

    BDD_ID xnor2(BDD_ID a, BDD_ID b);

    string getTopVarName(const BDD_ID &root);

    void findNodes(const BDD_ID &root, set<BDD_ID> &nodes_of_root);
   
    void findVars(const BDD_ID &root, set<BDD_ID> &vars_of_root);

    size_t uniqueTableSize();
    
    TableEntry getNode(const BDD_ID id);

private:
    void findNodesHigh(const BDD_ID &root, set<BDD_ID> &nodes_of_root_high);
    void findNodesLow(const BDD_ID &root, set<BDD_ID> &nodes_of_root_low);

    vector<TableEntry> uniqueTable;
};
}

#endif