#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <bitset>

enum Direction{NORTH, SOUTH, EAST, WEST};

struct Elf{
    int x, y;
    int proposed;
    int px, py;
    friend std::ostream& operator<<(std::ostream& os, const Elf& e){
        os << "x: "<<e.x<<" y: "<<e.y <<" px: "<<e.px<<" py: "<<e.py;
        return os;
    }
    friend bool operator==(const Elf& a, const Elf& b){
        return (a.px == b.px) && (a.py == b.py);
    }

    void zero(const std::bitset<9>& pos){
        if(!pos[0] && !pos[1] && !pos[2]){ /* std::cout<<"NORTH\n"; */ proposed = NORTH; px = x; py = y - 1;}
        else if(!pos[8] && !pos[7] && !pos[6]){ /* std::cout<<"SOUTH\n"; */ proposed = SOUTH; px = x; py = y + 1; }
        else if(!pos[6] && !pos[3] && !pos[0]){ /* std::cout<<"WEST\n"; */proposed = WEST; px = x - 1; py = y; }
        else if(!pos[8] && !pos[5] && !pos[2]){ /* std::cout<<"EAST\n"; */proposed = EAST; px = x + 1; py = y; }
    }

    void one(const std::bitset<9>& pos){
        if(!pos[8] && !pos[7] && !pos[6]){ /* std::cout<<"SOUTH\n"; */ proposed = SOUTH; px = x; py = y + 1; }
        else if(!pos[6] && !pos[3] && !pos[0]){ /* std::cout<<"WEST\n"; */proposed = WEST; px = x - 1; py = y; }
        else if(!pos[8] && !pos[5] && !pos[2]){ /* std::cout<<"EAST\n"; */proposed = EAST; px = x + 1; py = y; }
        else if(!pos[0] && !pos[1] && !pos[2]){ /* std::cout<<"NORTH\n"; */ proposed = NORTH; px = x; py = y - 1;}
    }

    void two(const std::bitset<9>& pos){
        if(!pos[6] && !pos[3] && !pos[0]){ /* std::cout<<"WEST\n"; */proposed = WEST; px = x - 1; py = y; }
        else if(!pos[8] && !pos[5] && !pos[2]){ /* std::cout<<"EAST\n"; */proposed = EAST; px = x + 1; py = y; }
        else if(!pos[0] && !pos[1] && !pos[2]){ /* std::cout<<"NORTH\n"; */ proposed = NORTH; px = x; py = y - 1;}
        else if(!pos[8] && !pos[7] && !pos[6]){ /* std::cout<<"SOUTH\n"; */ proposed = SOUTH; px = x; py = y + 1; }
    }

    void three(const std::bitset<9>& pos){
        if(!pos[8] && !pos[5] && !pos[2]){ /* std::cout<<"EAST\n"; */proposed = EAST; px = x + 1; py = y; }
        else if(!pos[0] && !pos[1] && !pos[2]){ /* std::cout<<"NORTH\n"; */ proposed = NORTH; px = x; py = y - 1;}
        else if(!pos[8] && !pos[7] && !pos[6]){ /* std::cout<<"SOUTH\n"; */ proposed = SOUTH; px = x; py = y + 1; }
        else if(!pos[6] && !pos[3] && !pos[0]){ /* std::cout<<"WEST\n"; */proposed = WEST; px = x - 1; py = y; }
    }


    void getProposed(const std::vector<Elf>& elves, int round, int& numNoMove){
        //  8  7   6  5  4  3   2  1   0
        //(SE, S, SW, E, P, W, NE, N, NW)
        std::bitset<9> pos{0b000000000};
        //std::cout<<pos<<'\n';
        for(int j = -1; j < 2; j++){
            for(int i = -1; i < 2; i++){
                if(!(i == 0 && j == 0)){
                    for(auto& e : elves){
                        if(e.x == (x + i) && e.y == (y + j)){ 
                            //std::cout<<i<<' '<<j<<' '<<e<<'\n';
                            pos.set((j + 1) * 3 + (i+ 1), true); 
                            break;
                        }
                    }
                }
            }
        }
        //std::cout<<pos<<'\n';
        //if(pos.count() == 1){numNoMove++; return; }
        if(pos.none()){ px = x; py = y; /* std::cout<< "x: "<<x<<" y: "<<y <<" px: "<<px<<" py: "<<py<<"\n"; */ numNoMove++; return; }
        //std::cout<<"-------------------------------  "<<pos<<'\n';

        switch (round % 4){
            case 0: zero(pos); break;
            case 1: one(pos); break;
            case 2: two(pos); break;
            case 3: three(pos); break;
            default: std::cout<<"ERROR WITH ROUND: "<<round<<'\n'; break;
        }
        //zero(pos);
        
        //std::cout<< "x: "<<x<<" y: "<<y <<" px: "<<px<<" py: "<<py<<"\n\n\n";
    }
};

auto getInput(const std::string f = "..\\..\\Day2\\input.txt"){
    //std::ifstream file(f);
    std::string linetxt;
    std::vector<Elf> out;
    int y = 0;
    while (std::getline(std::cin, linetxt)){
        for(int i = 0; i < linetxt.length(); i++){
            if(linetxt[i] == '#'){ out.emplace_back(Elf{i, y}); }
        }
        y++;
    }
    return out;
}

void print(const std::vector<Elf>& elves){
    std::cout<<'\n';
    int minx = 1000000;
    int miny = 1000000;
    int maxx = -1000000;
    int maxy = -1000000;
    for(auto& e : elves){
        if(e.x < minx){ minx = e.x; }
        if(e.y < miny){ miny = e.y; }
        if(e.x > maxx){ maxx = e.x; }
        if(e.y > maxy){ maxy = e.y; }
    }
    for(int j = miny; j <= maxy; j++){
        for(int i = minx; i <= maxx; i++){
            bool elf = false;
            for(auto& e : elves){ if(e.x == i && e.y == j){ std::cout<<'#'; elf = true; }}
            if(!elf){ std::cout<<'.';}
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';
    std::cout<<maxx<<' '<<minx<<' '<<maxy<<' '<<miny<<'\n';
}

int count(const std::vector<Elf>& elves){
    int minx = 1000000;
    int miny = 1000000;
    int maxx = -1000000;
    int maxy = -1000000;
    for(auto& e : elves){
        if(e.x < minx){ minx = e.x; }
        if(e.y < miny){ miny = e.y; }
        if(e.x > maxx){ maxx = e.x; }
        if(e.y > maxy){ maxy = e.y; }
    }
    //std::cout<<maxx<<' '<<minx<<' '<<maxy<<' '<<miny<<'\n';
    return (++maxx - minx) * (++maxy - miny) - elves.size(); 
}

template<typename T>
auto run1(T input){
    int i = 0;
    for(int round = 0; round < 10; round++){
        for(auto& e : input){
            e.getProposed(input, round, i);
        }
        for(auto& e : input){
            //-1 since when sees itself it will go to 0
            int move = -1;
            for(auto& o : input){
                if(o == e){ move++; }
            }
            if(!move){ e.x = e.px; e.y = e.py; }
        }
    }
 
    return count(input);
}

template<typename T>
auto run2(T input){
    std::cout<<input.size()<<'\n';
    //print(input);
    int num = 0;
    int round = 0;
    T prev = input;
    //int prevc = 0;
    do{
        prev = input;
        //prevc = count(input);
        num = 0;
        for(auto& e : input){
            e.getProposed(input, round, num);
        }
        for(auto& e : input){
            int move = -1;
            for(auto& o : input){
                if(o == e){ /* if(round > 1000){std::cout<<"SAME: "<<o<<'\n';} */ move++; }
            }
            if(!move){ e.x = e.px; e.y = e.py; }
        }
        round++;
        std::cout<<num<<" "<<round<<'\n';
        /* if(round > 980){ print(input); }
        int minx = 1000000;
        int miny = 1000000;
        int maxx = -1000000;
        int maxy = -1000000;
        for(auto& e : input){
            if(e.x < minx){ minx = e.x; }
            if(e.y < miny){ miny = e.y; }
            if(e.x > maxx){ maxx = e.x; }
            if(e.y > maxy){ maxy = e.y; }
        }
        std::cout<<maxx<<' '<<minx<<' '<<maxy<<' '<<miny<<'\n'; */
    }while (num < input.size());

        

    //}while(prev != input);


    //for(auto& e : input){ std::cout<<e<<'\n';}
    
    //print(input);
 
    return round;
}

int main(){
    auto input = getInput();
    
    /* for(auto& i : input){
        std::cout<<i<<'\n';
    } */
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}


//Part 1: 4138

//1018 too high
//969 too low
//982 too low