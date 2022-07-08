/* File: PA2.cpp
* Course: CS216-002
* Project: Project 2
* Purpose: Creates a cpp file that runs a game of poker.
* between a player and a computer and determines a winner.
*/ 


#include <iostream>
#include <vector>
#include "pokerhand.h"
#include "card.h"
#include "deck.h"

using namespace std;

//Constant values
const int INITIAL = 2;
const int TOTALCARDS = 7;
const int HANDS = 5;

//Function for finding the best 5 cards for a 7 cards
PokerHand bestHand(const vector<Card>& cards)
 { 
     PokerHand bestH;
     PokerHand cardsH;
 
     // check if the parameter is valid
     if (cards.size() != TOTALCARDS)
     {
         cout << "Invalid Cards, we need SEVEN cards!" << endl;
         return cardsH; // return a PokerHand object by default constructor
     }
 
     // Consider all possible ways of dropping two cards
     // from all seven cards 
     // i is the index of the first card dropped
     // and j is the index of the second card dropped.
     // There are 21 different ways to pick 5 cards out of 7
	for (int i=0; i < TOTALCARDS; i++)
     {
         for (int j=i+1; j < TOTALCARDS; j++)
         {
             Card pick[HANDS];
             int index = 0;
 
             // Iterate over all seven cards and assign them to the pick[] array
             // exclude cards with index numbers of #i and #j.
             for (int k=0 ; k < TOTALCARDS ; k++)
             {
                 if (k == i || k == j)
                     continue;
                 pick[index] = cards[k];
                 index++;
             }
 
             // create a PokerHand with pick[]
             cardsH.setPokerHand(pick, HANDS);
 
             // Check to see if current pick is better than
             // the best you have seen so far
             if (bestH.compareHand(cardsH) < 0)
             {
                 bestH = cardsH ;
             }
         }
     }
     // Now bestH holds the best poker hand among all 21 poker hand
     cout << "*** Best five-card hand ***" << endl;
     bestH.print();
     cout << endl << endl;
    return bestH;
}


int main(){

//Initialize variables
string check;
Deck deck;
vector<Card> playerHand;
vector<Card> cpuHand;
vector<Card> sharedCards;
PokerHand pBestHand;
PokerHand cBestHand;
int computeWinner;

//Start loop to play until the player types "q" or "Q"
while(check != "q" && check != "Q"){
    
    //Creates a new deck
    deck.createDeck();
    //Shuffle the deck
    deck.shuffleDeck();

    //Draw two cards for player and computer hand
    for(int i =0; i < INITIAL; i++){
        playerHand.push_back(deck.deal_a_card());
        cpuHand.push_back(deck.deal_a_card());
    }
    
    //Print the cards in the player's hand
    cout << "The cards in your hand are:" << endl;
    for(int i = 0; i < INITIAL; i++){
        for(int j = 0; j < i +1; j++){
            cout << "   ";
        }
        playerHand[i].print();
        cout << "\n";
    }

    //Deal and print the 5 cards that are shared between the player
    cout << "The FIVE cards in the deck to share are: " << endl;
    cout << "   *************************" << endl;
    for(int i = 0; i < HANDS; i++){
        sharedCards.push_back(deck.deal_a_card());
        cout << "   *  ";
        sharedCards[i].print();
        cout << "       *" << endl;
    }
    cout << "   *************************" << endl;

    //Print the cards in the computer's hand
    cout << "The cards in computer's hand are: " << endl;
    for(int i = 0; i < INITIAL; i++){
        for(int j = 0; j < i +1; j++){
             cout << "   ";
         }

        cpuHand[i].print();
        cout << "\n";
    }

    cout << "\nPlayer 1: You" << endl;
    
    //Print the Player's best hand
    for(int i = 0; i < HANDS; i++){
        playerHand.push_back(sharedCards[i]);
        cpuHand.push_back(sharedCards[i]);
    }
        
    pBestHand = bestHand(playerHand);
    
    cout << "\n\n";
    
    //Print the Computer's best hand
    cout << "Player 2: Computer" << endl;
    cBestHand = bestHand(cpuHand);

    cout << "\n\n";
    
    computeWinner = pBestHand.compareHand(cBestHand);
    
    //Determine the winner of the game
    if(computeWinner > 0){
    cout << "Congratulations, you win the game!" << endl;
    }
    else if(computeWinner < 0){
    cout << "Sorry, the computer wins the game!" << endl;
    }
    else{
    cout << "Its a tie!" << endl;
    }
    
    //Empty players, computers, and shared hand
    playerHand.clear();
    cpuHand.clear();
    sharedCards.clear();
    
    //Find if player wants to play again or end loop
    cout << "\nDo you want to play poker game again? (Press \"q\" or \"Q\" to quit the program)";
    getline(cin, check);
    if(check  == "\n") cin.ignore();

    
    }

//End of program
cout << "Thank you for using this program!" << endl;;
    return 0;
}


