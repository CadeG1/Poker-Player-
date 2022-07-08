/* File: deck.cpp
* Course: CS216-002
* Project: Project 2
* Purpose: the implementation of member functions for the Deck class.
* Author: Cade Gallenstein
*/

#include "deck.h"
#include <cstdlib>

// create a standard 52-card deck
void Deck::createDeck(){
    for(int i = 2; i <= 14; i++){
            deck.push_back(Card('H',i));   
    }
    for(int i = 2; i <= 14; i++){
            deck.push_back(Card('D',i));
    }
    for(int i =2; i <= 14; i++){
            deck.push_back(Card('C',i));
    }
    for(int i = 2; i <= 14; i++){   
            deck.push_back(Card('S',i));
    }
  }

// shuffle the cards in 52-card deck
void Deck::shuffleDeck(){
    vector<Card> newDeck;
    Card ranCard;
    int random;

    srand(time(0));

    for(int i=0; i < 51; i++){
        random = rand() % (deck.size());
        
        ranCard = deck[random];

        newDeck.push_back(ranCard);
        deck.erase(deck.begin() + random);
    }
        deck = newDeck;
}

// return a card from the tail of the deck
Card Deck::deal_a_card(){
    int lastCard = deck.size()-1;
    Card dealtCard = deck[lastCard];
    deck.pop_back();

    return dealtCard;
}
 

