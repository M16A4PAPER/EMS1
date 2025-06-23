// main.cpp
#include "AuthenticateUser.h"
#include <memory>

int main() {
    EventManager manager;
    manager.loadFromFile();

    AuthenticateUser auth;
    unique_ptr<User> user = auth.login(manager);

    user->showMenu();

    manager.saveToFile();
    cout << "\nThank you for using the Event Management System." << endl;
    return 0;
}
