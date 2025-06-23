// GuestUser.h
#pragma once
#include "User.h"

class GuestUser : public User {
public:
    GuestUser(EventManager& mgr);
    void showMenu() override;
};
