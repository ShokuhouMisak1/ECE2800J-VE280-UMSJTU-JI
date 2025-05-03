#include<iostream>
#include<string>
#include<cstdlib>
#include"card.h"
#include"deck.h"
#include"hand.h"
#include"player.h"
#include"rand.h"

void shuffle(Deck& deck,Player *player);
void player_round(Deck& deck,Player *player,Hand &player_hand);

int main(int argc, char* argv[]){
    Deck deck;
    deck.reset();
    const int MINIMUM = 5;
    int bankroll = atoi(argv[1]);
    int hand = atoi(argv[2]);
    Player* player;
    if(std::string(argv[3]) == "simple"){
        player = get_Simple();
    }
    else {
        player = get_Counting();
    }
    shuffle(deck,player);
    int thishand = 1;
    for(;thishand<=hand;thishand++){
        Hand player_hand;
        Hand dealer_hand;
        if(bankroll<MINIMUM){
            break;
        }
        std::cout<<"Hand "<< thishand <<" bankroll "<<bankroll<<std::endl;
        if(deck.cardsLeft()<20) shuffle(deck,player);
        int wager = player->bet(bankroll,MINIMUM);
        std::cout<<"Player bets "<<wager<<std::endl;
        player_round(deck,player,player_hand);
        Card deal_card = deck.deal();
        std::cout<<"Dealer dealt "<<SpotNames[deal_card.spot]<<" of "<<SuitNames[deal_card.suit]<<std::endl;
        player->expose(deal_card);
        dealer_hand.addCard(deal_card);
        player_round(deck,player,player_hand);
        Card hole_card = deck.deal();
        dealer_hand.addCard(hole_card);
        if(player_hand.handValue().count == 21 && player_hand.handValue().soft){
            std::cout<<"Player dealt natural 21\n";
            bankroll += (wager*3)/2;
            continue;
        }
        while(player->draw(deal_card,player_hand) && player_hand.handValue().count<=21){
            Card temp_card = deck.deal();
            player_hand.addCard(temp_card);
            player->expose(temp_card);
            std::cout<<"Player dealt "<<SpotNames[temp_card.spot]<<" of "<<SuitNames[temp_card.suit]<<std::endl;
        }
        std::cout<<"Player's total is "<<player_hand.handValue().count<<std::endl;
        if(player_hand.handValue().count > 21){
            std::cout<<"Player busts\n";
            bankroll -= wager;
            continue;
        }
        std::cout<<"Dealer's hole card is "<<SpotNames[hole_card.spot]<<" of "<<SuitNames[hole_card.suit]<<std::endl;
        player->expose(hole_card);
        while(dealer_hand.handValue().count<17){
            Card temp_card = deck.deal();
            dealer_hand.addCard(temp_card);
            player->expose(temp_card);
            std::cout<<"Dealer dealt "<<SpotNames[temp_card.spot]<<" of "<<SuitNames[temp_card.suit]<<std::endl;
        }
        std::cout<<"Dealer's total is "<<dealer_hand.handValue().count<<std::endl;
        if(dealer_hand.handValue().count > 21){
            std::cout<<"Dealer busts\n";
            bankroll += wager;
            continue;
        }
        if(player_hand.handValue().count>dealer_hand.handValue().count){
            std::cout<<"Player wins\n";
            bankroll += wager;
        }
        if(player_hand.handValue().count<dealer_hand.handValue().count){
            std::cout<<"Dealer wins\n";
            bankroll -= wager;
        }
        if(player_hand.handValue().count==dealer_hand.handValue().count){
            std::cout<<"Push\n";
        }
    }
    std::cout<<"Player has "<<bankroll<<" after "<<thishand-1<<" hands\n";
    return 0;
}

void shuffle(Deck& deck,Player *player){
    std::cout<<"Shuffling the deck\n";
    for(int i=1;i<=7;i++){
        int cut = get_cut();
        std::cout<<"cut at "<<cut<<std::endl;
        deck.shuffle(cut);
    }
    player->shuffled();
}

void player_round(Deck& deck,Player *player,Hand &player_hand){
    Card temp_card = deck.deal();
    std::cout<<"Player dealt "<<SpotNames[temp_card.spot]<<" of "<<SuitNames[temp_card.suit]<<std::endl;
    player->expose(temp_card);
    player_hand.addCard(temp_card);
}

