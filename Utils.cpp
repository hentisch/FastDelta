#include "Utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

vector<string> split(string text){  
    /*This function will return a vector of words, 
    based on the words used in the passed text. Each
    word featured in the list corresponds to one use of the 
    word in the source text*/  

    text = removePunctuation(text);
    vector<string> words;    

    int lastIndex = -1;
    for(int i = 0; i < text.length(); i++){
        if(text[i] == ' ')
        {
            words.push_back(text.substr(lastIndex+1, i - lastIndex));
            lastIndex = i;
        }
    }
    words.push_back(text.substr(lastIndex+1));
    return words;
}

string stringFromFile(string filePath){
    /*This function will return a string
    representing all text found at the file
    filePath points towards*/
    ifstream t(filePath);
    stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

string removePunctuation(string text){
    /*This function will return a version of 
    text will all punctuation removed*/
    string noPunc = "";
    for(int i = 0; i < text.size(); i++){
        if(!ispunct(text[i]))
            noPunc.push_back(text[i]);
    }
    return noPunc;
}

unordered_map<string, double> sumMaps(vector<unordered_map<string, double>> maps){
    /*This will return the "sum" of all maps in the maps vector.
    Every key in each individual map will be represented, and if multiple
    maps have the same key, the sum of both of the maps values for those keys 
    will be represnted in the returned map.*/
    unordered_map<string, double> sumMap;
    for(unordered_map<string, double> map: maps){
        for(auto feature: map){
            if(map.find(feature.first) == map.end()) //Checks if the feature already is in the sumMap
                sumMap[feature.first] = map[feature.first];
            else
                sumMap[feature.first] += map[feature.first];
        }
    }
    return sumMap;
}