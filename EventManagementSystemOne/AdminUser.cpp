// AdminUser.cpp
#include "AdminUser.h"
#include <iostream>
#include <limits>

using namespace std;

AdminUser::AdminUser(EventManager& mgr) : User(mgr) {}

void AdminUser::showMenu() {
    int choice;
    do {
        cout << "\n=============================================\n";
        cout << "|         Admin Event Management Menu        |\n";
        cout << "=============================================\n";
        cout << "| 1. Add Event                               |\n";
        cout << "| 2. Update Existing Event                   |\n";
        cout << "| 3. Delete Event                            |\n";
        cout << "| 4. View All Events                         |\n";
        cout << "| 5. Export Events to CSV                    |\n";
        cout << "| 6. Import Events from CSV                  |\n";
        cout << "| 0. Exit to Main Menu                       |\n";
        cout << "=============================================\n";
        cout << " Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
            case 1: {
                int id; string name, date, venue;
                cout << "\n--- Add New Event ---\n";
                cout << "ID: "; cin >> id; cin.ignore();
                cout << "Name: "; getline(cin, name);
                cout << "Date (YYYY-MM-DD): "; getline(cin, date);
                cout << "Venue: "; getline(cin, venue);
                manager.addEvent(Event(id, name, date, venue));
                cout << "Event added successfully.\n";
                break;
            }
            case 2: {
                int id; string name, date, venue;
                cout << "\n--- Update Event ---\n";
                cout << "ID to update: "; cin >> id; cin.ignore();
                cout << "New Name: "; getline(cin, name);
                cout << "New Date (YYYY-MM-DD): "; getline(cin, date);
                cout << "New Venue: "; getline(cin, venue);
                manager.updateEvent(id, name, date, venue);
                cout << "Event updated successfully.\n";
                break;
            }
            case 3: {
                int id;
                cout << "\n--- Delete Event ---\n";
                cout << "ID to delete: "; cin >> id;
                manager.deleteEvent(id);
                cout << "Event deleted successfully.\n";
                break;
            }
            case 4: {
                cout << "\n--- All Scheduled Events ---\n";
                manager.displayEvents();
                break;
            }
            case 5: {
                string filename;
                cout << "\n--- Export Events to CSV ---\n";
                cout << "Enter filename (e.g., events.csv): ";
                getline(cin, filename);
                manager.exportToCSV(filename);
                break;
            }
            case 6: {
                string filename;
                cout << "\n--- Import Events from CSV ---\n";
                cout << "Enter filename (e.g., events.csv): ";
                getline(cin, filename);
                manager.importFromCSV(filename);
                break;
            }
            case 0:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
            }
        }
        catch (const exception& ex) {
            cout << "Error: " << ex.what() << endl;
        }
    } while (choice != 0);
}
