#include <iostream>
#include <limits>
#include "Event.cpp"
#include "AuthenticateUser.cpp"  // Include the new class

using namespace std;

enum class UserRole { Guest, Admin };

int main() {
	Event eventSystem;
	AuthenticateUser auth;
	UserRole role = UserRole::Guest;

	int userChoice = auth.selectUserRole();

	if (userChoice == 1) {
		if (auth.authenticateAdmin()) {
			cout << "Admin login successful.\n";
			role = UserRole::Admin;
		}
		else {
			cout << "Admin login failed. Defaulting to Guest access.\n";
		}
	}
	else {
		cout << "Guest access granted.\n";
	}

	int choice;

	do {
		cout << "\n";
		cout << "======================================================\n";
		cout << "|               Event Management System              |\n";
		cout << "======================================================\n";
		cout << "|  1. Add Event                                      |\n";
		cout << "|  2. Display All Events                             |\n";
		cout << "|  3. Update Event                                   |\n";
		cout << "|  4. Delete Event                                   |\n";
		cout << "|  5. Search Event                                   |\n";
		cout << "|  6. Export Events to CSV (Desktop)                 |\n";
		cout << "|  7. Export Events to TXT (Desktop)                 |\n";
		cout << "|  0. Exit                                           |\n";
		cout << "======================================================\n";
		cout << " Enter your choice: ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

		cout << "\n";

		if ((choice == 1 || choice == 3 || choice == 4) && role != UserRole::Admin) {
			cout << "Access denied. Admin privileges required for this operation.\n";
			continue;
		}

		switch (choice) {
		case 1:
			eventSystem.addEvent();
			break;
		case 2:
			eventSystem.displayEvents();
			break;
		case 3:
			eventSystem.updateEvent();
			break;
		case 4:
			eventSystem.deleteEvent();
			break;
		case 5:
			eventSystem.searchEvent();
			break;
		case 6:
			eventSystem.exportToCSV();
			break;
		case 7:
			eventSystem.exportToTXT();
			break;
		case 0:
			cout << " Farewell, The program now concludes. \n";
			break;
		default:
			cout << " Invalid choice. Please select a valid option.\n";
		}

	} while (choice != 0);

	return 0;
}
