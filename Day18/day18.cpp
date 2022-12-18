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
    std::ifstream file("../../../../Day18/test.txt");
    std::string linetxt;
    std::vector<std::tuple<int, int,int>> out;
    while (std::getline(file, linetxt)){
        std::stringstream ss(linetxt);
        int x, y, z;
        char c1, c2, c3;
        ss >> x>>c1>>y>>c2>>z;
        out.emplace_back(std::tuple(x, y, z));
    }
    return out;
}

template<typename T>
auto run1(T input){
    std::vector<std::tuple<int, int, int>> all;

    for(auto& i : input){
        all.emplace_back(std::tuple(std::get<0>(i) + 1, std::get<1>(i), std::get<2>(i)));
        all.emplace_back(std::tuple(std::get<0>(i) - 1, std::get<1>(i), std::get<2>(i)));
        all.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i) + 1, std::get<2>(i)));
        all.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i) - 1, std::get<2>(i)));
        all.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i), std::get<2>(i) + 1));
        all.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i), std::get<2>(i) - 1));
    }

    all.erase(std::remove_if(all.begin(), all.end(), [&](const auto& a){ return std::find(input.begin(),  input.end(), a) != input.end(); }), all.end());

    /* for(int i = 0; i < all.size(); i++){
        if(std::find(input.begin(), input.end(), all[i]) != input.end()){
            all.erase(all.begin() + i--);
        }
    } */


    return all.size();
}

void getVals(std::vector<std::tuple<int, int, int>>& all, const std::vector<std::tuple<int, int, int>>& input, std::tuple<int, int, int> curr, const std::tuple<int, int, int>& max){
    if(std::get<0>(curr) < -1 || std::get<0>(curr) > std::get<0>(max)
        || std::get<1>(curr) < -1 || std::get<1>(curr) > std::get<1>(max)
        || std::get<2>(curr) < -1 || std::get<2>(curr) > std::get<2>(max)
        || std::find(input.begin(), input.end(), curr) != input.end()
        /* || std::find(all.begin(), all.end(), curr) != all.end() */ ){ /* std::cout<<"RETURNING\n"; */ return; }

    //std::cout<<"CURR: "<<std::get<0>(curr) << ' '<< std::get<1>(curr) << ' '<< std::get<2>(curr)<<'\n';

    std::vector<std::tuple<int, int, int>> ps;
    ps.emplace_back(std::tuple(std::get<0>(curr) + 1, std::get<1>(curr), std::get<2>(curr)));
    ps.emplace_back(std::tuple(std::get<0>(curr) - 1, std::get<1>(curr), std::get<2>(curr)));
    ps.emplace_back(std::tuple(std::get<0>(curr), std::get<1>(curr) + 1, std::get<2>(curr)));
    ps.emplace_back(std::tuple(std::get<0>(curr), std::get<1>(curr) - 1, std::get<2>(curr)));
    ps.emplace_back(std::tuple(std::get<0>(curr), std::get<1>(curr), std::get<2>(curr) + 1));
    ps.emplace_back(std::tuple(std::get<0>(curr), std::get<1>(curr), std::get<2>(curr) - 1));
    
    ps.erase(std::remove_if(ps.begin(), ps.end(), [&](const auto& a){ return std::find(all.begin(),  all.end(), a) != all.end(); }), ps.end());
    ps.erase(std::remove_if(ps.begin(), ps.end(), [&](const auto& a){ return std::find(input.begin(),  input.end(), a) != input.end(); }), ps.end());
    
    //std::cout<<"PS SIZE: "<<ps.size()<<'\n';
    
    all.insert(all.end(), ps.begin(), ps.end());
    for(auto& i : ps){
        //std::cout<<"I: "<<std::get<0>(i) << ' '<< std::get<1>(i) << ' '<< std::get<2>(i)<<'\n';
        //all.push_back(i);
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

    std::cout<<'\n';
    std::cout<<"MAXX: "<<maxx<<'\n';
    std::cout<<"MAXY: "<<maxy<<'\n';
    std::cout<<"MAXZ: "<<maxz<<'\n';

    /* maxx += 1;
    maxy += 1;
    maxz += 1; */

    /*
    All values positive and 0, 0, 0 not a value
    */

    std::vector<std::tuple<int, int, int>> all;
    std::tuple<int, int, int> O{0, 0, 0};
    std::tuple<int, int, int> max{maxx, maxy, maxz};

    getVals(all, input, std::tuple(0, 0, 0), std::tuple{maxx+1,maxy+1,maxz+1});
    std::cout<<all.size()<<'\n';

    std::vector<std::tuple<int, int, int>> borders;

    for(auto& i : input){
        borders.emplace_back(std::tuple(std::get<0>(i) + 1, std::get<1>(i), std::get<2>(i)));
        borders.emplace_back(std::tuple(std::get<0>(i) - 1, std::get<1>(i), std::get<2>(i)));
        borders.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i) + 1, std::get<2>(i)));
        borders.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i) - 1, std::get<2>(i)));
        borders.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i), std::get<2>(i) + 1));
        borders.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i), std::get<2>(i) - 1));
    }

    all.erase(std::remove_if(all.begin(), all.end(), [&](const auto& a){ return std::find(borders.begin(),  borders.end(), a) == borders.end(); }), all.end());
    //auto a = std::unique(all.begin(), all.end());
    int count = 0;
    for(auto& i : all){
         std::vector<std::tuple<int, int, int>> sa;
        sa.emplace_back(std::tuple(std::get<0>(i) + 1, std::get<1>(i), std::get<2>(i)));
        sa.emplace_back(std::tuple(std::get<0>(i) - 1, std::get<1>(i), std::get<2>(i)));
        sa.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i) + 1, std::get<2>(i)));
        sa.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i) - 1, std::get<2>(i)));
        sa.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i), std::get<2>(i) + 1));
        sa.emplace_back(std::tuple(std::get<0>(i), std::get<1>(i), std::get<2>(i) - 1)); 
        count += std::count_if(sa.begin(), sa.end(), [&](auto& a){ return std::find(input.begin(), input.end(), a) != input.end(); });
        /* for(auto& s : sa){
            if(std::find(input.begin(), input.end(), s) != input.end()){ count++; }
        } */
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

//2094 low