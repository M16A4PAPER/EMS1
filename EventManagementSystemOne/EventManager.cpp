// EventManager.cpp
#include "EventManager.h"
#include <fstream>
#include <sstream>
#include <regex>

const char* DuplicateEventException::what() const noexcept {
    return "Event ID already exists.";
}

const char* EventNotFoundException::what() const noexcept {
    return "Event not found.";
}

void EventManager::loadFromFile() {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Warning: Could not open file '" << filename << "' for reading." << endl;
        return;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        stringstream ss(line);
        string idStr, name, date, venue;

        if (!getline(ss, idStr, ',')) {
            cerr << "Skipping line " << lineNumber << ": missing ID." << endl;
            continue;
        }
        if (!getline(ss, name, ',')) {
            cerr << "Skipping line " << lineNumber << ": missing name." << endl;
            continue;
        }
        if (!getline(ss, date, ',')) {
            cerr << "Skipping line " << lineNumber << ": missing date." << endl;
            continue;
        }
        if (!getline(ss, venue)) {
            cerr << "Skipping line " << lineNumber << ": missing venue." << endl;
            continue;
        }

        try {
            int id = stoi(idStr);

            // Basic checks
            if (name.empty() || date.empty() || venue.empty()) {
                cerr << "Skipping line " << lineNumber << ": empty fields." << endl;
                continue;
            }

            // Optional: validate date format (YYYY-MM-DD)
            if (!regex_match(date, regex(R"(\d{4}-\d{2}-\d{2})"))) {
                cerr << "Skipping line " << lineNumber << ": invalid date format." << endl;
                continue;
            }

            events.emplace_back(id, name, date, venue);
        }
        catch (const invalid_argument&) {
            cerr << "Skipping line " << lineNumber << ": non-integer ID." << endl;
        }
        catch (const out_of_range&) {
            cerr << "Skipping line " << lineNumber << ": ID out of range." << endl;
        }
    }

    file.close();
}

void EventManager::saveToFile() const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "' for writing." << endl;
        return;
    }

    for (const auto& e : events) {
        file << e.id << "," << e.name << "," << e.date << "," << e.venue << "\n";
    }
    file.close();
}

void EventManager::addEvent(const Event& e) {
    if (e.id <= 0) throw invalid_argument("Event ID must be a positive integer.");
    if (e.name.empty() || e.date.empty() || e.venue.empty())
        throw invalid_argument("Event fields cannot be empty.");

    for (const auto& existing : events) {
        if (existing == e) throw DuplicateEventException();
    }
    events.push_back(e);
}

void EventManager::updateEvent(int id, const string& name, const string& date, const string& venue) {
    if (id <= 0) throw invalid_argument("ID must be positive.");
    if (name.empty() || date.empty() || venue.empty())
        throw invalid_argument("Fields cannot be empty.");

    for (auto& e : events) {
        if (e.id == id) {
            e.name = name;
            e.date = date;
            e.venue = venue;
            return;
        }
    }
    throw EventNotFoundException();
}

void EventManager::deleteEvent(int id) {
    if (id <= 0) throw invalid_argument("ID must be a positive integer.");

    for (auto it = events.begin(); it != events.end(); ++it) {
        if (it->id == id) {
            events.erase(it);
            return;
        }
    }
    throw EventNotFoundException();
}

void EventManager::displayEvents() const {
    if (events.empty()) {
        cout << "No events found." << endl;
        return;
    }

    cout << "ID\tName\tDate\tVenue\n";
    for (const auto& e : events) {
        e.display();
    }
}

void EventManager::exportToCSV(const string& csvFilename) const {
    ofstream file(csvFilename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << csvFilename << "' for exporting." << endl;
        return;
    }

    file << "ID,Name,Date,Venue\n";
    for (const auto& e : events) {
        file << e.id << "," << e.name << "," << e.date << "," << e.venue << "\n";
    }

    file.close();
    cout << "Events successfully exported to '" << csvFilename << "'.\n";
}

void EventManager::importFromCSV(const string& csvFilename) {
    ifstream file(csvFilename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << csvFilename << "' for importing." << endl;
        return;
    }

    string line;
    int lineNumber = 0;
    bool headerSkipped = false;

    while (getline(file, line)) {
        lineNumber++;
        if (!headerSkipped) { headerSkipped = true; continue; } // skip header

        stringstream ss(line);
        string idStr, name, date, venue;

        if (!getline(ss, idStr, ',')) continue;
        if (!getline(ss, name, ',')) continue;
        if (!getline(ss, date, ',')) continue;
        if (!getline(ss, venue)) continue;

        try {
            int id = stoi(idStr);

            if (name.empty() || date.empty() || venue.empty()) {
                cerr << "Skipping line " << lineNumber << ": empty field.\n";
                continue;
            }

            if (!regex_match(date, regex(R"(\d{4}-\d{2}-\d{2})"))) {
                cerr << "Skipping line " << lineNumber << ": invalid date format.\n";
                continue;
            }

            addEvent(Event(id, name, date, venue));
        }
        catch (const exception& e) {
            cerr << "Skipping line " << lineNumber << ": " << e.what() << endl;
        }
    }

    file.close();
    cout << "Events imported from '" << csvFilename << "'.\n";
}

