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

B_Node::B_Node(User &user, bool isTop) {
    this->isLeaf = true;
    if(isTop) {
        this->top_leaf = user;
    } else {
        this->bottom_leaf = user;
    }
}

void B_Node::set_l(B_Node *node) {
    this->ptr_l = node;
}

void B_Node::set_ml(B_Node *node) {
    this->ptr_ml = node;
}

void B_Node::set_mr(B_Node *node) {
    this->ptr_mr = node;
}

void B_Node::set_r(B_Node *node) {
    this->ptr_mr = node;
}