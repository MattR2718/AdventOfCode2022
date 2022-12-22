#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

enum Direction{UP, RIGHT, DOWN, LEFT};

auto getInput(const std::string f = "..\\..\\Day22\\input.txt"){
    //std::ifstream file(f);
    std::string linetxt;
    std::vector<std::vector<char>> out;
    std::string instr;
    bool done = false;
    while (std::getline(std::cin, linetxt)){
        if(linetxt.length() == 0){ done = true; }
        else if(!done){
            std::vector<char> temp;
            for(auto& c : linetxt){temp.emplace_back(c);}
            out.emplace_back(temp);
        }else{
            instr = linetxt;
        }
    }
    return std::pair(out, instr);
}

struct Person{
    int x, y, dir = RIGHT;
    friend std::ostream& operator<<(std::ostream& os, const Person& p){
        std::string d;
        switch (p.dir){
        case UP:
            d = "UP";
            break;
        case RIGHT:
            d = "RIGHT";
            break;
        case DOWN:
            d = "DOWN";
            break;
        case LEFT:
            d = "LEFT";
            break;
        default:
            d = "INVALID p.dir: " + std::to_string(p.dir) + "\n";
            break;
        }
        os<<"x: "<<p.x<<" y: "<<p.y<<" dir: "<<p.dir<< " ("<<d<<")";
        return os;
    }
    void changeDir(char c){
        switch(c){
            case 'R':{
                dir = (dir + 1) % 4;
                break;
            }
            case 'L':{
                dir = ((dir - 1) == -1) ? 3 : dir - 1;
                break;
            }
            default:{
                std::cout<<"INVALID DIRECTION: "<<c<<'\n';
                break;
            }
        }
    }
    void move1(std::string ins, std::vector<std::vector<char>>& map){
        if(ins == "L" || ins == "R"){ changeDir(ins[0]); return; }
        int number = std::stoi(ins);
        switch(dir){
            case UP:{
                //std::cout<<"UP\n";
                map[y][x] = '^';
                //For number
                for(int i = 1; i <= number; i++){
                    //If spot above is value then move up
                    if((y - 1) >= 0 && map[y - 1].size() > x && map[y - 1][x] != ' ' && map[y - 1][x] != '#'){ y--; map[y][x] = '^'; }
                    else if((y - 1) < 0 || map[y - 1][x] == ' '){ //If spot above an edge
                        int n = 0;
                        while((y + n) < map.size() && map[y + n].size() > x && map[y + n][x] != ' '){ //While spot below is a spot and is not equal to blank
                            n++;
                        }
                        n--; //n is the nnumber of steps below the bottom is
                        if(map[y + n][x] == '#'){ return; } //If # then stop moving and return
                        else{ y += n; map[y][x] = '^'; } //Move down to bottom
                    }
                }
                break;
            }
            case RIGHT:{
                //std::cout<<"RIGHT\n";
                map[y][x] = '>';
                for(int i = 1; i <= number; i++){
                    //If spot to right is value then move up
                    if((x + 1) < map[y].size() && map[y][x + 1] != ' ' && map[y][x + 1] != '#'){ x++; map[y][x] = '>'; }
                    else if((x + 1) >= map[y].size() || map[y][x + 1] == ' '){ //If spot to right an edge
                        int n = 0;
                        while((x - n) != -1 && map[y][x - n] != ' '){ //While spot to left is a spot and is not equal to blank
                            n++;
                        }
                        n--; //n is the number of steps to edge
                        if(map[y][x - n] == '#'){ return; } //If # then stop moving and return
                        else{ x -= n; map[y][x] = '>'; } //Move across to left
                    }
                }
                break;
            }
            case DOWN:{
                //std::cout<<"DOWN\n";
                map[y][x] = 'v';
                //For number
                for(int i = 1; i <= number; i++){
                    //If spot below is value then move up
                    if((y + 1) < map.size() && map[y + 1].size() > x && map[y + 1][x] != ' ' && map[y + 1][x] != '#'){ y++; map[y][x] = 'v'; }
                    else if((y + 1) >= map.size() || map[y + 1].size() < x || map[y + 1][x] == ' '){ //If spot below is an edge
                        int n = 0;
                        while((y - n) >= 0 && map[y - n].size() > x && map[y - n][x] != ' '){ //While spot above is a spot and is not equal to blank
                            n++;
                        }
                        n--; //n is the nnumber of steps above the top is
                        if(map[y - n][x] == '#'){ return; } //If # then stop moving and return
                        else{ y -= n; map[y][x] = 'v'; } //Move down to bottom
                    }
                }

                break;
            }
            case LEFT:{
                //std::cout<<"LEFT\n";
                map[y][x] = '<';
                for(int i = 1; i <= number; i++){
                    //If spot to left is value then move left
                    if((x - 1) >= 0 && map[y][x - 1] != ' ' && map[y][x - 1] != '#'){ x--; map[y][x] = '<'; }
                    else if((x - 1) < 0 || map[y][x - 1] == ' '){ //If spot to left an edge
                        int n = 0;
                        while((x + n) < map[y].size() && map[y][x + n] != ' '){ //While spot to right is a spot and is not equal to blank
                            n++;
                        }
                        n--; //n is the number of steps to edge
                        if(map[y][x + n] == '#'){ return; } //If # then stop moving and return
                        else{ x += n; map[y][x] = '<'; } //Move across to right
                    }
                }
                break;
            }
            default:{
                return;
                break;
            }
        }
    }
    void setdirection(const int x, const int y, const std::vector<std::vector<char>>& map){
        //std::cout<<"SET DOWN\n";
        //Should be facing down
        if(y == 0 || map[y - 1].size() < x || map[y - 1][x] == ' '){ dir = DOWN; return;}
        //std::cout<<"SET UP "<<y<<' '<<map.size()<<'\n';
        //std::cout<<"y: "<<y<<" x: "<<x<<'\n';
        //std::cout<<"map[y + 1].size(): "<<map[y + 1].size()<<'\n';
        //std::cout<<"map[y + 1][x]: "<<map[y + 1][x]<<'\n';
        //Should be fcaing up
        if(y == map.size() - 1 || map[y + 1].size() <= x || map[y + 1][x] == ' '){ dir = UP; return; }
        //std::cout<<"SET RIGHT\n";
        //Should be facing right
        if(x == 0 || map[y][x - 1] == ' '){ dir = RIGHT; return; }
        //std::cout<<"SET LEFT\n";
        //Should be facing left
        if(x == map[y].size() - 1 || map[y][x + 1] == ' '){ dir = LEFT; return; }
    }
    void move2(std::string ins, std::vector<std::vector<char>>& map, const std::map<std::pair<int, int>, std::pair<int, int>>& edges){
        if(ins == "L" || ins == "R"){ changeDir(ins[0]); return; }
        int number = std::stoi(ins);
        for(int i = 1; i <= number; i++){
            switch(dir){
                case UP:{
                    //std::cout<<"UP\n";
                    map[y][x] = '^';
                    //If spot above is value then move up
                    if((y - 1) >= 0 && map[y - 1].size() > x && map[y - 1][x] != ' ' && map[y - 1][x] != '#'){ y--; map[y][x] = '^'; }
                    else if((y - 1) < 0 || map[y - 1][x] == ' '){ //If spot above an edge
                        //std::cout<<x<<' '<<y<<' ';
                        std::pair<int, int> next = edges.at(std::pair(x, y));
                        if(map[next.second][next.first] != '#'){
                            x = next.first;
                            y = next.second;
                            //std::cout<<x<<' '<<y<<'\n';
                            setdirection(x, y, map);
                        }
                        
                    }
                    
                    break;
                }
                case RIGHT:{
                    //std::cout<<"RIGHT\n";
                    map[y][x] = '>';
                    //If spot to right is value then move up
                    if((x + 1) < map[y].size() && map[y][x + 1] != ' ' && map[y][x + 1] != '#'){ x++; map[y][x] = '>'; }
                    else if((x + 1) >= map[y].size() || map[y][x + 1] == ' '){ //If spot to right an edge
                        //std::cout<<x + 1<<' '<<y<<' ';
                        //std::cout<<x<<' '<<y<<' ';
                        std::pair<int, int> next = edges.at(std::pair(x, y));
                        if(map[next.second][next.first] != '#'){
                            x = next.first;
                            y = next.second;
                            //std::cout<<x<<' '<<y<<'\n';
                            setdirection(x, y, map);
                        }
                        
                    }
                    break;
                }
                case DOWN:{
                    //std::cout<<"DOWN\n";
                    map[y][x] = 'v';
                    //If spot below is value then move up
                    if((y + 1) < map.size() && map[y + 1].size() > x && map[y + 1][x] != ' ' && map[y + 1][x] != '#'){ y++; map[y][x] = 'v'; }
                    else if((y + 1) >= map.size() || map[y + 1].size() < x || map[y + 1][x] == ' '){ //If spot below is an edge
                        //std::cout<<x<<' '<<y + 1<<' ';
                        //std::cout<<x<<' '<<y<<' ';
                        std::pair<int, int> next = edges.at(std::pair(x, y));
                        if(map[next.second][next.first] != '#'){
                            x = next.first;
                            y = next.second;
                            //std::cout<<x<<' '<<y<<'\n';
                            setdirection(x, y, map);
                        }
                        
                    }

                    break;
                }
                case LEFT:{
                    //std::cout<<"LEFT\n";
                    map[y][x] = '<';
                    //If spot to left is value then move left
                    if((x - 1) >= 0 && map[y][x - 1] != ' ' && map[y][x - 1] != '#'){ x--; map[y][x] = '<'; }
                    else if((x - 1) < 0 || map[y][x - 1] == ' '){ //If spot to left an edge
                        //std::cout<<x - 1<<' '<<y<<' ';
                        //std::cout<<x<<' '<<y<<' ';
                        std::pair<int, int> next = edges.at(std::pair(x, y));
                        if(map[next.second][next.first] != '#'){
                            x = next.first;
                            y = next.second;
                            //std::cout<<x<<' '<<y<<'\n';
                            setdirection(x, y, map);
                        }
                        
                    }
                    break;
                }
                default:{
                    return;
                    break;
                }
            }
            //std::cout<<"NEXT\n";
        }
    }
};

auto getInstructions(std::string s){
    std::vector<std::string> Lwords;
    std::vector<std::string> out;
    boost::split(Lwords, s, boost::is_any_of("L"), boost::token_compress_on);
    for(auto& w : Lwords){ 
        std::vector<std::string> Rwords;
        boost::split(Rwords, w, boost::is_any_of("R"), boost::token_compress_on);
        for(auto& rw : Rwords){
            out.push_back(rw);
            out.push_back("R");
        }
        out.erase(out.begin() + out.size() - 1);
        out.push_back("L");
    }
    out.erase(out.begin() + out.size() - 1);
    /* for(auto& o : out){
        std::cout<<o<<'\n';
    }
    std::cout<<'\n'; */

    return out;
}

void printMap(const std::vector<std::vector<char>>& map){
    std::cout<<'\n';
    for(auto& r : map){
        for(auto& c : r){ std::cout<<c; }
        std::cout<<'\n';
    }
    std::cout<<'\n';
}

auto getedges(std::vector<std::vector<char>> map, bool input){
    std::map<std::pair<int, int> , std::pair<int, int>> edges;

    if(input){
        for(int i = 0; i < 50; i++){
            //Silver
            edges[std::pair(50 + i, 0)] = std::pair(0, 150 + i);
            edges[std::pair(0, 150 + i)] = std::pair(50 + i, 0);
            //Green
            edges[std::pair(50, i)] = std::pair(0, 149 - i);
            edges[std::pair(0, 149 - i)] = std::pair(50, i);
            //Purple
            edges[std::pair(50, i + 50)] = std::pair(i, 100);
            edges[std::pair(i, 100)] = std::pair(50, i + 50);
            
            //Blank
            edges[std::pair(100 + i, 0)] = std::pair(i, 199);
            edges[std::pair(i, 199)] = std::pair(100 + i, 0);
            /* edges[std::pair(149 - i, 0)] = std::pair(i, 199);
            edges[std::pair(i, 199)] = std::pair(149 - i, 0); */
           
            //Yellow
            edges[std::pair(149, i)] = std::pair(99, 149 - i);
            edges[std::pair(99, 149 - i)] = std::pair(149, i);
            //Red
            edges[std::pair(100 + i, 49)] = std::pair(99, 50 + i);
            edges[std::pair(99, 50 + i)] = std::pair(100 + i, 49);
            //Blue
            edges[std::pair(50 + i, 149)] = std::pair(49, 150 + i);
            edges[std::pair(49, 150 + i)] = std::pair(50 + i, 149);
        }
    }else{
        for(int i = 0; i < 4; i++){
            //Blue
            edges[std::pair(8 + i, 0)] = std::pair(i, 4);
            edges[std::pair(i, 4)] = std::pair(8 + i, 0);
            //Red
            edges[std::pair(8, i)] = std::pair(4 + i, 4);
            edges[std::pair(4 + i, 4)] = std::pair(8, i);
            //Purple
            edges[std::pair(11, i)] = std::pair(15, i + 8);
            edges[std::pair(15, i + 8)] = std::pair(11, i);
            //Green
            edges[std::pair(11, i + 4)] = std::pair(15 - i, 8);
            edges[std::pair(15 - 8, 8)] = std::pair(11, i + 4);
            //Silver
            edges[std::pair(4 + i, 7)] = std::pair(8, 8 + i);
            edges[std::pair(8, 8 + i)] = std::pair(4 + i, 7);
            //Yellow
            edges[std::pair(i, 7)] = std::pair(11 - i, 11);
            edges[std::pair(11 - i, 11)] = std::pair(i, 7);
            //Blank
            edges[std::pair(0, 7 - i)] = std::pair(12 + i, 11);
            edges[std::pair(12 + i, 11)] = std::pair(0, 7 - i);
        }
    }

    return edges;
}

template<typename T>
auto run1(T input){
    auto[map, instru]{input};
    std::vector<std::string> instructions = getInstructions(instru);
    int startx = -1;
    for(int i = 0; i < map[0].size(); i++){
        if(map[0][i] == '.'){ startx = i; break; }
    }
    Person p{startx, 0};

    for(auto& ins : instructions){
        p.move1(ins, map);
        //std::cout<<p<<'\n';
    }
    printMap(map);

    int dirval = 0;
    switch(p.dir){
        case RIGHT: dirval = 0; break;
        case DOWN: dirval = 1; break;
        case LEFT: dirval = 2; break;
        case UP: dirval = 3; break;
    }
    //std::cout<<p<<'\n';
    return 1000 * (p.y + 1) + 4 * (p.x + 1) + dirval;
}

template<typename T>
auto run2(T input){
    auto[map, instru]{input};
    std::vector<std::string> instructions = getInstructions(instru);
    int startx = -1;
    for(int i = 0; i < map[0].size(); i++){
        if(map[0][i] == '.'){ startx = i; break; }
    }
    Person p{startx, 0};
    //std::cout<<p<<'\n';

    std::map<std::pair<int, int> , std::pair<int, int>> edges;
    if(startx == 8){ //Test
        edges =  getedges(map, false);
    }else{ //Input
        edges =  getedges(map, true);
    }

    int count = 0;

    for(auto& ins : instructions){
        //std::cout<<ins<<'\n';
        p.move2(ins, map, edges);
        //if(count++ % 100 == 0){ printMap(map); }
        //printMap(map);
        //std::cout<<p<<'\n';
    }
    printMap(map);

    int dirval = 0;
    switch(p.dir){
        case RIGHT: dirval = 0; break;
        case DOWN: dirval = 1; break;
        case LEFT: dirval = 2; break;
        case UP: dirval = 3; break;
    }
    std::cout<<p<<'\n';
    return 1000 * (p.y + 1) + 4 * (p.x + 1) + dirval;
}

int main(){
    auto input = getInput();
    
    /* for(auto& i : input.first){
        for(auto& c: i){ std::cout<<c; }
        std::cout<<'\n';
    }
    std::cout<<input.second<<'\n'; */
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}


//Part 1: 1428

//40307 too low
//150156 too high