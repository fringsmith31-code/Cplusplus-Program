#pragma once
// ItemTracker.h
// Declares the ItemTracker class, which is responsible for reading the
// Corner Grocer's daily purchase record, counting how many times each
// item was purchased, and presenting that information back to the user
// in a few different formats (single lookup, full list, histogram).
//
// Author: Abdulmalik Alawee
// Course: CS 210 - Programming Languages
// Project Three - Corner Grocer Item-Tracking Program

#ifndef ITEM_TRACKER_H
#define ITEM_TRACKER_H

#include <string>
#include <map>

class ItemTracker
{
public:
    // Constructor: takes the path to the input text file that contains
    // one purchased item per line.
    explicit ItemTracker(const std::string& inputFileName);

    // Reads the input file and builds the frequency map in memory.
    // Returns true if the file was opened and read successfully.
    bool loadFromFile();

    // Writes the current frequency map out to frequency.dat in the
    // "ItemName Count" format. This is called automatically at startup
    // so a backup file exists before the user interacts with the menu.
    void writeBackupFile(const std::string& outputFileName) const;

    // Menu Option 1: looks up a single item the user types in and
    // returns how many times it appears. Returns 0 if the item was
    // never purchased that day.
    int getFrequency(const std::string& itemName) const;

    // Menu Option 2: prints every item paired with its frequency.
    void printFrequencyList() const;

    // Menu Option 3: prints every item as a row of a histogram, using
    // one asterisk per purchase of that item.
    void printHistogram() const;

private:
    // Path to the raw input file (e.g. CS210_Project_Three_Input_File.txt).
    std::string inputFile;

    // Holds each distinct item name mapped to how many times it was
    // purchased. A map keeps the items in alphabetical order automatically,
    // which keeps the printed list and histogram easy to read.
    std::map<std::string, int> itemFrequencies;

    // Helper that trims leading/trailing whitespace and carriage-return
    // characters from a line of input. Protects against files that were
    // saved with Windows-style line endings or stray spaces.
    static std::string trim(const std::string& text);
};

#endif // ITEM_TRACKER_H