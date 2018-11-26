#ifndef _B_NODE_H_
#define _B_NODE_H_

#include "user.h"

class B_Node {
    public: 
        B_Node();
        B_Node(int num);
        B_Node(User *user, bool isTop);
        void addValue(int num);
        void set_l(B_Node *node);
        void set_ml(B_Node *node);
        void set_mr(B_Node *node);
        void set_r(B_Node *node);
        int get_l();
        int get_m();
        int get_r();
        bool checkLeaf();
    private: 
        int value_l;
        int value_m;
        int value_r;
        B_Node *ptr_l;
        B_Node *ptr_ml;
        B_Node *ptr_mr;
        B_Node *ptr_r;
        bool isLeaf;
        User *top_leaf;
        User *bottom_leaf;
};

#endif