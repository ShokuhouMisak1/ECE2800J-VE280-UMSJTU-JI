#include<iostream>
#include"deck.h"
#include"card.h"
#include"hand.h"
#include"player.h"

class Player_Simple : public Player{
    int bankroll;
    public:
    Player_Simple();
    int bet(unsigned int bankroll,unsigned int minimum);
    bool draw(Card dealer,const Hand &player);
    void expose(Card c);
    void shuffled();
};

class Player_Counting : public Player_Simple{
    int bankroll;
    int count;
    public:
    Player_Counting();
    int bet(unsigned int bankroll,unsigned int minimum);
    bool draw(Card dealer,const Hand &player);
    void expose(Card c);
    void shuffled();
};

Player_Simple::Player_Simple(): bankroll(0) {
}

int Player_Simple::bet(unsigned int bankroll,unsigned int minimum){
    return minimum;
}

bool Player_Simple::draw(Card dealer,const Hand &player){
    if(!player.handValue().soft){
        if(player.handValue().count<=11) return true;
        if(player.handValue().count==12){
            if(dealer.spot >= FOUR && dealer.spot <= SIX) return false;
            return true;
        }
        if(player.handValue().count>=13 && player.handValue().count<=16){
            if(dealer.spot >= TWO && dealer.spot <= SIX) return false;
            return true;
        }
        if(player.handValue().count>=17) return false;
    }
    else{
        if(player.handValue().count<=17) return true;
        if(player.handValue().count==18){
            if(dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT) return false;
            return true;
        }
        if(player.handValue().count>=19) return false;
    }
    return false;
}

void Player_Simple::expose(Card c){
}

void Player_Simple::shuffled(){
}

Player_Counting::Player_Counting(): bankroll(0),count(0) {
}

int Player_Counting::bet(unsigned int bankroll,unsigned int minimum){
    if(count>=2 && bankroll>=2*minimum) return 2*minimum;
    else return minimum;
}

bool Player_Counting::draw(Card dealer,const Hand &player){
    if(!player.handValue().soft){
        if(player.handValue().count<=11) return true;
        if(player.handValue().count==12){
            if(dealer.spot >= FOUR && dealer.spot <= SIX) return false;
            return true;
        }
        if(player.handValue().count>=13 && player.handValue().count<=16){
            if(dealer.spot >= TWO && dealer.spot <= SIX) return false;
            return true;
        }
        if(player.handValue().count>=17) return false;
    }
    else{
        if(player.handValue().count<=17) return true;
        if(player.handValue().count==18){
            if(dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT) return false;
            return true;
        }
        if(player.handValue().count>=19) return false;
    }
    return false;
}

void Player_Counting::expose(Card c){
    if(c.spot>=TWO && c.spot<=SIX) count++;
    if(c.spot>=TEN && c.spot<=ACE) count--;
}

void Player_Counting::shuffled(){
    count = 0;
}

static Player_Simple ps;

static Player_Counting pc;

Player *get_Simple(){
    return &ps;
}

Player *get_Counting(){
    return &pc;
}
