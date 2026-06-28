// main.cpp
// Corner Grocer Item-Tracking Program
// CS 210 - Project Three
//
// This program reads a day's worth of grocery purchase records from a
// text file (one item name per line), counts how many times each item
// was purchased, and lets the user explore that data through a simple
// text menu: look up a single item, view the full frequency list, view
// a histogram, or exit. A backup file (frequency.dat) is written
// automatically at startup, before the menu is shown.
//
// Author: Abdulmalik Alawee

#include <iostream>
#include <string>
#include "ItemTracker.h"

// Displays the menu options and returns the user's validated choice (1-4).
// Looping here keeps invalid, non-numeric input from crashing the program
// or silently doing nothing.
int getMenuChoice()
{
    int choice = 0;

    std::cout << "===== Corner Grocer Item Tracker =====\n";
    std::cout << "1. Search for an item's purchase frequency\n";
    std::cout << "2. Print full frequency list\n";
    std::cout << "3. Print frequency histogram\n";
    std::cout << "4. Exit program\n";
    std::cout << "Enter your choice (1-4): ";

    while (!(std::cin >> choice) || choice < 1 || choice > 4)
    {
        std::cout << "Invalid input. Please enter a number from 1 to 4: ";
        std::cin.clear();                                  // reset error flag
        std::cin.ignore(10000, '\n');                       // discard bad input
    }

    // Clear the trailing newline left in the input buffer so the next
    // call to std::getline() (used for item name lookups) works correctly.
    std::cin.ignore(10000, '\n');

    return choice;
}

int main()
{
    // File names are kept as named constants near the top of main so they
    // are easy to find and change if the Corner Grocer renames their
    // export file in the future.
    const std::string inputFileName = "CS210_Project_Three_Input_File.txt";
    const std::string backupFileName = "frequency.dat";

    ItemTracker tracker(inputFileName);

    // Load the day's purchase data. If the file can't be read, there is
    // nothing useful the menu can do, so the program exits early.
    if (!tracker.loadFromFile())
    {
        std::cout << "The program will now close.\n";
        return 1;
    }

    // Per the project requirements, the backup file is created
    // automatically at startup, with no user action required.
    tracker.writeBackupFile(backupFileName);

    bool running = true;
    while (running)
    {
        int choice = getMenuChoice();

        switch (choice)
        {
        case 1:
        {
            std::string searchItem;
            std::cout << "\nEnter the item name you want to search for: ";
            std::getline(std::cin, searchItem);

            int frequency = tracker.getFrequency(searchItem);
            std::cout << searchItem << " was purchased " << frequency
                << " time(s).\n\n";
            break;
        }
        case 2:
            tracker.printFrequencyList();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            std::cout << "\nThank you for using the Corner Grocer Item"
                << " Tracker. Goodbye!\n";
            running = false;
            break;
        default:
            // Unreachable because getMenuChoice() already validates input,
            // but kept here as a defensive fallback.
            std::cout << "Unexpected error. Please try again.\n";
            break;
        }
    }

    return 0;
}