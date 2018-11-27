#include "b-node.h"

B_Node::B_Node() {
    //Default Constructor
}

B_Node::B_Node(int num) {
    this->isLeaf = false;
    this->value_l = num;
    this->value_m = -1;
    this->value_r = -1;
}

B_Node::B_Node(User *user, bool isTop) {
    this->isLeaf = true;
    if(isTop) {
        this->top_leaf = user;
    } else {
        this->bottom_leaf = user;
    }
}