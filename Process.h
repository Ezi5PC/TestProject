#pragma once
#include <iostream>
#include <vector>

struct Place;
struct ProcessedPlace;
class Process{
    public:
        void getData();
        void processData();
        void writeData();
    private:
        std::vector<ProcessedPlace> _processedData;
        std::vector<Place> _rawData; 
        std::vector<ProcessedPlace> _odds;
        std::vector<ProcessedPlace> _evens;
        enum overlapType{BETWEEN, HIGHER, LOWER, WIDER, EQUAL, NO};
        void handleOverlaps(std::vector<ProcessedPlace> vec);
        bool contains(std::string name, std::vector<Place> vec);
        overlapType checkOverlapType(ProcessedPlace p1, ProcessedPlace p2);
        std::vector<ProcessedPlace> sort(std::string type);
        bool contains(ProcessedPlace place, std::vector<ProcessedPlace> vec);
};

struct ProcessedPlace{
    ProcessedPlace(std::string n, std::string t, std::string p, int st, int e){
        name = n;
        type = t;
        parity = p;
        start = st;
        end = e;
    }
    std::string name;
    std::string type;
    std::string parity;
    int start;
    int end;
    void writeData(){
        std::cout << name << " " << type << ": " << parity << " " << start << "-" << end << std::endl; 
    }
    bool operator==(ProcessedPlace that){
        return (name == that.name && type == that.type && parity == that.parity && start == that.start && end == that.end); 
    }
};