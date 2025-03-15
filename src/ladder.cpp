#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cassert>
#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg) { cout << "word1: [" << word1 << "] word2: [" << word2 << "]. " << msg << endl; }

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int size1 = str1.size();
    int size2 = str2.size();
    if (size1 - size2 > 1 || size1 - size2 < -1) { return false; }
    if (size1 == size2) { return is_adjacent(str1, str2); }
    
    // shorter size
    int shorter = size1 < size2 ? size1 : size2;
    // shorter word
    string str_short = shorter == size1 ? str1 : str2;
    // longer word
    string str_long = shorter == size1 ? str2 : str1;
    
    for (int i = 0; i < shorter; ++i) {
        if (str_long[i] != str_short[i]) { 
            str_long.erase(i, 1); 
            return (str_short == str_long);
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {

    if (word1.size() != word2.size()) { return edit_distance_within(word1, word2, 1); }
    
    int difference = 0;
    // assumed word same lengths
    for (int i = 0; i < word1.size(); ++i) {
        if (word1[i] != word2[i]) { 
            ++difference;
            if (difference > 1) { return false; }
        }
    }
    return (difference == 1 || difference == 0);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) { 
        error(begin_word, end_word, "Same word.");
        return {};
    }
    if (word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "End word not in dictionary.");
        return {};
    }
    queue<vector<string>> ladder_q;
    ladder_q.push({begin_word});
    
    set<string> visited;
    visited.insert(begin_word);

    vector<string> curr_lad;
    while (!ladder_q.empty()) 
    {
        curr_lad = ladder_q.front();
        ladder_q.pop();
            
        string last_word = curr_lad[curr_lad.size()-1];

        for (string word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) { 
                visited.insert(word);
                vector<string> new_lad = curr_lad;
                new_lad.push_back(word);
                if (word == end_word) {
                    return new_lad;
                }
                ladder_q.push(new_lad);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    string line;
    ifstream in(file_name);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    while(getline(in, line)) { 
        transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return tolower(c); });
        word_list.insert(line);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.size() == 0) { cout << "No word ladder found." << endl; }
    else { 
        cout << "Word ladder found: ";
        for (string word : ladder) { cout << word << " "; } 
        cout << endl;
    }
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    //assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    //assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    // ? assert(generate_word_ladder("code", "data", word_list).size() == 6);
    //assert(generate_word_ladder("work", "play", word_list).size() == 6);
    //assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    //assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

