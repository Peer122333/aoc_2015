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

/**
 * @brief Liest den gesamten Inhalt einer Datei und gibt ihn als std::string zurück.
 * @param filepath Der Pfad zur Datei, die gelesen werden soll.
 * @return Der Inhalt der Datei als String. Gibt einen leeren String zurück, falls die Datei nicht geöffnet werden kann.
 */
std::string file_to_string(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {  // Überprüft, ob die Datei erfolgreich geöffnet wurde
        throw std::runtime_error("Fehler: Datei konnte nicht geöffnet werden: " + filepath);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();  // Liest den gesamten Dateiinhalt in den Stream
    return buffer.str();
}

/**
 * @brief Zählt die Stockwerke basierend auf den Zeichen '(' und ')'.
 * @param input Der String mit den Stockwerkanweisungen.
 * @return Das finale Stockwerk von Santa.
 */
int count_floors(const std::string& input) {
    int santa_floor = 0;

    for (char ch : input) {  // Verwende einen Range-Based-For-Loop
        if (ch == '(') {
            ++santa_floor;  // Erhöhe den Stockwerkzähler
        } else if (ch == ')') {
            --santa_floor;  // Verringere den Stockwerkzähler
        }
    }

    return santa_floor;  // Rückgabe des finalen Stockwerks
}

/**
 * @brief Führt die Berechnung des Stockwerks aus basierend auf einer Datei.
 */
void aoc1() {
    const std::string filepath = "aoc1_floor_plan.txt";
    try {
        std::string input = file_to_string(filepath);  // Lese den Dateiinhalt
        if (input.empty()) {
            throw std::runtime_error("Fehler: Datei ist leer: " + filepath);
        }

        int santa_floor = count_floors(input);  // Berechne das finale Stockwerk
        std::cout << "Das finale Stockwerk von Santa ist: " << santa_floor << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;  // Gibt eine Fehlermeldung aus
    }
}
