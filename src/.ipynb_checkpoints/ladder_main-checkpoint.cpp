#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "ladder.h"

/*

g++ -std=c++20 -c src/ladder.cpp -o ladder.o 
g++ -std=c++20 -g -fsanitize=address src/ladder_main.cpp -o hw9 ladder.o
./hw9

*/

int main() {
    
    set<string> words;
    load_words(words, "src/words.txt");
    
    vector<string> ladder = generate_word_ladder("work", "play", words);
    
    print_word_ladder(ladder);
    
    //verify_word_ladder();
    return 0;
}
