// AdminUser.h
#pragma once
#include "User.h"

class AdminUser : public User {
public:
    AdminUser(EventManager& mgr);
    void showMenu() override;
};
