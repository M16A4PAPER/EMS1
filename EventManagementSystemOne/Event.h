// Event.h
#pragma once
#include <string>
using namespace std;

class Event {
public:
    int id;
    string name;
    string date;
    string venue;

    Event(int id, string name, string date, string venue);

    bool operator==(const Event& other) const;

    void display() const;
};
