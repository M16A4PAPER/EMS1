// AuthenticateUser.cpp
#include "AuthenticateUser.h"
#include "AdminUser.h"
#include "GuestUser.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

unique_ptr<User> AuthenticateUser::login(EventManager& mgr) {
    int choice;
    cout << "\nSelect Role:\n1. Admin\n2. Guest\nChoice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1) {
        string uname, pwd;
        cout << "Username: "; getline(cin, uname);
        cout << "Password: "; getline(cin, pwd);
        if (uname == "admin" && pwd == "password") {
            return make_unique<AdminUser>(mgr);
        }
        else {
            cout << "Login failed. Proceeding as Guest.\n";
        }
    }

    return make_unique<GuestUser>(mgr);
}
