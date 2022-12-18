#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <variant>
#include <numeric>

#include "rocks.h"

using svar = std::variant<Flat_1, Cross_2, L_3, Tall_4, Square_5>;

auto getInput(const std::string f = "..\\..\\Day17\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::string out;
    while (std::getline(file, linetxt)){
        out += linetxt;
    }
    return out;
}

template <typename T>
void printRocks(const T& rocks, const int maxy){
    std::vector<std::pair<int, int>> allPoints;
    for(auto& r : rocks){ 
        std::vector<std::pair<int, int>> ps = std::visit([](auto arg){ return arg.getPs(); }, r);
        allPoints.insert(allPoints.end(), ps.begin(), ps.end());
    }
    std::vector<char> chamber;
    for(int j = maxy; j > -1; j--){
        for(int i = 0; i < 7; i++){
            if(std::find(allPoints.begin(), allPoints.end(), std::pair(i, j)) == allPoints.end()){ chamber.push_back('.'); }else{chamber.push_back('#'); }
        }
    }
    std::cout<<"\n.......\n.......\n.......";
    for(int i = 0; i < chamber.size(); i++){
        if(abs(i) % 7 == 0){ std::cout<<'\n'; }
        //if(i < 0){std::cout<<'.'; }else{ std::cout<<chamber[i]; }
        std::cout<<chamber[i];
    }
    std::cout<<'\n';
}

int getMaxY(const std::vector<svar>& rocks){
    int m = -1;
    for(auto& v : rocks){
        int maxy = std::visit([](auto arg){ return arg.getMy(); }, v);
        m = (maxy > m) ? maxy : m;
    }
    return m;
}

template<typename T>
auto run1(T input){
    std::vector<svar> rocks;
    int rockToAdd = -1;
    int inputPos = 0;
    int prev = 0;
    std::vector<int> diff;
    for(int rocklim = 0; rocklim < 2022; rocklim++){
        rockToAdd = (rockToAdd + 1) % 5;
        int maxy = getMaxY(rocks);
        switch(rockToAdd){
            case 0 : rocks.emplace_back(Flat_1(maxy + 4)); break;
            case 1 : rocks.emplace_back(Cross_2(maxy + 4)); break;
            case 2 : rocks.emplace_back(L_3(maxy + 4)); break;
            case 3 : rocks.emplace_back(Tall_4(maxy + 4)); break;
            case 4 : rocks.emplace_back(Square_5(maxy + 4)); break;
            default: std::cout<<"ERROR ROCKTOADD GREATER THAN 4\n"; break;
        }
        std::vector<std::pair<int, int>> allPoints;
        for(int rockNum = 0; rockNum < rocks.size() - 1; rockNum++){ 
            std::vector<std::pair<int, int>> ps = std::visit([](auto arg){ return arg.getPs(); }, rocks[rockNum]);
            allPoints.insert(allPoints.end(), ps.begin(), ps.end());
        }
        while(!std::visit([](auto arg){ return arg.getStuck(); }, rocks[rocks.size() - 1])){
            std::visit([&](auto& arg){ arg.shift(input[inputPos++], allPoints); }, rocks[rocks.size() - 1]);
            inputPos %= input.length();
            std::visit([&](auto& arg){ arg.drop(allPoints); }, rocks[rocks.size() - 1]);
        }
        if(rocks.size() == 1){
            std::visit([&](auto& arg){ arg.shift(input[inputPos++], allPoints); }, rocks[rocks.size() - 1]);
            inputPos %= input.length();
        }

    }

    return getMaxY(rocks) + 1;
}


template<typename T>
auto run2(T input){
    std::vector<svar> rocks;
    int rockToAdd = -1;
    int inputPos = 0;
    int prev = 0;
    std::vector<int> diff;
    for(int rocklim = 0; rocklim < 15000; rocklim++){
        rockToAdd = (rockToAdd + 1) % 5;
        int maxy = getMaxY(rocks);
        switch(rockToAdd){
            case 0 : rocks.emplace_back(Flat_1(maxy + 4)); break;
            case 1 : rocks.emplace_back(Cross_2(maxy + 4)); break;
            case 2 : rocks.emplace_back(L_3(maxy + 4)); break;
            case 3 : rocks.emplace_back(Tall_4(maxy + 4)); break;
            case 4 : rocks.emplace_back(Square_5(maxy + 4)); break;
            default: std::cout<<"ERROR ROCKTOADD GREATER THAN 4\n"; break;
        }
        std::vector<std::pair<int, int>> allPoints;
        for(int rockNum = 0; rockNum < rocks.size() - 1; rockNum++){ 
            std::vector<std::pair<int, int>> ps = std::visit([](auto arg){ return arg.getPs(); }, rocks[rockNum]);
            allPoints.insert(allPoints.end(), ps.begin(), ps.end());
        }
        while(!std::visit([](auto arg){ return arg.getStuck(); }, rocks[rocks.size() - 1])){
            std::visit([&](auto& arg){ arg.shift(input[inputPos++], allPoints); }, rocks[rocks.size() - 1]);
            inputPos %= input.length();
            std::visit([&](auto& arg){ arg.drop(allPoints); }, rocks[rocks.size() - 1]);
        }
        if(rocks.size() == 1){
            std::visit([&](auto& arg){ arg.shift(input[inputPos++], allPoints); }, rocks[rocks.size() - 1]);
            inputPos %= input.length();
        }
        if((rocklim + 1) % 1 == 0){
            diff.push_back(getMaxY(rocks) + 1 - prev);
            prev = getMaxY(rocks) + 1;
        }
    }

    //std::cout<<"SEARCHING FOR REPEATED\n";
    //std::cout<<"DIFF SIZE: "<<diff.size()<<'\n';
    std::vector<int8_t> first, second;
    int length = 20;
    do{
        for(int j = 0; j < diff.size() - 2 * length; j++){
            first.clear();
            second.clear();
            //std::cout<<' '<<j<<'\n';
            for(int i = 0; i < length; i++){
                
                first.push_back(diff[i + j]); 
                second.push_back(diff[i + j + length]); 
            }
            if(first == second){ break; }
        }
        length++;
    }while(first != second);
    length--;
    //std::cout<<"LENGTH: "<<length<<'\n';

    uint64_t start = std::search(diff.begin(), diff.end(), first.begin(), first.end()) - diff.begin();
    //std::cout<<"START POS: "<<start<<'\n';

    uint64_t beginSum = std::accumulate(diff.begin(), diff.begin() + start, 0);
    //std::cout<<"BEGIN SUM: "<<beginSum<<'\n';

    uint64_t len = 1000000000000 - (start - 1);
    uint64_t repeatedNum = len / length;
    //std::cout<<"REPEATED NUM: "<<repeatedNum<<'\n';

    uint64_t repeatedsum = std::accumulate(first.begin(), first.end(), 0);
    //std::cout<<"REPEATED SUM: "<<repeatedsum<<'\n';

    uint64_t totatRepeatedSum = repeatedsum * repeatedNum;
    //std::cout<<"TOTAL REPEATED SUM: "<<totatRepeatedSum<<'\n';

    uint64_t end = len % length;
    //std::cout<<"END LENGTH: "<<end<<'\n';

    uint64_t endSum = std::accumulate(first.begin(), first.begin() + end, 0);
    //std::cout<<"END SUM: "<<endSum<<'\n';
    uint64_t totalSum = beginSum + totatRepeatedSum + endSum;
    //std::cout<<"TOTAL: "<<totalSum<<'\n';

    return totalSum - 1;
}

int main(){
    auto input = getInput();
    
    //std::cout<<input<<'\n';
    
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}


//Part 1: 3085
//Part 2: 1535483870924

/*
RELEASE:

    Days              : 0
    Hours             : 0
    Minutes           : 4
    Seconds           : 30
    Milliseconds      : 435
    Ticks             : 2704351193
    TotalDays         : 0.00313003610300926
    TotalHours        : 0.0751208664722222
    TotalMinutes      : 4.50725198833333
    TotalSeconds      : 270.4351193
    TotalMilliseconds : 270435.1193

*/