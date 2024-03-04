#include "header.h"
#include <iostream>
#include "vector"
#include "sstream"
using namespace std;

Game::Game(const std::string& g, const std::string& u, double p){
    this->gameName = g;
    this->userName = u;
    this->price = p;
}
Game::Game() {
    this->gameName = "";
    this->userName = "";
    this->price = 0;
}
     

//getters
string Game::getGameName(){
    return gameName;
}
string Game::getSellerName(){
    return userName;
}
double Game::getGamePrice(){
    return price;
}
void Game::setGameName(string name){
    this->gameName=name;
}
void Game::setSellerName(string name){
    this->userName=name;
}
void Game::setPrice(double price){
    this->price=price;
}

Game getGameByName(string name) {
    ifstream inFile("games.txt");
    string line;

    if(inFile.is_open()) {
        while(getline(inFile, line)) {

            vector<string> tokens;
            stringstream check1(line);
            string intermediate;

            while(getline(check1, intermediate, '_')) {
                tokens.push_back(intermediate);
            }

            if(tokens[0] == name) {
                return Game(tokens[0], tokens[1], stod(tokens[2]));
            }


        }
    }
    return Game();
}



//traverse through games owned by a user to check the the game is owned by him
// boolean isOwnedBy(User user){
//     int size = sizeof(user.game)/sizeof(user.game[0]);

//     for(int i = 0; i<size; i++){
//         if(gameName==user.game[i]){
//             return true;
//         }
//     }
//     cout << getGameName() <<" is not owned by " << getSellerName() <<endl; 
//     return false;
//}


//simple print statment to see the game seller and price
// void toString(){
//     cout<< "Game                 Seller             Price" << endl;
//     cout<< gameName << "   " << userName << "  " << price << endl;
// }



