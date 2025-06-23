// Event.cpp
#include "Event.h"
#include <iostream>

using namespace std;

Event::Event(int id, string name, string date, string venue)
    : id(id), name(move(name)), date(move(date)), venue(move(venue)) {
}

bool Event::operator==(const Event& other) const {
    return this->id == other.id;
}

void Event::display() const {
    cout << id << "\t" << name << "\t" << date << "\t" << venue << endl;
}
