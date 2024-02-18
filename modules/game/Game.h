#ifndef GAME_H
#define GAME_H

#include <string>;
using namespace std;

class Game {
private:

    string gameName;
    string userName;
    double price;

public:
    void setGameName(string g);
    void setSellerName(string u);
    void setPrice(double p);
    string getGameName();
    string getSellerName();
    double getGamePrice();

};

#endif