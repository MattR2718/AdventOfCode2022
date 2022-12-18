#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <set>

auto getInput(const std::string f = "..\\..\\Day9\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::pair<char, int>> out;
    while (std::getline(file, linetxt)){
        char c;
        int i;
        std::stringstream ss(linetxt);
        ss >> c >> i;
        out.emplace_back(std::make_pair(c, i));
    }
    return out;
}

template<typename T, typename U>
void moveT(const T&h, T& t, U& tpath, bool add){
    if(abs(h.first - t.first) < 2 && abs(h.second - t.second) < 2){
        return;
    }else{
        /* if(h.first == t.first){
            t.second += (h.second > t.second) ? 1 : -1;
        }else if(h.second == t.second){
            t.first += (h.first > t.first) ? 1 : -1;
        }else{
            t.first += (h.first > t.first) ? 1 : -1;
            t.second += (h.second > t.second) ? 1 : -1;
        } */
        t.first += (h.first == t.first) ? 0 : (h.first > t.first) ? 1 : -1;
        t.second += (h.second == t.second) ? 0 : (h.second > t.second) ? 1 : -1;
    }
    if(add){ tpath.insert(t); }
}

template<typename T, typename U>
void move(T& knots, const std::pair<char, int>& instr, U& tpath, int x, int y, bool p2 = false){
    for(int i = 0; i < instr.second; i++){
        knots[0].first += x;
        knots[0].second += y;
        for(int i = 0; i < knots.size() - 1; i++){
            if(p2 && i == 8 || !p2){ moveT(knots[i], knots[i + 1], tpath, true); }
            else{ moveT(knots[i], knots[i + 1], tpath, false); }
        }
    }
}

/* template<typename T>
auto run1(T input){
    std::set<std::pair<int, int>> tpath;
    tpath.insert({0, 0});
    //std::pair<int, int> h, t;
    std::vector<std::pair<int, int>> knots(2, {0, 0});
    for(auto& i : input){
        switch(i.first){
            case 'R':{
                move(knots, i, tpath, 1, 0);
                break;
            }
            case 'U':{
                move(knots, i, tpath, 0, 1);
                break;
            }
            case 'L':{
                move(knots, i, tpath, -1, 0);
                break;
            }
            case 'D':{
                move(knots, i, tpath, 0, -1);
                break;
            }
            default:{ std::cout<<"INVALID INSTRIUCTION "<<i.first<<' '<<i.second<<'\n'; }
        }
    }

    return tpath.size();
}

template<typename T>
auto run2(T input){
    std::set<std::pair<int, int>> tpath;
    tpath.insert({0, 0});
    std::vector<std::pair<int, int>> knots(10, {0, 0});

    for(auto& i : input){
        switch(i.first){
            case 'R':{
                move(knots, i, tpath, 1, 0, true);
                break;
            }
            case 'U':{
                move(knots, i, tpath, 0, 1, true);
                break;
            }
            case 'L':{
                move(knots, i, tpath, -1, 0, true);
                break;
            }
            case 'D':{
                move(knots, i, tpath, 0, -1, true);
                break;
            }
            default:{ std::cout<<"INVALID INSTRIUCTION "<<i.first<<' '<<i.second<<'\n'; }
        }
    }

    return tpath.size();
} */

template<typename T>
auto run(T input, int n){
    std::set<std::pair<int, int>> tpath;
    tpath.insert({0, 0});
    std::vector<std::pair<int, int>> knots(n, {0, 0});

    for(auto& i : input){
        switch(i.first){
            case 'R':{
                move(knots, i, tpath, 1, 0, (n == 2) ? false : true);
                break;
            }
            case 'U':{
                move(knots, i, tpath, 0, 1, (n == 2) ? false : true);
                break;
            }
            case 'L':{
                move(knots, i, tpath, -1, 0, (n == 2) ? false : true);
                break;
            }
            case 'D':{
                move(knots, i, tpath, 0, -1, (n == 2) ? false : true);
                break;
            }
            default:{ std::cout<<"INVALID INSTRIUCTION "<<i.first<<' '<<i.second<<'\n'; }
        }
    }

    return tpath.size();
}


int main(){
    auto input = getInput();
    
    /* for(auto& i : input){
        std::cout<<i.first<<' '<<i.second<<'\n';
    } */
   
    std::cout<<"Part 1: "<<run(input, 2)<<'\n';
    std::cout<<"Part 2: "<<run(input, 10)<<'\n';
}


//Part 1: 6018
//Part 2: 2619

//TotalMilliseconds : 62.7441

//Big Input Release
//TotalSeconds      : 53.1779112