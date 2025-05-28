#include <iostream>
#include <string>

using namespace std;

class AuthenticateUser {
private:
	const string ADMIN_USERNAME = "admin";
	const string ADMIN_PASSWORD = "password";

public:
	bool authenticateAdmin() {
		string username, password;

		cout << "Enter Admin Username: ";
		getline(cin, username);

		cout << "Enter Admin Password: ";
		getline(cin, password);

		return (username == ADMIN_USERNAME && password == ADMIN_PASSWORD);
	}

	int selectUserRole() {
		int choice = 0;
		cout << "Select User Role:\n1. Admin\n2. Guest\nChoice: ";

		while (!(cin >> choice) || (choice != 1 && choice != 2)) {
			cout << "Invalid input. Enter 1 for Admin or 2 for Guest: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

		return choice;
	}
};
