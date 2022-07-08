/* File: rank.cpp
 * Course: CS216-002
 * Project: Project 2
 * Purpose: the implementation of member functions for the Rank class.
 *
 */
#include <iostream>
#include <sstream>
#include <iomanip>
#include "rank.h"

using namespace std;

// Default constructor.
Rank::Rank()
{
    kind = hRanks::NoRank;
    point = 0;
}

// Alternate constructor.
// Create a Rank object with specified ranking name and points.
Rank::Rank(hRanks r, rPoints p)
{
    kind = r;
    point = p;
}

// access the hand ranking kind
Rank::hRanks Rank::getKind() const
{
    return kind;
}

// access the card point value of the corresponding ranking kind
Rank::rPoints Rank::getPoint() const
{
    return point;
}

// Display a description of the hand-ranking category to standard output.
// The output should look like:
//   FourOfAKind( 4)
//   FullHouse(10)
//   Flush( A)
//   ...
void Rank::print() const
{
    string test;
    int position = static_cast<int>(kind);
    stringstream ss;
    
    ss <<  RANK_NAMES[position];
    ss >> test;
    if(point <= 10){
    cout << test <<  "("<< point << ")" <<  endl;    
    }
    else if(point == 11){
    cout << test <<  "( J)" <<  endl;
    }
    else if(point == 12){
    cout << test <<  "( Q)" <<  endl;

    }
    else if(point == 13){
    cout << test <<  "( K)" <<  endl;

    }
    else if (point == 14){
    cout << test <<  "( A)" <<  endl;

    }
}

