//
//  main.cpp
//  AOC2015
//
//  Created by Peer Orzelek on 28.12.24.

#include <iostream>
#include <fstream>
#include <sstream>
#include "aoc1.hpp"

int main(int argc, const char * argv[]) {
    std::cout << "AOC1: " << std::endl;
    std::cout << "################################################" << std::endl;
    
//    TRYING TO DEBUG FILE NOT FOUND; TXT FILE WAS SECRETELY SAVED IN ANOTHER DIR
    
//    std::ifstream datei("aoc1_floor_plan.txt");
//    std::string zeile;
//    if (datei.is_open()) {
//        while (std::getline(datei, zeile)) {
//            std::cout << zeile << std::endl;
//        }
//        datei.close();
//    } else{
//        std::cout << "Datei nicht öffenbar" << std::endl;
//    }
    
    aoc1("aoc1_floor_plan.txt");
    
    return 0;
}
