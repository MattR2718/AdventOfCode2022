/*
int getBit(int num, int bitnum){
    return num & (1 << bitnum);
}

void printChamber(const std::vector<int8_t>& chamber){
    std::cout<<'\n';
    for(int i = chamber.size() - 1; i > -1; i--){
        for(int k = 6; k > -1; k--){
            if(getBit(chamber[i], k)){ std::cout<<'#'; }else{ std::cout<<'.'; }
            //if(1){ std::cout<<'#'; }else{ std::cout<<'.'; }
        }
        std::cout<<"  "<<(int)chamber[i];
        std::cout<<'\n';
    }
}
*/

/*run1
std::vector<int8_t> chamber = {0, 0, 0, 0};
    std::variant<Flat_1, Cross_2, L_3, Tall_4, Square_5> shape;
    printChamber(chamber);
    shape = Flat_1();
    std::visit([&](auto& arg){arg.addToChamber(chamber); }, shape);
    shape = Cross_2();
    std::visit([&](auto& arg){arg.addToChamber(chamber); }, shape);
    shape = L_3();
    std::visit([&](auto& arg){arg.addToChamber(chamber); }, shape);
    shape = Tall_4();
    std::visit([&](auto& arg){arg.addToChamber(chamber); }, shape);
    shape = Square_5();
    std::visit([&](auto& arg){arg.addToChamber(chamber); }, shape);
    printChamber(chamber);
*/

struct Flat_1{
    int8_t r1 = 0b0011110;
    Flat_1(){};

    void addToChamber(std::vector<int8_t>& chamber){
        while(chamber[chamber.size() - 1] + chamber[chamber.size() - 2] + chamber[chamber.size() - 3]){
            chamber.push_back(0);
        }
        chamber.push_back(r1);
    }
};

struct Cross_2{
    int8_t r1 = 0b0001000;
    int8_t r2 = 0b0011100;
    int8_t r3 = 0b0001000;
    Cross_2(){};

    void addToChamber(std::vector<int8_t>& chamber){
        while(chamber[chamber.size() - 1] + chamber[chamber.size() - 2] + chamber[chamber.size() - 3]){
            chamber.push_back(0);
        }
        chamber.push_back(r1);
        chamber.push_back(r2);
        chamber.push_back(r3);
    }

};

struct L_3{
    int8_t r1 = 0b0000100;
    int8_t r2 = 0b0000100;
    int8_t r3 = 0b0011100;
    L_3(){};

    void addToChamber(std::vector<int8_t>& chamber){
        while(chamber[chamber.size() - 1] + chamber[chamber.size() - 2] + chamber[chamber.size() - 3]){
            chamber.push_back(0);
        }
        chamber.push_back(r1);
        chamber.push_back(r2);
        chamber.push_back(r3);
    }

};

struct Tall_4{
    int8_t r1 = 0b0010000;
    int8_t r2 = 0b0010000;
    int8_t r3 = 0b0010000;
    int8_t r4 = 0b0010000;
    Tall_4(){};

    void addToChamber(std::vector<int8_t>& chamber){
        while(chamber[chamber.size() - 1] + chamber[chamber.size() - 2] + chamber[chamber.size() - 3]){
            chamber.push_back(0);
        }
        chamber.push_back(r1);
        chamber.push_back(r2);
        chamber.push_back(r3);
        chamber.push_back(r4);
    }

};

struct Square_5{
    int8_t r1 = 0b0011000;
    int8_t r2 = 0b0011000;
    Square_5(){};

    void addToChamber(std::vector<int8_t>& chamber){
        while(chamber[chamber.size() - 1] + chamber[chamber.size() - 2] + chamber[chamber.size() - 3]){
            chamber.push_back(0);
        }
        chamber.push_back(r1);
        chamber.push_back(r2);
    }

};