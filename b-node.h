#ifndef _B_NODE_H_
#define _B_NODE_H_

#include "user.h"

struct B_Node {
    // Constructors
    B_Node();
    ~B_Node();
    B_Node(int num);
    B_Node(User *user);
    // Attributes
    int value_arr[3];
    B_Node *parent;
    B_Node *ptr_arr[4];
    bool isLeaf;
    User *leaf_arr[2];
};

#endif