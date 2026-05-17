#include "NotinOOP.hpp"
#include <sstream> 
void NotinOOP::processCommand(const std::string &commandLine)
{
    if (commandLine.empty()) return;

    std::stringstream ss(commandLine);
    std::string command;
    ss >> command;

    // Basic commands:
    if (command == "register")
    {
        std::string username, password;
        ss >> username >> password;
        handleRegister(username, password);
    }
    else if (command == "login")
    {
        std::string username, password;
        ss >> username >> password;
        handleLogin(username, password);
    }

    // Buyer commands:
}