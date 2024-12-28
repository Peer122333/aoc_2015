//
//  aoc1.cpp
//  AOC2015
//
//  Created by Peer Orzelek on 28.12.24.
//

//--- Day 1: Not Quite Lisp ---
//Santa was hoping for a white Christmas, but his weather machine's "snow" function is powered by stars, and he's fresh out! To save Christmas, he needs you to collect fifty stars by December 25th.
//
//Collect stars by helping Santa solve puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!
//
//Here's an easy puzzle to warm you up.
//
//Santa is trying to deliver presents in a large apartment building, but he can't find the right floor - the directions he got are a little confusing. He starts on the ground floor (floor 0) and then follows the instructions one character at a time.
//
//An opening parenthesis, (, means he should go up one floor, and a closing parenthesis, ), means he should go down one floor.
//
//The apartment building is very tall, and the basement is very deep; he will never find the top or bottom floors.
//
//For example:
//
//  (()) and ()() both result in floor 0.
//  ((( and (()(()( both result in floor 3.
//  ))((((( also results in floor 3.
//  ()) and ))( both result in floor -1 (the first basement level).
//  ))) and )())()) both result in floor -3.
//  To what floor do the instructions take Santa?

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "aoc1.hpp"

std::string file_to_string(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Datei konnte nicht geöffnet werden." << std::endl;
        return "";  // Rückgabe eines leeren Strings bei Fehler
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // Liest den gesamten Inhalt der Datei in den buffer
    file.close();  // Schließe die Datei
    return buffer.str();  // Konvertiere den Inhalt zu einem std::string und gebe ihn zurück
}

int count_floors(const std::string& input) {
    int santa_floor = 0;
    for (int i = 0; i < input.length(); i++) {
        char ch = input[i];
        if (ch == '(') {
            santa_floor++;  // Erhöhe den Stockwerkzähler bei '('
        } else if (ch == ')') {
            santa_floor--;  // Verringere den Stockwerkzähler bei ')'
        }
    }
    return santa_floor;  // Rückgabe des finalen Stockwerks
}

void aoc1(const std::string& filename) {
    std::string input = file_to_string(filename); // Lese Dateiinhalt
//    if (input.empty()) {
//        std::cerr << "Fehler beim Lesen der Datei oder Datei ist leer." << std::endl;
//        return;
//    }

    int santa_floor = count_floors(input);  // Berechne das endgültige Stockwerk
    std::cout << "The ending floor of Santa is: " << santa_floor << std::endl;
}
