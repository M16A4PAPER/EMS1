// AuthenticateUser.h
#pragma once
#include "User.h"
#include <memory>

class AuthenticateUser {
public:
    std::unique_ptr<User> login(EventManager& mgr);
};
