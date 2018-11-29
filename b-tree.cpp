#include <iostream>
#include "b-tree.h"

B_Tree::B_Tree() {
    this->root = NULL;
}

B_Tree::~B_Tree() {
    // Destructor
}

void B_Tree::addUser(User *user) {
    // Initialize the to be inserted value for easier implementation
    int goal = user->getPerm();
    if(this->root == NULL) { // Root is Null
        this->root = new B_Node(user);
        return;
    } else if(this->root->isLeaf == true) { // Root has one leaf element
        B_Node *new_root = new B_Node(goal);
        new_root->ptr_arr[1] = new B_Node(user);
        new_root->ptr_arr[1]->parent = new_root;
        if(this->root->leaf_arr[0]->getPerm() < goal) {
            new_root->ptr_arr[0] = new B_Node(this->root->leaf_arr[0]);
            new_root->ptr_arr[0]->parent = new_root;
            new_root->value_arr[0] = goal;
        } else {
            new_root->value_arr[0] = goal;
            new_root->ptr_arr[2] = new B_Node(this->root->leaf_arr[0]);
            new_root->ptr_arr[2]->parent = new_root;
            new_root->value_arr[1] = this->root->leaf_arr[0]->getPerm();
        }
        this->root = new_root;
        return;
    }
    // Traverse to the leaf based on the user's perm number, make a new leaf node if there is no leaf at the to be inserted spot yet
    B_Node *runner = this->root;
    B_Node *prev_runner = runner;
    bool noNewLeaf = true;
    while(runner->isLeaf != true) {
        std::cout << "Roadmaps: " << runner->value_arr[0] << ", " << runner->value_arr[1] << ", " << runner->value_arr[2] << std::endl;
        if(goal < runner->value_arr[0]) {
            std::cout << "came to 0" << std::endl;
            if(runner->ptr_arr[0] != NULL) { runner = runner->ptr_arr[0]; } else { noNewLeaf = false; runner->ptr_arr[0] = new B_Node(user); runner->ptr_arr[0]->parent = runner; break; }
        } else if(runner->value_arr[0] == -1 || goal < runner->value_arr[1]) {
            std::cout << "came to 1" << std::endl;
            if(runner->ptr_arr[1] != NULL) { runner = runner->ptr_arr[1]; } else { noNewLeaf = false; prev_runner->value_arr[0] = goal; runner->ptr_arr[1] = new B_Node(user); runner->ptr_arr[1]->parent = runner; break; }
        } else if(runner->value_arr[1] == -1 || goal < runner->value_arr[2]) {
            std::cout << "came to 2" << std::endl;
            if(runner->ptr_arr[2] != NULL) { runner = runner->ptr_arr[2]; } else { noNewLeaf = false; prev_runner->value_arr[1] = goal; runner->ptr_arr[2] = new B_Node(user); runner->ptr_arr[2]->parent = runner; break; }
        } else {
            std::cout << "came to 3" << std::endl;
            if(runner->ptr_arr[3] != NULL) { runner = runner->ptr_arr[3]; } else { noNewLeaf = false; prev_runner->value_arr[2] = goal; runner->ptr_arr[3] = new B_Node(user); runner->ptr_arr[3]->parent = runner; break; }
        }
        if(runner->isLeaf != true) {
            prev_runner = runner;
        }
    }
    // If no new leaf node were created in the traversal process...
    if(noNewLeaf) {
        // If the leaf has a spot for the new user to the inserted
        if(runner->leaf_arr[1] == NULL) {
            runner->leaf_arr[1] = user;
        } else { // If there are no spots available, split and insert
            std::cout << "no spot to insert" << std::endl;
            B_Node *original = runner->parent;
            while(runner->parent != NULL) {
                runner = runner->parent;
            }
            // Making new left B Node and right B Node
            B_Node *new_left = NULL;
            B_Node *new_right = NULL;
            if(original->ptr_arr[0] == NULL) { // If the original node is null on left side
                new_left = new B_Node(original->ptr_arr[1]->leaf_arr[0]->getPerm());
                new_left->ptr_arr[1] = original->ptr_arr[1];
                new_right = new B_Node(original->ptr_arr[2]->leaf_arr[0]->getPerm());
                new_right->ptr_arr[1] = original->ptr_arr[2];
                new_right->ptr_arr[2] = original->ptr_arr[3];
                if(new_right->ptr_arr[2] != NULL) {
                    new_right->value_arr[1] = new_right->ptr_arr[2]->leaf_arr[0]->getPerm();
                }
            } else if(original->ptr_arr[2] == NULL) { // If the original node is null on right side
                new_left = new B_Node(original->ptr_arr[0]->leaf_arr[0]->getPerm());
                new_left->ptr_arr[1] = original->ptr_arr[0];
                new_right = new B_Node(original->ptr_arr[1]->leaf_arr[0]->getPerm());
                new_right->ptr_arr[1] = original->ptr_arr[1];
            } else { // If the original node has everything
                new_left = new B_Node(original->ptr_arr[0]->leaf_arr[0]->getPerm());
                new_left->ptr_arr[1] = original->ptr_arr[0];
                new_left->ptr_arr[2] = original->ptr_arr[1];
                if(new_left->ptr_arr[2] != NULL) {
                    new_left->value_arr[1] = new_left->ptr_arr[2]->leaf_arr[0]->getPerm();
                }
                new_right = new B_Node(original->ptr_arr[2]->leaf_arr[0]->getPerm());
                new_right->ptr_arr[1] = original->ptr_arr[2];
                new_right->ptr_arr[2] = original->ptr_arr[3];
                if(new_right->ptr_arr[2] != NULL) {
                    new_right->value_arr[1] = new_right->ptr_arr[2]->leaf_arr[0]->getPerm();
                }
            }
            // Making a new root and call function again to insert the new user
            B_Node *new_root = new B_Node(original->value_arr[1]);
            new_root->ptr_arr[0] = new_left;
            new_root->ptr_arr[1] = new_right;
            new_left->parent = new_root;
            new_right->parent = new_root;
            this->root = new_root;
            addUser(user);
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