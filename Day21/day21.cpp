#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>

struct Monkey{
    std::string name;
    int64_t value;
    std::string m1;
    char instr;
    std::string m2;
    friend std::ostream& operator<<(std::ostream& os, const Monkey& m);
};

std::ostream& operator<<(std::ostream& os, const Monkey& m){
    if(m.value != 9223372036854775807LL){
        os <<"  "<<m.name<<": "<<m.value;
    }else{
        os <<"  "<<m.name<<": "<<m.m1<<' '<<m.instr<<' '<<m.m2;
    }
    return os;
}

auto getInput(){
    std::string linetxt;
    std::vector<Monkey> out;
    while (std::getline(std::cin, linetxt)){
        std::vector<std::string> temp;
        std::string token;
        std::stringstream ss(linetxt);
        while(std::getline(ss, token, ' ')){
            temp.push_back(token);
        }
        if(temp.size() == 2){
            out.emplace_back(Monkey{temp[0].substr(0, 4), std::stoll(temp[1])});
        }else{
            out.emplace_back(Monkey{temp[0].substr(0, 4), 9223372036854775807LL, temp[1], temp[2][0], temp[3]});
        }
    }
    return out;
}

int64_t getVal1(const int i, std::vector<Monkey>& monkeys){
    auto findMonkey = [&](const std::string& str){
        for(int j = 0; j < monkeys.size(); j++){
            if(monkeys[j].name == str){ return j; }
        }
        return -1;
    };

    if(monkeys[i].value == 9223372036854775807LL){
        int m1 = findMonkey(monkeys[i].m1);
        int m2 = findMonkey(monkeys[i].m2);
        switch(monkeys[i].instr){
            case '+':{
                monkeys[i].value = getVal1(m1, monkeys) + getVal1(m2, monkeys);
                break;
            }
            case '-':{
                monkeys[i].value = getVal1(m1, monkeys) - getVal1(m2, monkeys);
                break;
            }
            case '/':{
                monkeys[i].value = getVal1(m1, monkeys) / getVal1(m2, monkeys);
                break;
            }
            case '*':{
                monkeys[i].value = getVal1(m1, monkeys) * getVal1(m2, monkeys);
                break;
            }
            default:{
                std::cout<<"ERROR UNKNOWN INSTRUCTION: "<<monkeys[i].instr<<'\n';
            }
        }
    }

    return monkeys[i].value;
}


int64_t getVal2(const int i, std::vector<Monkey>& monkeys, int64_t n, int64_t& v1, int64_t& v2){
    auto findMonkey = [&](const std::string& str){
        for(int j = 0; j < monkeys.size(); j++){
            if(monkeys[j].name == str){ return j; }
        }
        return -2;
    };

    if(monkeys[i].name == "root"){
        int m1 = findMonkey(monkeys[i].m1);
        int m2 = findMonkey(monkeys[i].m2);
        v1 = getVal2(m1, monkeys, n, v1, v2); v2 = getVal2(m2, monkeys, n, v1, v2);
        return 1;
    }

    if(monkeys[i].name == "humn"){ 
        monkeys[i].value = n;
    }else

    if(monkeys[i].value == 9223372036854775807LL){
        int m1 = findMonkey(monkeys[i].m1);
        int m2 = findMonkey(monkeys[i].m2);
        switch(monkeys[i].instr){
            case '+':{
                monkeys[i].value = getVal2(m1, monkeys, n, v1, v2) + getVal2(m2, monkeys, n, v1, v2);
                break;
            }
            case '-':{
                monkeys[i].value = getVal2(m1, monkeys, n, v1, v2) - getVal2(m2, monkeys, n, v1, v2);
                break;
            }
            case '/':{
                monkeys[i].value = getVal2(m1, monkeys, n, v1, v2) / getVal2(m2, monkeys, n, v1, v2);
                break;
            }
            case '*':{
                monkeys[i].value = getVal2(m1, monkeys, n, v1, v2) * getVal2(m2, monkeys, n, v1, v2);
                break;
            }
            default:{
                std::cout<<"ERROR UNKNOWN INSTRUCTION: "<<monkeys[i]<<'\n';
            }
        }
    }

    return monkeys[i].value;
}

template<typename T>
auto run1(T input){
    auto findMonkey = [&](const std::string& str){
        for(int j = 0; j < input.size(); j++){
            if(input[j].name == str){ return j; }
        }
        return -1;
    };
    int r = findMonkey("root");

    return getVal1(r, input);
}

template<typename T>
auto run2(T input){
    auto findMonkey = [&](const std::string& str){
        for(int j = 0; j < input.size(); j++){
            if(input[j].name == str){ return j; }
        }
        return -1;
    };
    int r = findMonkey("root");

    /*
    As number shouted increases, value decreases
    556
    30974319006394 != 12725480108701
    557
    30974319006377 != 12725480108701
    558
    30974319006377 != 12725480108701
    559
    30974319006360 != 12725480108701
    560
    30974319006360 != 12725480108701
    561
    30974319006360 != 12725480108701
    562
    30974319006343 != 12725480108701
    563
    30974319006343 != 12725480108701
    564
    30974319006343 != 12725480108701
    565
    30974319006326 != 12725480108701
    566
    30974319006326 != 12725480108701    
    */

    int64_t num;
    int64_t fp = 0; int64_t bp = 10000000000000; int64_t mp = (bp - fp) / 2 + fp;
    int64_t v1f = 0; int64_t v2f = 0;
    int64_t v1b = 0; int64_t v2b = 0;
    int64_t v1m = 0; int64_t v2m = 0;
    //std::cout<<fp<<' '<<mp<<' '<<bp<<"    ("<<v1f<<", "<<v2f<<")  "<<"    ("<<v1m<<", "<<v2m<<")  "<<"    ("<<v1b<<", "<<v2b<<")  \n";
    do{
        auto msf = input;
        auto msb = input;
        auto msm = input;
        num = getVal2(r, msf, fp, v1f, v2f);
        num = getVal2(r, msb, bp, v1b, v2b);
        num = getVal2(r, msm, mp, v1m, v2m);
        //if(v1f == v2f){ return fp; }
        //if(v1b == v2b){ return bp; }
        if(bp-fp < 1000){ break; }
        if(v1m == v2m){ return mp; }
        //Test has opposite relationship to input
        if(input[0].name == "root"){
            if(v1m < v2m){ fp = mp; mp = ((bp - fp) / 2) + fp; }
            else{ bp = mp; mp = (bp - fp) / 2; }
        }else{
            if(v1m > v2m){ fp = mp; mp = ((bp - fp) / 2) + fp; }
            else{ bp = mp; mp = (bp - fp) / 2; }
        }
        //std::cout<<fp<<' '<<mp<<' '<<bp<<"    ("<<v1f<<", "<<v2f<<")  "<<"    ("<<v1m<<", "<<v2m<<")  "<<"    ("<<v1b<<", "<<v2b<<")  \n";
    }while(1);

    for(int64_t n = fp; n <= bp; n++){
        auto mon = input;
        int64_t v1 = 0;
        int64_t v2 = 0;
        num = getVal2(r, mon, n, v1, v2);
        if(v1 == v2){ return n; }
    }


    return num;
}

int main(){
    auto input = getInput();
    
    for(auto& i : input){
        std::cout<<i<<'\n';
    }
   
    std::cout<<"Part 1: "<<run1(input)<<'\n';
    std::cout<<"Part 2: "<<run2(input)<<'\n';
}

//Part 1: 43699799094202
//Part 2: 3375719472770

//Binary search broke when close to the answer, pattern of increasing value, decrease number appears not to hold when close
//3375719472772 too high

/*
Release:
    Days              : 0
    Hours             : 0
    Minutes           : 0
    Seconds           : 21
    Milliseconds      : 607
    Ticks             : 216079305
    TotalDays         : 0.000250091788194444
    TotalHours        : 0.00600220291666667
    TotalMinutes      : 0.360132175
    TotalSeconds      : 21.6079305
    TotalMilliseconds : 21607.9305
*/