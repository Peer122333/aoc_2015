//
//  aoc2.cpp
//  AOC2015
//
//  Created by Peer Orzelek on 28.12.24.
//

#include "aoc2.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

//    --- Day 2: I Was Told There Would Be No Math ---
//    The elves are running low on wrapping paper, and so they need to submit an order for more. They have a list of the dimensions (length l, width w, and height h) 
//    of each   present, and only want to order exactly as much as they need.
//
//    Fortunately, every present is a box (a perfect right rectangular prism), which makes calculating the required wrapping paper for each gift a little easier: 
//    find the surface area of the box, which is 2*l*w + 2*w*h + 2*h*l. The elves also need a little extra paper for each present: the area of the smallest side.
//
//    For example:
//
//    A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52 square feet of wrapping paper plus 6 square feet of slack, for a total of 58 square feet.
//    A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42 square feet of wrapping paper plus 1 square foot of slack, for a total of 43 square feet.
//    All numbers in the elves' list are in feet. How many total square feet of wrapping paper should they order?

// --- Helper Functions ---

/**
 * @brief Calculates the area of the smallest side of a box.
 * @param l Length of the box.
 * @param w Width of the box.
 * @param h Height of the box.
 * @return Area of the smallest side.
 */
double area_of_smallest_side(double l, double w, double h) {
    return std::min({l * w, w * h, h * l});  // Kleinste Seitenfläche ermitteln
}

/**
 * @brief Calculates the surface area of a box.
 * @param l Length of the box.
 * @param w Width of the box.
 * @param h Height of the box.
 * @return Total surface area of the box.
 */
double surface_area_of_box(double l, double w, double h) {
    return 2 * (l * w + w * h + h * l);  // Oberfläche berechnen
}

/**
 * @brief Calculates the total wrapping paper needed for a box.
 * @param l Length of the box.
 * @param w Width of the box.
 * @param h Height of the box.
 * @return Total wrapping paper needed, including slack.
 */
double total_wrapping_paper(double l, double w, double h) {
    return surface_area_of_box(l, w, h) + area_of_smallest_side(l, w, h);
}

/**
 * @brief Reads the entire content of a file and returns it as a string.
 * @param filepath Path to the file.
 * @return The file's content as a string. Returns an empty string if the file cannot be opened.
 */
std::string package_list_to_string(const std::string& filepath) {
    std::ifstream mypackage_list(filepath);
    if (!mypackage_list.is_open()) {
        std::cerr << "Error: Could not open file: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << mypackage_list.rdbuf();
    return buffer.str();
}

/**
 * @brief Parses a single line in the format "LxWxH" and extracts the dimensions.
 * @param line String containing the dimensions of a box in the format "LxWxH".
 * @return A tuple containing the dimensions (length, width, height).
 * @throws std::invalid_argument if the line is not in the correct format.
 */
std::tuple<int, int, int> parse_line(const std::string& line) {
    int l, w, h;
    char x;  // Zwischenspeicher für das Trennzeichen
    std::istringstream stream(line);

    if (stream >> l >> x >> w >> x >> h) {
        return {l, w, h};
    } else {
        throw std::invalid_argument("Invalid line format: " + line);
    }
}

/**
 * @brief Calculates the total wrapping paper needed for all boxes listed in a file.
 * @param filepath Path to the file containing the list of boxes.
 * @return Total wrapping paper needed.
 */
double calculate_total_paper(const std::string& filepath) {
    std::string data = package_list_to_string(filepath);
    if (data.empty()) {
        return 0;  // Keine Daten vorhanden
    }

    std::istringstream input_string_stream(data);
    std::string line;
    double total_paper = 0;

    while (std::getline(input_string_stream, line)) {
        try {
            auto [l, w, h] = parse_line(line);  // Parse die Maße
            total_paper += total_wrapping_paper(l, w, h);  // Fläche berechnen und summieren
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;  // Fehler ausgeben
        }
    }

    return total_paper;
}


/*
    --- Part Two ---
    The elves are also running low on ribbon. Ribbon is all the same width,
    so they only have to worry about the length they need to order, which they would again like to be exact.

    The ribbon required to wrap a present is the shortest distance around its sides, or the smallest perimeter of any one face.
    Each present also requires a bow made out of ribbon as well; the feet of ribbon required for the perfect 
    bow is equal to the cubic feet of volume of the present.
    Don't ask how they tie the bow, though; they'll never tell.

    For example:

    A present with dimensions 2x3x4 requires 2+2+3+3 = 10 feet of ribbon to wrap the present plus 2*3*4 = 24 feet of ribbon for the bow, for a total of 34 feet.
    A present with dimensions 1x1x10 requires 1+1+1+1 = 4 feet of ribbon to wrap the present plus 1*1*10 = 10 feet of ribbon for the bow, for a total of 14 feet.
    How many total feet of ribbon should they order?
*/

double wrap_ribbon(double l, double w, double h){
    return std::min({2*(l+w), 2*(l+h), 2*(w+h)});
}

double bow_ribbon(double l, double w, double h){
    return l*w*h;
}

double total_ribbon(double l, double w, double h){
    return wrap_ribbon(l, w, h) + bow_ribbon(l, w, h);
}

/**
 * @brief Calculates the total ribbon amount needed for all boxes listed in a file.
 * @param filepath Path to the file containing the list of boxes.
 * @return Total ribbon needed.
 */
double calculate_total_ribbon(const std::string& filepath) {
    std::string data = package_list_to_string(filepath);
    if (data.empty()) {
        return 0;  // Keine Daten vorhanden
    }

    std::istringstream input_string_stream(data);
    std::string line;
    double total_ribbon_len = 0;

    while (std::getline(input_string_stream, line)) {
        try {
            auto [l, w, h] = parse_line(line);  // Parse die Maße
            total_ribbon_len += total_ribbon(l, w, h);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;  // Fehler ausgeben
        }
    }

    return total_ribbon_len;
}


// --- Main Function ---
int aoc2() {
    const std::string filepath = "aoc2_package_dimensions.txt";  // Eingabedatei mit Paketmaßen
    double total_paper = calculate_total_paper(filepath);
    
    std::cout << "Part 1 - Wrapping Paper" << std::endl;
    if (total_paper > 0) {
        std::cout << "Total wrapping paper needed: " << std::fixed << total_paper << " square feet" << std::endl;
    } else {
        std::cerr << "No valid data found or an error occurred." << std::endl;
    }

    double total_ribbon_length = calculate_total_ribbon(filepath);
    std::cout << "Part 2 - Wrapping Ribbon" << std::endl;
    if (total_ribbon_length > 0) {
        std::cout << "Total ribbon for wrapping presents needed: " << std::fixed << total_ribbon_length << " feet" << std::endl;
    } else {
        std::cerr << "No valid data found or an error occurred." << std::endl;
    }
    return 0;
}
