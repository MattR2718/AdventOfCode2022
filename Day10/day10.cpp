#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>

struct Instr{
    std::string instruction;
    int val;
    Instr(std::string n, int i = 0){
        instruction = n;
        val = i;
    }
    void print(){
        std::cout<<instruction<<' '<<val<<'\n';
    }
};

auto getInput(const std::string f = "..\\..\\Day10\\input.txt"){
    std::ifstream file(f);
    std::string linetxt;
    std::vector<Instr> out;
    while (std::getline(file, linetxt)){
        if(linetxt.length() == 4){
            out.emplace_back(Instr(linetxt));
        }else{
            out.emplace_back(Instr(linetxt.substr(0, 4), std::stoi(linetxt.substr(5, linetxt.length() - 5))));
        }
        //out[out.size() - 1].print();
    }
    return out;
}

template<typename T>
auto run1(T input){
    int tick = 0;
    int reg = 1;
    int sum = 0;
    for(auto& i : input){
        if(i.instruction == "noop"){ tick++; if((tick - 20) % 40 == 0){ sum += tick * reg; }}
        else if(i.instruction == "addx"){ tick += 2; if((tick - 20) % 40 == 0){ sum += tick * reg;}else if((tick - 20) % 40 == 1){ sum += (tick - 1) * reg; }}
        if(i.instruction == "addx"){ reg += i.val; }
    }

    return sum;
}

template<typename T>
auto run2(T input){
    int tick = -1;
    int reg = 1;
    std::string screen = "";
    for(auto& i : input){
        if(i.instruction == "noop"){ tick++; if(reg-1 <= (tick%40) && reg+1>=(tick%40)){ screen += '#'; }else{ screen += '.'; }}
        else if(i.instruction == "addx"){ 
            tick++; if(reg-1 <= (tick%40) && reg+1>=(tick%40)){ screen += '#'; }else{ screen += '.'; }
            tick++; if(reg-1 <= (tick%40) && reg+1>=(tick%40)){ screen += '#'; }else{ screen += '.'; }
            //tick++; if(reg - 1 == (tick%40) || reg == (tick%40) || reg + 1 == (tick%40)){ screen += '#'; }else{ screen += '.'; }
            //tick++; if(reg - 1 == (tick%40) || reg == (tick%40) || reg + 1 == (tick%40)){ screen += '#'; }else{ screen += '.'; }
        }
        if(i.instruction == "addx"){ reg += i.val; }
    }

    for(int i = 0; i < screen.length(); i++){
        if(i % 40 == 0){ std::cout<<'\n';}
        std::cout<<screen[i];
    }

    
    return -1;
}

int main(){
    auto input = getInput();
    
    /* for(auto& i : input){
        i.print();
    } */
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}

//Part 1: 13060
//Part 2: FJUBULRZ
/*
####...##.#..#.###..#..#.#....###..####.
#.......#.#..#.#..#.#..#.#....#..#....#.
###.....#.#..#.###..#..#.#....#..#...#..
#.......#.#..#.#..#.#..#.#....###...#...
#....#..#.#..#.#..#.#..#.#....#.#..#....
#.....##...##..###...##..####.#..#.####.
*/

//TotalMilliseconds : 25.8596