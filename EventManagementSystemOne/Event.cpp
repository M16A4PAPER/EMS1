#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

class Event {
private:

	static const int MAX_EVENTS = 100;

	int eventId[MAX_EVENTS];
	string eventName[MAX_EVENTS];
	string eventDate[MAX_EVENTS];
	string eventVenue[MAX_EVENTS];
	int eventCount = 0;

	const string filename = "events.txt";

	int findEventIndexById(int id) {
		for (int i = 0; i < eventCount; i++) {
			if (eventId[i] == id) {
				return i;
			}
		}
		return -1;
	}

	int getValidatedIntInput(const string& prompt) {
		int value;
		cout << prompt;
		while (!(cin >> value)) {
			cout << "Invalid input. Please enter a valid integer: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline
		return value;
	}


public:
	Event() {
		loadEvents();
	}

	void displayEvents() {
		if (eventCount == 0) {
			cout << "No events to display." << endl;
			return;
		}

		cout << "\n======================" << endl;
		cout << "     Current Events   " << endl;
		cout << "======================" << endl;
		cout << "ID\tName\tDate\t\tVenue" << endl;
		cout << "---------------------------------------------" << endl;

		for (int i = 0; i < eventCount; i++) {
			cout << eventId[i] << "\t"
				<< eventName[i] << "\t"
				<< eventDate[i] << "\t"
				<< eventVenue[i] << endl;
		}

		cout << "---------------------------------------------" << endl;
		cout << "Total Events: " << eventCount << "\n" << endl;
	}

	void addEvent() {
		if (eventCount >= MAX_EVENTS) {
			cout << "Event storage is full. Cannot add more events." << endl;
			return;
		}

		int id = getValidatedIntInput("Enter Event ID: ");

		if (findEventIndexById(id) != -1) {
			cout << "Event ID already exists. Please use a unique ID." << endl;
			return;
		}

		string name = getValidatedNameOrVenue("Enter Event Name: ");
		string date = getValidatedNameOrVenue("Enter Event Date (YYYY-MM-DD): ");
		string venue = getValidatedNameOrVenue("Enter Event Venue: ");

		// Store event data
		eventId[eventCount] = id;
		eventName[eventCount] = name;
		eventDate[eventCount] = date;
		eventVenue[eventCount] = venue;

		eventCount++;
		saveEvents();

		cout << "Event added successfully." << endl;
	}

	void updateEvent() {
		if (eventCount == 0) {
			cout << "No events to update." << endl;
			return;
		}

		int id = getValidatedIntInput("Enter Event ID to update: ");
		int idx = findEventIndexById(id);

		if (idx == -1) {
			cout << "Event not found with ID " << id << "." << endl;
			return;
		}

		cout << "Updating Event ID " << id << ":" << endl;

		string name = getValidatedNameOrVenue("Enter new Event Name: ");
		string date = getValidatedNameOrVenue("Enter new Event Date (YYYY-MM-DD): ");
		string venue = getValidatedNameOrVenue("Enter new Event Venue: ");

		eventName[idx] = name;
		eventDate[idx] = date;
		eventVenue[idx] = venue;

		saveEvents();
		cout << "Event updated successfully." << endl;
	}

	void deleteEvent() {
		if (eventCount == 0) {
			cout << "No events to delete." << endl;
			return;
		}

		int id = getValidatedIntInput("Enter Event ID to delete: ");
		int idx = findEventIndexById(id);

		if (idx == -1) {
			cout << "Event with ID " << id << " not found." << endl;
			return;
		}

		// Shift remaining events to overwrite the deleted one
		for (int i = idx; i < eventCount - 1; i++) {
			eventId[i] = eventId[i + 1];
			eventName[i] = eventName[i + 1];
			eventDate[i] = eventDate[i + 1];
			eventVenue[i] = eventVenue[i + 1];
		}

		eventCount--; // Reduce total event count
		saveEvents();

		cout << "Event with ID " << id << " deleted successfully." << endl;
	}

	void searchEvent() {
		if (eventCount == 0) {
			cout << "No events to search." << endl;
			return;
		}

		int choice = 0;

		cout << "\nSearch by:\n"
			<< "1. Event ID\n"
			<< "2. Event Name\n"
			<< "3. Event Date\n"
			<< "4. Event Venue\n"
			<< "Choice (1-4): ";

		// Validate input to ensure choice is between 1 and 4
		while (!(cin >> choice) || choice < 1 || choice > 4) {
			cout << "Invalid choice. Please enter a number between 1 and 4: ";
			cin.clear(); // clear error flags
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove leftover newline

		// Call the appropriate search function based on user choice
		switch (choice) {
		case 1:
			searchEventById();
			break;
		case 2:
			searchEventByName();
			break;
		case 3:
			searchEventByDate();
			break;
		case 4:
			searchEventByVenue();
			break;
		default:
			// This case is unreachable because of input validation,
			// but included for completeness
			cout << "Invalid choice." << endl;
		}
	}

#pragma region Export Functions

	void exportToCSV() {
		ofstream outFile("C:\\Users\\m16a4\\Desktop\\events.csv");
		if (!outFile) {
			cout << "Error creating CSV file.\n";
			return;
		}

		outFile << "Event ID,Event Name,Event Date,Event Venue\n";
		for (int i = 0; i < eventCount; i++) {
			outFile << eventId[i] << "," << eventName[i] << "," << eventDate[i] << "," << eventVenue[i] << "\n";
		}
		outFile.close();
		cout << "CSV export complete.\n";
	}

	void exportToTXT() {
		ofstream outFile("C:\\Users\\m16a4\\Desktop\\events.txt");
		if (!outFile) {
			cout << "Error creating TXT file.\n";
			return;
		}

		for (int i = 0; i < eventCount; i++) {
			outFile << "ID: " << eventId[i] << "\n";
			outFile << "Name: " << eventName[i] << "\n";
			outFile << "Date: " << eventDate[i] << "\n";
			outFile << "Venue: " << eventVenue[i] << "\n";
			outFile << "---------------------------\n";
		}
		outFile.close();
		cout << "TXT export complete.\n";
	}

#pragma endregion

private:

#pragma region Helper Functions

	void loadEvents() {
		ifstream file(filename);

		// Check if the file opens successfully
		if (!file.is_open()) {
			cout << "No previous event data found or file could not be opened." << endl;
			return;
		}

		string line;
		eventCount = 0;

		while (getline(file, line)) {
			if (eventCount >= MAX_EVENTS) {
				cout << "Warning: Maximum number of events (" << MAX_EVENTS << ") reached. Some events may not be loaded." << endl;
				break;
			}

			stringstream ss(line);
			string idStr, name, date, venue;

			// Get each field separated by a comma
			if (!getline(ss, idStr, ',')) continue;
			if (!getline(ss, name, ',')) continue;
			if (!getline(ss, date, ',')) continue;
			if (!getline(ss, venue)) continue;

			// Trim spaces from idStr (basic way)
			idStr.erase(0, idStr.find_first_not_of(" \t"));
			idStr.erase(idStr.find_last_not_of(" \t") + 1);

			// Convert idStr to integer safely
			int id;
			bool isValid = true;

			for (char c : idStr) {
				if (!isdigit(c)) {
					isValid = false;
					break;
				}
			}

			if (!isValid || idStr.empty()) {
				cout << "Skipping invalid ID: " << idStr << endl;
				continue;
			}

			id = stoi(idStr);

			// Store values into arrays
			eventId[eventCount] = id;
			eventName[eventCount] = name;
			eventDate[eventCount] = date;
			eventVenue[eventCount] = venue;

			eventCount++;
		}

		file.close();

		if (eventCount == 0) {
			cout << "No valid events were loaded from the file." << endl;
		}
		else {
			cout << eventCount << " event(s) loaded successfully." << endl;
		}
	}

	void saveEvents() {
		ofstream file(filename);

		// Check if the file opened successfully
		if (!file.is_open()) {
			cout << "Error: Could not open file for writing. Events were not saved." << endl;
			return;
		}

		// Write each event's data to the file
		for (int i = 0; i < eventCount; i++) {
			file << eventId[i] << ","
				<< eventName[i] << ","
				<< eventDate[i] << ","
				<< eventVenue[i] << "\n";
		}

		file.close();
		cout << "Events saved successfully to '" << filename << "'." << endl;
	}

	string getValidatedNameOrVenue(const string& prompt) {
		string input;

		while (true) {
			cout << prompt;
			getline(cin, input);

			// Check if input is empty
			if (input.empty()) {
				cout << "Input cannot be empty. Please try again." << endl;
				continue;
			}

			// Remove leading/trailing spaces (optional but recommended)
			size_t start = input.find_first_not_of(" \t");
			size_t end = input.find_last_not_of(" \t");
			if (start == string::npos) {  // input was only spaces
				cout << "Input cannot be empty. Please try again." << endl;
				continue;
			}
			string trimmed = input.substr(start, end - start + 1);

			// Check if trimmed input is all digits (pure integer)
			bool allDigits = true;
			for (char ch : trimmed) {
				if (!isdigit(static_cast<unsigned char>(ch))) {
					allDigits = false;
					break;
				}
			}

			if (allDigits) {
				cout << "Input cannot be only numbers. Please enter a valid name or venue." << endl;
				continue;
			}

			// Input passes validation
			return trimmed;
		}
	}

#pragma endregion

#pragma region Search Functions

	void searchEventById() {
		int id = getValidatedIntInput("Enter Event ID to search: ");
		int idx = findEventIndexById(id);
		if (idx == -1) {
			cout << "No event found with ID " << id << "." << endl;
		}
		else {
			cout << "Event found:" << endl;
			cout << "ID: " << eventId[idx] << endl;
			cout << "Name: " << eventName[idx] << endl;
			cout << "Date: " << eventDate[idx] << endl;
			cout << "Venue: " << eventVenue[idx] << endl;
		}
	}

	void searchEventByName() {
		string name = getValidatedNameOrVenue("Enter Event Name to search: ");
		bool found = false;
		for (int i = 0; i < eventCount; i++) {
			if (eventName[i].find(name) != string::npos) {
				if (!found) {
					cout << "Matching events:" << endl;
					cout << "ID\tName\tDate\tVenue" << endl;
				}
				cout << eventId[i] << "\t" << eventName[i] << "\t"
					<< eventDate[i] << "\t" << eventVenue[i] << endl;
				found = true;
			}
		}
		if (!found) {
			cout << "No events found matching name '" << name << "'." << endl;
		}
	}

	void searchEventByDate() {
		string date = getValidatedNameOrVenue("Enter Event Date (YYYY-MM-DD) to search: ");
		bool found = false;
		for (int i = 0; i < eventCount; i++) {
			if (eventDate[i] == date) {
				if (!found) {
					cout << "Events on " << date << ":" << endl;
					cout << "ID\tName\tDate\tVenue" << endl;
				}
				cout << eventId[i] << "\t" << eventName[i] << "\t"
					<< eventDate[i] << "\t" << eventVenue[i] << endl;
				found = true;
			}
		}
		if (!found) {
			cout << "No events found on date '" << date << "'." << endl;
		}
	}

	void searchEventByVenue() {
		string venue = getValidatedNameOrVenue("Enter Event Venue to search: ");
		bool found = false;
		for (int i = 0; i < eventCount; i++) {
			if (eventVenue[i].find(venue) != string::npos) {
				if (!found) {
					cout << "Events at venue matching '" << venue << "':" << endl;
					cout << "ID\tName\tDate\tVenue" << endl;
				}
				cout << eventId[i] << "\t" << eventName[i] << "\t"
					<< eventDate[i] << "\t" << eventVenue[i] << endl;
				found = true;
			}
		}
		if (!found) {
			cout << "No events found at venue matching '" << venue << "'." << endl;
		}
	}

#pragma endregion

#pragma region Date Validation Functions

	bool isLeapYear(int year) {
		return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
	}

	bool isValidDate(int year, int month, int day) {
		if (year < 1900 || month < 1 || month > 12 || day < 1) return false;

		int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && isLeapYear(year)) {
			return day <= 29;
		}
		return day <= daysInMonth[month - 1];
	}

	void getCurrentDate(int& year, int& month, int& day) {
		time_t t = time(nullptr);
		tm now;
		localtime_s(&now, &t);
		year = now.tm_year + 1900;
		month = now.tm_mon + 1;
		day = now.tm_mday;
	}


	string getValidatedFutureDate(const string& prompt) {
		string dateStr;

		while (true) {
			cout << prompt;
			getline(cin, dateStr);

			if (dateStr.empty()) {
				cout << "Date cannot be empty. Please enter a valid date." << endl;
				continue;
			}

			// Basic format check: must be 10 characters YYYY-MM-DD
			if (dateStr.length() != 10 ||
				dateStr[4] != '-' || dateStr[7] != '-') {
				cout << "Invalid format. Please enter date as YYYY-MM-DD." << endl;
				continue;
			}

			// Extract year, month, day substrings
			int year, month, day;
			try {
				year = stoi(dateStr.substr(0, 4));
				month = stoi(dateStr.substr(5, 2));
				day = stoi(dateStr.substr(8, 2));
			}
			catch (...) {
				cout << "Invalid date components. Please enter numeric values." << endl;
				continue;
			}

			if (!isValidDate(year, month, day)) {
				cout << "Entered date is not valid. Please enter a real date." << endl;
				continue;
			}

			// Check if date is in the future
			int currentYear, currentMonth, currentDay;
			getCurrentDate(currentYear, currentMonth, currentDay);

			if (year < currentYear ||
				(year == currentYear && month < currentMonth) ||
				(year == currentYear && month == currentMonth && day <= currentDay)) {
				cout << "Date must be in the future (after today)." << endl;
				continue;
			}

			// Date is valid and in the future
			return dateStr;
		}
	}

#pragma endregion
};


