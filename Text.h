#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#include "Utils.h"

using namespace std;

class Text{
    public:
        string authorName;
        unordered_map <string, double> wordFrequencies;
        Text(string name, string text);
        Text();
        void printFrequencies();
    private:
        int wordsWritten;
};