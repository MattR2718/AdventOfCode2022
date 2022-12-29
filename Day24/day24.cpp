#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <ranges>
#include <iomanip>
#include <queue>

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
    while (std::getline(std::cin, linetxt)){
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

std::vector<char> makeMap(const std::vector<Blizzard>& blizzards, int maxx, int maxy, int startx, int endx){
    std::vector<char> bmaps;
    for(int j = 0; j <= maxy; j++){
        for(int i = 0; i <= maxx; i++){
            if(i == 0 || i == maxx || (j == 0 && i != startx) || (j == maxy && i != endx)){ bmaps.emplace_back('#');}
            else{
                bool boo = true;
                int count = 0;
                int n = 0;
                int c = 0;
                for(auto& b: blizzards){ if(b.x == i && b.y == j){ count++; n = c; } c++; }
                if(count == 1){ bmaps.emplace_back(blizzards[n].c); }else if(count){ bmaps.emplace_back(count + '0'); } else{bmaps.emplace_back('.'); }
            }
        }
    }
    return bmaps;
}

void printBMap(const std::vector<char>& map, int maxx){
    for(int i = 0; i < map.size(); i++){
        if(i % (maxx + 1) == 0){ std::cout<<'\n'; }
        std::cout<<map[i];
    }
    std::cout<<'\n';
}

void addToAdj(const std::vector<char>& from, const std::vector<char>& to, const int fromStartID, const int toStartID, const int width, std::map<int, std::vector<int>>& adj){
    for(int j = 0; j < from.size() / width; j++){
        for(int i = 0; i < width; i++){
            if(from[j * width + i] == '.'){
                adj[fromStartID + j * width + i];
                if(to[j * width + i] == '.'){ //Stay
                    adj[fromStartID + j * width + i].emplace_back(toStartID + j * width + i);
                }

                if(j - 1 > -1 && to[(j - 1) * width + i] == '.'){ //Up
                    adj[fromStartID + j * width + i].emplace_back(toStartID + (j - 1) * width + i);
                }

                if(j + 1 < (from.size() / width) && to[(j + 1) * width + i] == '.'){ //Down
                    adj[fromStartID + j * width + i].emplace_back(toStartID + (j + 1) * width + i);
                }
                
                if(i - 1 > -1 && to[j * width + (i - 1)] == '.'){ //Left
                    adj[fromStartID + j * width + i].emplace_back(toStartID + j * width + (i - 1));
                }
                
                if(i + 1 < width && to[j * width + (i + 1)] == '.'){ //Right
                    adj[fromStartID + j * width + i].emplace_back(toStartID + j * width + (i + 1));
                }
            }
        }
    }
}

void printAdj(const std::map<int, std::vector<int>>& adj){
    for(auto& v : adj){
        std::cout<<v.first<<": ";
        for(auto& i : v.second){
            std::cout<<std::setw(4)<<i<<' ';
        }
        std::cout<<'\n';
    }
}

std::pair<int, int> bfs(const int start, const std::vector<int>& ends, const std::map<int, std::vector<int>>& adj){
    std::queue<int> q;
    std::set<int> visited;
    //                    <prev, dist>
    std::map<int, std::pair<int, int>> prev;
    for(auto& a : adj){
        prev[a.first] = std::make_pair(-1, 10000000);
    }
    q.push(start);
    visited.emplace(start);
    prev[start] = std::make_pair(start, 0);

    bool done = false;
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        for(auto& nei : adj.at(curr)){
            if(!visited.contains(nei)){
                q.push(nei);
                int tempDist = prev[curr].second + 1;
                if(tempDist < prev[nei].second){
                    prev[nei] = std::make_pair(curr, tempDist);
                }
                if(std::find(ends.begin(), ends.end(), nei) != ends.end()){ done = true; break;}
                visited.emplace(nei);
            }
        }
        if(done){ break; }
    }
    //                      <val,   dist>
    std::pair<int, int> min{1000000, 1000000};
    for(int i = 0; i < ends.size(); i++){
        if(prev[ends[i]].second < min.second){ min = std::pair{ends[i], prev[ends[i]].second}; }
    }

    return min;
}

template <typename T>
auto getMaps(T input){
    auto[bs, maxx, maxy, startx, endx]{input};
    std::vector<std::vector<char>> blizzMaps;
    std::vector<char> tMap = makeMap(std::get<0>(input), maxx, maxy, startx, endx);
    do{
        blizzMaps.emplace_back(tMap);
        step(input);
        tMap = makeMap(std::get<0>(input), maxx, maxy, startx, endx);
    }while(std::find(blizzMaps.begin(), blizzMaps.end(), tMap) == blizzMaps.end());

    return blizzMaps;
}

template <typename T>
auto createAdj(const auto& blizzMaps, const T input){
    auto[bs, maxx, maxy, startx, endx]{input};
    int size = (maxx + 1) * (maxy + 1);
    std::map<int, std::vector<int>> adj;
    for(int i = 0; i < blizzMaps.size() - 1; i++){
        addToAdj(blizzMaps[i], blizzMaps[i + 1], i * size, (i + 1) * size, maxx + 1, adj);
    }
    addToAdj(blizzMaps[blizzMaps.size() - 1], blizzMaps[0], (blizzMaps.size() - 1) * size, 0, maxx + 1, adj);

    return adj;
}

template<typename T>
auto run1(T input, const auto& blizzMaps, const auto& adj){
    auto[bs, maxx, maxy, startx, endx]{input};
    int size = (maxx + 1) * (maxy + 1);

    //Multiple possible end points so will have to check all and return smallest
    std::vector<int> ends;
    for(int i = 0; i < blizzMaps.size(); i++){
        ends.emplace_back(i * size + ((maxx + 1) * maxy) + endx);
    }
    return bfs(startx, ends, adj).second;
}


template<typename T>
auto run2(T input, const auto& blizzMaps, const auto& adj){
    auto[bs, maxx, maxy, startx, endx]{input};

    int size = (maxx + 1) * (maxy + 1);

    std::vector<int> ends;
    std::vector<int> starts;
    for(int i = 0; i < blizzMaps.size(); i++){
        ends.emplace_back(i * size + ((maxx + 1) * maxy) + endx);
        starts.emplace_back(i * size + startx);
    }

    auto one = bfs(startx, ends, adj);
    auto two = bfs(one.first, starts, adj);
    auto three = bfs(two.first, ends, adj);
    
    return one.second + two.second + three.second;
}

int main(){
    auto input = getInput();

    auto bmap = getMaps(input);
    auto adj = createAdj(bmap, input);
   
    std::cout<<"Part 1: "<<run1(input, bmap, adj)<<'\n';
    std::cout<<"Part 2: "<<run2(input, bmap, adj)<<'\n';
}



//Part 1: 297
//Part 2: 856

/*
RELEASE: 
    Days              : 0
    Hours             : 0
    Minutes           : 0
    Seconds           : 4
    Milliseconds      : 879
    Ticks             : 48795067
    TotalDays         : 5.64757719907407E-05
    TotalHours        : 0.00135541852777778
    TotalMinutes      : 0.0813251116666667
    TotalSeconds      : 4.8795067
    TotalMilliseconds : 4879.5067
*/