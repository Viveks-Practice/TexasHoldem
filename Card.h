//
//  Card.h
//  poker
//
//  Created by Vivek Sharma on 2020-11-10.
//  Copyright © 2020 Vivek. All rights reserved.
//

#ifndef Card_h
#define Card_h

#include <cstdlib>
#include <iostream>

using namespace std;

class Card{
    
private:
    string face;
    string suit;
    
public:
    Card(); //default constructor for Card
    Card(string cardFace, string cardSuit); //parametrized constructor for Card
    Card(const Card &copyCard); //copy constructor
    string printCard();
    string getFace();
    string getSuit();
    void setFace(string newFace);
    void setSuit(string newSuit);    
};

#endif /* Card_h */
