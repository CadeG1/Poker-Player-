/* File: card.cpp
 * Course: CS216-002
 * Project: Project 2
 * Purpose: the implementation of member functions for the Card class.
 * Author: Cade Gallenstein
 */
#include <iomanip>
#include "card.h"
#include <sstream>

 // Default constructor marks card as invalid
Card::Card() {
    suit = 'I';
    point = 0;
}

// Alternate constructor
Card::Card(char s, int p)
{
    suit = s;
    point = p;
}

// access the card point value
int Card::getPoint() const
{
    return point;
}

// access the card suit value
char Card::getSuit() const
{
    return suit;
}

// compare with another Card object passed in as parameter: other
// if the object your are working on has higher point than other, return 1;
// if the object your are working on has lower point than other, return -1;
// otherwise, return 0
int Card::compareTo(Card other) const
{
    int higherValue = 0;

    if(point > other.getPoint()){
    higherValue = 1;
    }
    else if(point < other.getPoint()){
    higherValue = -1;
    }

    return higherValue;
}

// Display a description of the Card object to standard output
// The output should look like:
//   the sign of suit, followed by the point(occupy two-character width), then followed by the sign of suit again
//   for example: ♥ 6♥ and ♣ A♣
void Card::print() const
{   
    stringstream ss;
    string symbol;
    if(suit == 'S'){
    ss << SPADE;
    ss >> symbol;
    }
    else if(suit == 'H'){
    ss << HEART;
    ss >> symbol;
    }
    else if(suit == 'C'){
    ss << CLUB;
    ss >> symbol;
    }
    else if(suit == 'D'){
    ss << DIAMOND;
    ss >> symbol;
    }

    if(point <= 10){
    cout << symbol << setw(2) << right << point << symbol;
    }
    else if(point == 11){
    cout << symbol << setw(2) << right  << "J" << symbol;
    }
    else if(point == 12){
    cout << symbol << setw(2) << right << "Q" << symbol;
   }
    else if(point == 13){
    cout << symbol << setw(2) << right << "K" << symbol;
    }
    else if(point == 14){
    cout << symbol << setw(2) << right << "A" << symbol;
    }
}

