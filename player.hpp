//
//  player.hpp
//  poker
//
//  Created by Vivek Sharma on 2020-11-10.
//  Copyright © 2020 Vivek. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "Card.h"
#include <cstdlib>


using namespace std;

class player{
    
private:
    Card card1;
    Card card2;
    bool participating;
    long chipStack;
    
    
public:
    player();//Default Constructor
    player(Card firstCard, Card secondCard);//Parametrized Constructor
    player(const player &dealtHand);//Copy constructor
    void revealHand();
    void receiveHand(Card firstCard, Card secondCard);
    void fold();
    void addChips(long chips);
    long getChips();
    long bet();
    string printPlayer();
    int turnAction();
    bool getParticipating();
    void setParticipating(bool participate);
    Card* getHand();
    Card getCard1();
    Card getCard2();

    
};

#endif /* player_hpp */
