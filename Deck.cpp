//
//  Deck.cpp
//  poker
//
//  Created by Vivek Sharma on 2020-11-10.
//  Copyright © 2020 Vivek. All rights reserved.
//

#include "Deck.hpp"




Deck::Deck(){
    
    cardCount = 52;
    string faces[] = {"Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
    string suits[] = { "Diamonds", "Clubs", "Hearts", "Spades"};
    
    
    deck = new Card[52];
    for(int i = 0; i<52; i++){//add all the cards into the deck
        deck[i] = Card(faces[i % 13], suits[i / 13]);
    }
}

Deck::~Deck(){
    delete[] deck;
}

void Deck::startGame(){
    shuffle();
}

void Deck::shuffle(){
    

    cardCount = 52;
    srand(8);
    for(int i = 0; i<(rand()%1000); i++){
            swap(rand()%52,rand()%52);
    }
}

void Deck::swap(int index1, int index2){
    Card temp = deck[index1];
    deck[index1] = deck[index2];
    deck[index2] = temp;
}

void Deck::revealDeck(){
    for(int i = 0; i<cardCount; i++){
        cout << deck[i].printCard() << endl;
        if((i%5) == 0){
            //cout << endl;
        }
    }
    cout << endl << endl;
}

Card Deck::deal(){
    
    Card dealtCard = deck[cardCount - 1];
    cardCount--;
    
    return dealtCard;
    
}

int Deck::getCardCount(){
    return cardCount;
}
