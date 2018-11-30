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
        if(this->root->leaf_arr[0]->getPerm() < goal) {
            new_root->ptr_arr[1] = new B_Node(user);
            new_root->ptr_arr[1]->parent = new_root;
            new_root->ptr_arr[0] = new B_Node(this->root->leaf_arr[0]);
            new_root->ptr_arr[0]->parent = new_root;
            new_root->value_arr[0] = goal;
        } else {
            new_root->ptr_arr[0] = new B_Node(user);
            new_root->ptr_arr[0]->parent = new_root;
            new_root->ptr_arr[1] = new B_Node(this->root->leaf_arr[0]);
            new_root->ptr_arr[1]->parent = new_root;
            new_root->value_arr[0] = this->root->leaf_arr[0]->getPerm();
        }
        this->root = new_root;
        return;
    }
    // Traverse to the leaf based on the user's perm number, make a new leaf node if there is no leaf at the to be inserted spot yet
    B_Node *runner = this->root;
    B_Node *prev_runner = runner;
    int runnerIdx;
    // Traverse to the correct spot first
    while(runner != NULL && runner->isLeaf == false) {
        std::cout << "Roadmaps: " << runner->value_arr[0] << ", " << runner->value_arr[1] << ", " << runner->value_arr[2] << std::endl;
        if(goal < runner->value_arr[0]) {
            runner = runner->ptr_arr[0];
            runnerIdx = 0;
        } else if(runner->value_arr[1] == -1 || runner->value_arr[0] <= goal < runner->value_arr[1]) {
            runner = runner->ptr_arr[1];
            runnerIdx = 1;
        } else if(runner->value_arr[2] == -1 || runner->value_arr[1] <= goal < runner->value_arr[2]) {
            runner = runner->ptr_arr[2];
            runnerIdx = 2;
        } else {
            runner = runner->ptr_arr[3];
            runnerIdx = 3;
        }
        if(runner != NULL && runner->isLeaf == false) {
            prev_runner = runner;
        }
    }
    // If the runner is null
    if(runner == NULL) {
        prev_runner->ptr_arr[runnerIdx] = new B_Node(user);
        prev_runner->ptr_arr[runnerIdx]->parent = prev_runner;
        if(runnerIdx > 0) {
            prev_runner->value_arr[runnerIdx - 1] = prev_runner->ptr_arr[runnerIdx]->leaf_arr[0]->getPerm();
        }
    } else { // If no new leaf node were created in the traversal process...
        if(runner->leaf_arr[1] == NULL) { // If the leaf has a spot for the new user to the inserted
            runner->leaf_arr[1] = user; 
        } else if(runner->leaf_arr[1] != NULL && goal < runner->leaf_arr[1]->getPerm()) { // If the inserted value is bigger than the bottom leaf, insert the nee value instead and re-insert the previous bottom leaf
            User* temp = runner->leaf_arr[1];
            runner->leaf_arr[1] = user;
            addUser(temp);
            return;
        } else { // If there are no spots available, check if the previous internal node has a open spot.
            bool noOpenSlot = true;
            for(int i = runnerIdx + 1; i < 4; i++) {
                if(runner->parent->ptr_arr[i] == NULL) {
                    for(int j = i; j > runnerIdx; j--) {
                        runner->parent->ptr_arr[j] = runner->parent->ptr_arr[j - 1];
                        runner->parent->value_arr[j - 1] = runner->parent->ptr_arr[j]->leaf_arr[0]->getPerm();
                    }
                    runner->parent->ptr_arr[runnerIdx] = new B_Node(user);
                    runner->parent->ptr_arr[runnerIdx]->parent = runner->parent;
                    if(runnerIdx - 1 >= 0) {
                        runner->parent->value_arr[runnerIdx - 1] = runner->parent->ptr_arr[runnerIdx]->leaf_arr[0]->getPerm();
                    }
                    noOpenSlot = false;
                    break;
                }
            }
            // If all pointers are full, split and insert     
            if(noOpenSlot) {
                std::cout << "no spot to insert" << std::endl;
                B_Node *original = runner->parent;
                while(runner->parent != NULL) {
                    runner = runner->parent;
                }
                // Making new left B Node
                B_Node *new_left = new B_Node(original->ptr_arr[0]->leaf_arr[0]->getPerm());
                new_left->ptr_arr[0] = original->ptr_arr[0];
                new_left->ptr_arr[0]->parent = new_left;
                new_left->ptr_arr[1] = original->ptr_arr[1];
                new_left->ptr_arr[1]->parent = new_left;
                new_left->value_arr[0] = new_left->ptr_arr[1]->leaf_arr[0]->getPerm();
                // Making new right B Node
                B_Node *new_right = new B_Node(original->ptr_arr[2]->leaf_arr[0]->getPerm());
                new_right->ptr_arr[0] = original->ptr_arr[2];
                new_right->ptr_arr[0]->parent = new_right;
                new_right->ptr_arr[1] = original->ptr_arr[3];
                new_right->ptr_arr[1]->parent = new_right;
                new_right->value_arr[0] = new_right->ptr_arr[1]->leaf_arr[0]->getPerm();

                /*************** FIX: Should not always make a new root.****************
                If the parent of the full node has an avaiable spot, insert it there. */

                // Making a new root and call function again to insert the new user
                B_Node *new_root = new B_Node(original->value_arr[1]);
                new_root->ptr_arr[0] = new_left;
                new_root->ptr_arr[1] = new_right;
                new_root->ptr_arr[2] = NULL;
                new_root->ptr_arr[3] = NULL;
                new_left->parent = new_root;
                new_right->parent = new_root;
                this->root = new_root;
                addUser(user);
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
        } else if(runner->value_arr[1] == -1 || runner->value_arr[0] <= perm < runner->value_arr[1]) {
            runner = runner->ptr_arr[1];
        } else if(runner->value_arr[2] == -1 || runner->value_arr[1] <= perm < runner->value_arr[2]) {
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
        } else if(runner->value_arr[1] == -1 || runner->value_arr[0] <= perm < runner->value_arr[1]) {
            runner = runner->ptr_arr[1];
        } else if(runner->value_arr[2] == -1 || runner->value_arr[1] <= perm < runner->value_arr[2]) {
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

/* --------Backup code for checking the left side of a internal node
// Check left side second
if(noOpenSlot) {
    for(int i = runnerIdx - 1; i > -1; i--) {
        if(runner->parent->ptr_arr[i] == NULL) {
            for(int j = i; j < runnerIdx; j++) {
                runner->parent->ptr_arr[j] = runner->parent->ptr_arr[j + 1];
                if(j - 1 >= 0) {
                    runner->parent->value_arr[j - 1] = runner->parent->ptr_arr[j]->leaf_arr[0]->getPerm();
                }   
            }
            runner->parent->ptr_arr[runnerIdx] = new B_Node(user);
            runner->parent->ptr_arr[runnerIdx]->parent = runner->parent;
            runner->parent->value_arr[runnerIdx - 1] = runner->parent->ptr_arr[runnerIdx]->leaf_arr[0]->getPerm();
            noOpenSlot = false;
            break;
        }
    }
}

// Inserting a new node
if(goal < runner->value_arr[0]) {
    std::cout << "came to 0" << std::endl;
    if(runner->ptr_arr[0] != NULL) { 
        if(runner->ptr_arr[0]->isLeaf == true && runner->ptr_arr[0]->leaf_arr[1] != NULL && runner->ptr_arr[0]->leaf_arr[1]->getPerm() > goal && runner->ptr_arr[0]->leaf_arr[0]->getPerm() < goal) {
            User *temp = runner->ptr_arr[0]->leaf_arr[1];
            runner->ptr_arr[0]->leaf_arr[1] = user;
            addUser(temp);
            return;
        }
        runner = runner->ptr_arr[0]; 
        runnerIdx = 0; 
    } else { 
        noNewLeaf = false; 
        runner->ptr_arr[0] = new B_Node(user); 
        runner->ptr_arr[0]->parent = runner; 
        break; 
    }
} else if(runner->value_arr[0] == -1 || (goal > runner->value_arr[0] && runner->value_arr[1] != -1 && goal < runner->value_arr[1]) || (runner->ptr_arr[1] != NULL && runner->ptr_arr[1]->isLeaf == false && runner->value_arr[1] == -1)) {
    std::cout << "came to 1" << std::endl;
    if(runner->ptr_arr[1] != NULL) { 
        if(runner->ptr_arr[1]->isLeaf == true && runner->ptr_arr[1]->leaf_arr[1] != NULL && runner->ptr_arr[1]->leaf_arr[1]->getPerm() > goal) {
            std::cout << "detected middle" << std::endl;
            User *temp = runner->ptr_arr[1]->leaf_arr[1];
            runner->ptr_arr[1]->leaf_arr[1] = user;
            addUser(temp);
            return;
        }
        runner = runner->ptr_arr[1]; 
        runnerIdx = 1; 
    } else { 
        noNewLeaf = false; 
        prev_runner->value_arr[0] = goal; 
        runner->ptr_arr[1] = new B_Node(user); 
        runner->ptr_arr[1]->parent = runner; 
        break; 
    }
} else if(runner->value_arr[1] == -1 || (goal > runner->value_arr[1] && runner->value_arr[2] != -1 && goal < runner->value_arr[2]) || (runner->ptr_arr[2] != NULL && runner->ptr_arr[2]->isLeaf == false && runner->value_arr[2] == -1)) {
    std::cout << "came to 2" << std::endl;
    if(runner->ptr_arr[2] != NULL) { 
        if(runner->ptr_arr[2]->isLeaf == true && runner->ptr_arr[2]->leaf_arr[1] != NULL && runner->ptr_arr[2]->leaf_arr[1]->getPerm() > goal) {
            User *temp = runner->ptr_arr[2]->leaf_arr[1];
            runner->ptr_arr[2]->leaf_arr[1] = user;
            addUser(temp);
            return;
        }
        runner = runner->ptr_arr[2]; 
        runnerIdx = 2; 
    } else { 
        noNewLeaf = false; 
        prev_runner->value_arr[1] = goal; 
        runner->ptr_arr[2] = new B_Node(user); 
        runner->ptr_arr[2]->parent = runner; 
        break; 
    }
} else {
    std::cout << "came to 3" << std::endl;
    if(runner->ptr_arr[3] != NULL) { 
        if(runner->ptr_arr[3]->isLeaf == true && runner->ptr_arr[3]->leaf_arr[1] != NULL && runner->ptr_arr[3]->leaf_arr[1]->getPerm() > goal) {
            User *temp = runner->ptr_arr[3]->leaf_arr[1];
            runner->ptr_arr[3]->leaf_arr[1] = user;
            addUser(temp);
            return;
        }
        runner = runner->ptr_arr[3]; 
        runnerIdx = 3; 
    } else { 
        noNewLeaf = false; 
        prev_runner->value_arr[2] = goal; 
        runner->ptr_arr[3] = new B_Node(user); 
        runner->ptr_arr[3]->parent = runner; 
        break; 
    }
}
*/