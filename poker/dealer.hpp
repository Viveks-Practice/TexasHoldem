//
//  dealer.hpp
//  poker
//
//  Created by Vivek Sharma on 2020-11-19.
//  Copyright © 2020 Vivek. All rights reserved.
//

#ifndef dealer_hpp
#define dealer_hpp

#include "handData.hpp"
#include "Card.h"
#include <stdio.h>
#include <map>

class dealer{
    
public:
    //Default Constructor
    dealer();
    
    
private:
    
    int cpuPlayerCount;
    
    map<string, int> faceToValue;
    map<int, string> valueToFace;
    map<string, int> suitToValue;
    map<int, string> handScoreMap;
    
    
    int compareHand(Card hand1[], Card hand2[], handData data1, handData data2);
    int handTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2);
    handData typeOfHand(Card SevenCardHand[]);
    
    int highCardTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2);
    int pairTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2);
    int twoPairTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2);
    int threeOfAKindTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2);
    int straightTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2);
    int flushTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2);
    int fullHouseTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2);
    int fourOfAKindTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2);
    
    //Precondition: call this function when typeOfHand returns handData.handScore == 9
    //              there will be a non empty handData.card1 value
    int straightFlushTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2);
    
};


#endif /* dealer_hpp */
