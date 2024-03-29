#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <sstream>
#include "b-tree.h"
#include "graph.h"

using namespace std;

int main() {
    fstream word_file;
    B_Tree tree;
    Graph graph;
    cout << "\n\n\nFriend Recommender" << endl;
    cout << "Please select the action you would like to perform:" << endl;

    while(1) {
        cout << "-------------------------" << endl;
        cout << "1: Input file" << endl;
        cout << "2: Add a user" << endl;
        cout << "3: Find a user" << endl;
        cout << "4: Find a user's details" << endl;
        cout << "5: Recommend friends" << endl;
        cout << "0: Exit\n" << endl;
        cout << "Choice: ";
        char choice;
        cin >> choice;
        cin.ignore();
        cout << "-------------------------" << endl;

        switch(choice) {
            case '1': {
                word_file.close();
                cout << "Please enter the name of the file: ";
                string filename;
                getline(cin, filename);
                word_file.open(filename);
                if (word_file.is_open()) {
                    cout << "Successfully opened file." << endl;
                    tree.clear();
                    graph.clear();
                    string line;
                    string perm_input = "";
                    string name_input = "";
                    string genre1_input = "";
                    string genre2_input = "";
                    string friends_perm_input = "";
                    User *new_user;
                    int phase = 0;
                    while(getline(word_file, line)) {
                        for(int i = 0; i < line.length(); i++) {
                            if(line[i] == ';') {
                                if(phase < 4) {
                                    phase++;
                                    if(phase == 4) {
                                        new_user = new User(stoi(perm_input), name_input, genre1_input, genre2_input);
                                        new_user->setGraphIndex(graph.addUser(stoi(perm_input)));
                                    }
                                } else {
                                    graph.addFriend(new_user->getGraphIdx(), stoi(friends_perm_input));
                                    // cout << friends_perm_input << " ";
                                    friends_perm_input = "";
                                }
                            } else {
                                if(phase == 0) {
                                    perm_input += line[i];
                                } else if(phase == 1) {
                                    name_input += line[i];
                                } else if(phase == 2) {
                                    genre1_input += line[i];
                                } else if(phase == 3) {
                                    genre2_input += line[i];
                                } else {
                                    friends_perm_input += line[i];
                                }
                            }
                        }
                        graph.addFriend(new_user->getGraphIdx(), stoi(friends_perm_input));
                        tree.addUser(new_user);
                        // cout << friends_perm_input << " ";
                        // cout << "Added: Perm - " << perm_input << ", Name - " << name_input << ", Genre1 - " << genre1_input << ", Genre2 - " << genre2_input << endl;
                        perm_input = "";
                        name_input = "";
                        genre1_input = "";
                        genre2_input = "";
                        friends_perm_input = "";
                        phase = 0;
                    }
                } else {
                    cout << "Unable to open this file." << endl;
                }
                break;
            }
            case '2': {
                // Entered Attributes
                string perm_input;
                string name_input;
                string genre1_input;
                string genre2_input;
                string friends_input;
                // Getting user input
                cout << "Please enter the user's perm number: ";
                getline(cin, perm_input);
                try {
                    int temp = stoi(perm_input);
                    if(stoi(perm_input) < 0) {
                        throw 99;
                    }
                } catch(invalid_argument i) {
                    cout << "ERROR: Failed to add user. Invalid perm number." << endl;
                    break;
                } catch(out_of_range o) {
                    cout << "ERROR: Failed to add user. Perm number too large." << endl;
                    break;
                } catch(int e) {
                    cout << "ERROR: Failed to add user. Perm number cannot be negative." << endl;
                    break;
                }
                cout << "Please enter the user's name: ";
                getline(cin, name_input);
                cout << "Please enter the user's first favourite movie genre: ";
                getline(cin, genre1_input);
                cout << "Please enter the user's second favourite movie genre: ";
                getline(cin, genre2_input);
                cout << "Please enter the user's list of friends by using their perm numbers, separated by spaces: ";
                getline(cin, friends_input);
                // Adding the new user to the graph
                User *new_user = new User(stoi(perm_input), name_input, genre1_input, genre2_input);
                new_user->setGraphIndex(graph.addUser(stoi(perm_input)));
                // Parsing the friends perm from string into integers
                stringstream ss;
                ss << friends_input;
                string temp;
                int found;
                while(!ss.eof()) {
                    ss >> temp;
                    if(stringstream(temp) >> found) {
                        User *reverse = tree.findUserDetailNoPrint(found);
                        if(reverse != NULL) {
                            graph.addFriend(new_user->getGraphIdx(), found);
                            graph.addFriend(reverse->getGraphIdx(), stoi(perm_input));
                        }
                    }
                    temp = "";
                }
                // Adding the new user to the tree
                tree.addUser(new_user);
                cout << "User added successfully." << endl;
                break;
            }
            case '3': {
                // Entered Attributes
                string perm_input;
                // Getting user input
                cout << "Please enter the user's perm number: ";
                getline(cin, perm_input);
                try {
                    tree.findUser(stoi(perm_input));
                } catch(invalid_argument i) {
                    cout << "ERROR: Failed to find user. Invalid perm number." << endl;
                } catch(out_of_range o) {
                    cout << "ERROR: Failed to find user. Perm number too large." << endl;
                }
                break;
            }
            case '4': {
                // Entered Attributes
                string perm_input;
                // Getting user input
                cout << "Please enter the user's perm number: ";
                getline(cin, perm_input);
                try {
                    User* user = tree.findUserDetail(stoi(perm_input));
                    if (user != NULL) {
                        graph.printFriend(user->getGraphIdx());
                    }
                } catch(invalid_argument i) {
                    cout << "ERROR: Failed to find user detail. Invalid perm number." << endl;
                } catch(out_of_range o) {
                    cout << "ERROR: Failed to find user detail. Perm number too large." << endl;
                }
                break;
            }
            case '5': {
                // Entered Attributes
                string perm_input;
                // Getting user input
                cout << "Please enter the user's perm number: ";
                getline(cin, perm_input);
                try {
                    User* user = tree.findUserDetailNoPrint(stoi(perm_input));
                    if (user != NULL) {
                        cout << "Here is the list of recommended friends: " << endl;
                        cout << "-------------------------" << endl;
                        graph.traverse(stoi(perm_input), tree, user->getGenre1(), user->getGenre2());
                    }
                } catch(invalid_argument i) {
                    cout << "ERROR: Failed to find user detail. Invalid perm number." << endl;
                } catch(out_of_range o) {
                    cout << "ERROR: Failed to find user detail. Perm number too large." << endl;
                }
                break;
            }
            case '0': {
                cout << "Goodbye" << endl;
                word_file.close();
                exit(0);
            }
            default:
                cout << "Please enter 1, 2, 3, 4 or 5 to perform an action or 0 to quit" << endl;
        }
    }
    return 0;
}

/********* Backup code for testing *********
case 't': { // B Tree test function
    int test_arr[100];
    for(int i = 0; i < 100; i++) {
        test_arr[i] = i;
    }
    for(int i = 99; i >= 0; i--) {
        int j = rand() % (i + 1);
        swap(test_arr[i], test_arr[j]);
    }
    for(int i = 0; i < 100; i++) {
        cout << test_arr[i] << " ";
    }
    for(int i = 0; i < 100; i++) {
        tree.addUser(new User(test_arr[i], "a", "a", "a"));
    }
    cout << endl;
}
case 'g': { // Graph test function
    int idx;
    cout << "Enter the graph index: ";
    cin >> idx;
    cin.ignore();
    graph.printFriend(idx);
}
*/