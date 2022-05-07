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

    for(pair author: dataset.writings){
        cout << author.first << endl;
    }
    cout << endl;

    for(pair rank: rankings){
        cout << rank.first << endl;
    }
}