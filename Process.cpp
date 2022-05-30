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
    handleOddOverlaps();
    handleEvenOverlaps();
}

void Process::writeData(){
    for(ProcessedPlace* p : _processedData){
        p->writeData();
    }
}

void Process::sortEvens(){
    for (Place p : _rawData){
        if (p.firstType == "E" && contains(p.name, _rawData) == 1){
            _evens.push_back(new ProcessedPlace(p.name, p.type, 'E', stoi(p.firstStart), stoi(p.firstEnd)));
        }
        else if (p.secondType == "E" && contains(p.name, _rawData) == 1){
            _evens.push_back(new ProcessedPlace(p.name, p.type, 'E', stoi(p.secondStart), stoi(p.secondEnd)));
        }
    }
}

void Process::sortOdds(){
    for (Place p : _rawData){
        if (p.firstType == "O" && contains(p.name, _rawData) == 1){
            _odds.push_back(new ProcessedPlace(p.name, p.type, 'O', stoi(p.firstStart), stoi(p.firstEnd)));
        }
        else if (p.secondType == "O" && contains(p.name, _rawData) == 1){
            _odds.push_back(new ProcessedPlace(p.name, p.type, 'O', stoi(p.secondStart), stoi(p.secondEnd)));
        }
    }
}

void Process::handleOddOverlaps(){
    sortOdds();
    int processed;
    for (int i = 0; i < _odds.size();i++){
        processed = 0;
        for(int j = i+1; j < _odds.size();j++){
            if (_odds[i]->name == _odds[j]->name){
                switch(checkOverlapType(_odds[i], _odds[j])){
                    case 'B':
                        delete(_odds[j]);
                        processed++;
                        break;
                    case 'L':
                        _odds[i]->start = _odds[j]->start;
                        delete(_odds[j]);
                        processed++;
                        break;
                    case 'H':
                        _odds[i]->end = _odds[j]->end;
                        delete(_odds[j]);
                        processed++;
                        break;
                    case 'A':
                        _odds[i]->start = _odds[j]->start;
                        _odds[i]->end = _odds[j]->end;
                        delete(_odds[j]);
                        processed++;
                        break;
                }
            }
        }
        if (processed > 0){
            _processedData.push_back(_odds[i]);
        }
    }
}

void Process::handleEvenOverlaps(){
    sortEvens();
    int processed;
    for (int i = 0; i < _evens.size();i++){
        processed = 0;
        for(int j = i+1; j < _evens.size();j++){
            if (_evens[i]->name == _evens[j]->name){
                switch(checkOverlapType(_evens[i], _evens[j])){
                    case 'B':
                        delete(_evens[j]);
                        processed++;
                        break;
                    case 'L':
                        _evens[i]->start = _evens[j]->start;
                        delete(_evens[j]);
                        processed++;
                        break;
                    case 'H':
                        _evens[i]->end = _evens[j]->end;
                        delete(_evens[j]);
                        processed++;
                        break;
                    case 'A':
                        _evens[i]->start = _evens[j]->start;
                        _evens[i]->end = _evens[j]->end;
                        delete(_evens[j]);
                        processed++;
                        break;
                }
            }
        }
        if (processed > 0){
            _processedData.push_back(_evens[i]);
        }
    }
}

bool Process::contains(std::string name, std::vector<Place> vec){
    int howManyTimes = 0;
    for(Place p : vec){
        if (p.name == name){
            howManyTimes++;
        }
    }
    return howManyTimes > 1;
}

char Process::checkOverlapType(ProcessedPlace* p1, ProcessedPlace* p2){
    if (p1->start < p2->start && p2->end < p1->end){
        return 'B';
    }
    if (p2->start < p1->start && p2->end < p1->end && p1->start < p2->end){
        return 'L';
    }
    if (p1->start < p2->start && p1->end < p2->end && p2->start < p1->end){
        return 'H';
    }
    if (p2->start < p1->start && p1->end < p2->end){
        return 'A';
    }
    return 'N';
}