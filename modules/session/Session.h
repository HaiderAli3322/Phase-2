//
// Created by harish on 2/16/2024.
//

#ifndef SQAPROJECT_SESSION_H
#define SQAPROJECT_SESSION_H

#include <string>
#include "User.h"

using namespace std;


class Session {
private:
    User* currentSession;

public:
    Session(User* currentSession);
    Session();
    User* getSession();
    User* setSession(User* currentSession);
    void startSession(User* currentSession);
    void endSession(User* currentSession);
};


#endif //SQAPROJECT_SESSION_H
