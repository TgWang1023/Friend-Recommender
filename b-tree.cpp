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
        return;
    }
    // Traverse to the leaf based on the user's perm number, make a new leaf node if there is no leaf at the to be inserted spot yet
    int goal = user->getPerm();
    B_Node *runner = this->root;
    B_Node *prev_runner = runner;
    bool noNewLeaf = true;
    while(runner->isLeaf != true) {
        if(goal < runner->value_arr[0]) {
            if(runner->ptr_arr[0] != NULL) { runner = runner->ptr_arr[0]; } else { noNewLeaf = false; runner->ptr_arr[0] = new B_Node(user); break; }
        } else if(runner->value_arr[1] == -1 || goal < runner->value_arr[1]) {
            if(runner->ptr_arr[1] != NULL) { runner = runner->ptr_arr[1]; } else { noNewLeaf = false; runner->ptr_arr[1] = new B_Node(user); break; }
        } else if(runner->value_arr[2] == -1 || goal < runner->value_arr[2]) {
            if(runner->ptr_arr[2] != NULL) { runner = runner->ptr_arr[2]; } else { noNewLeaf = false; runner->ptr_arr[2] = new B_Node(user); break; }
        } else {
            if(runner->ptr_arr[3] != NULL) { runner = runner->ptr_arr[3]; } else { noNewLeaf = false; runner->ptr_arr[3] = new B_Node(user); break; }
        }
        if(runner->isLeaf != true) {
            prev_runner = runner;
        }
    }
    // If no new leaf node were created in the traversal process...
    if(noNewLeaf) {
        // If the leaf has a spot for the new user to the inserted
        if(runner->leaf_arr[1] == NULL) {
            if(runner->leaf_arr[0]->getPerm() > goal) {
                runner->leaf_arr[1] = runner->leaf_arr[0];
                runner->leaf_arr[0] = user;
            } else {
                runner->leaf_arr[1] = user;
            }
        } else { // Otherwise either find another leaf with empty spot or make a new leaf, then reorganize
            bool noEmptySpot = true;
            for(int idx = 0; idx < 4; idx++) {
                if(prev_runner->ptr_arr[idx] == NULL) {
                    noEmptySpot = false;
                    prev_runner->ptr_arr[idx] = new B_Node(user);
                    break;
                } else if (prev_runner->ptr_arr[idx]->leaf_arr[1] == NULL) {

                }
            }
            // If all 8 spots are completely filled, split the node recursively
            if(noEmptySpot) {
                /* NEXT STEP: Currently B-Tree only supports inserting 8 leaf values. 
                Get the recursive split case to work for all situations. */
            }
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