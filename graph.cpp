#include "graph.h"
#include <iostream>
#include <algorithm>

Graph::Graph() {
    // Default Constructor
}

Graph::~Graph() {
    // Destructor
}

int Graph::addUser(int user) {
    std::vector<int> single_user;
    single_user.push_back(user);
    this->adj_list.push_back(single_user);
    this->marker_rec.push_back(false);
    return this->adj_list.size() - 1;
}

void Graph::addFriend(int user_idx, int new_friend) {
    this->adj_list.at(user_idx).push_back(new_friend);
}

void Graph::traverse(int perm, B_Tree &tree, std::string genre1, std::string genre2) { // DFS
    User* user = tree.findUserDetail(perm);
    if(user == NULL) {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
        return;
    } else {
        int idx = user->getGraphIdx();
        for(int i = 1; i < this->adj_list.at(idx).size(); i++) {
            if(marker_rec.at(idx) == false) {
                marker_rec[idx] = true;
                //stack.push_back(idx);
                if(user->getGenre1() == genre1 || user->getGenre1() == genre2 || user->getGenre2() == genre1 || user->getGenre2() == genre2) {
                    std::cout << "<" << user->getPerm() << ", " << user->getName() << ", " << user->getGenre1() << ", " << user->getGenre2() << ">" << std::endl;
                }
                traverse(this->adj_list.at(idx).at(i), tree, genre1, genre2);
            }
        }
        //stack.pop_back();
        return;
    }
}

void Graph::filterFriend(int perm, B_Tree &tree) {
    int user_idx = tree.findUserDetail(perm)->getGraphIdx();
    for(int i = 0; i <this->adj_list.at(user_idx).size(); i++) {
        marker_rec[tree.findUserDetail(this->adj_list.at(user_idx).at(i))->getGraphIdx()] = true;
    }
}

void Graph::printFriend(int user_idx) {
    std::cout << "User's friends: ";
    for(int i = 1; i <this->adj_list.at(user_idx).size(); i++) {
        std::cout << this->adj_list.at(user_idx).at(i) << " ";
    }
    std::cout << std::endl;
}

void Graph::reset() {
    for(int i = 0; i < marker_rec.size(); i++) {
        marker_rec[i] = false;
    }
    //stack.clear();
}
