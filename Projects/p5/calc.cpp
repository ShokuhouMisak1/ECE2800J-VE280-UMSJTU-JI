#include<iostream>
#include<string>
#include"dlist.h"

bool isInteger(const std::string str);
bool isSingleList(Dlist<int> &list);

int main(){
    Dlist<int> stack;
    std::string input;
    while(1){
        std::cin>>input;
        if(isInteger(input)){
            int* temp = new int(stoi(input));
            stack.insertFront(temp);
        }
        else{
            if(input == "+"){
                if(stack.isEmpty() || isSingleList(stack)){
                    std::cout<<"Not enough operands\n";
                }
                else{
                    int* num1 = stack.removeFront();
                    int* num2 = stack.removeFront();
                    int *result = new int((*num1)+(*num2));
                    stack.insertFront(result);
                    delete num1;
                    delete num2;
                }
            }
            else if(input == "-"){
                if(stack.isEmpty() || isSingleList(stack)){
                    std::cout<<"Not enough operands\n";
                }
                else{
                    int* num1 = stack.removeFront();
                    int* num2 = stack.removeFront();
                    int *result = new int((*num2)-(*num1));
                    stack.insertFront(result);
                    delete num1;
                    delete num2;
                }
            }
            else if(input == "*"){
                if(stack.isEmpty() || isSingleList(stack)){
                    std::cout<<"Not enough operands\n";
                }
                else{
                    int* num1 = stack.removeFront();
                    int* num2 = stack.removeFront();
                    int *result = new int((*num2)*(*num1));
                    stack.insertFront(result);
                    delete num1;
                    delete num2;
                }
            }
            else if(input == "/"){
                if(stack.isEmpty() || isSingleList(stack)){
                    std::cout<<"Not enough operands\n";
                }
                else{
                    int* num1 = stack.removeFront();
                    if(*num1 == 0){
                        std::cout<<"Divide by zero\n";
                        stack.insertFront(num1);
                        continue;
                    }
                    int* num2 = stack.removeFront();
                    int *result = new int((*num2)/(*num1));
                    stack.insertFront(result);
                    delete num1;
                    delete num2;
                }
            }
            else if(input == "n"){
                if(stack.isEmpty()) std::cout<<"Not enough operands\n";
                else{
                    int* temp = stack.removeFront();
                    *temp *= -1;
                    stack.insertFront(temp);
                }
            }
            else if(input == "d"){
                if(stack.isEmpty()) std::cout<<"Not enough operands\n";
                else{
                    int* temp = stack.removeFront();
                    int* temp_cp = new int(*temp);
                    stack.insertFront(temp);
                    stack.insertFront(temp_cp);
                }
            }
            else if(input == "r"){
                if(stack.isEmpty() || isSingleList(stack)){
                    std::cout<<"Not enough operands\n";
                }
                else{
                    int* num1 = stack.removeFront();
                    int* num2 = stack.removeFront();
                    stack.insertFront(num1);
                    stack.insertFront(num2);
                }
            }
            else if(input == "p"){
                if(stack.isEmpty()) std::cout<<"Not enough operands\n";
                else{
                    int* temp = stack.removeFront();
                    std::cout<<*temp<<std::endl;
                    stack.insertFront(temp);
                }
            }
            else if(input == "c"){
                while(1){
                    int* result = stack.removeFront();
                    delete result;
                    if(stack.isEmpty()) break;
                }
            }
            else if(input == "a"){
                Dlist<int> stack_mirror(stack);
                while(1){
                    int* result = stack_mirror.removeFront();
                    std::cout<<*result<<" ";
                    delete result;
                    if(isSingleList(stack_mirror) || stack_mirror.isEmpty()) break;
                }
                if(isSingleList(stack_mirror)){
                    int* result = stack_mirror.removeFront();
                    std::cout<<*result;
                    delete result;
                }
                std::cout<<std::endl;
                stack_mirror.~Dlist();
            }
            else if(input == "q"){
                break;
            }
            else{
                std::cout<<"Bad input\n";
            }
        }
    }
    return 0;
}

bool isInteger(const std::string str){
    if(str.empty()) return false;
    if(str[0] != '-'){
        for(unsigned int i=0;i<str.length();i++){
            if(str[i] < '0' || str[i] >'9') return false;
        }
    }
    if(str[0] == '-'){
        for(unsigned int i=1;i<str.length();i++){
            if(str[i] < '0' || str[i] >'9') return false;
        }
        if(str.length() == 1) return false;
    }
    return true;
}

bool isSingleList(Dlist<int> &list){
    if(list.isEmpty()) return false;
    int* temp = list.removeFront();
    if(list.isEmpty()){
        list.insertFront(temp);
        return true;
    }
    else{
        list.insertFront(temp);
        return false;
    }
}