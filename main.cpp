#include <iostream>
#include <fstream>
#include "b-tree.h"
#include "graph.h"

using namespace std;

int main() {
    fstream word_file;
    B_Tree tree;
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
        cout << "-------------------------" << endl;

        switch(choice) {
            case '1': {
                word_file.close();
                cout << "Please enter the name of the file: ";
                string filename;
                cin.ignore();
                getline(cin, filename);
                word_file.open(filename);
                if (word_file.is_open()) {
                    cout << "Successfully opened file." << endl;
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
                // Getting user input
                cout << "Please enter the user's perm number: ";
                cin.ignore();
                getline(cin, perm_input);
                cout << "Please enter the user's name: ";
                cin.ignore();
                getline(cin, name_input);
                cout << "Please enter the user's first favourite movie genre: ";
                cin.ignore();
                getline(cin, genre1_input);
                cout << "Please enter the user's second favourite movie genre: ";
                cin.ignore();
                getline(cin, genre2_input);
                // Adding the new user to the tree
                try {
                    User *new_user = new User(stoi(perm_input), name_input, genre1_input, genre2_input);
                    tree.addUser(new_user);
                    cout << "User added successfully." << endl;
                } catch(invalid_argument i) {
                    cout << "ERROR: Failed to add user. Invalid perm number." << endl;
                } catch(out_of_range o) {
                    cout << "ERROR: Failed to add user. Perm number too large." << endl;
                }
                break;
            }
            case '3': {
                // Entered Attributes
                string perm_input;
                // Getting user input
                cout << "Please enter the user's perm number: ";
                cin.ignore();
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
                cin.ignore();
                getline(cin, perm_input);
                try {
                    tree.findUserDetail(stoi(perm_input));
                } catch(invalid_argument i) {
                    cout << "ERROR: Failed to find user detail. Invalid perm number." << endl;
                } catch(out_of_range o) {
                    cout << "ERROR: Failed to find user detail. Perm number too large." << endl;
                }
                break;
            }
            case '5': {
                cout << "case 5" << endl;
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