//
//  aoc3.cpp
//  AOC2015
//
//  Created by Peer Orzelek on 29.12.24.
//

/*
     --- Day 3: Perfectly Spherical Houses in a Vacuum ---
     Santa is delivering presents to an infinite two-dimensional grid of houses.

     He begins by delivering a present to the house at his starting location, and then an elf at the North Pole calls him 
     via radio and tells him where to move next. Moves are always exactly one house to the north (^), south (v), east (>), or west (<).
     After each move, he delivers another present to the house at his new location.

     However, the elf back at the north pole has had a little too much eggnog, and so his directions are a little off, 
 and Santa ends up visiting some houses more than once. How many houses receive at least one present?

     For example:

     > delivers presents to 2 houses: one at the starting location, and one to the east.
     ^>v< delivers presents to 4 houses in a square, including twice to the house at his starting/ending location.
     ^v^v^v^v^v delivers a bunch of presents to some very lucky children at only 2 houses.
 */

#include "aoc3.hpp"
#include <iostream>      // Für Standard-Ein- und Ausgabe
#include <fstream>       // Für Dateioperationen wie ifstream und ofstream
#include <sstream>       // Für ostringstream
#include <stdexcept>     // Für runtime_error
#include <string>        // Für std::string
#include <vector>        // Für std::vector
#include <map>           // Für std::map
#include <utility>       // Für std::pair

/* 
 Starting thoughts:
 ------------------
 function to read the directions

 How should we map out the "field"?
 just use x,y coordinates (x,y) | if ^ y++ | if v y-- | if < x-- | if > x++ |

 for each step save coordinates to a list of 2-dimensional vectors

 use a counter which only goes up if the coordinates are not already in the list --> check after each step
*/

/**
 * @brief Liest den Inhalt einer Datei in einen String.
 * @param filepath Der Pfad zur Eingabedatei.
 * @return Der gesamte Dateiinhalt als std::string.
 * @throws std::runtime_error, wenn die Datei nicht geöffnet werden kann.
 */
std::string txt_to_string(const std::string& filepath){
    std::ifstream file(filepath);
    if (!file){
        throw std::runtime_error("Fehler: Datei konnte nicht geöffnet werden: " + filepath);
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/**
 * @brief Berechnet alle Positionen und die Anzahl der Besuche jedes Hauses basierend auf einer Bewegungsanweisung.
 * @param roadmap Ein String mit Bewegungsanweisungen ('^', 'v', '<', '>').
 * @return Ein std::vector mit allen besuchten Positionen in der Reihenfolge der Bewegung.
 */
std::vector<std::pair<int, int>> get_next_move_from_elf(const std::string& roadmap){
    std::vector<std::pair<int, int>> all_positions; // Liste der besuchten Positionen
    std::pair<int, int> curr_coor{0,0}; // Startposition
    
    std::map<std::pair<int, int>, int> visited_houses; // Map für Koordinaten und Anzahl der Besuche
    visited_houses[curr_coor] = 1; // Startposition als erster Hausbesuch
    
    all_positions.push_back(curr_coor); //Anfangsposition hinzufügen
    
    for (char ch : roadmap){
        if (ch == '^'){
            curr_coor.second++; // y - Koordinate um eins erhöhen
        } else if (ch == 'v'){
            curr_coor.second--; // y - Koordinate um eins verringern
        } else if (ch == '<'){
            curr_coor.first--; // y - Koordinate um eins verringern
        } else if (ch == '>'){
            curr_coor.first++; // y - Koordinate um eins verringern
        } else {
            std::cerr << "No useful command from the drunken elf." << std::endl;
            continue; //Ungültige Befehle überspringen
        }
        all_positions.push_back(curr_coor); // Neue Position hinzufügen
        visited_houses[curr_coor]++;        // Anzahl der Besuche erhöhen
        
        }

    // Ausgabe der Besuchszahlen pro Haus
    std::cout << "Besuchte Häuser und Besuchszahlen:\n";
    for (const auto& [coords, visits] : visited_houses) {
        std::cout << "Haus (" << coords.first << ", " << coords.second << ") wurde " << visits << " mal besucht.\n";
    }

    // Anzahl der verschiedenen besuchten Häuser
    std::cout << "\nVerschiedene Häuser insgesamt besucht: " << visited_houses.size() << "\n";
    
    return all_positions;
};

/*
--- Part Two ---
The next year, to speed up the process, Santa creates a robot version of himself, 
 Robo-Santa, to deliver presents with him.

Santa and Robo-Santa start at the same location (delivering two presents to the same starting house), 
 then take turns moving based on instructions from the elf, who is eggnoggedly reading from
 the same script as the previous year.

This year, how many houses receive at least one present?
*/

/**
 * @brief Berechnet die Positionen und Anzahl der Besuche jedes Hauses basierend auf alternierenden Bewegungen von Santa und Robo-Santa.
 * @param roadmap Ein String mit Bewegungsanweisungen ('^', 'v', '<', '>').
 * @return Ein std::vector mit allen besuchten Positionen in der Reihenfolge der Bewegung.
 */
std::vector<std::pair<int, int>> alternating_moves_with_robo_santa(const std::string& roadmap) {
    std::vector<std::pair<int, int>> all_positions; // Liste der besuchten Positionen
    std::pair<int, int> curr_coor_santa{0, 0};      // Startposition von Santa
    std::pair<int, int> curr_coor_robo_santa{0, 0}; // Startposition von Robo-Santa

    std::map<std::pair<int, int>, int> visited_houses; // Map für Koordinaten und Anzahl der Besuche
    visited_houses[curr_coor_santa] = 2;              // Startposition erhält zwei Besuche (Santa und Robo-Santa)

    all_positions.push_back(curr_coor_santa); // Anfangsposition hinzufügen

    // Abwechselnd Santa und Robo-Santa bewegen
    bool is_santas_turn = true;
    for (char ch : roadmap) {
        if (is_santas_turn) {
            // Bewegung von Santa
            if (ch == '^') {
                curr_coor_santa.second++;
            } else if (ch == 'v') {
                curr_coor_santa.second--;
            } else if (ch == '<') {
                curr_coor_santa.first--;
            } else if (ch == '>') {
                curr_coor_santa.first++;
            } else {
                std::cerr << "Ungültiger Befehl vom Elf: " << ch << std::endl;
                continue; // Ungültige Befehle überspringen
            }
            all_positions.push_back(curr_coor_santa);   // Position von Santa speichern
            visited_houses[curr_coor_santa]++;         // Besuchszahl für Santa erhöhen
        } else {
            // Bewegung von Robo-Santa
            if (ch == '^') {
                curr_coor_robo_santa.second++;
            } else if (ch == 'v') {
                curr_coor_robo_santa.second--;
            } else if (ch == '<') {
                curr_coor_robo_santa.first--;
            } else if (ch == '>') {
                curr_coor_robo_santa.first++;
            } else {
                std::cerr << "Ungültiger Befehl vom Elf: " << ch << std::endl;
                continue; // Ungültige Befehle überspringen
            }
            all_positions.push_back(curr_coor_robo_santa); // Position von Robo-Santa speichern
            visited_houses[curr_coor_robo_santa]++;        // Besuchszahl für Robo-Santa erhöhen
        }

        // Abwechseln der Züge
        is_santas_turn = !is_santas_turn;
    }

    // Ausgabe der Besuchszahlen pro Haus
    std::cout << "Besuchte Häuser und Besuchszahlen:\n";
    for (const auto& [coords, visits] : visited_houses) {
        std::cout << "Haus (" << coords.first << ", " << coords.second << ") wurde " << visits << " mal besucht.\n";
    }

    // Anzahl der verschiedenen besuchten Häuser
    std::cout << "\nVerschiedene Häuser insgesamt besucht: " << visited_houses.size() << "\n";

    return all_positions;
}





// --- Main Function ---
/**
 * @brief Hauptfunktion für Day 3 des Advent of Code 2015.
 * @return 0 bei erfolgreicher Ausführung.
 */
int aoc3() {
    try {
        // Pfad zur Eingabedatei mit den Bewegungsanweisungen
        const std::string filepath = "radio_moves_from_eggnog_elf.txt";

        // Dateiinhalt in String einlesen
        std::string directions = txt_to_string(filepath);

        // Bewegungen analysieren
        // std::vector<std::pair<int, int>> visited_positions = get_next_move_from_elf(directions);
        std::vector<std::pair<int, int>> visited_positions = alternating_moves_with_robo_santa(directions);
        
        // Zusätzliche Ausgabe: Liste der besuchten Positionen
//        std::cout << "\nAlle besuchten Positionen in Reihenfolge:\n";
//        for (const auto& pos : visited_positions) {
//            std::cout << "(" << pos.first << ", " << pos.second << ")\n";
//        }
        
    } catch (const std::runtime_error& e) {
        std::cerr << "Fehler: " << e.what() << std::endl;
        return 1; // Fehlercode
    }

    return 0; // Erfolg
}
