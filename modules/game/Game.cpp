#include "Game.h"
#include <iostream>

void Game::setGameName(string g){
        
    gameName = g;
}
void Game::setSellerName(string u){
    userName = u;
}
void Game::setPrice(double p){
    price = p;
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



