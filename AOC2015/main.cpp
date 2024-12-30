//
//  main.cpp
//  AOC2015
//
//  Created by Peer Orzelek on 28.12.24.

#include <iostream>
#include <fstream>
#include <sstream>
#include "aoc1.hpp"
#include "aoc2.hpp"
#include "aoc3.hpp"
#include "aoc4.hpp"

int main(int argc, const char * argv[]) {
    std::cout << "AOC1: " << std::endl;
    std::cout << "################################################" << std::endl;
//  DAY 1 - ####################
    aoc1();
    
    
    
    std::cout << "AOC2: " << std::endl;
    std::cout << "################################################" << std::endl;
//  DAY 2 - ####################
    aoc2();

    std::cout << "AOC3: " << std::endl;
    std::cout << "################################################" << std::endl;
//  DAY 3 - ####################
    aoc3();
    return 0;
}
