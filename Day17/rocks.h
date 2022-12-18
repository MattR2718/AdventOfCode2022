#include <vector>
#include <ranges>
#include <algorithm>

class Rock{
    protected: std::vector<std::pair<int, int>> points;
    public: int getMaxY(){
        int m = 0;
        for(auto& p : this->points){
            m = (p.second > m) ? p.second : m;
        }
        return m;
    };

    public: bool stuck = false;

    public: std::vector<std::pair<int, int>> getPoints(){ return this->points; }

    public: void shiftShape(const char c, std::vector<std::pair<int, int>>& otherPoints){
        if(c == '>'){
            for(auto& p : points){ if(p.first == 6){ return; }}

            std::vector<std::pair<int, int>> pc = this->points;
            for(auto& p : pc){p.first++;}
            for(int i = 0; i < pc.size(); i++){
                for(int j = 0; j < otherPoints.size(); j++){
                    if(pc[i] == otherPoints[j]){ return; }
                }
            }
            this->points = pc;
            //for(auto& p : points){ p.first++; }
        }else if(c == '<'){
            for(auto& p : points){ if(p.first == 0){ return; }}

            std::vector<std::pair<int, int>> pc = this->points;
            for(auto& p : pc){p.first--;}
            for(int i = 0; i < pc.size(); i++){
                for(int j = 0; j < otherPoints.size(); j++){
                    if(pc[i] == otherPoints[j]){ return; }
                }
            }
            this->points = pc;
            //for(auto& p : points){ p.first--; }
        }else{
            std::cout<<"ERROR UNKNOWN INPUT INTO SHIFT: "<<c<<'\n';
        }
    }

    public: void dropShape(std::vector<std::pair<int, int>>& otherPoints){
        std::vector<std::pair<int, int>> pc = this->points;
        for(auto& p : pc){ p.second--;}

        for(int i = 0; i < pc.size(); i++){
            for(int j = 0; j < otherPoints.size(); j++){
                if(pc[i] == otherPoints[j]){ this->stuck = true; return; }
            }
        }
        this->points = pc;
        for(auto& p : this->points){
            if(p.second == 0){ this->stuck = true; }
        }
    }
};

class Flat_1 : Rock{

public:
    //std::vector<std::pair<int, int>> points;
    Flat_1(int y){
        this->points.emplace_back(std::pair(2, y));
        this->points.emplace_back(std::pair(3, y));
        this->points.emplace_back(std::pair(4, y));
        this->points.emplace_back(std::pair(5, y));
    };

    int getMy(){ return this->getMaxY(); }
    auto getPs(){ return this->getPoints(); }
    auto getStuck(){ return this->stuck; }
    auto shift(const char c, std::vector<std::pair<int, int>>& otherPoints){ this->shiftShape(c, otherPoints); }
    void drop(std::vector<std::pair<int, int>>& otherPoints){ this->dropShape(otherPoints); }
};

class Cross_2 : Rock{
    public:
    //std::vector<std::pair<int, int>> points;
    Cross_2(int y){
        this->points.emplace_back(std::pair(3, y + 2));
        this->points.emplace_back(std::pair(2, y + 1));
        this->points.emplace_back(std::pair(3, y + 1));
        this->points.emplace_back(std::pair(4, y + 1));
        this->points.emplace_back(std::pair(3, y));
    };

    int getMy(){ return this->getMaxY(); }
    auto getPs(){ return this->getPoints(); }
    auto getStuck(){ return this->stuck; }
    auto shift(const char c, std::vector<std::pair<int, int>>& otherPoints){ this->shiftShape(c, otherPoints); }
    void drop(std::vector<std::pair<int, int>>& otherPoints){ this->dropShape(otherPoints); }

};

class L_3 : Rock{
    public:
    //std::vector<std::pair<int, int>> points;
    L_3(int y){
        this->points.emplace_back(std::pair(2, y));
        this->points.emplace_back(std::pair(3, y));
        this->points.emplace_back(std::pair(4, y));
        this->points.emplace_back(std::pair(4, y + 1));
        this->points.emplace_back(std::pair(4, y + 2));
    };

    int getMy(){ return this->getMaxY(); }
    auto getPs(){ return this->getPoints(); }
    auto getStuck(){ return this->stuck; }
    auto shift(const char c, std::vector<std::pair<int, int>>& otherPoints){ this->shiftShape(c, otherPoints); }
    void drop(std::vector<std::pair<int, int>>& otherPoints){ this->dropShape(otherPoints); }

};

class Tall_4 : Rock{
    public:
    //std::vector<std::pair<int, int>> points;
    Tall_4(int y){
        this->points.emplace_back(std::pair(2, y));
        this->points.emplace_back(std::pair(2, y + 1));
        this->points.emplace_back(std::pair(2, y + 2));
        this->points.emplace_back(std::pair(2, y + 3));
    };

    int getMy(){ return this->getMaxY(); }
    auto getPs(){ return this->getPoints(); }
    auto getStuck(){ return this->stuck; }
    auto shift(const char c, std::vector<std::pair<int, int>>& otherPoints){ this->shiftShape(c, otherPoints); }
    void drop(std::vector<std::pair<int, int>>& otherPoints){ this->dropShape(otherPoints); }

};

class Square_5 : Rock{
    public:
    //std::vector<std::pair<int, int>> points;
    Square_5(int y){
        this->points.emplace_back(std::pair(2, y));
        this->points.emplace_back(std::pair(2, y + 1));
        this->points.emplace_back(std::pair(3, y));
        this->points.emplace_back(std::pair(3, y + 1));
    };

    int getMy(){ return this->getMaxY(); }
    auto getPs(){ return this->getPoints(); }
    auto getStuck(){ return this->stuck; }
    auto shift(const char c, std::vector<std::pair<int, int>>& otherPoints){ this->shiftShape(c, otherPoints); }
    void drop(std::vector<std::pair<int, int>>& otherPoints){ this->dropShape(otherPoints); }

};