#include <iostream>
#include "b-tree.h"

B_Tree::B_Tree() {
    this->root = NULL;
}

B_Tree::~B_Tree() {
    // Destructor
}

void B_Tree::addUser(User *user) {
    // Root is Null
    if(this->root == NULL) {
        this->root = new B_Node(user->getPerm());
        this->root->ptr_ml = new B_Node(user, true);
        return;
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

void B_Tree::findUser(int perm) {
    // Empty tree case
    if(this->root == NULL) {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
        return;
    }
    // Traverse to the leaf based on the user's perm number
    B_Node *runner = this->root;
    while(runner != NULL && runner->isLeaf != true) {
        if(perm < runner->value_l) {
            runner = runner->ptr_l;
        } else if(runner->value_m == -1 || perm < runner->value_m) {
            runner = runner->ptr_ml;
        } else if(runner->value_r == -1 || perm < runner->value_r) {
            runner = runner->ptr_mr;
        } else {
            runner = runner->ptr_r;
        }
    }
    // Return true if the perm matches one of the leaves, false otherwise
    if(runner == NULL || (runner->top_leaf->getPerm() != perm && runner->bottom_leaf == NULL) || (runner->top_leaf->getPerm() != perm && runner->bottom_leaf->getPerm() != perm)) {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
    } else {
        std::cout << "User with the perm number " << perm << " was found." << std::endl;
    }
}

int B_Tree::findUserDetail(int perm) {
    // Empty tree case
    if(this->root == NULL) {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
        return -1;
    }
    // Traverse to the leaf based on the user's perm number
    B_Node *runner = this->root;
    while(runner != NULL && runner->isLeaf != true) {
        if(perm < runner->value_l) {
            runner = runner->ptr_l;
        } else if(runner->value_m == -1 || perm < runner->value_m) {
            runner = runner->ptr_ml;
        } else if(runner->value_r == -1 || perm < runner->value_r) {
            runner = runner->ptr_mr;
        } else {
            runner = runner->ptr_r;
        }
    }
    // Return the graph index if found, -1 otherwise
    if(runner == NULL || (runner->top_leaf->getPerm() != perm && runner->bottom_leaf == NULL)) {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
        return -1;
    } else if(runner->top_leaf != NULL && runner->top_leaf->getPerm() == perm) {
        std::cout << "User's perm number: " << runner->top_leaf->getPerm() << std::endl;
        std::cout << "User's name: " << runner->top_leaf->getName() << std::endl;
        std::cout << "User's first favourite genre: " << runner->top_leaf->getGenre1() << std::endl;
        std::cout << "User's second favourite genre: " << runner->top_leaf->getGenre2() << std::endl;
        return 9999; // STUB!!!!!!!!!!! Change to Graph Index once implemented
    } else if(runner->bottom_leaf != NULL && runner->bottom_leaf->getPerm() == perm) {
        std::cout << "User's perm number: " << runner->bottom_leaf->getPerm() << std::endl;
        std::cout << "User's name: " << runner->bottom_leaf->getName() << std::endl;
        std::cout << "User's first favourite genre: " << runner->bottom_leaf->getGenre1() << std::endl;
        std::cout << "User's second favourite genre: " << runner->bottom_leaf->getGenre2() << std::endl;
        return 9999; // STUB!!!!!!!!!!! Change to Graph Index once implemented
    } else {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
    }
    return -1;
}