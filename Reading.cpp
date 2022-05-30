#include "Reading.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void Reading::readData(std::string fileName){
    std::ifstream input(fileName);
    std::string line;
    getline(input, line);
    Place p;
    std::string splitOn = ",";
    std::string sstring;
    int dataCounter;
    while(line != ""){
        dataCounter = 0;
        while(dataCounter < 26){
            sstring = line.substr(0, line.find(splitOn));
            switch(dataCounter){
                case 16:
                    p.name = sstring;
                    break;
                case 17:
                    p.type = sstring;
                    break;
                case 20:
                    p.firstType = sstring;
                    break;
                case 21:
                    p.firstStart = sstring;
                    break;
                case 22:    
                    p.firstEnd = sstring;
                    break;
                case 23:                 
                    p.secondType = sstring;
                    break;
                case 24:
                    p.secondStart = sstring;
                    break;
                case 25:
                    p.secondEnd = sstring;
                    break;
            }
            dataCounter++;
            line.erase(0, line.find(splitOn) + splitOn.length());
        }
        if (!(p.name == "" || (p.firstStart == "0" && p.firstEnd == "0" && p.secondStart == "0" && p.secondEnd == "0"))){
            p.name.erase(remove(p.name.begin(), p.name.end(), '"'), p.name.end());
            p.type.erase(remove(p.type.begin(), p.type.end(), '"'), p.type.end());
            p.firstType.erase(remove(p.firstType.begin(), p.firstType.end(), '"'), p.firstType.end());
            p.secondType.erase(remove(p.secondType.begin(), p.secondType.end(), '"'), p.secondType.end());
            _data.push_back(p);
        }
        getline(input, line);
    }
}

/*std::string Reading::next(std::ifstream &input){
    std::string line;
    getline(input, line);
    return line;
}*/
std::vector<Place> Reading::passData(){
    return _data;
}

void Reading::writeData(){
    for (Place p : _data){
        p.writeData();
    }
}


//17 utcanév, 18 tér típusa,21 ODD / EVEN, 22 kezdet, 23 vég, 24 ODD/EVEN,25 kezdet, 26 vég, ahol van ODD és EVEN is az MIXED