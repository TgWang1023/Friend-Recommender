#ifndef _USER_H_
#define _USER_H_

#include <string>

class User {
    public: 
        User();
        User(int perm_number, std::string name, std::string genre1, std::string genre2);
        int getPerm();
        std::string getName();
        std::string getGenre1();
        std::string getGenre2();
    private: 
        int perm_number;
        std::string name;
        std::string genre1;
        std::string genre2;
};

#endif