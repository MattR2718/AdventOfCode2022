#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>

auto getInput(const std::string f = "..\\..\\Day8\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<int> out;
    int width = 0;
    while (std::getline(file, linetxt)){
        width = linetxt.length();
        for(auto& i : linetxt){ out.push_back(i - '0'); }
    }
    return std::make_pair(out, width);
}

auto viewable(const std::vector<int>& trees, const int width, const int x, const int y){
    //top
    bool top = true;
    for(int i = 0; i < y; i++){
        if(trees[y * width + x] <= trees[i * width + x]){ top = false; }
    }
    //bottom
    bool bottom = true;
    for(int i = trees.size() / width - 1; i > y; i--){
        if(trees[y * width + x] <= trees[i * width + x]){ bottom = false; }
    }
    //Left
    bool left = true;
    for(int i = 0; i < x; i++){
        if(trees[y * width + x] <= trees[y * width + i]){ left = false; }
    }
    //right
    bool right = true;
    for(int i = width - 1; i > x; i--){
        if(trees[y * width + x] <= trees[y * width + i]){ right = false; }
    }
    return top || bottom || left || right;
}

template<typename T>
auto run1(T input){
    auto[trees, width]{input};
    int sum = 0;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < trees.size()/width; j++){
            if(viewable(trees, width, i, j)){ sum++; }
        }
    }
    return sum;
}

auto scenicScore(const std::vector<int>& trees, const int width, const int x, const int y){
    //top
    int top = 0;
    for(int i = y - 1; i > -1; i--){
        top++;
        if(trees[y * width + x] <= trees[i * width + x]){ break; }
    }
    //bottom
    int bottom = 0;
    for(int i = y + 1; i < trees.size()/width; i++){
        bottom++;
        if(trees[y * width + x] <= trees[i * width + x]){ break; }
    }
    //Left
    int left = 0;
    for(int i = x - 1; i > -1; i--){
        left++;
        if(trees[y * width + x] <= trees[y * width + i]){ break; }
    }
    //right
    int right = 0;
    for(int i = x + 1; i < width; i++){
        right++;
        if(trees[y * width + x] <= trees[y * width + i]){ break; }
    }

    return top * bottom * left * right;
}

template<typename T>
auto run2(T input){
    auto[trees, width]{input};
    std::vector<int> scores;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < trees.size()/width; j++){
            scores.emplace_back(scenicScore(trees, width, i, j));
        }
    }
    return *std::max_element(scores.begin(), scores.end());
}

int main(){
    auto[input, width]{getInput()};
   
    std::cout<<"Part 1: "<<run1(std::make_pair(input, width))<<'\n';
    std::cout<<"Part 2: "<<run2(std::make_pair(input, width))<<'\n';
}

//Part 1: 1794
//Part 2: 199272

//Debug
//TotalMilliseconds : 74.971

//Release
//TotalMilliseconds : 20.3426