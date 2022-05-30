#include <iostream>
#include <fstream>
#include <sstream>
#include "Process.h"
#include "Reading.h"

int main(){
    Process p;
    p.getData();
    p.processData();
    p.writeData();
    return 0;
}