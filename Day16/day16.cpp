#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>

struct Valve{
    std::string name;
    int flowRate;
    std::vector<std::string> links;
    Valve(std::string n_, int fr_, std::vector<std::string> l_){
        name = n_;
        flowRate = fr_;
        links = l_;
    }
    void print(){
        std::cout<<"NAME: "<<name<<" FLOW RATE: "<<flowRate<<" LINKS: ";
        for(auto& l : links){ std::cout<<l<<' '; }
        std::cout<<'\n';
    }
};

auto getInput(const std::string f = "..\\..\\Day16\\test.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<Valve> out;
    while (std::getline(file, linetxt)){
        std::stringstream ss(linetxt);
        std::string token;
        std::vector<std::string> line;
        while(std::getline(ss, token, ' ')){
            line.push_back(token);
        }
        std::vector<std::string> links;
        for(int i = 9; i < line.size(); i++){
            links.emplace_back(line[i].substr(0, 2));
        }
        out.emplace_back(Valve(line[1], std::stoi(line[4].substr(5, line[4].size() - 5)), links));

    }
    return out;
}

template <typename T>
auto createAdj(const T& valves){
    std::map<std::string, std::vector<std::string>> adj;
    for(auto& v : valves){
        adj[v.name] = v.links;
    }

    return adj;
}

template <typename T>
void printAdj(const T& adj){
    for(auto& a : adj){
        std::cout<<a.first<<": ";
        for(auto& n : a.second){
            std::cout<<n<<' ';
        }
        std::cout<<'\n';
    }
}

template<typename T>
auto run1(T input){
    
    auto adj = createAdj(input);
    printAdj(adj);

    /*
        DEPTH FIRST SEARCH WITH A PAIR WHICH CONTAINS THE CURRENT DEPTH?
        WHEN DEPTH REACHES 30 ADD ALL ROUTES WITH 30 TO VECTOR AND POP OFF TO 29?
    */

    return -1;
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
        i.print();
    }
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    //std::cout<<"Part 2: "<<run2(input)<<'\n';
}