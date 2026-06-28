// ItemTracker.cpp
// Implements the ItemTracker class declared in ItemTracker.h.
//
// Author: Abdulmalik Alawee
// Course: CS 210 - Programming Languages
// Project Three - Corner Grocer Item-Tracking Program

#include "ItemTracker.h"
#include <iostream>
#include <fstream>

// Constructor: store the input file name for later use by loadFromFile().
ItemTracker::ItemTracker(const std::string& inputFileName)
    : inputFile(inputFileName)
{
}

// Removes leading/trailing whitespace and carriage-return characters
// from a string. This keeps item names clean even if the text file
// has trailing spaces or was edited on a different operating system.
std::string ItemTracker::trim(const std::string& text)
{
    const std::string whitespace = " \t\r\n";
    size_t start = text.find_first_not_of(whitespace);
    if (start == std::string::npos)
    {
        return ""; // The line was empty or all whitespace.
    }
    size_t end = text.find_last_not_of(whitespace);
    return text.substr(start, end - start + 1);
}

// Opens the input file and reads it one line at a time. Each line is
// treated as a single purchased item. The map automatically handles
// counting: if the item already exists as a key, its value increases;
// if not, it is inserted with a starting count of 1.
bool ItemTracker::loadFromFile()
{
    std::ifstream inFile(inputFile);

    if (!inFile.is_open())
    {
        std::cout << "Error: could not open input file \"" << inputFile
            << "\". Please verify the file is in the same folder as"
            << " the executable.\n";
        return false;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        std::string item = trim(line);
        if (!item.empty())
        {
            // operator[] inserts the key with value 0 if it does not yet
            // exist, then we increment it - this is the standard idiom
            // for frequency counting with std::map.
            itemFrequencies[item]++;
        }
    }

    inFile.close();
    return true;
}

// Writes the accumulated frequency data to a backup file. This runs
// automatically at program startup, before the menu is ever shown,
// per the project requirement that frequency.dat be created without
// user intervention.
void ItemTracker::writeBackupFile(const std::string& outputFileName) const
{
    std::ofstream outFile(outputFileName);

    if (!outFile.is_open())
    {
        std::cout << "Error: could not create backup file \""
            << outputFileName << "\".\n";
        return;
    }

    for (const auto& entry : itemFrequencies)
    {
        outFile << entry.first << " " << entry.second << "\n";
    }

    outFile.close();
}

// Menu Option 1 support: looks up a single item name (case-sensitive,
// matching how it appears in the input file) and returns its count.
// Returns 0 for any item that was not purchased that day, rather than
// treating it as an error - a frequency of zero is still a valid answer.
int ItemTracker::getFrequency(const std::string& itemName) const
{
    auto result = itemFrequencies.find(itemName);
    if (result != itemFrequencies.end())
    {
        return result->second;
    }
    return 0;
}

// Menu Option 2: prints every item next to its frequency count.
// Because itemFrequencies is a std::map, iterating over it naturally
// produces the items in alphabetical order.
void ItemTracker::printFrequencyList() const
{
    std::cout << "\n--- Item Frequency List ---\n";
    for (const auto& entry : itemFrequencies)
    {
        std::cout << entry.first << " " << entry.second << "\n";
    }
    std::cout << "\n";
}

// Menu Option 3: prints a simple text-based histogram. Each item is
// followed by one asterisk for every time it was purchased, giving a
// quick visual sense of which produce items are most popular.
void ItemTracker::printHistogram() const
{
    std::cout << "\n--- Item Frequency Histogram ---\n";
    for (const auto& entry : itemFrequencies)
    {
        std::cout << entry.first << " ";
        for (int i = 0; i < entry.second; ++i)
        {
            std::cout << "*";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}