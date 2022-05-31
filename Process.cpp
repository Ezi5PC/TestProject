#include "Reading.h"
#include "Process.h"
#include <iostream>
#include <algorithm>

void Process::getData(){
    Reading r;
    r.readData("network.mid");
    _rawData = r.passData();
}

void Process::processData(){
    _odds = sort("O");
    _evens = sort("E");
    handleOverlaps(_evens);
    handleOverlaps(_odds);
}

void Process::writeData(){
    for(ProcessedPlace p : _processedData){
        p.writeData();
    }
}

std::vector<ProcessedPlace> Process::sort(std::string type){
    std::vector<ProcessedPlace> result;
    for (Place p : _rawData){
        if (p.firstType == type && contains(p.name, _rawData) == 1){
            result.push_back(ProcessedPlace(p.name, p.type, type, stoi(p.firstStart), stoi(p.firstEnd)));
        }
        else if (p.secondType == type && contains(p.name, _rawData) == 1){
            result.push_back(ProcessedPlace(p.name, p.type, type, stoi(p.secondStart), stoi(p.secondEnd)));
        }
    }
    return result;
}

void Process::handleOverlaps(std::vector<ProcessedPlace> vec){
    int duplicates;
    for (int i = 0; i < vec.size();i++){
        duplicates = 0;
        for(int j = i+1; j < vec.size();j++){
            if (vec[i].name == vec[j].name){
                switch(checkOverlapType(vec[i], vec[j])){
                    case overlapType::BETWEEN:
                        if(!(contains(vec[j], _processedData))){
                            _processedData.push_back(vec[j]);
                        }
                        break;
                    case overlapType::LOWER:
                        vec[j].start = vec[i].start;
                        if(!(contains(vec[j], _processedData))){
                            _processedData.push_back(vec[j]);
                        }
                        break;
                    case overlapType::HIGHER:
                        vec[j].start = vec[i].end;
                        if(!(contains(vec[j], _processedData))){
                            _processedData.push_back(vec[j]);
                        }
                        break;
                    case overlapType::WIDER:
                        if(!(contains(vec[i], _processedData))){
                            _processedData.push_back(vec[i]);
                        }
                        break;
                    case overlapType::EQUAL:
                        if(!(contains(vec[i], _processedData))){
                            _processedData.push_back(vec[i]);
                        }
                        break;
                }
            }
        }
    }
}

bool Process::contains(ProcessedPlace place, std::vector<ProcessedPlace> vec){
    for(ProcessedPlace p : vec){
        if(place == p){
            return 1;
        }
    }
    return 0;
}

bool Process::contains(std::string name, std::vector<Place> vec){
    int howManyTimes = 0;
    for(Place p : vec){
        if (p.name == name){
            howManyTimes++;
            if(howManyTimes >= 2){
                return 1;
            }
        }
    }
    return 0;
}

Process::overlapType Process::checkOverlapType(ProcessedPlace p1, ProcessedPlace p2){
    if (p1.start < p2.start && p2.end < p1.end){
        return overlapType::BETWEEN;
    }
    if (p2.start < p1.start && p2.end < p1.end && p1.start < p2.end){
        return overlapType::LOWER;
    }
    if (p1.start < p2.start && p1.end < p2.end && p2.start < p1.end){
        return overlapType::HIGHER;
    }
    if (p2.start < p1.start && p1.end < p2.end){
        return overlapType::WIDER;
    }
    if (p2.start == p1.start && p2.end == p1.end){
        return overlapType::EQUAL;
    }
    return overlapType::NO;
}