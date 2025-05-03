#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;

string triangle_number(int num);
string power_number(int num);
string sum_of_consecutive_squares(int num);
string abundant_number(int num);string abundant_number(int num);

int main(){
    int num=0,test=0;
    while(1){
        cout << "Please enter the integer and the test choice: ";
        cin >> num >> test;
        if(num>0 && num<=10000000 && test>0 && test<5){
            break;
        }
    }
    switch (test)
    {
    case 1 :
        cout << triangle_number(num)<< endl;
        break;
    case 2 :
        cout << power_number(num) << endl;
        break;
    case 3 :
        cout << sum_of_consecutive_squares(num) << endl;
        break;
    case 4 :
        cout << abundant_number(num) << endl;
        break;
    }
    return 0;
}

string triangle_number(int num){
    num *=2;
    for(int i=0; i<sqrt(num); i++){
        if(num == i*(i+1)){
            return "Pass";
        }
    }
    return "Fail";
}
// judge whether it is a triangle number.

string power_number(int num){
    if(num == 1){
        return "Pass";
    }
    else{
        for(int m=2;m<=sqrt(num);m++){
            int n = int(round(log(num)/log(m)));
            if(num == pow(m,n)&& n>=2){
                return "Pass";
            }
        }
        return "Fail";
    }
}
// judge whether it is a power number.

string sum_of_consecutive_squares(int num){
    int n = int(sqrt(num));
    for(int m = n;m>=0;m--){
        int num_2 = num;
        for(int t=m;t>=0;t--){
            num_2 = num_2 - pow(t,2);
            if(num_2 == 0){
                return "Pass";
            }
            if(num_2 < 0){
                break;
            }
        }
    }
    return "Fail";
}
//judge whether it is a sum of consecutive squares
//Calculation: first calculate the square root of the integer part of the next from this number has been reduced by 1 square, 
//found that does not work, from this number minus one to start and then try in turn

string abundant_number(int num){
    int sum=0;
    for(int i=1;i<=sqrt(num);i++){
        if(num%i ==0){
            if(i != sqrt(num) && i!=1){
            sum += i;
            sum += num/i;
            }
            else{
                sum += i;
            }
        }
    }
    if(sum > num){
        return "Pass";
    }
    else{
        return "Fail";
    }
}
//judge whether it is a abundant number