//
// Created by harish on 2/16/2024.
//

#include "header.h"

//Constructor
Session::Session(User* currentSession) {
    this->currentSession = currentSession;
}

//Default Constructor
Session::Session() {
    this->currentSession = nullptr;
}

//Get userSession
User* Session::getSession() {
    return this->currentSession;
}

//Set userSession
User* Session::setSession(User* userSession) {
    this->currentSession = userSession;
    return this->currentSession;
}

//Start userSession
void Session::startSession(User* userSession) {
    this->currentSession = userSession;
}

//End userSession
void Session::endSession(User* userSession) {
    if(this->currentSession == userSession) {
        this->currentSession = nullptr;
    }
}

User* Session::getCurrentSession() const {
    return currentSession;
}
