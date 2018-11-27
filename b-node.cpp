#include "b-node.h"

B_Node::B_Node() {
    // Default Constructor
}

B_Node::~B_Node() {
    // Destructor
}

B_Node::B_Node(int num) {
    this->isLeaf = false;
    this->value_l = num;
    this->value_m = -1;
    this->value_r = -1;
    this->ptr_l = NULL;
    this->ptr_ml = NULL;
    this->ptr_mr = NULL;
    this->ptr_r = NULL;
}

B_Node::B_Node(User *user, bool isTop) {
    this->isLeaf = true;
    if(isTop) {
        this->top_leaf = user;
        this->bottom_leaf = NULL;
    } else {
        this->top_leaf = NULL;
        this->bottom_leaf = user;
    }
}