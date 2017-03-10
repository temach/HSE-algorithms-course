// Артем Абрамов БПИ 151

/**
* Here is a template for implementation of Knuth-Morris-Pratt (KMP) algorithm for searching
* substring occurences in a string.
* It consists of only one function so feel free to add any additional classes, 
* functions etc. in your kmp.cpp file.
*/

#include "kmp.h"
#include <vector>

using namespace std;

void compute_prefix_function(vector<int>& border, string pattern) {
    int m = pattern.size();
    // mark first as -1
    border[0] = -1;
    for (int i = 0; i < m; i++)
    {
        // add minus ones
        border[i+1] = border[i];
        while (border[i+1] > -1 && pattern[border[i+1]] != pattern[i])
        {
            // keep putting
            border[i+1] = border[border[i+1]];
        }
        // increment the submatch count
        border[i+1]++;
    }
}

std::vector<int>* find_substrings(std::string& source, std::string& substring) {
    vector<int>* matches = new vector<int>();

    // first get prefix function, to negate comparisons
    int m = substring.size();
    vector<int> border(m + 1);
    compute_prefix_function(border, substring);

    int n = source.size();
    int seen = 0;
    // iter as the number of letters
    for (int i = 0; i < n; i++)
    {
        // if you have seen or the chars matched
        while (seen > -1 && substring[seen] != source[i]) 
        {
            // mark it as new
            seen = border[seen];
        }
        if (++seen == m)
        {
            // record match
            matches->push_back(i - m + 1);
            // no more chars in source, with next char try the last ending chars
            seen = border[m];
        }
    }
    return matches;
}

