#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>

auto getInput(const std::string f = "..\\..\\Day6\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::string out = "";
    while (std::getline(file, linetxt)){
        out += linetxt;
    }
    return out;
}

int getstart(std::string input, int n){
    auto different = [](std::string s){
        std::sort(s.begin(), s.end());
        return std::unique(s.begin(), s.end()) == s.end();
    };
    
    int i = -1;
    while(!different(input.substr(++i, n))){
    }
    return i + n;
}

int main(){
    auto input = getInput();
    //std::cout<<input<<'\n';
    std::cout<<"Part 1: "<<getstart(input, 4)<<'\n';
    std::cout<<"Part 2: "<<getstart(input, 14)<<'\n';
}

//Part 1: 1757
//Part 2: 2950

//TotalMilliseconds : 32.9214