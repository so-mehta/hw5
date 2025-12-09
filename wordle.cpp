#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> results;
    int size = in.size();

    //this sets represents floating letters
    int letters[26] = {0};

    //letters has an index for each letter-- the value at each 
    //index represents the number of those letters that appear as 
    //floating letters in the word

    for (int i = 0; i < floating.size(); i++){
        letters[floating[i] - 'a'] = letters[floating[i] - 'a'] + 1;
    }
    //totalFloat stores the number of floating letters
    int totalFloat = floating.size();
    std::string word = in;

    wordle_helper(0, totalFloat, size, word, dict, results, letters);
    return results;// Add your code here

}

// Define any helper functions here
void wordle_helper(int curr_pos, int floats_left, int size, std::string& word, const std::set<std::string>& dict, std::set<std::string>& results, int* letters){
    // base case: completed all letters of the word -- word is either found in the dictionary or wrong word
    if (curr_pos == size){ 
        if (floats_left == 0 && (dict.find(word)!= dict.end())){
            results.insert(word);
            // return;
        }
        return;
    }

    //calculate number of remaining blanks
    int blanks = 0;
    for (int i = curr_pos; i < size; i++){
        if (word[i] == '-'){
            blanks++;
        }
    }

    //return if fixed letter at this position
    if (word[curr_pos] != '-'){
        wordle_helper(curr_pos+ 1, floats_left, size, word, dict, results, letters);
        return;
    }

    //return if this combination is impossible--pruning
    if (floats_left > blanks){
        return;
    }

    //now, try different values for the blanks a-z
    for (char c = 'a'; c <= 'z'; c++){
        word[curr_pos] = c;
        int nw = floats_left;

        if (letters[c-'a']>0){
            letters[c-'a'] = letters[c-'a'] -1;
            nw--;
            wordle_helper(curr_pos +1, nw, size, word, dict, results, letters);
            letters[c-'a']++;
        } else {
            wordle_helper(curr_pos + 1, nw, size, word, dict, results, letters);
        }

        word[curr_pos] = '-';

    }

}