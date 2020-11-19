//
//  Card.cpp
//  poker
//
//  Created by Vivek Sharma on 2020-11-10.
//  Copyright © 2020 Vivek. All rights reserved.
//

#include "Card.h"
#include <stdio.h>

Card::Card(){
    face = "faceInit";
    suit = "suitInit";
}

Card::Card(string cardFace, string cardSuit){
    face = cardFace;
    suit = cardSuit;
}


Card::Card(const Card &copyCard){
    face = copyCard.face;
    suit = copyCard.suit;
}

string Card::printCard(){
    return face + " of " + suit;
}

string Card::getFace(){
    return face;
}

string Card::getSuit(){
    return suit;
}

void Card::setFace(string newFace){
    face = newFace;
}

void Card::setSuit(string newSuit){
    suit = newSuit;
}

