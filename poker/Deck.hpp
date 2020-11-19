//
//  Deck.hpp
//  poker
//
//  Created by Vivek Sharma on 2020-11-10.
//  Copyright © 2020 Vivek. All rights reserved.
//

#ifndef Deck_hpp
#define Deck_hpp

#include "Card.h"
#include <stdio.h>

using namespace std;


class Deck{
    
private:
    
    int cardCount;
    Card* deck;
    
    
    void shuffle(); //shuffle the deck
    
    void flop(); //Reveal the flop
    void card(); //Reveal a card from the top of the deck, this can be the turn or the river
    void swap(int index1, int index2); //Helper function - Used in shuffle
    
    
public:
    
    Deck();//Default constructor
    ~Deck();
    void startGame();
    void revealDeck();
    Card deal(); //Deals a card to a player
    int getCardCount();
    
};

#endif /* Deck_hpp */
