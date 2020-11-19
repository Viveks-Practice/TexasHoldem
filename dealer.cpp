//
//  dealer.cpp
//  poker
//
//  Created by Vivek Sharma on 2020-11-19.
//  Copyright © 2020 Vivek. All rights reserved.
//

#include "dealer.hpp"


dealer::dealer(){
    
    faceToValue["Deuce"] = 0;
    faceToValue["Three"] = 1;
    faceToValue["Four"] = 2;
    faceToValue["Five"] = 3;
    faceToValue["Six"] = 4;
    faceToValue["Seven"] = 5;
    faceToValue["Eight"] = 6;
    faceToValue["Nine"] = 7;
    faceToValue["Ten"] = 8;
    faceToValue["Jack"] = 9;
    faceToValue["Queen"] = 10;
    faceToValue["King"] = 11;
    faceToValue["Ace"] = 12;
    
    valueToFace[0] = "Deuce";
    valueToFace[1] = "Three";
    valueToFace[2] = "Four";
    valueToFace[3] = "Five";
    valueToFace[4] = "Six";
    valueToFace[5] = "Seven";
    valueToFace[6] = "Eight";
    valueToFace[7] = "Nine";
    valueToFace[8] = "Ten";
    valueToFace[9] = "Jack";
    valueToFace[10] = "Queen";
    valueToFace[11] = "King";
    valueToFace[12] = "Ace";
    
    suitToValue["Diamonds"] = 1;
    suitToValue["Clubs"] = 2;
    suitToValue["Hearts"] = 3;
    suitToValue["Spades"] = 4;
    
    handScoreMap[1] = "High Card";
    handScoreMap[2] = "Pair";
    handScoreMap[3] = "Two Pair";
    handScoreMap[4] = "Three of a Kind";
    handScoreMap[5] = "Straight";
    handScoreMap[6] = "Flush";
    handScoreMap[7] = "Full House";
    handScoreMap[8] = "Four of a Kind";
    handScoreMap[9] = "Straight Flush";
}

//Precondition: call this function when typeOfHand returns handData.handScore == 9
//              there will be a non empty handData.card1 value
int dealer::straightFlushTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if(faceToValue[data1.card1Face] > faceToValue[data2.card1Face])
        return 1;
    else if(faceToValue[data1.card1Face] < faceToValue[data2.card1Face])
        return 2;
    else
        return 0;
    
    return 0;
}

//return a card face for the other types as well, and use it to find the tiebreaker for each specific type of hand
int dealer::fourOfAKindTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if(faceToValue[data1.card1Face] > faceToValue[data2.card1Face] )
        return 1;
    else if(faceToValue[data1.card1Face] < faceToValue[data2.card1Face])
        return 2;
    //check which of the "kickers" is greater
    int i=7;
    int j=7;
    while( (i>=2) && (j>=2) ){
        j--;
        i--;
        //if relevant card is found, ignore it and move forward, for hand1
        while(hand1[i].getFace() == data1.card1Face){
            i--;
        }
        //if relevant card if found, ignore it and move forward, for hand2
        while(hand2[j].getFace() == data2.card1Face){
            j--;
        }
        if( (i<2) || (j<2) ){
            break;
        }
        if(faceToValue[hand1[i].getFace()] > faceToValue[hand2[j].getFace()] ){
            return 1;
        }
        else if(faceToValue[hand1[i].getFace()] < faceToValue[hand2[j].getFace()] ){
            return 2;
        }
        else{
            return 0;
        }
        
    }
    return 0;
}

int dealer::fullHouseTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    if(faceToValue[data1.card1Face] > faceToValue[data2.card1Face])
        return 1;
    else if(faceToValue[data1.card1Face] < faceToValue[data2.card1Face])
        return 2;
    else{
        if(faceToValue[data1.card2Face] > faceToValue[data2.card2Face])
            return 1;
        else if(faceToValue[data1.card2Face] < faceToValue[data2.card2Face])
            return 2;
    }
    return 0;
}

int dealer::flushTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if(faceToValue[data1.card1Face] > faceToValue[data2.card1Face])
        return 1;
    else if(faceToValue[data1.card1Face] < faceToValue[data2.card1Face])
        return 2;
    else
        return 0;
    
    return 0;
}

int dealer::straightTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if(faceToValue[data1.card1Face] > faceToValue[data2.card1Face])
        return 1;
    else if(faceToValue[data1.card1Face] < faceToValue[data2.card1Face])
        return 2;
    else
        return 0;
    
    return 0;
}

int dealer::threeOfAKindTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if(faceToValue[data1.card1Face] > faceToValue[data2.card1Face] )
        return 1;
    else if(faceToValue[data1.card1Face] < faceToValue[data2.card1Face])
        return 2;
    //check which of the "kickers" is greater
    int i=7;
    int j=7;
    while( (i>=2) && (j>=2) ){
        j--;
        i--;
        //if relevant card is found, ignore it and move forward, for hand1
        if(hand1[i].getFace() == data1.card1Face){
            i--;
        }
        //if relevant card if found, ignore it and move forward, for hand2
        if(hand2[j].getFace() == data2.card1Face){
            j--;
        }
        if( (i<2) || (j<2) ){
            break;
        }
        if(faceToValue[hand1[i].getFace()] > faceToValue[hand2[j].getFace()] ){
            return 1;
        }
        else if(faceToValue[hand1[i].getFace()] < faceToValue[hand2[j].getFace()] ){
            return 2;
        }
        else{
            //do nothing
        }
        
    }
    
    return 0;
}

int dealer::twoPairTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if(faceToValue[data1.card1Face] > faceToValue[data2.card1Face])
        return 1;
    else if(faceToValue[data1.card1Face] < faceToValue[data2.card1Face])
        return 2;
    else{
        if(faceToValue[data1.card2Face] > faceToValue[data2.card2Face])
            return 1;
        else if(faceToValue[data1.card2Face] < faceToValue[data2.card2Face])
            return 2;
    }
    //check which of the "kickers" is greater
    int i=7;
    int j=7;
    while( (i>=2) && (j>=2) ){
        j--;
        i--;
        //if relevant card is found, ignore it and move forward, for hand1
        while( (hand1[i].getFace() == data1.card1Face) || (hand1[i].getFace() == data1.card2Face)  ){
            i--;
        }
        //if relevant card if found, ignore it and move forward, for hand2
        while( (hand2[j].getFace() == data2.card1Face)  || (hand2[j].getFace() == data2.card2Face) ){
            j--;
        }
        if( (i<2) || (j<2) ){
            break;
        }
        if(faceToValue[hand1[i].getFace()] > faceToValue[hand2[j].getFace()] ){
            return 1;
        }
        else if(faceToValue[hand1[i].getFace()] < faceToValue[hand2[j].getFace()] ){
            return 2;
        }
        else{
            return 0;
        }
        
    }
    return 0;
}

int dealer::pairTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if( faceToValue[data1.card1Face] > faceToValue[data2.card1Face] )
        return 1;
    else if( faceToValue[data1.card1Face] < faceToValue[data2.card1Face] )
        return 2;
    //check which of the "kickers" is greater
    int i=7;
    int j=7;
    while( (i>=2) && (j>=2) ){
        j--;
        i--;
        //if relevant card is found, ignore it and move forward, for hand1
        if(hand1[i].getFace() == data1.card1Face){
            i--;
        }
        //if relevant card if found, ignore it and move forward, for hand2
        if(hand2[j].getFace() == data2.card1Face){
            j--;
        }
        if( (i<2) || (j<2) ){
            break;
        }
        if(faceToValue[hand1[i].getFace()] > faceToValue[hand2[j].getFace()] ){
            return 1;
        }
        else if(faceToValue[hand1[i].getFace()] < faceToValue[hand2[j].getFace()] ){
            return 2;
        }
        else{
            //do nothing
        }
        
    }
    return 0;
}

int dealer::highCardTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    for(int i=6; i>=2; i--){
        if( faceToValue[hand1[i].getFace()] > faceToValue[hand2[i].getFace()] )
            return 1;
        else if( faceToValue[hand1[i].getFace()] < faceToValue[hand2[i].getFace()] )
            return 2;
    }
    return 0;
}

//Pre condition: The Card arrays passed into this function are of the same "typeOfHand"
//              and the handData parameters will only have a non empty cardFace2 if cardFace1 is non empty
//              and because of this, both handData variables will have the same non empty cardFaces
//Post condition: returns 0 if they are the same hand, returns 1 if the first hand is greater, and 2 if the second hand is greater
int dealer::handTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if(data1.handScore == 9)
        return straightFlushTieBreaker(hand1, hand2,  data1, data2);
    else if(data1.handScore == 8)
        return fourOfAKindTieBreaker(hand1, hand2, data1, data2);
    else if(data1.handScore == 7)
        return fullHouseTieBreaker(hand1, hand2, data1, data2);
    else if(data1.handScore == 6)
        return flushTieBreaker(hand1, hand2, data1, data2);
    else if(data1.handScore == 5)
        return straightTieBreaker(hand1, hand2, data1, data2);
    else if(data1.handScore == 4)
        return threeOfAKindTieBreaker(hand1, hand2, data1, data2);
    else if(data1.handScore == 3)
        return twoPairTieBreaker(hand1, hand2, data1, data2);
    else if(data1.handScore == 2)
        return pairTieBreaker(hand1, hand2, data1, data2);
    else if(data1.handScore == 1)
        return highCardTieBreaker(hand1, hand2, data1, data2);
    else{
        return -1;
    }
}

int dealer::compareHand(Card hand1[], Card hand2[], handData data1, handData data2){
    if(data1.handScore > data2.handScore)
        return 1;
    else if (data1.handScore < data2.handScore)
        return 2;
    else{
        return handTieBreaker(hand1, hand2, data1, data2);
    }
}


//Precondition: Input parameter SevenCardHand is an array sorted by card faces
//Postcondition:
handData dealer::typeOfHand(Card SevenCardHand[]){
    
    
    cout  << "*********************Start of hand evaluation****************" << endl << endl;
    handData pokerHand;
    
    pokerHand.handScore = 0;
    int straightFlushindex = -1;
    int straightIndex = -1;
    int flushIndex = -1;//location of a card with the flush suit in the SVH
    int largestSuitIndex[4] = {0}; //used in Flush check
    int suitsArray[4] = {0};//0: dia, 1: clu, 2: hea, 3: spa - Used in Flush check
    int fourOfKindFace = -1;//Used in Four of a Kind check
    int allFacesArr[13] = {0};//Used in Four of a Kind check
    int tripleHand = -1;//Used in Three of a Kind check (and Full House check)
    int pairHandFullHouse = -1;//Used in Full House check
    int fullHouse = -1;//Used in Full House check
    int firstPair = -1;//Used in Two Pair check
    int secondPair = -1;//Used in Two Pair check
    int twoPair = -1;//Used in Two Pair check
    int highCardIndex = -1; //Used in High Card check
    
    /****************9. Start of checking for a straight flush****************/
    for(int i=6; i>=4; i--){ // after 4, it can't be a 5 card hand
        straightFlushindex = i;
        for(int j=0; j<4; j++){//check the next 5 cards for the Straight requirement
            //if i-jth card face is one greater than the i-j-1th card face
            //and if the suits are the same
            if( (faceToValue[SevenCardHand[i-j].getFace()] ==
                 (faceToValue[SevenCardHand[i-j-1].getFace()] + 1 ) )
               &&(suitToValue[SevenCardHand[i-j].getSuit()] ==
                  suitToValue[SevenCardHand[i-j-1].getSuit()] )
               ){
                //do nothing
            }
            else{
                straightFlushindex = -1;
                break;
            }
        }
        //If a straight was found, it is the highest straight in this hand, so exit
        if(straightFlushindex != -1){
            break;
        }
    }
    cout << endl << endl << "Is this a Straight Flush: " << straightFlushindex << endl;
    if(straightFlushindex != -1){
        if(pokerHand.handScore < 9){
            pokerHand.handScore = 9;
            pokerHand.card1Face = SevenCardHand[straightFlushindex].getFace();
        }
        cout << "With a " << SevenCardHand[straightFlushindex].getFace() << " high card! And a suit of "  << SevenCardHand[straightFlushindex].getSuit() << endl;
    }
    /****************9. End of checking for a Straight Flush****************/
    /****************5. Start of checking for a Straight****************/
    for(int i=6; i>=4; i--){ // after 4, it can't be a 5 card hand
        straightIndex = i;
        for(int j=0; j<4; j++){//check the next 5 cards for the Straight requirement
            //if i-jth card face is one greater than the i-j-1th card face
            if(faceToValue[SevenCardHand[i-j].getFace()] ==
               (1 + faceToValue[SevenCardHand[i-j-1].getFace()])
               ){
                //do nothing
            }
            else{
                straightIndex = -1;
                break;
            }
        }
        //If a straight was found, it is the highest straight in this hand, so exit
        if(straightIndex != -1){
            break;
        }
    }
    cout << endl << endl << "Is this a straight: " << straightIndex << endl;
    if(straightIndex != -1){
        if(pokerHand.handScore < 5){
            pokerHand.handScore = 5;
            pokerHand.card1Face = SevenCardHand[straightIndex].getFace();
        }
        cout << "With a " << SevenCardHand[straightIndex].getFace() << " high card!"<< endl;
    }
    
    /****************5. End of checking for a Straight****************/
    /****************6. Start of checking for a Flush****************/
    for(int i=6; i>=0; i--){ // for every card in Seven Card Hand
        suitsArray[suitToValue[SevenCardHand[i].getSuit()] - 1]++;//increment the counter for each suit encountered
        if(suitsArray[suitToValue[SevenCardHand[i].getSuit()] - 1] == 1 ){
            largestSuitIndex[suitToValue[SevenCardHand[i].getSuit()] -1 ]  = i;
        }
        if(i<=2){//after the counter is less than or under 2
            for(int z=0; z<4; z++){//check through the suit counter and look for a flush
                if(suitsArray[z] == 5){//a flush already exists
                    flushIndex = largestSuitIndex[z];
                    i = -1;
                    break;
                }
            }
        }
    }
    
    cout << endl << endl << "Does this hand contain a Flush: " << flushIndex;
    if(flushIndex != -1){
        if(pokerHand.handScore < 6){
            pokerHand.handScore = 6;
            pokerHand.card1Face = SevenCardHand[flushIndex].getFace();
        }
        cout << endl << "It is a Flush of " << SevenCardHand[flushIndex].getSuit();
        cout << ", with a " << SevenCardHand[flushIndex].getFace() << " high card!";
    }
    cout << endl << endl;
    
    /****************6. End of checking for a Flush****************/
    /****************8. Start of checking for a Four of a Kind****************/
    for(int i=0; i<7; i++){
        allFacesArr[faceToValue[SevenCardHand[i].getFace()]]++;
    }
    cout << endl << "The array of faces is: " <<  endl;
    for(int i = 0; i<13; i++){
        cout << "@ i = " << i << ", count is = " << allFacesArr[i] << endl;
    }
    cout << endl;
    
    for(int i=12; i>=0; i--){
        if(allFacesArr[i] >= 4){
            fourOfKindFace = i;
        }
    }
    cout << "Does the hand hold a four of a kind: " << fourOfKindFace << endl;
    if(fourOfKindFace != -1){
        if(pokerHand.handScore < 8){
            pokerHand.handScore = 8;
            pokerHand.card1Face = valueToFace[fourOfKindFace];
        }
        cout << "The Four Of A Kind is of face: " << valueToFace[fourOfKindFace];
    }
    cout << endl << endl;
    
    /****************8. End of checking for a Four of a Kind****************/
    /****************7. Start checking for a Full House****************/
    /****************4. Start of checking for a Three of a Kind****************/
    //Check for the highest triple
    for(int i=12; i>=0; i--){
        if(allFacesArr[i] >= 3){
            tripleHand = i;
            break;
        }
    }
    //Check for the highest double
    for(int i=12; i>=0; i--){
        if(i != tripleHand){ // Excluding the triple
            if(allFacesArr[i] >= 2){
                pairHandFullHouse = i;
                break;
            }
        }
        
    }
    
    cout << "Does the hand hold Three of a Kind: " << tripleHand << endl;
    if(tripleHand != -1){
        if(pokerHand.handScore < 4){
            pokerHand.handScore = 4;
            pokerHand.card1Face = valueToFace[tripleHand];
        }
        cout << "The Three of a Kind is a: " << valueToFace[tripleHand] << endl;
    }
    /****************4. End of checking for a Three of a Kind****************/
    
    if( (tripleHand != -1) && (pairHandFullHouse != -1) ){
        fullHouse = 1;
    }
    
    cout << "Does the hand hold Full House: " << fullHouse << endl;
    if(fullHouse != -1){
        if(pokerHand.handScore < 7){
            pokerHand.handScore = 7;
            pokerHand.card1Face = valueToFace[tripleHand];
            pokerHand.card2Face = valueToFace[pairHandFullHouse];
        }
        cout << "The FullHouse is a: " << valueToFace[tripleHand];
        cout << ", full of: " << valueToFace[pairHandFullHouse] << endl;;
    }
    
    /****************7. End of checking for a Full House****************/
    /****************3. Start of checking for a two pair****************/
    //find the first pair
    for(int i=12; i>=0; i--){
        if(allFacesArr[i] >= 2){
            firstPair = i;
            break;
        }
    }
    //find the second pair
    if(firstPair != -1){
        for(int i=12; i>=0; i--){
            if(i != firstPair){
                if(allFacesArr[i] >= 2){
                    secondPair = i;
                    break;
                }
            }
        }
    }
    
    if( (firstPair != -1) && (secondPair != -1) ){
        twoPair = 1;
    }
    
    cout << "Does the hand hold Two Pair: " << twoPair << endl;
    if(twoPair != -1){
        if(pokerHand.handScore < 3){
            pokerHand.handScore = 3;
            pokerHand.card1Face = valueToFace[firstPair];
            pokerHand.card2Face = valueToFace[secondPair];
        }
        cout << "A pair of: " << valueToFace[firstPair] << "s";
        cout << ", and pair of: " << valueToFace[secondPair] << "s" << endl;
    }
    
    /****************3. End of checking for a two pair****************/
    /****************2. Start of checking for a pair****************/
    //It has already been found by the previous algorithm
    cout << "Does the hand hold a Pair: " << firstPair << endl;
    if(firstPair != -1){
        if(pokerHand.handScore < 2){
            pokerHand.handScore = 2;
            pokerHand.card1Face = valueToFace[firstPair];
        }
        cout << "A pair of: " << valueToFace[firstPair] << "s" << endl;
    }
    /****************2. End of checking for a pair****************/
    
    /****************1. Start of checking for the highest card****************/
    //find the high card
    for(int i=12; i>=0; i--){
        if(allFacesArr[i] > 0){
            highCardIndex = i;
            break;
        }
    }
    
    
    cout << "What is the hand's high card: " << highCardIndex << endl;
    if(highCardIndex != -1){
        if(pokerHand.handScore < 1){
            pokerHand.handScore = 1;
            pokerHand.card1Face = SevenCardHand[6].getFace();
        }
        cout << "A high card of: " << valueToFace[highCardIndex] << endl;
    }
    
    /****************1. End of checking for the highest card****************/
    
    
    cout << endl << endl << "The hand score of the hand is: " << pokerHand.handScore;
    cout << endl << "In function: And that is a " << handScoreMap[pokerHand.handScore];
    cout << endl << "The key cards in this function are: " << pokerHand.card1Face;
    cout << ", " << pokerHand.card2Face;
    cout << endl << endl;
    
    cout  << "*********************End of hand evaluation****************" << endl << endl;
    
    return pokerHand;
}
