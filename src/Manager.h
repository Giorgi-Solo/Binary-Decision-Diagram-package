// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include<boost/functional/hash/hash.hpp>

/*NODE Structure {label, id, high, low, topVar}*/
#define NODE_FALSE {"False", 0, 0, 0, 0}
#define NODE_TRUE  {"True",  1, 1, 1, 1}

using namespace std;

namespace ClassProject 
{
    struct CashEntry
    {
        BDD_ID f;
        BDD_ID g;
        BDD_ID h;

        bool operator == (const CashEntry& c2) const
        {
            return (f == c2.f) &&
                    (g == c2.g) &&
                    (h == c2.h);
        }
    };

    struct TableEntry
    {
        string label;
        BDD_ID id;
        BDD_ID high;
        BDD_ID low;
        BDD_ID topVar;
        
        bool operator == (const TableEntry& c2) const
        {
            return  (id == c2.id) &&
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

    BDD_ID add_node(TableEntry entry);

    BDD_ID getCashNode(const string key);

    size_t cashNodeSize();
 
 private:

    bool findComputedIte(const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID &r);
    BDD_ID find_or_add_unique_table(const BDD_ID topVar, const BDD_ID r_low, const BDD_ID r_high);
    string to_key(const BDD_ID i, const BDD_ID t, const BDD_ID e);

    vector<TableEntry> uniqueTable;
    unordered_map<string, BDD_ID> reverseUniqueTable;
    unordered_map<string, BDD_ID> reverseComputedTable;
};
}

#endif