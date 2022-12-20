#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <regex>
#include <iomanip>
#include <set>

#define TEST false

#if TEST
#define X_BUFFER 10
#define Y_BUFFER 10
#define P1_ROW 10
#define P2_MAX_VAL 20
#else
#define X_BUFFER 500000
#define Y_BUFFER 500000
#define P1_ROW 2000000
#define P2_MAX_VAL 4000000
#endif

#if TEST
auto getInput(const std::string f = "..\\..\\Day15\\test.txt"){
#else
auto getInput(const std::string f = "..\\..\\Day15\\input.txt"){
#endif
    std::ifstream file(f);
    std::string linetxt;
    std::vector<std::vector<int>> out;
    std::regex ex("-*\\d+");
    std::smatch m;
    while (std::getline(file, linetxt)){
        std::string str = linetxt;
        std::vector<int> nums;
        while (std::regex_search(str, m, ex)) {
            for (auto match : m) {
                nums.push_back(std::stoll(match));
            }
            str = m.suffix().str();
        }
        out.emplace_back(nums);
    }
    return out;
}

template <typename T>
auto printMap(const T& input, int miny){
    auto[map, width]{input};
    for(int i = 0; i < map.size(); i++){
        if(i % width == 0){ std::cout<<'\n'; std::cout<<std::setw(3)<<miny++<<": "; }
        std::cout<<map[i];
    }
    std::cout<<'\n';
}

template<typename T>
auto run1(T input){
    int minx = 2147483647;
    int maxx = -2147483647;
    int miny = 2147483647;
    int maxy = -2147483647;

    for(auto& row : input){
        if(row[0] < minx){ minx = row[0]; }
        if(row[1] < miny){ miny = row[1]; }
        if(row[0] > maxx){ maxx = row[0]; }
        if(row[1] > maxy){ maxy = row[1]; }

        if(row[2] < minx){ minx = row[2]; }
        if(row[3] < miny){ miny = row[3]; }
        if(row[2] > maxx){ maxx = row[2]; }
        if(row[3] > maxy){ maxy = row[3]; }
    }

    /* std::cout<<'\n';
    std::cout<<"MINX: "<<minx<<'\n';
    std::cout<<"MAXX: "<<maxx<<'\n';
    std::cout<<"MINY: "<<miny<<'\n';
    std::cout<<"MAXY: "<<maxy<<'\n'; */

    minx -= X_BUFFER;
    maxx += X_BUFFER;
    miny -= Y_BUFFER;
    maxy += Y_BUFFER;

    std::vector<std::pair<int, int>> sensors;
    std::vector<std::pair<int, int>> beacons;
    for(auto& row : input){
        sensors.emplace_back(std::pair(row[0], row[1]));
        beacons.emplace_back(std::pair(row[2], row[3]));
    }


    // MAKING A FULL MAP FOR THE BEACON AREAS WORKS FOR TEST BECAUSE IT DOESN'T GET TOO BIG
    // FOR THE INPUT IT TRIES TO MAKE A VECTOR WITH (4,095,477--245,599) * (3,958,647--433,244) = 13,572,371,450,834 ELEMENTS :(
    /* minx -= X_BUFFER;
    maxx += X_BUFFER;
    miny -= Y_BUFFER;
    maxy += Y_BUFFER;

    int width = maxx - minx;

    std::vector<char> map;
    for(int j = miny; j < maxy; j++){
        for(int i = minx; i < maxx; i++){
            if(std::find(sensors.begin(), sensors.end(), std::pair(i, j)) != sensors.end()){ map.emplace_back('S'); }
            else if(std::find(beacons.begin(), beacons.end(), std::pair(i, j)) != beacons.end()){ map.emplace_back('B'); }
            else{ map.emplace_back('.'); }
        }
    }

    int counter = 0;
    for(int j = miny; j < maxy; j++){
        for(int i = minx; i < maxx; i++){
            for(int n = 0; n < sensors.size(); n++){
                int dist = abs(sensors[n].first - beacons[n].first) + abs(sensors[n].second - beacons[n].second);
                if(abs(sensors[n].first - i) + abs(sensors[n].second - j) <= dist && map[counter] == '.'){ map[counter] = '#'; }
            }
            counter++;
        }
    }

    printMap(std::pair(map, width), miny);

    int row = miny;
    int count = 0;
    for(int i = 0; i < map.size(); i++){
        if(i % width == 0){ std::cout<<'\n'; std::cout<<std::setw(3)<<miny++<<": "; row++; }
        if(row == P1_ROW + 1 && map[i] == '#'){ count++; }
    } */

    int count = 0;
    for(int i = minx; i < maxx; i++){
        for(int n = 0; n < sensors.size(); n++){
            int dist = abs(sensors[n].first - beacons[n].first) + abs(sensors[n].second - beacons[n].second);
            if(abs(sensors[n].first - i) + abs(sensors[n].second - P1_ROW) <= dist && std::find(beacons.begin(), beacons.end(), std::pair(i, static_cast<int>(P1_ROW))) == beacons.end()){ count++; /* std::cout<<i<<' '<<P1_ROW<<'\n'; */ break; }
        }
    }

    return count;
}

template<typename T>
auto run2(T input){
    int minx = 2147483647;
    int maxx = -2147483647;
    int miny = 2147483647;
    int maxy = -2147483647;

    for(auto& row : input){
        if(row[0] < minx){ minx = row[0]; }
        if(row[1] < miny){ miny = row[1]; }
        if(row[0] > maxx){ maxx = row[0]; }
        if(row[1] > maxy){ maxy = row[1]; }

        if(row[2] < minx){ minx = row[2]; }
        if(row[3] < miny){ miny = row[3]; }
        if(row[2] > maxx){ maxx = row[2]; }
        if(row[3] > maxy){ maxy = row[3]; }
    }

    minx -= X_BUFFER;
    maxx += X_BUFFER;
    miny -= Y_BUFFER;
    maxy += Y_BUFFER;

    std::vector<std::pair<int, int>> sensors;
    std::vector<std::pair<int, int>> beacons;
    std::vector<int> dists;
    for(auto& row : input){
        sensors.emplace_back(std::pair(row[0], row[1]));
        beacons.emplace_back(std::pair(row[2], row[3]));
        dists.emplace_back(abs(row[0] - row[2]) + abs(row[1] - row[3]));
    }

    /* int count = 0;
    for(int j = 0; j <= P2_MAX_VAL; j++){
        for(int i = 0; i <= P2_MAX_VAL; i++){
            bool good = true;
            for(int n = 0; n < sensors.size(); n++){
                //int dist = abs(sensors[n].first - beacons[n].first) + abs(sensors[n].second - beacons[n].second);
                if(abs(sensors[n].first - i) + abs(sensors[n].second - j) <= dists[n]){ good = false; break; }
            }
            if(good){ return i * 4000000 + j; }
        }
        std::cout<<j<<'\n';
    } */

    /*
    One solution so must be on the edge of at least one of the sensors ranges
    Find all points on edge of sensor radius and then search that list
    */

    //std::cout<<dists[6]<<'\n';

    auto check = [&](const std::pair<int64_t, int64_t>& edge){
        bool good = true;
        for(int n = 0; n < sensors.size(); n++){
            //int dist = abs(sensors[n].first - beacons[n].first) + abs(sensors[n].second - beacons[n].second);
            if(abs(sensors[n].first - edge.first) + abs(sensors[n].second - edge.second) <= dists[n] 
            || edge.first < 0 
            || edge.second > P2_MAX_VAL
            || edge.first > P2_MAX_VAL
            || edge.second < 0){ good = false; break; }
        }
        return good;
    };

    std::set<std::pair<int64_t, int64_t>> edges;
    for(int n = 0; n < sensors.size(); n++){
        for(int i = dists[n] + 1; i > -1; i--){
            int y = dists[n] + 1 - i;
            /* edges.emplace(std::pair(i + sensors[n].first, y + sensors[n].second));
            edges.emplace(std::pair(-i + sensors[n].first, y + sensors[n].second));
            edges.emplace(std::pair(i + sensors[n].first, -y + sensors[n].second));
            edges.emplace(std::pair(-i + sensors[n].first, -y + sensors[n].second)); */
            std::pair<int64_t, int64_t> ed = {i + sensors[n].first, y + sensors[n].second};
            if(check(ed)){ return ed.first * 4000000 + ed.second; }

            ed = {-i + sensors[n].first, y + sensors[n].second};
            if(check(ed)){ return ed.first * 4000000 + ed.second; }

            ed = {i + sensors[n].first, -y + sensors[n].second};
            if(check(ed)){ return ed.first * 4000000 + ed.second; }

            ed = {-i + sensors[n].first, -y + sensors[n].second};
            if(check(ed)){ return ed.first * 4000000 + ed.second; }
        }
    }

    /* std::cout<<'\n';
    for(auto& edge : edges){
        std::cout<<edge.first<<' '<<edge.second<<'\n';
    } */

    /* for(auto& edge : edges){
        bool good = true;
        for(int n = 0; n < sensors.size(); n++){
            //int dist = abs(sensors[n].first - beacons[n].first) + abs(sensors[n].second - beacons[n].second);
            if(abs(sensors[n].first - edge.first) + abs(sensors[n].second - edge.second) <= dists[n] 
            || edge.first < 0 
            || edge.second > P2_MAX_VAL
            || edge.first > P2_MAX_VAL
            || edge.second < 0){ good = false; break; }
        }
        if(good){ return edge.first * 4000000 + edge.second; }
    } */

    return LONG_LONG_MIN;
}

int main(){
    auto input = getInput();
    
    /* for(auto& i : input){
        for(auto& j : i){
            std::cout<<j<<' ';
        }
        std::cout<<'\n';
    } */
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}


//Part 1: 4876693
//Part 2: 11645454855041

//RELEASE
//TotalMilliseconds : 535.1691