#include <iostream>
#include <vector>
#include <string>
#include "Utils.h"
#include "Text.h"
#include "Corpus.h"

using namespace std;

int main(){
    cout << "Reading string" << endl;
    string content = readFile("/home/henry/Documents/Code/Open_Source/CStylo/Dataset/Dope_SathRohmer.txt");
    cout << "String read" << endl;
    Text writing("SathRohmer", content);
    writing.printFrequencies();
    return 0;
}