#ifndef _B_NODE_H_
#define _B_NODE_H_

#include "user.h"

struct B_Node {
    // Constructors
    B_Node();
    ~B_Node();
    B_Node(int num);
    B_Node(User *user);
    // Methods
    void addValue(int num);
    // Attributes
    int value_l;
    int value_m;
    int value_r;
    int value_arr[3];
    B_Node *ptr_arr[4];
    B_Node *ptr_l;
    B_Node *ptr_ml;
    B_Node *ptr_mr;
    B_Node *ptr_r;
    bool isLeaf;
    User *top_leaf;
    User *bottom_leaf;
};

#endif