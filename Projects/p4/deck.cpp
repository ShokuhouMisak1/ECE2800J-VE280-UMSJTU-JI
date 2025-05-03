#include<iostream>
#include"deck.h"
#include"card.h"

Deck::Deck(){
    reset();
}

void Deck::reset(){
    for(int i=0; i<DeckSize; i++){
        deck[i].spot = (Spot)(i%13);
        deck[i].suit = (Suit)(i/13);
    }
    next = 0;
}

void Deck::shuffle(int n){
    Card leftdeck[DeckSize];
    Card rightdeck[DeckSize];
    for(int i=0;i<n;i++)    leftdeck[i] = deck[i];
    for (int i = 0; i < DeckSize - n; i++) rightdeck[i] = deck[n + i];
    if(n<=26){
        for(int i=0;i<n;i++){
            deck[2*i] = rightdeck[i];
            deck[2*i+1] = leftdeck[i];
        }
        for(int i =n;i<DeckSize-n;i++)   deck[i+n] = rightdeck[i];
    }
    if(n>26){
        for(int i=0;i<DeckSize-n;i++){
            deck[2*i] = rightdeck[i];
            deck[2*i+1] = leftdeck[i];
        }
        for(int i = DeckSize-n;i<n;i++)   deck[i+DeckSize-n] = leftdeck[i];
    }
    next = 0;
}

Card Deck::deal(){
    if(next == 52){
        DeckEmpty empty;
        throw empty;
    }
    else{
        return deck[next++];
    }
}

int Deck::cardsLeft(){
    return (52-next);
}