#include <iostream>
#include <vector>
#include <string>
#include "Utils.h"
#include "Text.h"
#include "Corpus.h"

using namespace std;

int main(){
    Corpus dataset("/home/henry/Desktop/GitRepos/CStylo/Dataset", 50);

    vector<pair<string, double>> rankings = dataset.rankBySimilarity("Unknown");

    for(pair author: rankings){
        cout << author.first << "\n";
    }
}