#include <iostream>
#include <vector>
#include <string>
#include "Utils.h"
#include "Text.h"
#include "Corpus.h"

using namespace std;

int main(){
    Corpus dataset("/home/henry/Desktop/GitRepos/CStylo/Dataset", 50);

    dataset.writings["Unknown"].printFrequencies();

    return 0;
}