#include "graph.h"

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

void Graph::addFriend(int user, int new_friend) {
    this->adj_list.at(user).push_back(new_friend);
}

void Graph::traverse() {

}

