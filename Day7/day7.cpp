#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <stack>
#include <sstream>
#include <numeric>
#include <cstdint>

template<typename T>
auto formatInput(T input){
    std::map<std::string, int64_t> sizes;
    std::stack<std::string> dirLoc;
    std::string dir = "";
    for(auto& in : input){
        std::vector<std::string> data;
        std::string word;
        std::stringstream ss(in);
        while(std::getline(ss, word, ' ')){
            data.push_back(word);
        }
        if(data[0] == "$"){
            if(data[1] == "ls"){}
            else if(data[1] == "cd" && data[2] == ".."){
                dirLoc.pop();
                dir = dir.substr(0, dir.length() - 1);
            }else{
                dirLoc.push(data[2]);
                dir += data[2];
            }
        }else if(data[0] == "dir"){
        }else{
            std::stack<std::string> temp = dirLoc;
            while(!temp.empty()){
                std::string s = "";
                std::stack<std::string> st = temp;
                while(!st.empty()){ s += st.top(); st.pop(); }
                sizes[s] += std::stoll(data[0]);
                temp.pop();
            }
        }
        
    }
    return sizes;
}

auto getInput(const std::string f = "..\\..\\Day7\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::string> out;
    while (std::getline(file, linetxt)){
        out.push_back(linetxt);
    }
    return formatInput(out);
}

template<typename T>
auto run1(T input){
    int sum = 0;
    for(auto& i : input){
        if(i.second <= 100000){ sum += i.second; }
    }
    return sum;
}

template<typename T>
auto run2(T input){
    int totalSize = input["/"];
    int requiredDeletion = 30000000 - (70000000 - totalSize);
    int closest = INT_MAX;
    for(auto& in : input){
        if(in.second >= requiredDeletion && in.second < closest){
            closest = in.second;
        }
    }
    return closest;
}

int main(){
    auto input = getInput();
    /* for(auto& i : input){
        std::cout<<i.first<<' '<<i.second<<'\n';
    } */
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}

//Part 1: 1989474
//Part 2: 1111607

//TotalMilliseconds : 48.8985