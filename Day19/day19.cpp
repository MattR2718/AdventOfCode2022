#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <regex>

#define vscode false

struct Blueprint{
    int id, oreRobotOreCost, clayRobotOreCost, obsidianRobotOreCost, obsidianRobotClayCost, geodeRobotOreCost, geodeRobotObsidianCost;
    friend std::ostream& operator<<(std::ostream& os, const Blueprint& b);
};

std::ostream& operator<<(std::ostream& os, const Blueprint& b){
    os<<"Blueprint "<<b.id<<": Each ore robot costs "<<b.oreRobotOreCost<<" ore. Each clay robot costs "<<b.clayRobotOreCost<<" ore. Each obsidian robot costs "<<b.obsidianRobotOreCost<<" ore and "<<b.obsidianRobotClayCost<<" clay. Each geode robot costs "<<b.geodeRobotOreCost<<" ore and "<<b.geodeRobotObsidianCost<<" obsidian.";
    return os;
}

auto getInput(){
    std::ifstream f("../../../../Day19/input.txt");
    std::string linetxt;
    std::vector<Blueprint> out;
    std::regex ex("Blueprint ([0-9]+): Each ore robot costs ([0-9]+) ore. Each clay robot costs ([0-9]+) ore. Each obsidian robot costs ([0-9]+) ore and ([0-9]+) clay. Each geode robot costs ([0-9]+) ore and ([0-9]+) obsidian.");
    std::smatch m;
#if vscode
    while (std::getline(std::cin, linetxt)){
#else
    while (std::getline(f, linetxt)){
#endif
        //std::cout << linetxt << '\n';
        std::regex_match(linetxt, m, ex);
        out.emplace_back(Blueprint{std::stoi(m[1]), std::stoi(m[2]),std::stoi(m[3]), std::stoi(m[4]), std::stoi(m[5]), std::stoi(m[6]), std::stoi(m[7])});
    }
    return out;
}

//<time, geoNum>
//std::vector<std::pair<int8_t, int8_t>> cache;
std::pair<int8_t, int8_t> cache;

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
    Node(int8_t currentTime, int8_t oreNum, int8_t clayNum, int8_t obsidianNum, int8_t geodeNum, int8_t oreRobotNum, int8_t clayRobotNum, int8_t obsidianRobotNum, int8_t geodeRobotNum, const Blueprint& blueprint, int& maxG, const int8_t totalTime){
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

        /*for (auto& c : cache) {
            if (c.first < currentTime && c.second > geodeNum) { return; }
        }
        if (geodeNum > 0) { cache.emplace_back(std::pair(currentTime, geodeNum));  }*/

         if(cache.first < currentTime && cache.second > geodeNum){ return; }
        else if(geodeNum > 0){ cache = std::pair(currentTime, geodeNum); } 

        maxG = (maxG > geodeNum + geodeRobotNum) ? maxG : geodeNum + geodeRobotNum;


        //std::cout<<"ORENUM: "<<oreNum<<" CLAYNUM: "<<clayNum<<" OBSIDIANNUM: "<<obsidianNum<<" GEODENUM: "<<geodeNum<<'\n';

        //Make geode robot
        //Only make if can, since not used to make anything and want to maximise always try to make
        if (oreNum >= blueprint.geodeRobotOreCost && obsidianNum >= blueprint.geodeRobotObsidianCost) {
            //std::cout<<"GEODE ROBOT\n";
            next.push_back(Node(currentTime + 1, oreNum + oreRobotNum - blueprint.geodeRobotOreCost, clayNum + clayRobotNum, obsidianNum + obsidianRobotNum - blueprint.geodeRobotObsidianCost, geodeNum + geodeRobotNum, oreRobotNum, clayRobotNum, obsidianRobotNum, geodeRobotNum + 1, blueprint, maxG, totalTime));
        }
        else {

            //Just mine
            //std::cout<<"JUST MINE\n";
            next.push_back(Node(currentTime + 1, oreNum + oreRobotNum, clayNum + clayRobotNum, obsidianNum + obsidianRobotNum, geodeNum + geodeRobotNum, oreRobotNum, clayRobotNum, obsidianRobotNum, geodeRobotNum, blueprint, maxG, totalTime));
            //Make Ore Robot
            //Only make robot if have enough ore and the number of ore robots is less than the max required ore since no point making more ore each turn than can be used
            //Should significantly reduce branches
            int maxOreReq = 0;
            if (maxOreReq < blueprint.oreRobotOreCost) { maxOreReq = blueprint.oreRobotOreCost; }
            if (maxOreReq < blueprint.clayRobotOreCost) { maxOreReq = blueprint.clayRobotOreCost; }
            if (maxOreReq < blueprint.obsidianRobotOreCost) { maxOreReq = blueprint.obsidianRobotOreCost; }
            if (maxOreReq < blueprint.geodeRobotOreCost) { maxOreReq = blueprint.geodeRobotOreCost; }
            //if(oreNum >= blueprint.oreRobotOreCost && oreRobotNum < blueprint.oreRobotOreCost && oreRobotNum < blueprint.clayRobotOreCost && oreRobotNum < blueprint.obsidianRobotOreCost && oreRobotNum < blueprint.geodeRobotOreCost && oreRobotNum * (totalTime - currentTime) + oreNum < (totalTime - currentTime) * maxOreReq){
            if (oreNum >= blueprint.oreRobotOreCost && oreRobotNum < maxOreReq && oreRobotNum * (totalTime - currentTime) + oreNum < (totalTime - currentTime) * maxOreReq) {
                //std::cout<<"ORE ROBOT\n";
                next.push_back(Node(currentTime + 1, oreNum + oreRobotNum - blueprint.oreRobotOreCost, clayNum + clayRobotNum, obsidianNum + obsidianRobotNum, geodeNum + geodeRobotNum, oreRobotNum + 1, clayRobotNum, obsidianRobotNum, geodeRobotNum, blueprint, maxG, totalTime));
            }
            //Make Clay Robot
            //Only make if have enough clay and makes sense ^
            if (oreNum >= blueprint.clayRobotOreCost && clayRobotNum < blueprint.obsidianRobotClayCost && clayRobotNum * (totalTime - currentTime) + clayNum < (totalTime - currentTime) * blueprint.obsidianRobotClayCost) {
                //std::cout<<"CLAY ROBOT\n";
                next.push_back(Node(currentTime + 1, oreNum + oreRobotNum - blueprint.clayRobotOreCost, clayNum + clayRobotNum, obsidianNum + obsidianRobotNum, geodeNum + geodeRobotNum, oreRobotNum, clayRobotNum + 1, obsidianRobotNum, geodeRobotNum, blueprint, maxG, totalTime));
            }
            //Make obsidian Robot
            //Only make if have enough obsidian and makes sense ^
            if (oreNum >= blueprint.obsidianRobotOreCost && clayNum >= blueprint.obsidianRobotClayCost && obsidianRobotNum < blueprint.geodeRobotObsidianCost && obsidianRobotNum * (totalTime - currentTime) + obsidianNum < (totalTime - currentTime) * blueprint.geodeRobotObsidianCost) {
                //std::cout<<"OBSIDIAN ROBOT\n";
                next.push_back(Node(currentTime + 1, oreNum + oreRobotNum - blueprint.obsidianRobotOreCost, clayNum + clayRobotNum - blueprint.obsidianRobotClayCost, obsidianNum + obsidianRobotNum, geodeNum + geodeRobotNum, oreRobotNum, clayRobotNum, obsidianRobotNum + 1, geodeRobotNum, blueprint, maxG, totalTime));
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
        Node root(0, 0, 0, 0, 0, 1, 0, 0, 0, in, maxG, 24);
        //root.print();
        //int maxGeode = getMax(root);
        std::cout<<in.id<<' '<<maxG<<' '<<maxG * in.id<<'\n';
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
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    //std::cout<<"Part 2: "<<run2(input)<<'\n';
}


//1127 should probably be

/*
1
3
3
1
10
3
0
3
3
2
*/