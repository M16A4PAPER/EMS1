// User.h
#pragma once
#include "EventManager.h"

class User {
protected:
    EventManager& manager;

public:
    explicit User(EventManager& mgr);
    virtual ~User();

    virtual void showMenu() = 0;
};
