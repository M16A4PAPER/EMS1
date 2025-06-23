// EventManager.h
#pragma once
#include "Event.h"
#include <vector>
#include <string>
#include <exception>
#include <iostream>

using namespace std;

class DuplicateEventException : public exception {
public:
    const char* what() const noexcept override;
};

class EventNotFoundException : public exception {
public:
    const char* what() const noexcept override;
};

class EventManager {
private:
    vector<Event> events;
    const string filename = "events.txt";

public:
    void loadFromFile();
    void saveToFile() const;
    void addEvent(const Event& e);
    void updateEvent(int id, const string& name, const string& date, const string& venue);
    void deleteEvent(int id);
    void displayEvents() const;
    void exportToCSV(const string& csvFilename) const;
    void importFromCSV(const string& csvFilename);
};
