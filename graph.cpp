#include "graph.h"
#include <iostream>

Graph::Graph() {

}

Graph::~Graph() {
    // Destructor
}

int Graph::addUser(int user) {
    std::vector<int> single_user;
    single_user.push_back(user);
    this->adj_list.push_back(single_user);
    return this->adj_list.size() - 1;
}

int Graph::getCurrIdx() {
    return this->adj_list.size() - 1;
}

void Graph::addFriend(int user_idx, int new_friend) {
    this->adj_list.at(user_idx).push_back(new_friend);
}

void Graph::traverse() {

}

void Graph::printFriend(int user_idx) {
    for(int i = 0; i <this->adj_list.at(user_idx).size(); i++) {
        std::cout << this->adj_list.at(user_idx).at(i) << " ";
    }
    std::cout << std::endl;
}
