#include <iostream>
#include <vector>
#include <string>
#include "Utils.h"

using namespace std;

int main(){
    vector<string> words;    
    string text = stringFromFile("pg67772.txt");
    text = removePunctuation(text);

    words = split(text);

    for(int i = 0; i < words.size(); i++){
        cout << words[i] << "\n";
    }
}