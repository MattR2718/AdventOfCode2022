#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>

auto getInput(const std::string f = "..\\..\\Day2\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::pair<char, char>> out;
    while (std::getline(file, linetxt)){
        std::stringstream s(linetxt);
        char o, m;
        s >> o >> m;
        out.push_back(std::make_pair(o, m));
    }
    return out;
}

template <typename T>
int getScoreP1(T in){
    int score = (in.second - 'X') + 1;
    std::vector<std::pair<char, char>> win = {{'A', 'Y'}, {'B', 'Z'}, {'C', 'X'}};
    std::vector<std::pair<char, char>> lose = {{'A', 'Z'}, {'B', 'X'}, {'C', 'Y'}};
    if(std::find(win.begin(), win.end(), in) != win.end()){ return (6 + score); }
    if(std::find(lose.begin(), lose.end(), in) != lose.end()){ return (score); }
    else{ return (3 + score); }
}

template<typename T>
int run1(T input){
    int sum = 0;
    for(auto& in : input){
        sum += getScoreP1(in);
    }
    return sum;
}

template <typename T>
int getScoreP2(T input){
    int score = 3 * (input.second - 'X');
    if(input.second == 'X'){ //Lose
        //a -> 'z' = 3, b-> 'x' = 1, c->'y' = 2
        switch(input.first){
            case 'A': return score + 3;
            case 'B': return score + 1;
            case 'C': return score + 2;
        }
    }else if(input.second == 'Y'){ //Draw
        switch(input.first){
            case 'A': return score + 1;
            case 'B': return score + 2;
            case 'C': return score + 3;
        }
    }else{
        switch(input.first){
            case 'A': return score + 2;
            case 'B': return score + 3;
            case 'C': return score + 1;
        }
    }
    return -1;
}

template<typename T>
int run2(T input){
    int sum = 0;
    for(auto& in : input){
        sum += getScoreP2(in);
    }
    return sum;
}

int main(){
    auto input = getInput();
    /* for(auto& i : input){
        std::cout<<i.first<<' '<<i.second<<'\n';
    } */
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}

//Part 1: 14297
//Part 2: 10498