#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <tuple>
#include <sstream>

auto getInput(const std::string f = "..\\..\\Day4\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::tuple<int, int, int, int>> out;
    while (std::getline(file, linetxt)){
        std::stringstream s(linetxt);
        int a, b, c, d;
        char c1, c2, c3;
        s >> a>>c1>>b>>c2>>c>>c3>>d;
        out.push_back(std::make_tuple(a, b, c, d));
    }
    return out;
}

template<typename T>
auto run1(T input){
    int num = 0;
    for(auto& i : input){
        if(std::get<0>(i) >= std::get<2>(i) && std::get<3>(i) >= std::get<1>(i)){ num++; }
        else if(std::get<2>(i) >= std::get<0>(i) && std::get<1>(i) >= std::get<3>(i)){ num++; }
    }
    return num;
}

template<typename T>
auto run2(T input){
    int num = 0;
    for(auto& i : input){
        if(std::get<0>(i) <= std::get<2>(i) && std::get<1>(i) >= std::get<2>(i)
        || std::get<0>(i) <= std::get<3>(i) && std::get<1>(i) >= std::get<3>(i)){ num++; }
        else if(std::get<2>(i) <= std::get<0>(i) && std::get<3>(i) >= std::get<0>(i)
        || std::get<2>(i) <= std::get<1>(i) && std::get<3>(i) >= std::get<1>(i)){ num++; }
    }

    return num;
}

int main(){
    auto input = getInput();
    
    /* for(auto& i : input){
        std::cout<<std::get<0>(i)<<' '<<std::get<1>(i)<<' '<<std::get<2>(i)<<' '<<std::get<3>(i)<<'\n';
    } */
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}


//Part 1: 595
//Part 2: 952

//With Calculations: TotalMilliseconds : 33.4182
//No Calculations: TotalMilliseconds : 31.5887
//Time For Calculations: 1.8295ms