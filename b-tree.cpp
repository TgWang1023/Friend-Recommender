#include "b-tree.h"

B_Tree::B_Tree() {
    this->root = NULL;
}

void B_Tree::addUser(User *user) {
    // Root is Null
    if(this->root == NULL) {
        this->root = new B_Node(user->getPerm());
        this->root->ptr_ml = new B_Node(user, true);
    }
    // Traverse to the leaf based on the user's perm number
    int goal = user->getPerm();
    B_Node *runner = this->root;
    while(runner->isLeaf != true) {
        if(goal < runner->value_l) {
            runner = runner->ptr_l;
        } else if(goal < runner->value_m) {
            runner = runner->ptr_ml;
        } else if(goal < runner->value_r) {
            runner = runner->ptr_mr;
        } else {
            runner = runner->ptr_r;
        }
    }
    // If the leaf has a spot for the new user to the inserted
    if(runner->bottom_leaf == NULL) {
        if(runner->top_leaf->getPerm() > goal) {
            runner->bottom_leaf = runner->top_leaf;
            runner->top_leaf = user;
        } else {
            runner->bottom_leaf = user;
        }
    }
    // If the leaf doesn't have a spot, but the node before leaf has an available spot
    
}

bool B_Tree::findUser(int perm) {

}

void B_Tree::findUserDetail(int perm) {

}