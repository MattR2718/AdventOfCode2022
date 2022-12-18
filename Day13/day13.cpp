//#define BOOST_JSON_STANDALONE
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <regex>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

auto getInput(const std::string f = "..\\..\\Day13\\test.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::string> out;
    while (std::getline(file, linetxt)){
        if(linetxt.size() != 0){
            out.push_back(linetxt);
        }
    }
    return out;
}

template <typename T>
char compare(T l, T r){
    json left = json::parse(l);
    json right = json::parse(r);

    if(left.size() < right.size()) { return 'y'; }
    //std::cout<<left.size()<<' '<<right.size()<<'\n';

    if(left.size() == 1 && right.size() == 1){
        if(left.is_array() && right.is_array()){ 
            char c = compare(left[0].get<std::string>(), right[0].get<std::string>()); 
        }else if(left.is_number() && right.is_number()){
            if(left[0].get<int>() < right[0].get<int>()){ return 'y';}
            else if(left[0].get<int>() == right[0].get<int>()){ return 'm'; }
            else{ return 'n'; }
        }
    }

    return '-';
}

template<typename T>
auto run1(T input){

    int correct = 0;
    for(int i = 0; i < input.size(); i += 2){
        char c = compare(input[i], input[i+1]);
        if(c == 'y'){ correct++; }
    }

    return correct;    
}

template<typename T>
std::string run2(T input){
    for(int i = 0; i < input.size() - 1; i++){
        for (int j = i + 1; j < input.size(); j++){
            std::vector<int> diff;
            for (int k = 0; k < input[j].length(); k++){
                if (input[i][k] != input[j][k]){
                    diff.push_back(k);
                }
            }
            if (diff.size() == 1){
                input[i].erase(diff[0], 1);
                return input[i];
            }
        }
    }
    return "ERROR";
}

int main(){
    auto input = getInput();
    
    for(auto& i : input){
        std::cout<<i<<'\n';
    }
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    //std::cout<<"Part 2: "<<run2(input)<<'\n';
}