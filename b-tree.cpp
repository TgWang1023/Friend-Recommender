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
        //std::cout << "Roadmaps: " << runner->value_arr[0] << ", " << runner->value_arr[1] << ", " << runner->value_arr[2] << std::endl;
        if(goal < runner->value_arr[0]) {
            //std::cout << "came to 0" << std::endl;
            runner = runner->ptr_arr[0];
            runnerIdx = 0;
        } else if(runner->value_arr[1] == -1 || (runner->value_arr[0] <= goal && goal < runner->value_arr[1])) {
            //std::cout << "came to 1" << std::endl;
            runner = runner->ptr_arr[1];
            runnerIdx = 1;
        } else if(runner->value_arr[2] == -1 || (runner->value_arr[1] <= goal && goal < runner->value_arr[2])) {
            //std::cout << "came to 2" << std::endl;
            runner = runner->ptr_arr[2];
            runnerIdx = 2;
        } else {
            //std::cout << "came to 3" << std::endl;
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
        } else if(runner->leaf_arr[1] != NULL && goal < runner->leaf_arr[1]->getPerm() && goal > runner->leaf_arr[0]->getPerm()) { // If the inserted value is bigger than the bottom leaf, insert the nee value instead and re-insert the previous bottom leaf
            User* temp = runner->leaf_arr[1];
            runner->leaf_arr[1] = user;
            addUser(temp);
            return;
        } else { // If there are no spots available, check if the previous internal node has a open spot.
            if(runnerIdx < 3 && prev_runner->ptr_arr[runnerIdx + 1] == NULL) {
                prev_runner->ptr_arr[runnerIdx + 1] = new B_Node(user);
                prev_runner->ptr_arr[runnerIdx + 1]->parent = prev_runner;
                prev_runner->value_arr[runnerIdx] = prev_runner->ptr_arr[runnerIdx + 1]->leaf_arr[0]->getPerm();
                return;
            } else if(runnerIdx < 3 && prev_runner->ptr_arr[runnerIdx + 1]->leaf_arr[1] == NULL) {
                prev_runner->ptr_arr[runnerIdx + 1]->leaf_arr[1] = prev_runner->ptr_arr[runnerIdx + 1]->leaf_arr[0];
                prev_runner->ptr_arr[runnerIdx + 1]->leaf_arr[0] = user;
                prev_runner->value_arr[runnerIdx] = prev_runner->ptr_arr[runnerIdx + 1]->leaf_arr[0]->getPerm();
                return;
            }
            bool noOpenSlot = true;
            if(runnerIdx == 0 && goal < runner->leaf_arr[0]->getPerm()) {
                runnerIdx = 0;
            } else {
                runnerIdx += 1;
            }
            for(int i = runnerIdx + 1; i < 4; i++) {
                if(prev_runner->ptr_arr[i] == NULL) {
                    for(int j = i; j > runnerIdx; j--) {
                        prev_runner->ptr_arr[j] = prev_runner->ptr_arr[j - 1];
                        prev_runner->value_arr[j - 1] = prev_runner->ptr_arr[j]->leaf_arr[0]->getPerm();
                    }
                    prev_runner->ptr_arr[runnerIdx] = new B_Node(user);
                    prev_runner->ptr_arr[runnerIdx]->parent = prev_runner;
                    if(runnerIdx - 1 >= 0) {
                        prev_runner->value_arr[runnerIdx - 1] = prev_runner->ptr_arr[runnerIdx]->leaf_arr[0]->getPerm();
                    }
                    noOpenSlot = false;
                    break;
                }
            }
            // If all pointers are full, split and insert     
            if(noOpenSlot) {
                // Go upwards to make room for this new user
                while(prev_runner != NULL) {
                    if(prev_runner->parent == NULL) { // If there are no more internal node to insert this new element, make a new root and call function again to insert the new user
                        // Making new left B Node
                        //B_Node *new_left = new B_Node(prev_runner->ptr_arr[0]->leaf_arr[0]->getPerm());
                        B_Node *new_left = new B_Node(prev_runner->value_arr[0]);
                        new_left->ptr_arr[0] = prev_runner->ptr_arr[0];
                        new_left->ptr_arr[0]->parent = new_left;
                        new_left->ptr_arr[1] = prev_runner->ptr_arr[1];
                        new_left->ptr_arr[1]->parent = new_left;
                        // Making new right B Node
                        //B_Node *new_right = new B_Node(prev_runner->ptr_arr[2]->leaf_arr[0]->getPerm());
                        B_Node *new_right = new B_Node(prev_runner->value_arr[2]);
                        new_right->ptr_arr[0] = prev_runner->ptr_arr[2];
                        new_right->ptr_arr[0]->parent = new_right;
                        new_right->ptr_arr[1] = prev_runner->ptr_arr[3];
                        new_right->ptr_arr[1]->parent = new_right;
                        // Making a new root
                        B_Node *new_root = new B_Node(prev_runner->value_arr[1]);
                        new_root->ptr_arr[0] = new_left;
                        new_root->ptr_arr[1] = new_right;
                        new_root->ptr_arr[2] = NULL;
                        new_root->ptr_arr[3] = NULL;
                        new_left->parent = new_root;
                        new_right->parent = new_root;
                        this->root = new_root;
                        addUser(user);
                        return;
                    } else {
                        prev_runner = prev_runner->parent;
                        runner = runner->parent;
                        if(goal < prev_runner->value_arr[0]) {
                            bool foundSpot = false;
                            for(int i = 2; i < 4; i++) {
                                if(prev_runner->ptr_arr[i] == NULL) {
                                    foundSpot = true;
                                    for(int j = i; j > 0; j--) {
                                        prev_runner->ptr_arr[j] = prev_runner->ptr_arr[j - 1];
                                        if(j < 3) {
                                            prev_runner->value_arr[j] = prev_runner->value_arr[j - 1];
                                        }
                                    }  
                                    runner = prev_runner->ptr_arr[1];
                                    break; 
                                }
                            }
                            if(foundSpot == true) {
                                prev_runner->ptr_arr[0] = new B_Node(runner->value_arr[0]);
                                prev_runner->ptr_arr[0]->parent = prev_runner;
                                prev_runner->ptr_arr[0]->ptr_arr[0] = runner->ptr_arr[0];
                                prev_runner->ptr_arr[0]->ptr_arr[0]->parent = prev_runner->ptr_arr[0];
                                prev_runner->ptr_arr[0]->ptr_arr[1] = runner->ptr_arr[1];
                                prev_runner->ptr_arr[0]->ptr_arr[1]->parent = prev_runner->ptr_arr[0];
                                prev_runner->value_arr[0] = runner->value_arr[1];
                                prev_runner->ptr_arr[0]->value_arr[0] = runner->value_arr[0];
                                runner->ptr_arr[0] = runner->ptr_arr[2];
                                runner->ptr_arr[1] = runner->ptr_arr[3];
                                runner->value_arr[0] = runner->value_arr[2];
                                runner->value_arr[1] = -1;
                                runner->value_arr[2] = -1;
                                runner->ptr_arr[2] = NULL;
                                runner->ptr_arr[3] = NULL;
                                addUser(user);
                                return;
                            }
                        } else {
                            for(int i = 2; i < 4; i++) {
                                if(prev_runner->ptr_arr[i] == NULL) {
                                    runner = prev_runner->ptr_arr[i - 1];
                                    prev_runner->ptr_arr[i] = new B_Node(runner->value_arr[2]);
                                    prev_runner->ptr_arr[i]->parent = prev_runner;
                                    prev_runner->ptr_arr[i]->ptr_arr[0] = runner->ptr_arr[2];
                                    prev_runner->ptr_arr[i]->ptr_arr[0]->parent = prev_runner->ptr_arr[i];
                                    prev_runner->ptr_arr[i]->ptr_arr[1] = runner->ptr_arr[3];
                                    prev_runner->ptr_arr[i]->ptr_arr[1]->parent = prev_runner->ptr_arr[i];
                                    prev_runner->value_arr[i - 1] = runner->value_arr[1];
                                    prev_runner->ptr_arr[i]->value_arr[0] = runner->value_arr[2];
                                    runner->value_arr[1] = -1;
                                    runner->value_arr[2] = -1;
                                    runner->ptr_arr[2] = NULL;
                                    runner->ptr_arr[3] = NULL;
                                    addUser(user);
                                    return;
                                }
                            }
                        }
                    }  
                }     
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
        } else if(runner->value_arr[1] == -1 || (runner->value_arr[0] <= perm && perm < runner->value_arr[1])) {
            runner = runner->ptr_arr[1];
        } else if(runner->value_arr[2] == -1 || (runner->value_arr[1] <= perm && perm < runner->value_arr[2])) {
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

User* B_Tree::findUserDetail(int perm) {
    // Empty tree case
    if(this->root == NULL) {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
        return NULL;
    }
    // Traverse to the leaf based on the user's perm number
    B_Node *runner = this->root;
    while(runner != NULL && runner->isLeaf != true) {
        if(perm < runner->value_arr[0]) {
            //std::cout << "came to 0" << std::endl;
            runner = runner->ptr_arr[0];
        } else if(runner->value_arr[1] == -1 || (runner->value_arr[0] <= perm && perm < runner->value_arr[1])) {
            //std::cout << "came to 1" << std::endl;
            runner = runner->ptr_arr[1];
        } else if(runner->value_arr[2] == -1 || (runner->value_arr[1] <= perm && perm < runner->value_arr[2])) {
            //std::cout << "came to 2" << std::endl;
            runner = runner->ptr_arr[2];
        } else {
            //std::cout << "came to 3" << std::endl;
            runner = runner->ptr_arr[3];
        }
    }
    // Return the graph index if found, -1 otherwise
    if(runner == NULL || (runner->leaf_arr[0]->getPerm() != perm && runner->leaf_arr[1] == NULL)) {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
        return NULL;
    } else if(runner->leaf_arr[0] != NULL && runner->leaf_arr[0]->getPerm() == perm) {
        std::cout << "User's perm number: " << runner->leaf_arr[0]->getPerm() << std::endl;
        std::cout << "User's name: " << runner->leaf_arr[0]->getName() << std::endl;
        std::cout << "User's first favourite genre: " << runner->leaf_arr[0]->getGenre1() << std::endl;
        std::cout << "User's second favourite genre: " << runner->leaf_arr[0]->getGenre2() << std::endl;
        return runner->leaf_arr[0];
    } else if(runner->leaf_arr[1] != NULL && runner->leaf_arr[1]->getPerm() == perm) {
        std::cout << "User's perm number: " << runner->leaf_arr[1]->getPerm() << std::endl;
        std::cout << "User's name: " << runner->leaf_arr[1]->getName() << std::endl;
        std::cout << "User's first favourite genre: " << runner->leaf_arr[1]->getGenre1() << std::endl;
        std::cout << "User's second favourite genre: " << runner->leaf_arr[1]->getGenre2() << std::endl;
        return runner->leaf_arr[1];
    } else {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
    }
    return NULL;
}

User* B_Tree::findUserDetailNoPrint(int perm) {
    // Empty tree case
    if(this->root == NULL) {
        return NULL;
    }
    // Traverse to the leaf based on the user's perm number
    B_Node *runner = this->root;
    while(runner != NULL && runner->isLeaf != true) {
        if(perm < runner->value_arr[0]) {
            runner = runner->ptr_arr[0];
        } else if(runner->value_arr[1] == -1 || (runner->value_arr[0] <= perm && perm < runner->value_arr[1])) {
            runner = runner->ptr_arr[1];
        } else if(runner->value_arr[2] == -1 || (runner->value_arr[1] <= perm && perm < runner->value_arr[2])) {
            runner = runner->ptr_arr[2];
        } else {
            runner = runner->ptr_arr[3];
        }
    }
    // Return the graph index if found, -1 otherwise
    if(runner == NULL || (runner->leaf_arr[0]->getPerm() != perm && runner->leaf_arr[1] == NULL)) {
        return NULL;
    } else if(runner->leaf_arr[0] != NULL && runner->leaf_arr[0]->getPerm() == perm) {
        return runner->leaf_arr[0];
    } else if(runner->leaf_arr[1] != NULL && runner->leaf_arr[1]->getPerm() == perm) {
        return runner->leaf_arr[1];
    } 
    return NULL;
}

void B_Tree::clear() {
    this->root = NULL;
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