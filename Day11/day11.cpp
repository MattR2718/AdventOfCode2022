#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>

#define TEST false

#if TEST
#define P2_MOD_NUM 96577
#else
#define P2_MOD_NUM 9699690
#endif

struct Monkey{
    std::vector<int64_t> items;
    std::string instr;
    int64_t opNum, testNum, trueMonk, falseMonk;
    bool oldold;
    int64_t numInspected = 0;
    Monkey(std::vector<int64_t> ite, std::string ins, int64_t op, int64_t test, int64_t tru, int64_t fal, bool old){
        items = ite;
        instr = ins;
        opNum = op;
        testNum = test;
        trueMonk = tru;
        falseMonk = fal;
        oldold = old;
    }
    void print(){
        std::cout<<"ITEMS: ";
        for(auto& i : items){
            std::cout<<i<<' ';
        }
        std::cout<<'\n';
        if(!oldold){std::cout<<"INSTRUCTION: "<<instr<<' '<<opNum<<'\n';}
        else{ std::cout<<"INSTRUCTION: "<<instr<<' '<<"old"<<'\n'; }
        std::cout<<"TESTNUM: "<<testNum<<'\n';
        std::cout<<"TRUEMONK: "<<trueMonk<<'\n';
        std::cout<<"FALSEMONK: "<<falseMonk<<'\n';
    }
    void printItems(){
        for(auto& item : items){
            std::cout<<item<<' ';
        }
        std::cout<<"    "<<numInspected<<'\n';
        //std::cout<<'\n';
    }
    void printNumInspected(){
        std::cout<<numInspected<<'\n';
    }
    void inspect(std::vector<Monkey>& monkeys, bool p1 = true){
        int numItems = items.size();
        for(int i = 0; i < numItems; i++){
            numInspected++;
            int64_t inspectItem = items[0];
            items.erase(items.begin());
            if(oldold){
                if(instr == "+"){
                    inspectItem += inspectItem;
                }else if(instr == "*"){
                    inspectItem *= inspectItem;
                }
            }else{
                if(instr == "+"){
                    inspectItem += opNum;
                }else if(instr == "*"){
                    inspectItem *= opNum;
                }
            }
            if(p1){inspectItem /= 3;}
            inspectItem %= P2_MOD_NUM;
            if(inspectItem % testNum == 0){
            //if(inspectItem == 0){
                monkeys[trueMonk].items.push_back(inspectItem);
            }else{
                monkeys[falseMonk].items.push_back(inspectItem);
            }
        }
    }
};

#if TEST
auto getInput(const std::string f = "..\\..\\Day11\\test.txt"){
#else
auto getInput(const std::string f = "..\\..\\Day11\\input.txt"){
#endif
    std::ifstream file(f);
    std::string linetxt;
    std::vector<Monkey> out;
    std::vector<std::vector<std::string>> m;
    while (std::getline(file, linetxt)){
        std::stringstream ss(linetxt);

        if(linetxt.length() == 0){
            std::vector<int64_t> ite;
            for(int i = 4; i < m[1].size(); i++){
                ite.emplace_back(std::stoi(m[1][i]));
            }

            std::string op = m[2][6];
            bool oldold = false;
            int64_t opNum;
            if(m[2][7] == "old"){
                oldold = true;
                opNum = 1;
            }else{
                opNum = std::stoi(m[2][7]);
            }
            int64_t testNum = std::stoi(m[3][5]);
            int64_t trueMonk = std::stoi(m[4][9]);
            int64_t falseMonk = std::stoi(m[5][9]);
            out.emplace_back(Monkey(ite, op, opNum, testNum, trueMonk, falseMonk, oldold));
            m.clear();
        }else{
            std::vector<std::string> d;
            std::string s;
            int i = 0;
            while(std::getline(ss, s, ' ')){
                d.push_back(s);
            }
            m.push_back(d);
        }
    }
    return out;
}

bool comp(const Monkey& a, const Monkey& b){
    return a.numInspected > b.numInspected;
}

template<typename T>
auto run1(T input){
    for(int i = 0; i < 20; i++){
        for(auto& monk : input){
            monk.inspect(input);
        }
    }
    std::sort(input.begin(), input.end(), comp);
    return input[0].numInspected * input[1].numInspected;
}

template<typename T>
auto run2(T input){
    /*
        Part 2 numbers get very massive so they overflow
        Need to find a way to make the numbers smaller so that they still return the same number when modulo
        Need to modulo by a number which will not affect modulo for any of the monkeys
        Modulo by the smallest common multiple of all the monkey division test numbers
    */
    for(int i = 0; i < 10000; i++){
        for(auto& monk : input){
            monk.inspect(input, false);
        }
    }
    std::sort(input.begin(), input.end(), comp);
    
    return input[0].numInspected * input[1].numInspected;
}

int main(){
    auto input = getInput();
    
    /* for(auto& i : input){
        i.print();
        std::cout<<"\n\n\n\n";
    } */
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}


//Part 1: 61005
//Part 2: 20567144694

//Debug
//TotalMilliseconds : 450.4432
//Release
//TotalMilliseconds : 42.6206