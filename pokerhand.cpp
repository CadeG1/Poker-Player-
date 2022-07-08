/* File: pokerhand.cpp
* Course: CS216-002
* Project: Project 2
* Purpose: the definition for the PokerHand class.
*/

#include <iomanip>
#include "pokerhand.h"
#include <sstream>

        // Default constructor.
        // We allow a blank PokerHand to be created.
        // However, the default constructor should make sure
        // that hand_rank is (Rank::NoRank, 0).
        PokerHand::PokerHand(){
            hand_rank = Rank(Rank::hRanks::NoRank, 0);
        }

        // It should store the HANDS cards
        // given as parameters in the cards[] array.
        // if size is not HANDS, display "Invalid number of cards!"
        // It should also immediately evaluate the hand, determine
        // its rank: ranking kind and the card value
        void PokerHand::setPokerHand(Card in_hand[], int size){
            if(size != HANDS){
            cout << "Invalid number of cards!" << endl;
            }
            else{
                for(int i = 0; i < HANDS; i++){
                    cards[i] = in_hand[i];
                }
            
            //Sort the hand of cards
            sort();
            
            //Define the set of cards with a rank
            isStraightFlush();
            isFourOfAKind();
            isFullHouse();
            isStraight();
            isThreeOfAKind();
            isPair();
            isHighCard();
            }
        }
        // Compare this hand versus otherHand according
        // to the rules of poker. 
        // Returns a negative number (< 0) 
        // if this hand loses to the otherHand.
        // Returns a positive number (> 0) 
        // if this hand beats the otherHand.
        // Returns zero if it's a tie.
        //
        // An invalid hand loses to any hand. If both hands
        // are invalid, the result is undefined (could be
        // negative, zero or positive).
        //
        int PokerHand::compareHand(const PokerHand &otherHand) const{
            int hand1 = static_cast<int>(hand_rank.getKind());
            int hand2 = static_cast<int>(otherHand.getRank().getKind());
            int point1 = hand_rank.getPoint();
            int point2 = otherHand.getRank().getPoint();
            //Check to see which pokerhand is greater
            if(hand1 > hand2){
                return 1;
            }
            else if(hand2 > hand1){
                return -1;
            }
            else{
                //Same pokerhand rank, check for high card
                if(point1 > point2){
                 return 1;
                }
                else if(point2 > point1){
                 return -1;
                }
                else{
                 return 0;
                }
            }
        }


        // Prints out the five cards and its rank to standard output.
        // It should look like:
        // Five cards:
        // one card per line
        // then followed by "Its rank is: rank"
        void PokerHand::print() const{
            cout << "Five cards in order: " << endl;
            for(int i = 0;i < HANDS; i++){
                cards[i].print();
                cout << "   ";
            }
            cout << "\nIt's rank is: ";
            hand_rank.print();
        }
        
        // Return the rank of this hand
        Rank PokerHand::getRank() const{
            return hand_rank;
        }


        // The following "isXXXX()" functions shoudl all:
        // 1. Assume that the hand is already sorted;
        // 2. If true, store the rank in hand_rank;
        // 3. use the rank if hand_rank is available.
        
        // Returns true if the hand is a StraightFlush
        //              and set the hand_rank (StraightFlush, highest point of the sequential five cards)
        // otherwise returns false
        bool PokerHand::isStraightFlush(){
            if(isAllOneSuit() && isSequence()){
                hand_rank = Rank(Rank::hRanks::StraightFlush, cards[0].getPoint());
                return true;
            }
                return false;
        }


        // Returns true if the hand is a Four of a Kind
        //              and set the hand_rank (FourOfAKind, highest point of the same four cards)
        // otherwise returns false
        bool PokerHand::isFourOfAKind(){
           int point;
           //See if there was a straight flush 
           if(isStraightFlush()){
                return false;
           }

           int numCount = 0;
           //Sees if there are 3 straight equal cards, meaning a four of a kind
           for(int i = 0; i < HANDS-1; i++){
            if(cards[i].getPoint() == cards[i+1].getPoint()){
                numCount++;
                point = cards[i].getPoint();
            }
            else{
                if(numCount > 0 && numCount < 3){
                    return false;
                }
            }
           }

           //Check to see if there was a four of a kind
           if(numCount == 3){
               hand_rank = Rank(Rank::hRanks::FourOfAKind, point);
               return true;
           }
           return false;
        }

        // Returns true if the hand is a Full House
        //              and set the hand_rank (FullHouse, highest point of the same three cards)
        // otherwise returns false
        bool PokerHand::isFullHouse(){
        //Checks for higher ranks        
        if(isStraightFlush() || isFourOfAKind()){
            return false;
        }
        
        //See's if the first 2 are a pair and the last three are 3 of a kind,
        //or that the first 3 are three of a kind and the last two are a pair
            if((((cards[0].getPoint() == cards[1].getPoint()) == true) && ((cards[1].getPoint() == cards[2].getPoint()) ==true))  && ((cards[3].getPoint() == cards[4].getPoint()) == true)){
                hand_rank = Rank(Rank::hRanks::FullHouse, cards[1].getPoint());
                return true;
            }
            else if(((cards[0].getPoint() == cards[1].getPoint()) == true) && (((cards[2].getPoint() == cards[3].getPoint()) ==true) && ((cards[3].getPoint() == cards[4].getPoint()) == true))){
                hand_rank = Rank(Rank::hRanks::FullHouse, cards[2].getPoint());
                return true;
            }

            return false;
        }


        // Returns true if the hand is a Flush
        //              and set the hand_rank (Flush, highest point of the five cards)
        // otherwise returns false
        bool PokerHand::isFlush(){

            //Check for higher ranks
            if(isStraightFlush() || isFourOfAKind() || isFullHouse()){
                return false;
            }
            
            //Check if its all the same suit
            if(isAllOneSuit()){
                hand_rank = Rank(Rank::hRanks::Flush, cards[0].getPoint());
                return true;
            }
            return false;
        }

        // Returns true if the hand is a Straight
        //              and set the hand_rank (Straight, highest point of the sequential five cards)
        // otherwise returns false
        bool PokerHand::isStraight(){

            //Check for higher ranks
            if(isStraightFlush() || isFourOfAKind() || isFullHouse() || isFlush()){
                return false;
            }
            
            //Check if in sequence
            if(isSequence()){
                hand_rank = Rank(Rank::hRanks::Straight, cards[0].getPoint());
                return true;
            }
            return false;
        }

        // Returns true if the hand is a Three of a Kind
        //              and set the hand_rank (ThreeOfAKind, highest point of the same three cards)
        // otherwise returns false
        bool PokerHand::isThreeOfAKind(){

            //Check for higher ranks
            if(isStraightFlush() || isFourOfAKind() || isFullHouse() || isFlush() || isStraight()){
                return false;
            }
            int point;
            int three = 0;

            //See if there are two straight pairings, meaning a three of a kind
            for(int i = 0; i < HANDS-1; i++){
                if(cards[i].getPoint() == cards[i+1].getPoint()){
                    point = cards[i].getPoint();
                    three++;
                }
                else{
                    if(three != 2){
                        return false;
                    }
                }
            }
            
            //If two pairings, return true
            if(three == 2){
                hand_rank = Rank(Rank::hRanks::ThreeOfAKind, point);
                return true;
            }
            return false;

        }

        bool PokerHand::isPair(){

        //Check for higher ranks
    if(isStraightFlush() || isFourOfAKind() || isFullHouse() || isFlush() || isStraight() || isThreeOfAKind()){
        return false;
    }
            
            //Find highest pair, and on that pair return true
            for(int i = 0; i < HANDS - 1; i++){
                if(cards[i].getPoint() == cards[i+1].getPoint()){
                    hand_rank = Rank(Rank::hRanks::Pair, cards[i].getPoint());
                    return true;
                }

            }
            return false;
        }

        bool PokerHand::isHighCard(){
            
        //Check for higher ranks
    if(isStraightFlush() || isFourOfAKind() || isFullHouse() || isFlush() || isStraight() || isThreeOfAKind() || isPair()){
        return false;
    }
    else{
    hand_rank = Rank(Rank::hRanks::HighCard, cards[0].getPoint());
    return true;
    }
        }

        //Private 


        // helper functions (private)
        // they are helpful for the public member functions of this class
        // however they cannot be called outside of the class
        
        // to help sort the HANDS=5 cards in decreasing order by card points
        void PokerHand::sort(){
            Card swap;
            for(int i =0; i < HANDS; i++){
                for(int j = i; j < HANDS; j++){
                    if(cards[i].compareTo(cards[j]) == -1){
                        swap = cards[i];
                        cards[i] = cards[j];
                        cards[j] = swap;
                    }
                }
            }
        }

        // to help decide if HANDS=5 cards are all of one suit
        // return true if they are
        // otherwise return false
        bool PokerHand::isAllOneSuit() const{
        char checkS = cards[0].getSuit();

        for(int i = 0; i < HANDS; i++){                 
                if(cards[i].getSuit() != checkS){    
                    return false;  
                }
            }
                return true;
        }
        // to help decide if HANDS=5 cards are in a continuous sequence
        // return true if they are 
        // otherwise return false
        bool PokerHand::isSequence() const{

            for(int i = 1; i < HANDS; i++){
                if(cards[i-1].getPoint() != cards[i].getPoint() + 1){
                    return false;
                }
            }   
                return true;
        }
