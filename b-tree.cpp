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
        this->root->ptr_arr[1] = new B_Node(user);
        this->root->parent = this->root;
        return;
    }
    // Traverse to the leaf based on the user's perm number, make a new leaf node if there is no leaf at the to be inserted spot yet
    int goal = user->getPerm();
    B_Node *runner = this->root;
    B_Node *prev_runner = runner;
    bool noNewLeaf = true;
    while(runner->isLeaf != true) {
        if(goal < runner->value_arr[0]) {
            std::cout << "came to 0" << std::endl;
            if(runner->ptr_arr[0] != NULL) { runner = runner->ptr_arr[0]; } else { noNewLeaf = false; runner->ptr_arr[0] = new B_Node(user); break; }
        } else if(runner->value_arr[0] == -1 || goal < runner->value_arr[1]) {
            std::cout << "came to 1" << std::endl;
            if(runner->ptr_arr[1] != NULL) { runner = runner->ptr_arr[1]; } else { noNewLeaf = false; runner->parent->value_arr[0] = goal; runner->ptr_arr[1] = new B_Node(user); break; }
        } else if(runner->value_arr[1] == -1 || goal < runner->value_arr[2]) {
            std::cout << "came to 2" << std::endl;
            if(runner->ptr_arr[2] != NULL) { runner = runner->ptr_arr[2]; } else { noNewLeaf = false; runner->parent->value_arr[1] = goal; runner->ptr_arr[2] = new B_Node(user); break; }
        } else {
            std::cout << "came to 3" << std::endl;
            if(runner->ptr_arr[3] != NULL) { runner = runner->ptr_arr[3]; } else { noNewLeaf = false; runner->parent->value_arr[2] = goal; runner->ptr_arr[3] = new B_Node(user); break; }
        }
        runner->parent = prev_runner;
        if(runner->isLeaf != true) {
            prev_runner = runner;
        }
    }
    // If no new leaf node were created in the traversal process...
    if(noNewLeaf) {
        // If the leaf has a spot for the new user to the inserted
        if(runner->leaf_arr[1] == NULL) {
            runner->leaf_arr[1] = user;
        } else { // If there are no spots available, check to spot to the right of the node first
            /* NEXT STEP: Currently B-Tree only supports inserting 8 leaf values. 
            Get the recursive split case to work for all situations. */
        }
    }
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
        if(perm < runner->value_arr[0]) {
            runner = runner->ptr_arr[0];
        } else if(runner->value_arr[1] == -1 || perm < runner->value_arr[1]) {
            runner = runner->ptr_arr[1];
        } else if(runner->value_arr[2] == -1 || perm < runner->value_arr[2]) {
            runner = runner->ptr_arr[2];
        } else {
            runner = runner->ptr_arr[3];
        }
    }
    // Return true if the perm matches one of the leaves, false otherwise
    if(runner == NULL || (runner->leaf_arr[0]->getPerm() != perm && runner->leaf_arr[1] == NULL) || (runner->leaf_arr[0]->getPerm() != perm && runner->leaf_arr[1]->getPerm() != perm)) {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
    } else {
        std::cout << "User with the perm number " << perm << " was found." << std::endl;
    }
    return;
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
        if(perm < runner->value_arr[0]) {
            runner = runner->ptr_arr[0];
        } else if(runner->value_arr[1] == -1 || perm < runner->value_arr[1]) {
            runner = runner->ptr_arr[1];
        } else if(runner->value_arr[2] == -1 || perm < runner->value_arr[2]) {
            runner = runner->ptr_arr[2];
        } else {
            runner = runner->ptr_arr[3];
        }
    }
    // Return the graph index if found, -1 otherwise
    if(runner == NULL || (runner->leaf_arr[0]->getPerm() != perm && runner->leaf_arr[1] == NULL)) {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
        return -1;
    } else if(runner->leaf_arr[0] != NULL && runner->leaf_arr[0]->getPerm() == perm) {
        std::cout << "User's perm number: " << runner->leaf_arr[0]->getPerm() << std::endl;
        std::cout << "User's name: " << runner->leaf_arr[0]->getName() << std::endl;
        std::cout << "User's first favourite genre: " << runner->leaf_arr[0]->getGenre1() << std::endl;
        std::cout << "User's second favourite genre: " << runner->leaf_arr[0]->getGenre2() << std::endl;
        return 9999; // STUB!!!!!!!!!!! Change to Graph Index once implemented
    } else if(runner->leaf_arr[1] != NULL && runner->leaf_arr[1]->getPerm() == perm) {
        std::cout << "User's perm number: " << runner->leaf_arr[1]->getPerm() << std::endl;
        std::cout << "User's name: " << runner->leaf_arr[1]->getName() << std::endl;
        std::cout << "User's first favourite genre: " << runner->leaf_arr[1]->getGenre1() << std::endl;
        std::cout << "User's second favourite genre: " << runner->leaf_arr[1]->getGenre2() << std::endl;
        return 9999; // STUB!!!!!!!!!!! Change to Graph Index once implemented
    } else {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
    }
    return -1;
}