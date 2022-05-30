#pragma once
#include <iostream>
#include <vector>

struct Place;
struct ProcessedPlace;
class Process{
    public:
        void getData();
        void processData();
        void handleOddOverlaps();
        void handleEvenOverlaps();
        bool contains(std::string name, std::vector<Place> vec);
        void writeData();
        char checkOverlapType(ProcessedPlace* p1, ProcessedPlace* p2);
        void sortEvens();
        void sortOdds();
    private:
        std::vector<ProcessedPlace*> _processedData;
        std::vector<Place> _rawData; 
        std::vector<ProcessedPlace*> _odds;
        std::vector<ProcessedPlace*> _evens;
};

struct ProcessedPlace{
    ProcessedPlace(std::string n, std::string t, char p, int st, int e){
        name = n;
        type = t;
        parity = p;
        start = st;
        end = e;
    }
    std::string name;
    std::string type;
    char parity;
    int start;
    int end;
    void writeData(){
        std::cout << name << " " << type << ": " << parity << " " << start << "-" << end << std::endl; 
    }
};