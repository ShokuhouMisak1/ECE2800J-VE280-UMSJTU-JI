#include<iostream>
#include"deck.h"
#include"card.h"
#include"hand.h"

Hand::Hand(): curValue{0,false}{
}

void Hand::discardAll(){
    curValue = {0,false};
}

void Hand::addCard(Card c){
    if(c.spot >=TWO && c.spot<TEN){
        if(curValue.soft){
            curValue.count += c.spot + 2;
            if(curValue.count>21){
                curValue.count -= 10;
                curValue.soft = false;
            }
        }
        else curValue.count += c.spot + 2;
    }
    else if(c.spot>=TEN && c.spot<ACE){
        if(curValue.soft){
            if(curValue.count == 11) curValue.count += 10;
            else curValue.soft = false;
        }
        else curValue.count += 10;
    }
    else{
        if(curValue.soft) curValue.count += 1;
        else{
            if(curValue.count<=10){
                curValue.count += 11;
                curValue.soft = true;
            }
            else curValue.count += 1;
        }
    }
}

HandValue Hand::handValue() const{
    return curValue;
}