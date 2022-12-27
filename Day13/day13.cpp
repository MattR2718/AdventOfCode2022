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
    //std::ifstream file(f);
    std::string linetxt;
    std::vector<json> out;
    while (std::getline(std::cin, linetxt)){
        if(linetxt.size() != 0){
            out.push_back(json::parse(linetxt));
        }
    }
    return out;
}

bool operator<(const json& left, const json& right){
    if(left.is_number_integer() && right.is_number_integer()){
        return left.get<int>() < right.get<int>();
    }else if(left.is_array() && right.is_array()){
        return std::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
    }else if(left.is_array()){
        return left < json::array({right.get<int>()});
    }else if(right.is_array()){
        return json::array({left.get<int>()}) < right;
    }else{
        std::cout<<"ERROR LEFT AND RIGHT NOT KNOWN: "<<left<<' '<<right<<'\n';
        return 0;
    }
}

template<typename T>
auto run1(T input){
    std::cout<<"\n\n\n";
    int yes = 0;
    for(int i = 0; i < input.size(); i += 2){
        //json left = json::parse(input[i]);
        //json right = json::parse(input[i + 1]);
        if(input[i] < input[i + 1]){
            std::cout<<i<<": "<<input[i]<<' '<<input[i + 1]<<'\n';
            yes+=i/2 + 1; 
        }
    }
    

    return yes;    
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

//5501 too high