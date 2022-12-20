#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <iomanip>

auto getInput(){
    std::string linetxt;
    std::vector<int64_t> out;
    while (std::getline(std::cin, linetxt)){
        out.push_back(std::stoll(linetxt));
    }
    return out;
}

template <typename T>
auto run(T input, int loopnum, int64_t multnum){
    //<order, num>
    std::vector<std::pair<int64_t, int64_t>> nums;
    for(int i = 0; i < input.size(); i++){ input[i] *= multnum; nums.emplace_back(std::pair(i, input[i])); }

    auto find = [&](const std::pair<int64_t, int64_t> & a){
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] == a){ return i; }
        }
        return -1;
    };

    for(int loop = 0; loop < loopnum; loop++){
        for(int64_t i = 0; i < input.size(); i++){
            int64_t index = find(std::pair(i, input[i]));
            int64_t next = index;
            if(nums[index].second < 0){
                for(int64_t j = -(-nums[index].second % (nums.size() - 1)); j < 0; j++){
                    if(next - 1 == 0){ next = nums.size() - 1; }
                    else if(next - 1 == -1){ next = nums.size() - 2; }
                    else{ next = next - 1; }
                }
            }else{
                for(int64_t j = (nums[index].second % (nums.size() - 1)); j > 0; j--){
                    if(next + 1 == nums.size()){ next = 1; }
                    else if(next + 1 == nums.size() - 1){ next = 0; }
                    else { next = next + 1;}
                }
            }
            std::pair<int64_t, int64_t> p = nums[index];
            nums.erase(nums.begin() + index);
            nums.insert(nums.begin() + next, p);
        }
    }

    int zeroInd = -1;
    for(int i = 0; i < nums.size(); i++){
        if(nums[i].second == 0){ zeroInd = i; break;}
    }

    int64_t sum = nums[(1000 + zeroInd) % nums.size()].second + nums[(2000 + zeroInd) % nums.size()].second + nums[(3000 + zeroInd) % nums.size()].second;

    return sum;
}

int main(){
    auto input = getInput();
    
    /* for(auto& i : input){
        std::cout<<i<<'\n';
    } */

    std::cout<<"Part 1: "<<run(input, 1, 1)<<'\n';
    std::cout<<"Part 2: "<<run(input, 10, 811589153)<<'\n';
}


//Part 1: 4267
//Part 2: 6871725358451

/*
RELEASE: 
    Days              : 0
    Hours             : 0
    Minutes           : 0
    Seconds           : 0
    Milliseconds      : 867
    Ticks             : 8678438
    TotalDays         : 1.00444884259259E-05
    TotalHours        : 0.000241067722222222
    TotalMinutes      : 0.0144640633333333
    TotalSeconds      : 0.8678438
    TotalMilliseconds : 867.8438
*/