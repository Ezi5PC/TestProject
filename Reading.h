#pragma once
#include <iostream>
#include <vector>


struct Place;
class Reading{
    public:
        void readData(std::string fileName);
        std::string next(std::ifstream &input);
        std::vector<Place> passData();
        void writeData();
    private:
        std::vector<Place> _data;
};

struct Place{
    std::string name;
    std::string type;
    std::string firstType;
    std::string secondType;
    std::string firstStart;
    std::string firstEnd;
    std::string secondStart;
    std::string secondEnd;
    void writeData(){
        std::cout << name << " " << type << " " << firstType << " " << firstStart << " " << firstEnd << " " << secondType << " " << secondStart << " " << secondEnd << "\n";
    }
};


//17 utcanév, 18 tér típusa,21 ODD / EVEN, 22 kezdet, 23 vég, 24 ODD/EVEN,25 kezdet, 26 vég, ahol van ODD és EVEN is az MIXED