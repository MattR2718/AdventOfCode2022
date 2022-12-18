#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>

auto getInput(const std::string f = "..\\..\\Day2\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::string> out;
    while (std::getline(file, linetxt)){
        out.push_back(linetxt);
    }
    return out;
}

template<typename T>
int run1(T input){
    int two = 0;
    int three = 0;
    for (auto& t : input){
        std::map<char, int> let;
        for (auto l : t){
            //std::cout<<l;
            let[l]++;
        }
        bool thr=false, tw=false;
        for (auto& l : let){
            if ((l.second == 3) && (!thr)){
                three++;
                thr = true;
            }else if ((l.second == 2) && (!tw)){
                two++;
                tw = true;
            }
        }
    }
    //std::cout<<two<<"  "<<three<<'\n';
    return two * three;
}

template<typename T>
std::string run2(T input){
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
    /*
    for(auto& i : input){
        std::cout<<i<<'\n';
    }
    */
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}