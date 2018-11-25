#include "b-tree.h"

B_Tree::B_Tree() {
    this->root = NULL;
}

void B_Tree::addUser(User *user) {
    if(this->root == NULL) {
        this->root = new B_Node(user->getPerm());
        this->root->set_ml(new B_Node(user, true));
    }
}

bool B_Tree::findUser(int perm) {

}

void B_Tree::findUserDetail(int perm) {

}