#include <iostream>
#include <vector>
#include <string>
#include "Utils.h"
#include "Text.h"

using namespace std;

int main(){
    string text = stringFromFile("pg61.txt");

    Text book("Henry Tischler", text);

    book.printFrequencies();
}