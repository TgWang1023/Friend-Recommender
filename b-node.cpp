#include "b-node.h"

B_Node::B_Node(int num, bool leaf) {
    this->isLeaf = leaf;
    if(leaf) {
        this->value_l = num;
        this->value_m = -1;
        this->value_r = -1;
    }else{
        this->top_leaf = num;
        this->bottom_leaf = -1;
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