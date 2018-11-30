#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>

class Graph {
    public: 
        Graph();
        ~Graph();
        int addUser(int user);
        void addFriend(int user, int new_friend);
        void traverse();
    private: 
        std::vector< std::vector<int> > adj_list;
};

#endif