#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <regex>
#include <unordered_set>
#include <set>
#include <tuple>

#define X_BUFFER 175

template <typename T>
auto makeCave(const T& lines){
    int minx = 2147483647;
    int maxx = -2147483647;
    int miny = 2147483647;
    int maxy = -2147483647;
    for(auto& pp : lines){
        if(pp.first.first < minx){ minx = pp.first.first; }
        if(pp.first.first > maxx){ maxx = pp.first.first; }
        if(pp.first.second < miny){ miny = pp.first.second; }
        if(pp.first.second > maxy){ maxy = pp.first.second; }

        if(pp.second.first < minx){ minx = pp.second.first; }
        if(pp.second.first > maxx){ maxx = pp.second.first; }
        if(pp.second.second < miny){ miny = pp.second.second; }
        if(pp.second.second > maxy){ maxy = pp.second.second; }
    }

    minx -= X_BUFFER;
    maxx += X_BUFFER;

    /* std::cout<<"MINX: "<<minx<<'\n';
    std::cout<<"MAXX: "<<maxx<<'\n';
    std::cout<<"MINY: "<<miny<<'\n';
    std::cout<<"MAXY: "<<maxy<<'\n'; */

    std::set<std::pair<int, int>> points;
    for(auto& pp : lines){
        if(pp.first.first == pp.second.first){
            if(pp.first.second < pp.second.second){
                for(int j = pp.first.second; j <= pp.second.second; j++){
                    points.emplace(std::pair(pp.first.first, j));
                }
            }else{
                for(int j = pp.second.second; j <= pp.first.second; j++){
                    points.emplace(std::pair(pp.first.first, j));
                }
            }
        }else if(pp.first.second == pp.second.second){
            if(pp.first.first < pp.second.first){
                for(int i = pp.first.first; i <= pp.second.first; i++){
                    points.emplace(std::pair(i, pp.first.second));
                }
            }else{
                for(int i = pp.second.first; i <= pp.first.first; i++){
                    points.emplace(std::pair(i, pp.second.second));
                }
            }
        }else{ std::cout<<"ERROR WITH POINTS\n";}
    }

    std::vector<char> buckets;
    for(int j = 0; j < maxy + 1; j++){
        for(int i = minx; i < maxx + 2; i++){
            if(i == 500 && j == 0){buckets.push_back('+');
            }else if(points.find(std::pair(i, j)) != points.end()){
                buckets.push_back('#');
            }else{ buckets.push_back('.'); }
        }
    }
    for(int i = minx; i < maxx + 2; i++){
        buckets.push_back('.');
    }
    for(int i = minx; i < maxx + 2; i++){
        buckets.push_back('#');
    }

    return std::tuple(buckets, maxx - minx + 2, 500 - minx);
}

auto getInput(const std::string f = "..\\..\\Day14\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::pair<std::pair<int,int>, std::pair<int, int>>> out;
    std::regex ex("\\d+");
    std::smatch m;
    while (std::getline(file, linetxt)){
        std::vector<int> nums;
        std::string str = linetxt;
        while (std::regex_search(str, m, ex)) {
            for (auto match : m) {
                nums.push_back(std::stoi(match));
            }
            str = m.suffix().str();
        }
        for(int i = 0; i <= nums.size() - 4; i += 2){
            out.emplace_back(std::pair(std::pair(nums[i], nums[i+1]), std::pair(nums[i+2], nums[i+3])));
        }

    }
    return makeCave(out);
}

template <typename T>
void printCave(const T& input){
    auto[cave, width, start]{input};
    for(int i = 0; i < cave.size(); i++){
        if (i % width == 0){std::cout<<'\n'; }
        std::cout<<cave[i];
    }
    std::cout<<'\n';
}

template<typename T>
auto run1(T input){
    auto[cave, width, startx]{input};
    std::pair<int, int> sandpos = {startx, 0};
    int maxy = cave.size() / width - 3;
    int count = 0;

    while(sandpos.second < maxy){
        if(cave[(sandpos.second + 1) * width + sandpos.first] == '.'){ sandpos.second++; }
        else if(cave[(sandpos.second + 1) * width + (sandpos.first - 1)] == '.'){ sandpos.first--; sandpos.second++; }
        else if(cave[(sandpos.second + 1) * width + (sandpos.first + 1)] == '.'){ sandpos.first++; sandpos.second++; }
        else { cave[sandpos.second * width + sandpos.first] = 'O'; sandpos = {startx, 0}; count++; }
    }
    
    //printCave(std::tuple(cave, width, startx));

    return count;
}

template<typename T>
auto run2(T input){
    auto[cave, width, startx]{input};
    std::pair<int, int> sandpos = {startx, 0};
    int maxy = cave.size() / width - 3;
    int count = 0;

    do{
        if(cave[(sandpos.second + 1) * width + sandpos.first] == '.' && sandpos.second + 1 < maxy + 2){ sandpos.second++; }
        else if(cave[(sandpos.second + 1) * width + (sandpos.first - 1)] == '.' && sandpos.second + 1 < maxy + 2){ sandpos.first--; sandpos.second++; }
        else if(cave[(sandpos.second + 1) * width + (sandpos.first + 1)] == '.' && sandpos.second + 1 < maxy + 2){ sandpos.first++; sandpos.second++; }
        else { cave[sandpos.second * width + sandpos.first] = 'O'; sandpos = {startx, 0}; count++; }
    }while(cave[startx] != 'O');
    
    //printCave(std::tuple(cave, width, startx));

    return count;
}

int main(){
    auto input = getInput();
    //printCave(input);
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    //std::cout<<"\n\n\n";
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}

//Part 1: 644
//Part 2: 27324

//TIME DRAWING TO FILE out.txt
//TotalMilliseconds : 393.2681

//DEBUG WITHOUT DRAWING
//TotalMilliseconds : 350.8512

//RELEASE WITHOUT DRAWING
//TotalMilliseconds : 55.7608