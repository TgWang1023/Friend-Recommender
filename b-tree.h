#ifndef _B_TREE_H_
#define _B_TREE_H_

#include "b-node.h"

class B_Tree {
    public: 
        B_Tree();
        ~B_Tree();
        void addUser(User *user);
        void findUser(int perm);
        int findUserDetail(int perm);
    private: 
        B_Node *root;
};

#endif