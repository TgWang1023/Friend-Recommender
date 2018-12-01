#ifndef _B_TREE_H_
#define _B_TREE_H_

#include "b-node.h"

class B_Tree {
    public: 
        B_Tree();
        ~B_Tree();
        void addUser(User *user);
        void findUser(int perm);
        User* findUserDetail(int perm);
        User* findUserDetailNoPrint(int perm);
        void clear();
    private: 
        B_Node *root;
};

#endif