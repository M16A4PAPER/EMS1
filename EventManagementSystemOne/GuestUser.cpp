// GuestUser.cpp
#include "GuestUser.h"
#include <iostream>
#include <limits>

using namespace std;

GuestUser::GuestUser(EventManager& mgr) : User(mgr) {}

void GuestUser::showMenu() {
    int choice;
    do {
        cout << "\n=============================================\n";
        cout << "|           Guest Event View Menu            |\n";
        cout << "=============================================\n";
        cout << "| 1. View All Events                         |\n";
        cout << "| 0. Exit to Main Menu                       |\n";
        cout << "=============================================\n";
        cout << " Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "\n--- All Available Events ---\n";
            manager.displayEvents();
            break;
        case 0:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);
}

