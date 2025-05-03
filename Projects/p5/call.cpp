#include<iostream>
#include<string>
#include"dlist.h"

enum STATUS{regular,silver,gold,platinum};

struct Guest{
    int timestamp;
    std::string name;
    STATUS status;
    int duration;
};

STATUS string_to_status(std::string status);

STATUS status_of_first(Dlist<Guest> &stack);

void answer_call(Dlist<Guest>& call_queue, int& isbusy);

int main() {
    const std::string status_Name[] = {"regular","silver","gold","platinum"};
    std::string line;
    std::getline(std::cin,line);
    int guest_num = stoi(line);
    if(guest_num == 0){
        std::cout<<"Starting tick #0"<<std::endl;
        return 0;
    }
    Dlist<Guest> stack;
    Dlist<Guest> call_queue_regular;
    Dlist<Guest> call_queue_silver;
    Dlist<Guest> call_queue_gold;
    Dlist<Guest> call_queue_platinum;
    int isbusy = 0;
    int timestamp = 0;
    std::string name;
    std::string status;
    int duration;
    while (std::cin>>timestamp>>name>>status>>duration){
        Guest* guest=new Guest({timestamp,name,string_to_status(status),duration});
        stack.insertBack(guest);
    }
    int tick=0;
    while(1){
        std::cout<<"Starting tick #"<<tick<<std::endl;
        while(1){
            if(!stack.isEmpty()){
                Guest* temp = stack.removeFront();
                if(temp->timestamp != tick){
                    stack.insertFront(temp);
                    break;
                }
                std::cout<<"Call from "<<temp->name<<" a "<<status_Name[temp->status]<<" member"<<std::endl;
                if(temp->status == regular) call_queue_regular.insertBack(temp);
                else if(temp->status == silver) call_queue_silver.insertBack(temp);
                else if(temp->status == gold) call_queue_gold.insertBack(temp);
                else if(temp->status == platinum) call_queue_platinum.insertBack(temp);
            }
            if(stack.isEmpty()) break;
        }
        if(isbusy == 0){
            if(!call_queue_platinum.isEmpty() ){
                answer_call(call_queue_platinum,isbusy);
            }
            else if(!call_queue_gold.isEmpty() ){
                answer_call(call_queue_gold,isbusy);
            }
            else if(!call_queue_silver.isEmpty() ){
                answer_call(call_queue_silver,isbusy);
            }
            else if(!call_queue_regular.isEmpty() ){
                answer_call(call_queue_regular,isbusy);
            }
        }
        if(isbusy!=0) isbusy-=1;
        tick++;
        if(stack.isEmpty() && call_queue_regular.isEmpty() && call_queue_silver.isEmpty() && call_queue_gold.isEmpty()&& call_queue_platinum.isEmpty() && isbusy==0){
            std::cout<<"Starting tick #"<<tick<<std::endl;
            break;
        }
    }
    return 0;
}

STATUS string_to_status(std::string status){
    if(status[0] == 'r') return regular;
    else if(status[0] == 's') return silver;
    else if(status[0] == 'g') return gold;
    else return platinum;
}

STATUS status_of_first(Dlist<Guest> &stack){
    if(stack.isEmpty()) return regular;
    else{
        Guest* temp = stack.removeFront();
        STATUS first_status = temp->status;
        stack.insertFront(temp);
        return first_status;
    }
}

void answer_call(Dlist<Guest>& call_queue, int& isbusy){
    Guest* temp = call_queue.removeFront();
    std::cout<<"Answering call from "<<temp->name<<std::endl;
    isbusy += temp->duration;
    delete temp;
}