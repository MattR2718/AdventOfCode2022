#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <numeric>

auto getInput(const std::string f = "..\\..\\Day1\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::vector<int>> out;
    std::vector<int> temp;
    while (std::getline(file, linetxt)){
        if(linetxt.length() > 0){
            temp.push_back(std::stoi(linetxt));
        }else{
            out.push_back(temp);
            temp.clear();
        }
    }
    if(temp.size() > 0){
        out.push_back(temp);
    }
    return out;
}

template<typename T>
int run1(T input){
    std::vector<int>sums;
    for(auto& e : input){
        sums.push_back(std::accumulate(e.begin(), e.end(), 0));
    }
    return *std::max_element(sums.begin(), sums.end());
}

template<typename T>
std::string run2(T input){
    std::vector<int>sums;
    for(auto& e : input){
        sums.push_back(std::accumulate(e.begin(), e.end(), 0));
    }
    std::sort(sums.begin(), sums.end(), std::greater());
    return std::to_string(sums[0] + sums[1] + sums[2]);
}

int main(){
    auto input = getInput();
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}

//Part 1: 67658
//Part 2: 200158