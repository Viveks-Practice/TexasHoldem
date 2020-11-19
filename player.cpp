//
//  player.cpp
//  poker
//
//  Created by Vivek Sharma on 2020-11-10.
//  Copyright © 2020 Vivek. All rights reserved.
//

#include "player.hpp"


using namespace std;

//Default Constructor
player::player(){
    participating = true;
    chipStack = 1000;
}

//Parametrized constructor
player::player(Card firstCard, Card secondCard){
    
    card1 = firstCard;
    card2 = secondCard;
    cout << card1.printCard() << ", " << card2.printCard() << endl;
    participating = true;
    chipStack = 1000;
    
}

//Copy constructor
player::player(const player &dealtHand){
    
    cout << "PLAYER COPY CONSTRUCTOR!!" << endl << endl;
    /*card1 = dealtHand.card1;
    card2 = dealtHand.card2;
    participating = dealtHand.participating;
    chipStack = dealtHand.chipStack;*/
    
}

void player::receiveHand(Card firstCard, Card secondCard){
    
    card1 = firstCard;
    card2 = secondCard;
    participating = true;
}

void player::addChips(long chips){
    chipStack += chips;
}

long player::getChips(){
    return chipStack;
}

//Maybe make this take input from the user directly in the function.
long player::bet(){
    
    long bettingChips;
    cout << "Enter the amount you would like to bet: " << endl;
    cin >> bettingChips;
    while(bettingChips > chipStack){
        cout << "Error: You do not have enough chips for that bet!" << endl;
        cout << "Current chip stack: " << chipStack << endl;
        cout << "Enter the amount you would like to bet: " << endl;
        cin >> bettingChips;
    }
    chipStack -= bettingChips;
    return bettingChips;
}

void player::revealHand(){
    
    string str = card1.printCard() + ", " + card2.printCard();
    cout << str << endl;
}

string player::printPlayer(){
    return "TESTING PRINTS: " + card1.printCard() + ", and a " + card2.printCard();
    
}

void player::fold(){
    participating = false;
}

int player::turnAction(){
    int userSelection = 0;
    int addToPot = 0;
    
    cout << endl << endl << "It is your turn to make a move!" << endl;
    cout << "Enter the number corresponding to the action you wish you make, from the list below:" << endl;
    cout << "1 - fold" << endl;
    cout << "2 - check" << endl;
    cout << "3 - bet" << endl;
    cin >> userSelection;
    while ( (userSelection != 1) && (userSelection != 2) && (userSelection != 3)){
        cout << endl << "***That number is out of range***" << endl;
        cout << "Enter the number corresponding to the action you wish you make, from the list below:" << endl;
        cout << "1 - fold" << endl;
        cout << "2 - check" << endl;
        cout << "3 - bet" << endl;
        cin >> userSelection;
    }
    if(userSelection == 1){
        cout << "You have folded your hand." << endl;
        fold();
    }
    else if(userSelection == 2){
        cout << "You have checked." << endl;
        //do nothing
    }
    else if(userSelection == 3){
        addToPot = int(bet());
    }
    
    return addToPot;
}

bool player::getParticipating(){
    return participating;
}

void player::setParticipating(bool participate){
    participating = participate;
}

Card* player::getHand(){
    Card* playersHand;
    Card playersHandArr[2] = {card1, card2};
    playersHand = playersHandArr;
    return playersHand;
}

Card player::getCard1(){
    return card1;
}

Card player::getCard2(){
    return card2;
}
