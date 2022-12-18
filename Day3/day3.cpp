#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <cctype>

auto getInput(const std::string f = "..\\..\\Day3\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::string> out;
    while (std::getline(file, linetxt)){
        out.push_back(linetxt);
    }
    return out;
}

template<typename T>
int run1(T input){

    auto getChar = [](std::string& fh, std::string& sh){
        for(char c : fh){
            for(char d : sh){
                if(c == d){ return c; }
            }
        }
        return 'a';
    };

    auto getScore = [](char c){
        if(isupper(c)){ return (c - 64) + 26; }else{ return (c - 96); }
    };

    int sum = 0;
    for(std::string& s : input){
        std::string fh = s.substr(0, s.length()/2);
        std::string sh = s.substr(s.length()/2, s.length()/2);
        int score = getScore(getChar(fh, sh));
        sum += score;
    }
    return sum;
}

template<typename T>
int run2(T input){
    
    auto getChar = [](std::string s1, std::string s2, std::string s3){
        for(auto& c1 : s1){
            for(auto& c2 : s2){
                for(auto& c3 : s3){
                    if(c1 == c2 && c2 == c3){ return c1; }
                }
            }
        }

        return 'a';
    };

    auto getScore = [](char c){
        if(isupper(c)){ return (c - 64) + 26; }else{ return (c - 96); }
    };

    int sum = 0;
    for(int i = 0; i < input.size(); i += 3){
        sum += getScore(getChar(input[i], input[i+1], input[i+2]));
    }

    return sum;
}

int main(){
    auto input = getInput();
    
    /* for(auto& i : input){
        std::cout<<i<<'\n';
    } */
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}

//Part 1: 7997
//Part 2: 2545

//Debug
//With calculations: TotalMilliseconds : 120.6522
//Only Getting Input: TotalMilliseconds : 35.1661
//Total Calculation Time: 85.4861ms

//Release
//With calculations: TotalMilliseconds : 23.4766
//Only Getting Input: TotalMilliseconds : 14.2581
//Total Calculation Time: 9.2185ms