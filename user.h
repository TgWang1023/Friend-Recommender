#include <string>

class User {
    public: 
        User();
        User(int perm_number, std::string name, std::string genre1, std::string genre2);
        int getPerm();
    private: 
        int perm_number;
        std::string name;
        std::string genre1;
        std::string genre2;
};