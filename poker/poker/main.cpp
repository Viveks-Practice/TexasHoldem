//
//  main.cpp
//  poker
//
//  Created by Vivek Sharma on 2020-11-09.
//  Copyright © 2020 Vivek. All rights reserved.
//
//  User enters the number of players they want in the game, to begin. They are playing against computerized players.

#include "player.hpp"
#include "Card.h"
#include "Deck.hpp"
#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

/*
 Consider making the main function activites just be a dealer class doing all the work
 */




map<string, int> faceToValue;
map<int, string> valueToFace;
map<string, int> suitToValue;
map<int, string> handScoreMap;

struct handData{
    int handScore = 0;
    string card1Face = "";
    string card2Face = "";
};

//Precondition: call this function when typeOfHand returns handData.handScore == 9
//              there will be a non empty handData.card1 value
int straightFlushTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if(faceToValue[data1.card1Face] > faceToValue[data2.card1Face])
        return 1;
    else if(faceToValue[data1.card1Face] < faceToValue[data2.card1Face])
        return 2;
    else
        return 0;
    
    return 0;
}

//return a card face for the other types as well, and use it to find the tiebreaker for each specific type of hand
int fourOfAKindTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){

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

int fullHouseTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
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

int flushTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if(faceToValue[data1.card1Face] > faceToValue[data2.card1Face])
        return 1;
    else if(faceToValue[data1.card1Face] < faceToValue[data2.card1Face])
        return 2;
    else
        return 0;
    
    return 0;
}

int straightTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
    if(faceToValue[data1.card1Face] > faceToValue[data2.card1Face])
        return 1;
    else if(faceToValue[data1.card1Face] < faceToValue[data2.card1Face])
        return 2;
    else
        return 0;
    
    return 0;
}

int threeOfAKindTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
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

int twoPairTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
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

int pairTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
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

int highCardTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
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
int handTieBreaker(Card hand1[], Card hand2[], handData data1, handData data2){
    
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

int compareHand(Card hand1[], Card hand2[], handData data1, handData data2){
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
handData typeOfHand(Card SevenCardHand[]){
    
    
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

//Future features:
//0. The same cards are dealt every game! Big no no.
//1. Implement "raises" and another round of betting if a raise occurs, instead of lopsided bets
//1.1 Implement a flag for each player to check if they are out of chips and whether or not they
//    should be dealt a hand or not (***** or just a getter func to read if chips!= 0*****)
//1.2 Implement player names
//2. Make a dealer class that does all of the turns and stuff instead of the main function
//3. Implement inheritance with players being children of player class - CPU or Person
//4. Implement other OOP principles
//5. (Optional - no one will even appreciate this one) Implement all poker features, such as blinds, and poker button, and all that.
//6. Don't forget to account for straights that start with an Ace
int main(int argc, const char * argv[]) {

    int cint;
    int pot = 0;
    int cpuPlayerCount = 0;
    Deck pokerDeck;
    Card turnFlopRiver[5];
    
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
    
    
    
    
    /******************Start of Testing Stuff******************/
    
    //Test SevenCardHand
    Card TestSevenCardHand[7];
    TestSevenCardHand[0].setFace("Deuce");
    TestSevenCardHand[1].setFace("Three");
    TestSevenCardHand[2].setFace("Six");
    TestSevenCardHand[3].setFace("Eight");
    TestSevenCardHand[4].setFace("Nine");
    TestSevenCardHand[5].setFace("Ten");
    TestSevenCardHand[6].setFace("Ace");
    
    TestSevenCardHand[0].setSuit("Hearts");
    TestSevenCardHand[1].setSuit("Hearts");
    TestSevenCardHand[2].setSuit("Clubs");
    TestSevenCardHand[3].setSuit("Hearts");
    TestSevenCardHand[4].setSuit("Diamonds");
    TestSevenCardHand[5].setSuit("Diamonds");
    TestSevenCardHand[6].setSuit("Diamonds");
    
    
    Card Test2SevenCardHand[7];
    Test2SevenCardHand[0].setFace("Deuce");
    Test2SevenCardHand[1].setFace("Four");
    Test2SevenCardHand[2].setFace("Six");
    Test2SevenCardHand[3].setFace("Seven");
    Test2SevenCardHand[4].setFace("Eight");
    Test2SevenCardHand[5].setFace("Ten");
    Test2SevenCardHand[6].setFace("Ace");
    
    Test2SevenCardHand[0].setSuit("Hearts");
    Test2SevenCardHand[1].setSuit("Clubs");
    Test2SevenCardHand[2].setSuit("Clubs");
    Test2SevenCardHand[3].setSuit("Clubs");
    Test2SevenCardHand[4].setSuit("Diamonds");
    Test2SevenCardHand[5].setSuit("Hearts");
    Test2SevenCardHand[6].setSuit("Clubs");
    
    cout << endl << "The testing player's seven card hand is: " <<  endl;
    for(int i = 0; i<7; i++){
        cout << TestSevenCardHand[i].printCard() << endl;
    }
    cout << endl;
    
    handData test1PokerHand = typeOfHand(TestSevenCardHand);
    handData test2PokerHand = typeOfHand(Test2SevenCardHand);
    
    cout << endl << "~~~~~~~~Straight Flush TIE BREAKER???~~~~~~~~~" << endl << endl;
    if( (test1PokerHand.handScore != 9) || (test2PokerHand.handScore != 9) ){
        cout << endl << endl << "No Straight Flush tie breaker is required ";
        cout << endl << "First hand score: " << test1PokerHand.handScore;
        cout << ", Second hand score: " << test2PokerHand.handScore;
    }
    else if( (test1PokerHand.handScore == 9) && (test2PokerHand.handScore == 9) ){
        cout << endl << endl << "The Straight Flush tiebreaker result is: ";
        cout << straightFlushTieBreaker(TestSevenCardHand, Test2SevenCardHand, test1PokerHand, test2PokerHand);
    }
    cout << endl << endl;
    
    
    cout << endl << "~~~~~~~~Four of a Kind TIE BREAKER???~~~~~~~~~" << endl << endl;
    if( (test1PokerHand.handScore != 8) || (test2PokerHand.handScore != 8) ){
        cout << endl << endl << "No FoaK tie breaker is required ";
        cout << endl << "First hand score: " << test1PokerHand.handScore;
        cout << ", Second hand score: " << test2PokerHand.handScore;
    }
    else if( (test1PokerHand.handScore == 8) && (test2PokerHand.handScore == 8) ){
        cout << endl << endl << "The FoaK tiebreaker result is: ";
        cout << fourOfAKindTieBreaker(TestSevenCardHand, Test2SevenCardHand, test1PokerHand, test2PokerHand);
        cout << endl << "First hand score: " << test1PokerHand.handScore;
        cout << ", Second hand score: " << test2PokerHand.handScore;
    }
    cout << endl << endl;
    
    cout << endl << "~~~~~~~~Full House TIE BREAKER???~~~~~~~~~" << endl << endl;
    if( (test1PokerHand.handScore != 7) || (test2PokerHand.handScore != 7) ){
        cout << endl << endl << "No Full House tie breaker is required ";
        cout << endl << "First hand score: " << test1PokerHand.handScore;
        cout << ", Second hand score: " << test2PokerHand.handScore;
    }
    else if( (test1PokerHand.handScore == 7) && (test2PokerHand.handScore == 7) ){
        cout << endl << endl << "The Full House tiebreaker result is: ";
        cout << fullHouseTieBreaker(TestSevenCardHand, Test2SevenCardHand, test1PokerHand, test2PokerHand);
    }
    cout << endl << endl;
    
    cout << endl << "~~~~~~~~Flush TIE BREAKER???~~~~~~~~~" << endl << endl;
    if( (test1PokerHand.handScore != 6) || (test2PokerHand.handScore != 6) ){
        cout << endl << endl << "No Flush tie breaker is required ";
        cout << endl << "First hand score: " << test1PokerHand.handScore;
        cout << ", Second hand score: " << test2PokerHand.handScore;
    }
    else if( (test1PokerHand.handScore == 6) && (test2PokerHand.handScore == 6) ){
        cout << endl << endl << "The Flush tiebreaker result is: ";
        cout << flushTieBreaker(TestSevenCardHand, Test2SevenCardHand, test1PokerHand, test2PokerHand);
    }
    cout << endl << endl;
    
    cout << endl << "~~~~~~~~Straight TIE BREAKER???~~~~~~~~~" << endl << endl;
    if( (test1PokerHand.handScore != 5) || (test2PokerHand.handScore != 5) ){
        cout << endl << endl << "No Straight tie breaker is required ";
        cout << endl << "First hand score: " << test1PokerHand.handScore << " " << test1PokerHand.card1Face;
        cout << ", Second hand score: " << test2PokerHand.handScore << " " << test2PokerHand.card1Face;
    }
    else if( (test1PokerHand.handScore == 5) && (test2PokerHand.handScore == 5) ){
        cout << endl << endl << "The Straight tiebreaker result is: ";
        cout << straightTieBreaker(TestSevenCardHand, Test2SevenCardHand, test1PokerHand, test2PokerHand);
        cout << endl << "First hand score: " << test1PokerHand.handScore << " " << test1PokerHand.card1Face;
        cout << ", Second hand score: " << test2PokerHand.handScore << " " << test2PokerHand.card1Face;
    }
    cout << endl << endl;
    
    cout << endl << "~~~~~~~~Three Of A Kind TIE BREAKER???~~~~~~~~~" << endl << endl;
    if( (test1PokerHand.handScore != 4) || (test2PokerHand.handScore != 4) ){
        cout << endl << endl << "No Three of a Kind tie breaker is required ";
        cout << endl << "First hand score: " << test1PokerHand.handScore << " " << test1PokerHand.card1Face;
        cout << ", Second hand score: " << test2PokerHand.handScore << " " << test2PokerHand.card1Face;
    }
    else if( (test1PokerHand.handScore == 4) && (test2PokerHand.handScore == 4) ){
        cout << endl << endl << "The Three of a Kind tiebreaker result is: ";
        cout << threeOfAKindTieBreaker(TestSevenCardHand, Test2SevenCardHand, test1PokerHand, test2PokerHand);
        cout << endl << "First hand score: " << test1PokerHand.handScore << " " << test1PokerHand.card1Face;
        cout << ", Second hand score: " << test2PokerHand.handScore << " " << test2PokerHand.card1Face;
    }
    cout << endl << endl;
    
    cout << endl << "~~~~~~~~Two Pair TIE BREAKER???~~~~~~~~~" << endl << endl;
    if( (test1PokerHand.handScore != 3) || (test2PokerHand.handScore != 3) ){
        cout << endl << endl << "No Two Pair tie breaker is required ";
        cout << endl << "First hand score: " << test1PokerHand.handScore << " " << test1PokerHand.card1Face;
        cout << ", Second hand score: " << test2PokerHand.handScore << " " << test2PokerHand.card1Face;
    }
    else if( (test1PokerHand.handScore == 3) && (test2PokerHand.handScore == 3) ){
        cout << endl << endl << "The Two Pair tiebreaker result is: ";
        cout << twoPairTieBreaker(TestSevenCardHand, Test2SevenCardHand, test1PokerHand, test2PokerHand);
        cout << endl << "First hand score: " << test1PokerHand.handScore << " " << test1PokerHand.card1Face << ", " << test1PokerHand.card2Face;
        cout << ", Second hand score: " << test2PokerHand.handScore << " " << test2PokerHand.card1Face << ", " << test2PokerHand.card2Face;
    }
    cout << endl << endl;
    
    cout << endl << "~~~~~~~~Pair TIE BREAKER???~~~~~~~~~" << endl << endl;
    if( (test1PokerHand.handScore != 2) || (test2PokerHand.handScore != 2) ){
        cout << endl << endl << "No Pair tie breaker is required ";
        cout << endl << "First hand score: " << test1PokerHand.handScore << " " << test1PokerHand.card1Face;
        cout << ", Second hand score: " << test2PokerHand.handScore << " " << test2PokerHand.card1Face;
    }
    else if( (test1PokerHand.handScore == 2) && (test2PokerHand.handScore == 2) ){
        cout << endl << endl << "The Pair tiebreaker result is: ";
        cout << pairTieBreaker(TestSevenCardHand, Test2SevenCardHand, test1PokerHand, test2PokerHand);
        cout << endl << "First hand score: " << test1PokerHand.handScore << " " << test1PokerHand.card1Face << ", " << test1PokerHand.card2Face;
        cout << ", Second hand score: " << test2PokerHand.handScore << " " << test2PokerHand.card1Face << ", " << test2PokerHand.card2Face;
    }
    cout << endl << endl;
    
    cout << endl << "~~~~~~~~High Card TIE BREAKER???~~~~~~~~~" << endl << endl;
    if( (test1PokerHand.handScore != 1) || (test2PokerHand.handScore != 1) ){
        cout << endl << endl << "No High Card tie breaker is required ";
        cout << endl << "First hand score: " << test1PokerHand.handScore << " " << test1PokerHand.card1Face;
        cout << ", Second hand score: " << test2PokerHand.handScore << " " << test2PokerHand.card1Face;
    }
    else if( (test1PokerHand.handScore == 1) && (test2PokerHand.handScore == 1) ){
        cout << endl << endl << "The High Card tiebreaker result is: ";
        cout << highCardTieBreaker(TestSevenCardHand, Test2SevenCardHand, test1PokerHand, test2PokerHand);
        cout << endl << "First hand score: " << test1PokerHand.handScore << " " << test1PokerHand.card1Face << ", " << test1PokerHand.card2Face;
        cout << ", Second hand score: " << test2PokerHand.handScore << " " << test2PokerHand.card1Face << ", " << test2PokerHand.card2Face;
    }
    cout << endl << endl;
    
    cout << endl << "~~~~~~~~TIE BREAKER???~~~~~~~~~" << endl << endl;
    if(test1PokerHand.handScore != test2PokerHand.handScore){
        cout << endl << endl << "No tiebreaker is required ";
        cout << endl << "First hand score: " << test1PokerHand.handScore;
        cout << ", Second hand score: " << test2PokerHand.handScore;
    }
    else{
        cout << endl << endl << "The tiebreaker result is: ";
        cout << handTieBreaker(TestSevenCardHand, Test2SevenCardHand, test1PokerHand, test2PokerHand);
    }
    cout << endl << endl;
    
    
    cout << endl << endl << "Outside the function the cards are: " << test1PokerHand.card1Face << ", " << test1PokerHand.card2Face << endl;
    /******************End of Testing Stuff******************/


    
    /*Begin: Start of game messages*/
    cout << endl << endl;
    cout << "~~~~~~~~This will be a game of No Limit Texas Hold'em~~~~~~~~" << endl << endl;
    cout << "Welcome to the Poker table!" << endl;

    cout << "Please enter the number of computer players you would like to play against (max 6): ";
    cpuPlayerCount = 2;
    //cin >> cpuPlayerCount;
    
    while( (cpuPlayerCount < 1) || (cpuPlayerCount > 6) ){
        cout << "Error: player count is out of range" << endl << "Enter 1 or 6 or any number in between :";
        cin >> cpuPlayerCount;
    }
    cout << "You will be playing with " << cpuPlayerCount << " computer players. The total of players is " << cpuPlayerCount + 1 << "." << endl << endl;
    cout << "~~~~Good luck folks!~~~~" << endl << endl << "~~~~Now let's get the cards in the air!~~~~" << endl << endl <<  "~~~~Dealer, shuffle up and deal!~~~~" << endl << endl;
    
    /*End: Start of game messages*/
    
    //pokerDeck.revealDeck();
    pokerDeck.startGame();
    //pokerDeck.revealDeck();
    
    
    player allPlayers[cpuPlayerCount + 1];
    
    //Start: Deal hands to all players
    for(int i=0; i<=cpuPlayerCount; i++){//Only deal to players that have not lost all chips
        allPlayers[i].receiveHand(pokerDeck.deal(), pokerDeck.deal());
    }
    
    //Show each players hand
    for(int i=0; i<=cpuPlayerCount; i++){
        cout << "Revealing Hand of Player: " << (i+1) << endl;
        allPlayers[i].revealHand();
        cout << endl;
    }
    
    //First round of betting
    for(int i=0; i<=cpuPlayerCount; i++){
        if(allPlayers[i].getParticipating()){ //Not needed for first round
            pot += allPlayers[i].turnAction();
        }
    }
    
    cout << endl << "The pot size is: " << pot << endl;
    
    //The flop
    turnFlopRiver[0] = pokerDeck.deal();
    turnFlopRiver[1] = pokerDeck.deal();
    turnFlopRiver[2] = pokerDeck.deal();
    
    //Show the flop
    cout << endl << "The flop is: " << endl;
    cout << endl << turnFlopRiver[0].printCard() << ", ";
    cout << endl << turnFlopRiver[1].printCard() << ", ";
    cout << endl << turnFlopRiver[2].printCard() << endl;

    cout << endl << "Count of cards is: " << pokerDeck.getCardCount() << endl<< endl;
    
    //Second round of betting
    for(int i=0; i<=cpuPlayerCount; i++){
        if(allPlayers[i].getParticipating()){
            pot += allPlayers[i].turnAction();
        }
    }
    
    cout << endl << "The pot size is: " << pot << endl;
    
    //The turn
    turnFlopRiver[3] = pokerDeck.deal();
    
    //Show the turn
    cout << endl << "The turn is: " << endl;
    cout << endl << turnFlopRiver[0].printCard() << ", ";
    cout << endl << turnFlopRiver[1].printCard() << ", ";
    cout << endl << turnFlopRiver[2].printCard() << ", ";
    cout << endl << turnFlopRiver[3].printCard() << endl;
    
    cout << endl << "Count of cards is: " << pokerDeck.getCardCount() << endl<< endl;
    
    //Third round of betting
    for(int i=0; i<=cpuPlayerCount; i++){
        if(allPlayers[i].getParticipating()){
            pot += allPlayers[i].turnAction();
        }
    }
    
    cout << endl << "The pot size is: " << pot << endl;
    
    //The river
    turnFlopRiver[4] = pokerDeck.deal();
    
    //Show the river
    cout << endl << "The turn is: " << endl;
    cout << endl << turnFlopRiver[0].printCard() << ", ";
    cout << endl << turnFlopRiver[1].printCard() << ", ";
    cout << endl << turnFlopRiver[2].printCard() << ", ";
    cout << endl << turnFlopRiver[3].printCard() << ", ";
    cout << endl << turnFlopRiver[4].printCard() << endl;
    
    cout << endl << "Count of cards is: " << pokerDeck.getCardCount() << endl<< endl;
    
    //Fourth and final round of betting
    for(int i=0; i<=cpuPlayerCount; i++){
        if(allPlayers[i].getParticipating()){
            pot += allPlayers[i].turnAction();
        }
    }
    
    //Give chips to the hand with the highest value!
    Card playersSevenCardHands[cpuPlayerCount+1][7]; //Seven Card Hand of each player
    for(int i=0;i<=cpuPlayerCount; i++){//for each player
        for(int j=0; j<5; j++){//their first five cards will be from the community cards
            playersSevenCardHands[i][j] = turnFlopRiver[j];
        }
        //Their next two cards will be their own individual cards
        playersSevenCardHands[i][5] = allPlayers[i].getCard1();
        playersSevenCardHands[i][6] = allPlayers[i].getCard2();
    }
    //print each player's seven cards
    for(int i=0; i<(cpuPlayerCount + 1); i++){//for each player
        cout << endl << "Player: " << i << "'s seven card hand is: " <<  endl;
        for(int j=0; j<7; j++){
            cout << playersSevenCardHands[i][j].printCard() << endl;
        }
    }
    cout << endl;

    /*Sort all of the 7-Card Hands*/
    
    for(int z=0; z<(cpuPlayerCount + 1); z++){
        for(int i=0; i<6; i++){
            for(int j=(i+1); j<7; j++){
                if(faceToValue[playersSevenCardHands[z][i].getFace()] >
                   faceToValue[playersSevenCardHands[z][j].getFace()] ){
                    Card temp = playersSevenCardHands[z][i];
                    playersSevenCardHands[z][i] = playersSevenCardHands[z][j];
                    playersSevenCardHands[z][j] = temp;
                    i--;
                    break;
                }
            }
        }
    }
    
    //print each player's sorted seven cards
    for(int i=0; i<(cpuPlayerCount + 1); i++){//for each player
        cout << endl << "Player: " << i << "'s sorted seven card hand is: " <<  endl;
        for(int j=0; j<7; j++){
            cout << playersSevenCardHands[i][j].printCard() << endl;
        }
    }
    cout << endl;
    
    /*End of sorting the 7-Card Hand*/
    
    /****Test Hands!*****/
    playersSevenCardHands[0][0].setFace("Deuce");
    playersSevenCardHands[0][1].setFace("Four");
    playersSevenCardHands[0][2].setFace("Six");
    playersSevenCardHands[0][3].setFace("Seven");
    playersSevenCardHands[0][4].setFace("Eight");
    playersSevenCardHands[0][5].setFace("Ten");
    playersSevenCardHands[0][6].setFace("Ace");
    
    playersSevenCardHands[0][0].setSuit("Hearts");
    playersSevenCardHands[0][1].setSuit("Clubs");
    playersSevenCardHands[0][2].setSuit("Hearts");
    playersSevenCardHands[0][3].setSuit("Hearts");
    playersSevenCardHands[0][4].setSuit("Hearts");
    playersSevenCardHands[0][5].setSuit("Hearts");
    playersSevenCardHands[0][6].setSuit("Hearts");
    
    playersSevenCardHands[1][0].setFace("Deuce");
    playersSevenCardHands[1][1].setFace("Four");
    playersSevenCardHands[1][2].setFace("Six");
    playersSevenCardHands[1][3].setFace("Seven");
    playersSevenCardHands[1][4].setFace("Eight");
    playersSevenCardHands[1][5].setFace("Ten");
    playersSevenCardHands[1][6].setFace("Jack");
    
    playersSevenCardHands[1][0].setSuit("Hearts");
    playersSevenCardHands[1][1].setSuit("Clubs");
    playersSevenCardHands[1][2].setSuit("Diamonds");
    playersSevenCardHands[1][3].setSuit("Diamonds");
    playersSevenCardHands[1][4].setSuit("Diamonds");
    playersSevenCardHands[1][5].setSuit("Diamonds");
    playersSevenCardHands[1][6].setSuit("Diamonds");
    
    playersSevenCardHands[2][0].setFace("Deuce");
    playersSevenCardHands[2][1].setFace("Four");
    playersSevenCardHands[2][2].setFace("Six");
    playersSevenCardHands[2][3].setFace("Seven");
    playersSevenCardHands[2][4].setFace("Eight");
    playersSevenCardHands[2][5].setFace("Ten");
    playersSevenCardHands[2][6].setFace("Ace");
    
    playersSevenCardHands[2][0].setSuit("Hearts");
    playersSevenCardHands[2][1].setSuit("Hearts");
    playersSevenCardHands[2][2].setSuit("Clubs");
    playersSevenCardHands[2][3].setSuit("Clubs");
    playersSevenCardHands[2][4].setSuit("Clubs");
    playersSevenCardHands[2][5].setSuit("Clubs");
    playersSevenCardHands[2][6].setSuit("Clubs");
    /****End of Test Hands!*****/
    
    /*Start of deciding the winner of the poker round*/
    int winnerArray[7];
    for(int i=0; i<7; i++){
        winnerArray[i] = -1;
    }
    int winnerArrayIndex = 0;
    Card generalSevenCardHand[7];
    //initialize the temp arr to the first players hand
    //generalSevenCardHand = playersSevenCardHands[0];
    for(int j=0; j<7; j++){
        generalSevenCardHand[j] = playersSevenCardHands[0][j];
    }
    winnerArray[winnerArrayIndex] = 0;
    winnerArrayIndex++;
    for(int i=1; i<(cpuPlayerCount +1); i++){
        int comparison = compareHand(generalSevenCardHand, playersSevenCardHands[i],
                    typeOfHand(generalSevenCardHand), typeOfHand(playersSevenCardHands[i]));
        if(comparison == 1){
            //Keep the temp array at the same value
            //Keep the winning player index at the same value
        }
        else if(comparison == 2){
            //make the temp array the new winning hand
            for(int j=0; j<7; j++){
                generalSevenCardHand[j] = playersSevenCardHands[i][j];
            }
            //Reset the winnerArray to all -1
            for(int z=0; z<7; z++){
                winnerArray[z] = -1;
            }
            //Reset the winner array index to 0
            winnerArrayIndex = 0;
            winnerArray[winnerArrayIndex] = i;
            winnerArrayIndex++;
        }
        else if(comparison == 0){
            winnerArray[winnerArrayIndex] = i;
            winnerArrayIndex++;
        }
        else{
            //error!
            cout << endl << endl << "There is a comparison ERROR: " << comparison << endl << endl;
        }
    }
    
    /*Print winner Array*/
    cout << endl << endl << "Printing Winner Array: " << endl;
    for(int i=0; i<7; i++){
        cout << "i= " << winnerArray[i] << endl;
    }
    /*end of printing winner Array*/
    
    /*End of deciding the winner of the poker round*/
    //The index of all winners is stored in winnerArray (all indices that are not -1)
    
    int countOfWinners = 0;
    //cycle through the winners array to count the number of winners
    for(int i=0; i<7; i++){
        if(winnerArray[i] != -1)
            countOfWinners++;
    }
    
    cout << endl << "The pot size is: " << pot << endl;
    cout <<endl << endl << "There are " << countOfWinners << " players with the best hand" << endl;
    
    int potSplit = pot/countOfWinners;
    
    cout << "Each player receives " << potSplit << endl;
    
    for(int i=0; i<countOfWinners; i++){
        allPlayers[winnerArray[i]].addChips(potSplit);
        cout << "Player " << i << " now has " << allPlayers[winnerArray[i]].getChips() << " chips" << endl << endl;
    }
    
    //add the pot split by the number of winners to each winning player
    
    
    //Begin next round of poker!
    
    
    
    cout << "Enter a number to end the game: " << endl;
    cin >> cint;
    return 0;
}


//create an array of all hands
//check all hands possible with the flop and players' hands
//return the hand with the greatest value of the ones that match the players possible hands.
//
