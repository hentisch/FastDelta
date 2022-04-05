#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

vector<string> split(string text){    
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
    ifstream t(filePath);
    stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

string removePunctuation(string text){
    string noPunc = "";
    for(int i = 0; i < text.size(); i++){
        if(!ispunct(text[i]))
            noPunc.push_back(text[i]);
    }
    return noPunc;
}