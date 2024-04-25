#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include "songs.h"


int main () {

    // create Songs_List class instance
    Songs_List list;

    // initialize file name
    std::string filename = "./src/spotify_songs.csv";

    // initialize song list
    list.initialize(filename);

    //prints spotify in cute font
    std::cout << std::endl;
    std::cout << "  SSS  PPPP   OO0 TTTTTTT III  FFFFF  Y   Y\n";
    std::cout << " S     P   P O   O   T     I   F       Y Y \n";
    std::cout << "  SSS  PPPP  O   O   T     I   FFFF     Y  \n";
    std::cout << "     S P     O   O   T     I   F        Y  \n";
    std::cout << "  SSS  P      OOO    T    III  F        Y   \n";

    // ask user what sort they want
    std::string sort_type;
    std::cout << std::endl;
    std::cout << "What sort would you like to use?" << std::endl;
    std::cout << "1. Merge sort" << std::endl << "2. Quick sort" << std::endl;
    std::cout << "Enter a number: ";
    std::cin >> sort_type;

    // checks for valid input from user for sort_type and allows user to try again
    while(sort_type!="1" && sort_type != "2"){
        std:: cout << "Invalid Input :(( try again" << std::endl;
        std::cout << "Enter a number: ";
        std::cin >> sort_type;
    }

    std::cout << std::endl; // skips a line

    // ask user what variable they would like to sort by
    std::string sort_by;
    std::cout << "What would you like to sort the songs by?" << std::endl;
    std::cout << "1. Track Popularity" << std::endl;
    std::cout << "2. Danceability" << std::endl;
    std::cout << "3. Energy" << std::endl;
    std::cout << "4. Key" << std::endl;
    std::cout << "5. Loudness" << std::endl;
    std::cout << "6. Mode" << std::endl;
    std::cout << "7. Speechiness" << std::endl;
    std::cout << "8. Acousticness" << std::endl;
    std::cout << "9. Instrumentalness" << std::endl;
    std::cout << "10. Liveness" << std::endl;
    std::cout << "11. Valence" << std::endl;
    std::cout << "12. Tempo" << std::endl;
    std::cout << "13. Duration (ms)" << std::endl;
    std::cout << "Enter a number: ";
    std::cin >> sort_by;

    // checks for valid input from user for sort_by and allows user to try again
    while(sort_by != "1" && sort_by != "2" && sort_by != "3" && sort_by != "4" && sort_by != "5" && sort_by != "6"
    && sort_by !="7" && sort_by != "8" && sort_by != "9" && sort_by != "10" && sort_by != "11" && sort_by != "12" &&
    sort_by != "13"){
        std:: cout << "Invalid Input :(( try again" << std::endl;
        std::cout << "Enter a number: ";
        std::cin >> sort_by;
    }

    std::cout << std::endl; // skips a line

    // asks user if they want to sort by ascending or descending
    std::string sort_order;
    std::cout << "Would you like to sort by:" << std::endl;
    std::cout << "1. Ascending order" << std::endl;
    std::cout << "2. Descending order" << std::endl;
    std::cout << "Enter a number: ";
    std::cin >> sort_order;

    // checks for valid input and allows user to try again
    while(sort_order!="1" && sort_order != "2"){
        std:: cout << "Invalid Input :(( try again" << std::endl;
        std::cout << "Enter a number: ";
        std::cin >> sort_order;
    }

    std::cout << std::endl; // skips a line

    // try/catch to turn sort_by into int for if statement bounds
    int sort_criteria;
    try {
        sort_criteria = std::stoi(sort_by);
    } // invalid input
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid input found." << std::endl;
        return 0;
    }

    // calls sort and print function if all valid inputs
    if (sort_type > "0" && sort_type < "3" && sort_criteria > 0 && sort_criteria < 14 && sort_order > "0" && sort_order < "3") {
        // ascending boolean setup
        bool ascending;

        // sets value
        if (sort_order == "1") {
            ascending = true;
        }
        else {
            ascending = false;
        }

        // sorts and times it
        auto start = std::chrono::high_resolution_clock::now();
        list.sort(sort_type, sort_criteria, ascending);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        // asks user how many songs to print
        std::string num;
        std::cout << "How many songs would you like to see?" << std::endl;
        std::cin >> num;
        std::cout << std::endl; // skips a line

        // converts string input to int, checks for invalid input
        int n;
        try {
            n = std::stoi(num);
        } // invalid input
        catch (const std::invalid_argument& e) {
            std::cout << "Invalid input found." << std::endl;
            return 0;
        }

        // prints first n songs
        list.print(n);

        // timer prints
        std::cout << std::endl;
        if (sort_type == "1") {
            std::cout << "Merge sort took " << duration.count() << " milliseconds to sort." << std::endl;
        }
        else {
            std::cout << "Quick sort took " << duration.count() << " milliseconds to sort." << std::endl;
        }

    } // inavlid choice
    else {
        std::cout << "Invalid input found." << std::endl;
        return 0;
    }

    // program finished print
    std::cout << "End of program." << std::endl;
    std::cout << std::endl;

    // pauses so terminal doesn't instantly close
    system("pause");
    return 0;
}


// --- Citations ---
// timer:   https://cplusplus.com/reference/chrono/
// pause:   https://www.digitalocean.com/community/tutorials/system-pause-command-c-plus-plus


