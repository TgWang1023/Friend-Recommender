#include "b-node.h"

class B_Tree {
    public: 
        B_Tree();
        void addUser(User *user);
        bool findUser(int perm);
        void findUserDetail(int perm);
    private: 
        B_Node *root;
};