#include "Utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

/*NOTE: THE SPLIT FUNCTION IS FAIRLY INNEFICENT FOR TOKENIZATION,
AND IS NOT, AND SHOULD NOT BE USED FOR THAT TASK. INSTEAD,
THE tokenize() FUNCTION SHOULD BE USED TO PRODUCE A DIRECT
HASHMAP*/

vector<string> split(string text){  
    /*This function will return a vector of words, 
    based on the words used in the passed text. Each
    word featured in the list corresponds to one use of the 
    word in the source text*/  

    vector<string> words;    

    int lastIndex = -1;
    for(int i = 0; i < text.length(); i++){
        if(text[i] == ' ')
        {
            words.push_back(getCleanedWord(text.substr(lastIndex+1, i - lastIndex)));
            lastIndex = i;
        }
    }
    words.push_back(text.substr(lastIndex+1));
    return words;
}

string readFile(string filePath){
    /*This function will return a string
    representing all text found at the file
    filePath points towards*/
    ifstream t(filePath);
    stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

string getCleanedWord(string text){
    /*This function will return a version of 
    text will all non alphabetic characters removed*/
    string noPunc = "";
    for(int i = 0; i < text.size(); i++){
        if(isalpha(text[i]))
            noPunc.push_back(tolower(text[i]));
    }
    return noPunc;
}

void cleanWord(string& text){
    /*This function will remove all non-alphabetic characters from 
    a string, in-place*/
    text = getCleanedWord(text);
}

unordered_map<string, double> sumMaps(vector<unordered_map<string, double>> maps){
    /*This will return the "sum" of all maps in the maps vector.
    Every key in each individual map will be represented, and if multiple
    maps have the same key, the sum of both of the maps values for those keys 
    will be represnted in the returned map.*/
    unordered_map<string, double> sumMap;
    for(unordered_map<string, double> map: maps){
        for(auto feature: map){
                sumMap[feature.first] += map[feature.first];
        }
    }
    return sumMap;
}

unordered_map<string, double> tokenize(string content, int& numWords){
    /*This funciton returns a hash map, with the keys
    representing each word in the passed string, and the
    value representing the number of occurances of the 
    word in the passed content. Additionally, the passed numWords
    refrence will contain the total number of words in the passed
    string*/

    numWords = 0;

    unordered_map<string, double> wordFreqs;
    
    int lastIndex = -1;
    for(int i = 0; i < content.length(); i++){
        if(content[i] == ' ' || content[i] == '\n' || content[i] == '-'){ 
            numWords++;
            string currentWord = getCleanedWord(content.substr(lastIndex+1, i - lastIndex));
            cleanWord(currentWord);   
            wordFreqs[currentWord]++;
            lastIndex = i;
        }
    }

    /*In situtations where an author has a sequence of characters that are all non-alphabetic,
    the cleanWord() method will return an empty sting. As this does not represent any unique
    feature, we should remove this potential feature*/
    if(wordFreqs.find("") != wordFreqs.end()){
        wordFreqs.erase("");
    }

    return wordFreqs;
}

void relativize(unordered_map<string, double>& map, double dividend){
    /* This function will divide every value in the passed map by the specified
    dividend.*/

    for(pair feature: map)
    {
        map[feature.first] /= dividend;
    }
}

void insertFeature(vector<pair<string, double>>& features, pair<string, double> targetFeature, int targetIndex){
    /* This function will insert targetFeature at targetIndex in the given array, removing the last element
    of the array and then pushing all elements past targetIndex by one in order to make space to insert
    targetFeature*/
    for(int i = features.size(); i < targetIndex; i--){
        features[i] = features[i-1];
    }
    features[targetIndex] = targetFeature;
}

void autoInsertFeature(vector<pair<string, double>>& features, pair<string, double> targetFeature){
    /*this function will automatically insert a feature into an array of features, placing the
    feature in its correct posistion to maintain an array sorted from most frequent to least
    frequent feature*/

    
    if(features[features.size()-1].second > targetFeature.second)
    /*this checks if the last feature of the vector is larger than our target feature, 
    in which case our target feature is not in the top n elements, and we dont need to 
    bother finding it's proper position*/
        return;
        

    for(int i = 0; i < features.size(); i++){
        if(targetFeature.second > features[i].second){
            insertFeature(features, targetFeature, i);
            return;
        }
    }
}

vector<pair<string, double>> getEmptyFeatureVector(int length){
    /*This function returns a vector of the passed length, which
    will be filled with pairs of empty strings and vectors*/
    vector<pair<string, double>> emptyVec;
    pair<string, double> emptyFeature("", 0.0);
    for(int i = 0; i < length; i++){
        emptyVec.push_back(emptyFeature);
    }
    return emptyVec;
}