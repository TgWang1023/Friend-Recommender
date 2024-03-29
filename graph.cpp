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
    // this->marker_rec.push_back(false);
    return this->adj_list.size() - 1;
}

void Graph::addFriend(int user_idx, int new_friend) {
    this->adj_list.at(user_idx).push_back(new_friend);
}

void Graph::traverse(int perm, B_Tree &tree, std::string genre1, std::string genre2) {
    bool *visited = new bool[this->adj_list.size()]; 
    for (int i = 0; i < this->adj_list.size(); i++) {
        visited[i] = false; 
    }
    User *originalUser = tree.findUserDetailNoPrint(perm);
    if(originalUser != NULL) {
        traverseHelper(perm, tree, genre1, genre2, visited, originalUser->getGraphIdx()); 
    }
}

void Graph::traverseHelper(int perm, B_Tree &tree, std::string genre1, std::string genre2, bool visited[], int original_idx) {
    User* user = tree.findUserDetailNoPrint(perm);
    int user_idx = user->getGraphIdx();
    visited[user_idx] = true; 
    bool notFriend = true;
    for(int j = 0; j < this->adj_list.at(original_idx).size(); j++) {
        if(user->getPerm() == this->adj_list.at(original_idx).at(j)) {
            notFriend = false;
            break;
        }
    }
    if((user->getGenre1() == genre1 || user->getGenre1() == genre2 || user->getGenre2() == genre1 || user->getGenre2() == genre2) && notFriend) {
        std::cout << "<" << user->getPerm() << ", " << user->getName() << ", " << user->getGenre1() << ", " << user->getGenre2() << ">" << std::endl;
    } 

    for (int i = 0; i < this->adj_list[user_idx].size(); ++i) {
        User *temp = tree.findUserDetailNoPrint(this->adj_list[user_idx].at(i));
        if (temp != NULL && !visited[tree.findUserDetailNoPrint(this->adj_list[user_idx].at(i))->getGraphIdx()]) {
            traverseHelper(this->adj_list[user_idx].at(i), tree, genre1, genre2, visited, original_idx); 
        }
    }
    
}

void Graph::printFriend(int user_idx) {
    std::cout << "User's friends: ";
    for(int i = 1; i <this->adj_list.at(user_idx).size(); i++) {
        std::cout << this->adj_list.at(user_idx).at(i) << " ";
    }
    std::cout << std::endl;
}

void Graph::clear() {
    this->adj_list.clear();
    // this->marker_rec.clear();
}

/************* Backup Code ***************
void Graph::filterFriend(int perm, B_Tree &tree) {
    int user_idx = tree.findUserDetailNoPrint(perm)->getGraphIdx();
    for(int i = 0; i < this->adj_list.at(user_idx).size(); i++) {
        marker_rec[tree.findUserDetailNoPrint(this->adj_list.at(user_idx).at(i))->getGraphIdx()] = true;
    }
}

void Graph::traverse(int perm, B_Tree &tree, std::string genre1, std::string genre2, int original) { // DFS
    User* user = tree.findUserDetailNoPrint(perm);
    int original_idx = tree.findUserDetailNoPrint(original)->getGraphIdx();
    if(user == NULL) {
        std::cout << "No user with the perm number " << perm << " was found." << std::endl;
        return;
    } else {
        int idx = user->getGraphIdx();
        marker_rec[idx] = true;
        for(int i = 1; i < this->adj_list.at(idx).size(); i++) {
            int checking = tree.findUserDetailNoPrint(this->adj_list.at(idx).at(i))->getGraphIdx();
            if(marker_rec.at(checking) == false) {
                marker_rec[checking] = true;
                bool notFriend = true;
                for(int j = 0; j < this->adj_list.at(original_idx).size(); j++) {
                    if(user->getPerm() == this->adj_list.at(original_idx).at(j)) {
                        notFriend = false;
                        break;
                    }
                }
                if((user->getGenre1() == genre1 || user->getGenre1() == genre2 || user->getGenre2() == genre1 || user->getGenre2() == genre2) && notFriend) {
                    std::cout << "<" << user->getPerm() << ", " << user->getName() << ", " << user->getGenre1() << ", " << user->getGenre2() << ">" << std::endl;
                } 
                traverse(this->adj_list.at(idx).at(i), tree, genre1, genre2, original);
            }
        }
        //stack.pop_back();
        return;
    }
}
*/

