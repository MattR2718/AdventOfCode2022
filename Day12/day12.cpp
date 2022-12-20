#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <iomanip>
#include <tuple>
#include <queue>

#define PRINT_ADJ false

template <typename T>
auto createAdjList(const T& input, const int width){
    //Node 'name' is its index into input array
    std::map<int, std::vector<int>> adj;
    for(int i = 0; i < input.size(); i++){
        int x = i % width;
        int y = i / width;
        if(x - 1 > -1 && input[y*width+(x-1)]<=input[i]+1){adj[i].push_back(y*width+(x-1));}
        if(x + 1 < width && input[y*width+(x+1)]<=input[i]+1){adj[i].push_back(y*width+(x+1));}
        if(y - 1 > -1 && input[(y - 1)*width+x]<=input[i]+1){adj[i].push_back((y - 1)*width+x);}
        if(y + 1 < input.size() / width && input[(y + 1)*width+x]<=input[i]+1){adj[i].push_back((y + 1)*width+x);}
    }
#if PRINT_ADJ
    std::cout<<"\n";
    for(auto& in : adj){
        std::cout<<in.first<<": ";
        for(auto& to : in.second){
            std::cout<<to<<' ';
        }
        std::cout<<'\n';
    }
#endif

    return adj;
}

template <typename T>
auto printInput(const T& input, const int width, const int start, const int end){
    std::cout<<"START: "<<start<<'\n';
    std::cout<<"END: "<<end<<'\n';
    for(int i = 0; i < input.size(); i++){
        if(i % width == 0){ std::cout<<'\n'; }
        std::cout<<std::setw(3)<<input[i];
    }
    std::cout<<'\n';
}

auto getInput(const std::string f = "..\\..\\Day12\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<char> out;
    int width = 0;
    int start = -1;
    int end = -1;
    std::vector<int> as;
    int i = 0;
    while (std::getline(file, linetxt)){
        width = linetxt.length();
        for(auto& c : linetxt){
            if(c == 'S'){
                start = out.size();
                out.push_back('a');
                as.push_back(i);
            }else if(c == 'E'){
                end = out.size();
                out.push_back('z');
            }
            else{
                out.push_back(c);
                if(c == 'a'){
                    as.push_back(i);
                }
            }
            i++;
        }
    }
    //printInput(out, width, start, end);
    return std::tuple{createAdjList(out, width), start, end, as};
}

template <typename T>
int bfs(const T& input){
    //Node 'name' is its index into input array
    std::map<int, std::vector<int>> adj = std::get<0>(input);
    int start = std::get<1>(input);
    int end = std::get<2>(input);

    std::queue<int> q;
    std::map<int, bool> visited;
    std::map<int, std::pair<int, int>> prev;
    for(auto& a : adj){
        prev[a.first] = std::make_pair(-1, 10000000);
    }

    q.push(start);
    visited[start] = true;
    prev[start] = std::make_pair(start, 0);

    while(!q.empty()){
        int curr = q.front();
        q.pop();
        for(auto& nei : adj[curr]){
            if(!visited[nei]){
                q.push(nei);
                int tempDist = prev[curr].second + 1;
                if(tempDist < prev[nei].second){
                    prev[nei] = std::make_pair(curr, tempDist);
                }
                visited[nei] = true;
            }
        }
    }

    int count = 0;
    int i = end;
    while(i != start){
        i = prev[i].first;
        if(i == -1){ return 2147483647; }
        count++;
    }

    return count;
}

template<typename T>
auto run1(T input){
    return bfs(input);
}

template<typename T>
auto run2(T input){
    std::map<int, std::vector<int>> adj = std::get<0>(input);
    int end = std::get<2>(input);
    std::vector<int> as = std::get<1>(input);
    std::vector<int> dists;
    for(auto& a : as){
        dists.push_back(bfs(std::make_tuple(adj, a, end)));
    }
    return *std::min_element(dists.begin(), dists.end());
}

int main(){
    auto[input, start, end, as] = getInput();
    
    std::cout<<"Part 1: "<<run1(std::make_tuple(input, start, end))<<'\n';
    std::cout<<"Part 2: "<<run2(std::make_tuple(input, as, end))<<'\n';
}

//Part 1: 504
//Part 2: 500

/*
DEBUG: 
    Days              : 0
    Hours             : 0
    Minutes           : 1
    Seconds           : 12
    Milliseconds      : 81
    Ticks             : 720813852
    TotalDays         : 0.000834275291666667
    TotalHours        : 0.020022607
    TotalMinutes      : 1.20135642
    TotalSeconds      : 72.0813852
    TotalMilliseconds : 72081.3852

RELEASE: 
    Days              : 0
    Hours             : 0
    Minutes           : 0
    Seconds           : 12
    Milliseconds      : 416
    Ticks             : 124166540
    TotalDays         : 0.000143711273148148
    TotalHours        : 0.00344907055555556
    TotalMinutes      : 0.206944233333333
    TotalSeconds      : 12.416654
    TotalMilliseconds : 12416.654
*/