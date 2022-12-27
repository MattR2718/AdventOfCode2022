#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <bitset>
#include <set>
#include <ranges>

#define STILLFOR_LIMIT 10

struct Blizzard{
    int x, y;
    char c;
    friend bool operator==(const Blizzard& a, const Blizzard& b) { return (a.x == b.x && a.y == b.y && a.c == b.c); }
};

auto getInput(const std::string f = "..\\..\\..\\..\\Day24\\test.txt"){
    std::ifstream file(f);
    std::string linetxt;
    //std::vector<std::vector<char>> out;
    std::vector<Blizzard> out;
    std::vector<std::string> map;
    int y = 0;
    int x = 0;
    while (std::getline(file, linetxt)){
        std::vector<char> temp;
        x = linetxt.length();
        for(int i = 0; i < linetxt.length(); i++){ if(linetxt[i] != '#' && linetxt[i] != '.'){out.emplace_back(Blizzard{i, y, linetxt[i]}); }}
        y++;
        map.push_back(linetxt);
    }
    int startx = std::find(map[0].begin(), map[0].end(), '.') - map[0].begin();
    int endx = std::find(map[map.size() - 1].begin(), map[map.size() - 1].end(), '.') - map[map.size() - 1].begin();
    return std::tuple(out, --x, --y, startx, endx);
}

template<typename T>
void print(T input, int x, int y){
    std::cout<<'\n';
    auto[blizzards, maxx, maxy, startx, endx]{input};
    for(int j = 0; j <= maxy; j++){
        for(int i = 0; i <= maxx; i++){
            if (i == x && j == y) { std::cout << 'E'; }else
            if(i == 0 || i == maxx || (j == 0 && i != startx) || (j == maxy && i != endx)){ std::cout<<'#';}
            else{
                bool boo = true;
                int count = 0;
                int n = 0;
                int c = 0;
                for(auto& b: blizzards){ if(b.x == i && b.y == j){ count++; n = c; } c++; }
                if(count == 1){ std::cout<<blizzards[n].c; }else if(count){ std::cout<<count; } else{std::cout<<'.'; }
            }
        }
        std::cout<<'\n';
    }
}

template<typename T>
void step(T& input){
    auto&[blizzards, maxx, maxy, startx, endx]{input};
    for(auto& b : blizzards){
        switch(b.c){
            case '>': b.x = (b.x < maxx - 1) ? b.x + 1 : 1; break;
            case '<': b.x = (b.x == 1) ? maxx - 1 : b.x - 1; break;
            case '^': b.y = (b.y == 1) ? maxy - 1 : b.y - 1; break;
            case 'v': b.y = (b.y < maxy - 1) ? b.y + 1 : 1; break;
        }
    }

}

//<<blizzard location, x, y, time>>
std::vector<std::tuple<std::vector<Blizzard>, int, int, int>> cache;

struct Position{
    int x, y, time;
    std::vector<Blizzard> map;
    std::vector<Position> next;
    //template<typename T>
    Position(int x_, int y_, int t, std::tuple<std::vector<Blizzard>, int, int, int, int> input, int stillfor, bool st = true){
        //if(t > 20){ return; }
        //std::cout << t << '\n';
        x = x_;
        y = y_;
        time = t;
        const auto&[blizzards, maxx, maxy, startx, endx]{input};
        if(x == endx && y == maxy){ return; }
        if(st){ step(input); map = std::get<0>(input); }else{ map = std::get<0>(input);}

        
        

        std::bitset<4> pos(0b1111);
        //print(input, x, y);
        for(auto& b : map){
            //Right
            if((b.x == x + 1 && b.y == y) || x + 1 >= maxx || y == 0){ pos[0] = false; }
            //Left
            if((b.x == x - 1 && b.y == y) || x - 1 <= 0 || y == 0){ pos[1] = false; }
            //Up
            if((b.y == y - 1 && b.x == y) || y - 1 <= 0){ pos[2] = false; }
            //Down
            if((b.y == y + 1 && b.x == y) || y + 1 >= maxy){ pos[3] = false; }
        }
        if(pos[0]){ next.emplace_back(Position(x + 1, y, t + 1, input, 0)); }
        if(pos[1]){ next.emplace_back(Position(x - 1, y, t + 1, input, 0)); }
        if(pos[2]){ next.emplace_back(Position(x, y - 1, t + 1, input, 0)); }
        if(pos[3]){ next.emplace_back(Position(x, y + 1, t + 1, input, 0)); }
        if(stillfor > STILLFOR_LIMIT){ return; }
        else{ next.emplace_back(Position(x, y, t + 1, input, stillfor + 1)); }
    }

    void findMin(int ex, int ey, std::vector<int>& times) {
        if (x == ex && y == ey - 1) { times.push_back(time); }
        for (auto& e : next) {
            e.findMin(ex, ey, times);
        }
    }
};

template<typename T>
auto run1(T input){
    auto[blizzards, maxx, maxy, startx, endx]{input};
    std::cout<<maxx<<' '<<maxy<<'\n';

    std::vector<std::vector<Blizzard>> blizzs;
    do{
        blizzs.emplace_back(blizzards);
        step(blizzards);
    }while(std::find(blizzs.begin(), blizzs.end(), blizzards) ==)
    
    Position p(startx, 0, 0, input, 0, false);
    std::vector<int> mins;
    p.findMin(endx, maxy, mins);


    for (auto& m : mins) {
        std::cout << "MIN: " << m << '\n';
    }
    int m = *std::ranges::min_element(mins);

    return m;
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
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    //std::cout<<"Part 2: "<<run2(input)<<'\n';
}