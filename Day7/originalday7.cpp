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

struct Node{
    std::string name;
    std::vector<std::string> dirs;
    std::vector<std::pair<int, std::string>> files;
    long long size = 0;
    void print(int n, std::map<std::string, Node>& nodes){
        for(auto& i : dirs){
            //std::cout<<"YE\n";
            for(int s = 0; s < n; s++){
                std::cout<<"|";
            }
            std::cout<<i<<'\n';
            nodes[i].print(n+1, nodes);
        }
        for(auto& f : files){
            for(int s = 0; s < n; s++){
                std::cout<<"|";
            }
            std::cout<<f.first<<' '<<f.second<<'\n';
        }
    }
    int64_t sum(std::map<std::string, Node>& nodes, std::map<std::string, int64_t>& cache){
        int64_t sum = 0;
        for(auto& d : dirs){
            if(cache.find(d) == cache.end() ){
                cache[d] = nodes[d].sum(nodes, cache);
            }
            sum += cache[d];
        }
        for(auto& f : files){
            sum += f.first;
        }
        return sum;
        
        /* int sum = 0;
        for(auto& d : dirs){ sum += nodes[d].size; }
        return size + sum; */
    }
    /* int64_t add(std::map<std::string, Node>& nodes, std::map<std::string, int64_t>& size){
        int sum = 0;
        for(auto& d : dirs){
            sum += nodes[d].add(nodes, size);
        }
        return sum;
    } */
};

template<typename T>
auto formatInput(T input){
    std::map<std::string, Node> nodes;
    std::map<std::string, int64_t> size;
    std::stack<std::string> nodeStack;
    for(auto& in : input){
        std::vector<std::string> data;
        std::string word;
        std::stringstream ss(in);
        //std::cout<<in<<":  ";
        while(std::getline(ss, word, ' ')){
            data.push_back(word);
        }
        if(data[0] == "$"){ //Command
            if(data[1] == "cd"){ //Change Directory
                if(data[2] == ".."){ //Step up directory
                    nodeStack.pop();
                }/* else if(nodes.find(data[2]) == nodes.end()){ //new node
                    //nodes[data[2]] = Node();
                    //nodes[data[2]].name = data[2];
                    //std::cout<<data[2]<<'\n';
                    nodeStack.push(data[2]);
                }else{ //
                    nodeStack.push(data[2]);
                } */
                else{nodeStack.push(data[2]);}

            }else if(data[1] == "ls"){ //list
                //Next data is listed files in current node

            }else{
                std::cout<<"ERROR UNKNOWN COMMAND: "<<in<<'\n';
                /* for(auto& d : data){ std::cout<<d<<' '; }
                std::cout<<'\n'; */
            }

        }else if(data[0] == "dir"){ //Directory
            if(!nodeStack.empty()){
                //nodes[nodeStack.top()].dirs.push_back(data[1]);
                //size[data[1]] += size[nodeStack.top()];
            }else{
                std::cout<<"ERROR NODESTACK EMPTY\n";
            }

        }else{ //File
            if(!nodeStack.empty()){
                //nodes[nodeStack.top()].files.push_back(std::make_pair(std::stoi(data[0]), data[1]));
                //size[nodeStack.top()] += std::stoll(data[0]);
                std::stack<std::string> temp = nodeStack;
                while(!temp.empty()){
                    size[temp.top()] += std::stoll(data[0]);
                    temp.pop();
                }
            }else{
                std::cout<<"ERROR NODESTACK EMPTY\n";
            }
        }
    }
    return size;
}

auto getInput(const std::string f = "..\\..\\Day7\\stolen.txt"){
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
    std::map<std::string, int64_t> cache;
    for(auto& i : input){
        int64_t s = i.second.sum(input, cache);
        //std::cout<<i.first<<": "<<s<<'\n';
        if(s <= 100000){ /* std::cout<<"ADDED: "<<s<<'\n'; */sum += s; }
        //std::cout<<sum<<'\n';
    }
    return sum;
}

template<typename T>
auto run2(T input){
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
    //std::cout<<"INPUT GOT\n";

    //Print File Tree
    /* std::cout<<"/\n";
    input["/"].print(1, input);
    std::cout<<"\n\n\n"; */
    int sum = 0;
    for(auto& s : input){
        //int64_t su = nodes[s.first].add();
        if(s.second <= 100000){ sum += s.second;} /* }else{ */
        std::cout<<s.second<<' '<<s.first<<'\n';
    }
    std::cout<<sum<<'\n';
    std::cout<<"SHOULD BE 1513699\n";
    //std::cout<<"Part 1: "<<run1(input)<<'\n';
    //std::cout<<"Part 2: "<<run2(input)<<'\n';
}


// 1503310 low
// 1685530 too low
// 1664419 too low