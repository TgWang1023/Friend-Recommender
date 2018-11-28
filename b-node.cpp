#include "b-node.h"

B_Node::B_Node() {
    // Default Constructor
}

B_Node::~B_Node() {
    // Destructor
}

B_Node::B_Node(int num) {
    this->isLeaf = false;
    this->value_arr[0] = num;
    this->value_arr[1] = -1;
    this->value_arr[2] = -1;
    this->parent = NULL;
    this->ptr_arr[0] = NULL;
    this->ptr_arr[1] = NULL;
    this->ptr_arr[2] = NULL;
    this->ptr_arr[3] = NULL;
}

B_Node::B_Node(User *user) {
    this->isLeaf = true;
    this->leaf_arr[0] = user;
    this->leaf_arr[1] = NULL;
}