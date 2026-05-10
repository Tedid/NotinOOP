#include <string>

class User{
    protected:
        int userID;
        std::string username;
        std::string password;
    public:
        User(int id, const std::string& name, const std::string& pass);
        //ensures proper deletion of subclass objects through a User pointer
        virtual ~User() = default;

        int getUserID() const;
        std::string getUsername() const;

        bool checkPassword(const std::string& pass) const;

        //ensures every subclass has its own help menu
        virtual void showHelp() const = 0;
};
