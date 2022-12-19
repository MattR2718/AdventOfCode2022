#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <regex>

#define vscode true

struct Blueprint{
    int id, oreRobotOreCost, clayRobotOreCost, obsidianRobotOreCost, obsidianRobotClayCost, geodeRobotOreCost, geodeRobotObsidianCost;
    friend std::ostream& operator<<(std::ostream& os, const Blueprint& b);
};

std::ostream& operator<<(std::ostream& os, const Blueprint& b){
    os<<"Blueprint "<<b.id<<": Each ore robot costs "<<b.oreRobotOreCost<<" ore. Each clay robot costs "<<b.clayRobotOreCost<<" ore. Each obsidian robot costs "<<b.obsidianRobotOreCost<<" ore and "<<b.obsidianRobotClayCost<<" clay. Each geode robot costs "<<b.geodeRobotOreCost<<" ore and "<<b.geodeRobotObsidianCost<<" obsidian.";
    return os;
}

auto getInput(){
    std::ifstream f("../../../../Day19/test.txt");
    std::string linetxt;
    std::vector<Blueprint> out;
    std::regex ex("Blueprint ([0-9]+): Each ore robot costs ([0-9]+) ore. Each clay robot costs ([0-9]+) ore. Each obsidian robot costs ([0-9]+) ore and ([0-9]+) clay. Each geode robot costs ([0-9]+) ore and ([0-9]+) obsidian.");
    std::smatch m;
#if vscode
    while (std::getline(std::cin, linetxt)){
#else
    while (std::getline(f, linetxt)){
#endif
        std::cout << linetxt << '\n';
        std::regex_match(linetxt, m, ex);
        out.emplace_back(Blueprint{std::stoi(m[1]), std::stoi(m[2]),std::stoi(m[3]), std::stoi(m[4]), std::stoi(m[5]), std::stoi(m[6]), std::stoi(m[7])});
    }
    return out;
}

//<time, geoNum>
std::vector<std::pair<int8_t, int8_t>> cache;
//std::pair<int, int> cache;

struct Node{
    /*int8_t currentTime;
    int8_t oreNum;
    int8_t clayNum;
    int8_t obsidianNum;
    int8_t geodeNum;
    int8_t oreRobotNum;
    int8_t clayRobotNum;
    int8_t obsidianRobotNum;
    int8_t geodeRobotNum;*/
    //Blueprint blueprint;
    std::vector<Node> next;
    Node(int currentTime, int oreNum, int clayNum, int obsidianNum, int geodeNum, int oreRobotNum, int clayRobotNum, int obsidianRobotNum, int geodeRobotNum, const Blueprint& blueprint, int& maxG){
        /*currentTime = ct;
        oreNum = on;
        clayNum = cn;
        obsidianNum = obn;
        geodeNum = gn;
        oreRobotNum = orn;
        clayRobotNum = crn;
        obsidianRobotNum = obrn;
        geodeRobotNum = grn;*/
        //blueprint = b;
        //std::cout<<currentTime<<'\n';

        if(currentTime == 24){ /* std::cout<<"RETURNING\n"; */ return; }

        for (auto& c : cache) {
            if (c.first < currentTime && c.second > geodeNum) { return; }
        }
        if (geodeNum > 0) { cache.emplace_back(std::pair(currentTime, geodeNum)); }

        maxG = (maxG > geodeNum + geodeRobotNum) ? maxG : geodeNum + geodeRobotNum;

        /* if(cache.first < currentTime && cache.second > geodeNum){ return; }
        else if(geodeNum > 0){ cache = { currentTime, geodeNum }; } */

        //std::cout<<"ORENUM: "<<oreNum<<" CLAYNUM: "<<clayNum<<" OBSIDIANNUM: "<<obsidianNum<<" GEODENUM: "<<geodeNum<<'\n';

        //Make geode robot
        //Only make if can, since not used to make anything and want to maximise always try to make
        //if can make geode robot always make and dont try anything else to save branches
        if(oreNum >= blueprint.geodeRobotOreCost && obsidianNum >= blueprint.geodeRobotObsidianCost){
            //std::cout<<"GEODE ROBOT\n";
            next.push_back(Node(currentTime + 1, oreNum + oreRobotNum - blueprint.geodeRobotOreCost, clayNum + clayRobotNum, obsidianNum + obsidianRobotNum - blueprint.geodeRobotObsidianCost, geodeNum + geodeRobotNum, oreRobotNum, clayRobotNum, obsidianRobotNum, geodeRobotNum + 1, blueprint, maxG));
        }else{
            //Just mine
            //std::cout<<"JUST MINE\n";
            next.push_back(Node(currentTime + 1, oreNum + oreRobotNum, clayNum + clayRobotNum, obsidianNum + obsidianRobotNum, geodeNum + geodeRobotNum, oreRobotNum, clayRobotNum, obsidianRobotNum, geodeRobotNum, blueprint, maxG));
            //Make Ore Robot
            //Only make robot if have enough ore and the number of ore robots is less than the max required ore since no point making more ore each turn than can be used
            //Should significantly reduce branches
            if(oreNum >= blueprint.oreRobotOreCost && oreRobotNum < blueprint.oreRobotOreCost && oreRobotNum < blueprint.clayRobotOreCost && oreRobotNum < blueprint.obsidianRobotOreCost && oreRobotNum < blueprint.geodeRobotOreCost){
                //std::cout<<"ORE ROBOT\n";
                next.push_back(Node(currentTime + 1, oreNum + oreRobotNum - blueprint.oreRobotOreCost, clayNum + clayRobotNum, obsidianNum + obsidianRobotNum, geodeNum + geodeRobotNum, oreRobotNum + 1, clayRobotNum, obsidianRobotNum, geodeRobotNum, blueprint, maxG));
            }
            //Make Clay Robot
            //Only make if have enough clay and makes sense ^
            if(oreNum >= blueprint.clayRobotOreCost && clayRobotNum < blueprint.obsidianRobotClayCost){
                //std::cout<<"CLAY ROBOT\n";
                next.push_back(Node(currentTime + 1, oreNum + oreRobotNum - blueprint.clayRobotOreCost, clayNum + clayRobotNum, obsidianNum + obsidianRobotNum, geodeNum + geodeRobotNum, oreRobotNum, clayRobotNum + 1, obsidianRobotNum, geodeRobotNum, blueprint, maxG));
            }
            //Make obsidian Robot
            //Only make if have enough obsidian and makes sense ^
            if(oreNum >= blueprint.obsidianRobotOreCost && clayNum >= blueprint.obsidianRobotClayCost && obsidianRobotNum < blueprint.geodeRobotObsidianCost){
                //std::cout<<"OBSIDIAN ROBOT\n";
                next.push_back(Node(currentTime + 1, oreNum + oreRobotNum - blueprint.obsidianRobotOreCost, clayNum + clayRobotNum - blueprint.obsidianRobotClayCost, obsidianNum + obsidianRobotNum, geodeNum + geodeRobotNum, oreRobotNum, clayRobotNum, obsidianRobotNum + 1, geodeRobotNum, blueprint, maxG));
            }
        }
        

        //std::cout<<next.size()<<'\n';
    }

    void print(){
        std::cout<<next.size()<<'\n';
    }

};

template<typename T>
auto run1(T input){
    std::cout<<'\n';
    int sum = 0;
    for(auto& in : input){
        int maxG = 0;
        Node root(0, 0, 0, 0, 0, 1, 0, 0, 0, in, maxG);
        //root.print();
        //int maxGeode = getMax(root);
        //std::cout<<maxG<<'\n';
        sum += maxG * in.id;
    }

    return sum;
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
    
    for(auto& i : input){
        std::cout<<i<<'\n';
    }
   
    std::cout<<"Part 1: "<<run1(std::vector<Blueprint>{input[0]})<<'\n';
    //std::cout<<"Part 2: "<<run2(input)<<'\n';
}