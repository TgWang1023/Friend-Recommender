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
    // If the leaf has a spot for the new user to the inserted
}

bool B_Tree::findUser(int perm) {

}

void B_Tree::findUserDetail(int perm) {

}