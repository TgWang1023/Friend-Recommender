#include "user.h"

User::User() {
    // Default Construtor
}

User::User(int perm_number, std::string name, std::string genre1, std::string genre2) {
    this->perm_number = perm_number;
    this->name = name;
    this->genre1 = genre1;
    this->genre2 = genre2;
}

int User::getPerm() {
    return this-> perm_number;
}

