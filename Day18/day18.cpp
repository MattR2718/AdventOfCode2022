//Get-Content ../../Day18/input.txt | .\day18.exe
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <tuple>
#include <sstream>

auto getInput(){
    std::string linetxt;
    std::vector<std::tuple<int, int,int>> out;
    while (std::getline(std::cin, linetxt)){
        std::stringstream ss(linetxt);
        int x, y, z;
        char c1, c2, c3;
        ss >> x>>c1>>y>>c2>>z;
        out.emplace_back(std::tuple(x, y, z));
    }
    return out;
}

auto getSurround(const std::tuple<int, int, int>& a, std::vector<std::tuple<int, int, int>>& b){
    //std::vector<std::tuple<int, int, int>> all;
    b.emplace_back(std::tuple(std::get<0>(a) + 1, std::get<1>(a), std::get<2>(a)));
    b.emplace_back(std::tuple(std::get<0>(a) - 1, std::get<1>(a), std::get<2>(a)));
    b.emplace_back(std::tuple(std::get<0>(a), std::get<1>(a) + 1, std::get<2>(a)));
    b.emplace_back(std::tuple(std::get<0>(a), std::get<1>(a) - 1, std::get<2>(a)));
    b.emplace_back(std::tuple(std::get<0>(a), std::get<1>(a), std::get<2>(a) + 1));
    b.emplace_back(std::tuple(std::get<0>(a), std::get<1>(a), std::get<2>(a) - 1));
}

template<typename T>
auto run1(T input){
    std::vector<std::tuple<int, int, int>> all;

    for(auto& i : input){
        getSurround(i, all);
    }

    all.erase(std::remove_if(all.begin(), all.end(), [&](const auto& a){ return std::find(input.begin(),  input.end(), a) != input.end(); }), all.end());

    return all.size();
}

void getVals(std::vector<std::tuple<int, int, int>>& all, const std::vector<std::tuple<int, int, int>>& input, std::tuple<int, int, int> curr, const std::tuple<int, int, int>& max){
    if(std::get<0>(curr) < -1 || std::get<0>(curr) > std::get<0>(max)
        || std::get<1>(curr) < -1 || std::get<1>(curr) > std::get<1>(max)
        || std::get<2>(curr) < -1 || std::get<2>(curr) > std::get<2>(max)
        || std::find(input.begin(), input.end(), curr) != input.end()){ return; }

    std::vector<std::tuple<int, int, int>> ps;
    getSurround(curr, ps);
    
    ps.erase(std::remove_if(ps.begin(), ps.end(), [&](const auto& a){ return std::find(all.begin(),  all.end(), a) != all.end(); }), ps.end());
    ps.erase(std::remove_if(ps.begin(), ps.end(), [&](const auto& a){ return std::find(input.begin(),  input.end(), a) != input.end(); }), ps.end());
        
    all.insert(all.end(), ps.begin(), ps.end());
    for(auto& i : ps){
        getVals(all, input, i, max);
    }
}

template<typename T>
auto run2(T input){
    int maxx = 0;
    int maxy = 0;
    int maxz = 0;
    for(auto& i : input){
        maxx = (std::get<0>(i) > maxx) ? std::get<0>(i) : maxx;
        maxy = (std::get<1>(i) > maxy) ? std::get<1>(i) : maxy;
        maxz = (std::get<2>(i) > maxz) ? std::get<2>(i) : maxz;
    }

    std::vector<std::tuple<int, int, int>> all;
    std::tuple<int, int, int> O{0, 0, 0};
    std::tuple<int, int, int> max{maxx, maxy, maxz};

    getVals(all, input, std::tuple(0, 0, 0), std::tuple{maxx+1,maxy+1,maxz+1});

    std::vector<std::tuple<int, int, int>> borders;

    for(auto& i : input){
        getSurround(i, borders);
    }

    all.erase(std::remove_if(all.begin(), all.end(), [&](const auto& a){ return std::find(borders.begin(),  borders.end(), a) == borders.end(); }), all.end());
    int count = 0;
    for(auto& i : all){
         std::vector<std::tuple<int, int, int>> sa;
        getSurround(i, sa);
        count += std::count_if(sa.begin(), sa.end(), [&](auto& a){ return std::find(input.begin(), input.end(), a) != input.end(); });
    }

    return count;
}

int main(){
    auto input = getInput();
    
    /* for(auto& i : input){
        std::cout<<std::get<0>(i)<<' '<<std::get<1>(i)<<' '<<std::get<2>(i)<<'\n';
    } */
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}

//Part 1: 3636
//Part 2: 2102

/*
RELEASE: 

    Days              : 0
    Hours             : 0
    Minutes           : 0
    Seconds           : 0
    Milliseconds      : 534
    Ticks             : 5340036
    TotalHours        : 0.000148334333333333
    TotalMinutes      : 0.00890006
    TotalSeconds      : 0.5340036
    TotalMilliseconds : 534.0036

*/