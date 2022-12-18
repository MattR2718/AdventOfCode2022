#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <regex>
#include <stack>
#include <algorithm>

auto getInput(const std::string f = "..\\..\\Day5\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::vector<int>> instrs;
    std::vector<std::vector<char>> stacks(20);
    bool doneStacks = false;
    bool startInstructions = false;
    while (std::getline(file, linetxt)){
        if(!doneStacks && linetxt[1] == '1'){ doneStacks = true; }
        if(!doneStacks){
            for(int i = 1; i < linetxt.length(); i += 4){
                if(linetxt[i] != ' '){stacks[(i - 1) / 4].push_back(linetxt[i]);}
            }
        }else if(startInstructions){
            //std::regex ex("([0-9a-zA-z ]*([0-9]+)[0-9a-zA-z ]*)");
            std::regex ex(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))");
            std::smatch m;
            std::string str = linetxt;
            std::vector<int> temp;
            while(std::regex_search(str, m, ex)){
                temp.push_back(std::stoi(m[1]));
                str = m.suffix().str();
            }
            instrs.push_back(temp);
        }
        if(linetxt.length() == 0){ startInstructions = true; }
    }

    for(auto& stack : stacks){
        std::reverse(stack.begin(), stack.end());
    }

    std::vector<std::stack<char>> s;
    for(auto& stack : stacks){
        if(stack.size() != 0){
            std::stack<char> st;
            for(auto& c : stack){
                st.push(c);
            }
            s.push_back(st);
        }
    }

    return std::pair{s, instrs};
}

template<typename T>
auto run1(T input){
    std::vector<std::stack<char>> stacks = input.first;
    for(auto& in : input.second){
        for(int i = 0; i < in[0]; i++){
            stacks[in[2] - 1].push(stacks[in[1] - 1].top());
            stacks[in[1] - 1].pop();
        }
    }
    for(auto i : stacks){
        std::cout<<i.top();
    }

    return "";
}

template<typename T>
auto run2(T input){
    std::vector<std::stack<char>> stacks = input.first;
    for(auto& in : input.second){
        std::stack<char> st;
        for(int i = 0; i < in[0]; i++){
            st.push(stacks[in[1] - 1].top());
            stacks[in[1] - 1].pop();
        }
        while(!st.empty()){
            stacks[in[2] - 1].push(st.top());
            st.pop();
        }
        
    }
    for(auto i : stacks){
        std::cout<<i.top();
    }

    return "";
}

int main(){
    auto input = getInput();
    
    /* for(auto i : input.first){
        while(!i.empty()){ std::cout<<i.top()<<' '; i.pop();}
        std::cout<<'\n';
    }

    for(auto& i : input.second){
        for(auto& j : i){
            std::cout<<j<<' ';
        }
        std::cout<<'\n';
    } */

    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}


//Part 1: TQRFCBSJJ
//Part 2: RMHFJNVFP

//TotalMilliseconds : 407.4967