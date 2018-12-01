#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include "b-tree.h"

class Graph {
    public: 
        Graph();
        ~Graph();
        int addUser(int user);
        void addFriend(int user_idx, int new_friend);
        void traverse(int perm, B_Tree &tree, std::string genre1, std::string genre2);
        void traverseHelper(int perm, B_Tree &tree, std::string genre1, std::string genre2, bool visited[], int original_idx);
        // void filterFriend(int user_idx, B_Tree &tree);
        void printFriend(int user_idx);
        void clear();
    private: 
        std::vector< std::vector<int> > adj_list;
        // std::vector<bool> marker_rec;
        //std::vector<int> stack;
};

#endif