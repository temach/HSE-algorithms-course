// Артем Абрамов БПИ151
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>

#include "dictionary.h"

#include <set>

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);
set<string> check_transposed(string word, Dictionary& dict);
set<string> check_removed(string word, Dictionary& dict);
set<string> check_replacement(string word, Dictionary& dict);
set<string> check_insertion(string word, Dictionary& dict);

int main(int argc, char* argv[])
{
    // Output usage message if improper command line args were given.
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
        return EXIT_FAILURE;
    }

    ifstream inf(argv[2]);
    if (! inf)
    {
        cerr << "Could not open " << argv[2] << "\n";
        return EXIT_FAILURE;
    }

    // Read dictionary, but let user know what we are working on.
    cout << "Loading dictionary, this may take awhile...\n";

    Dictionary d{argv[1]};

    checkSpelling(inf, d);

    inf.close();

    return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict)
{
    int line_number = 0;

    while (in)
    {
        ++line_number;

        string line;
        getline(in, line);

        stringstream ss (stringstream::in | stringstream::out);
        ss << line;

        string word;
        while (ss >> word)
        {
            // prepare
            word = stripPunct(word);
            lower(word);

            // if word exists, continue
            if (dict.search(word))
                continue;

            cout << "line " << line_number << ": '" << word << "'\n";
            cout << "        suggestions:\n";

            set<string> suggestions;
            set<string> v1 = check_transposed(word, dict);
            set<string> v2 = check_removed(word, dict);
            set<string> v3 = check_insertion(word, dict);
            set<string> v4 = check_replacement(word, dict);
            suggestions.insert(v1.begin(), v1.end() );
            suggestions.insert(v2.begin(), v2.end() );
            suggestions.insert(v3.begin(), v3.end() );
            suggestions.insert(v4.begin(), v4.end() );
            for (const string& s : suggestions)
            {
                cout << "             " << s << "\n";
            }
        }
    }
}

set<string> check_transposed(string word, Dictionary& dict)
{
    const string original = word;
    set<string> ret;
    for (unsigned int i=0; i < original.length() - 1; i++)
    {
        word = original;
        char tmp = word[i];
        word[i] = word[i+1];
        word[i+1] = tmp;
        if (dict.search(word))
            ret.insert(word);
    }
    return ret;
}

set<string> check_removed(string word, Dictionary& dict)
{
    const string original = word;
    set<string> ret;
    for (unsigned int i=0; i < original.length(); i++)
    {
        word = original;
        word.erase(i, 1);
        if (dict.search(word))
            ret.insert(word);
    }
    return ret;
}

set<string> check_replacement(string word, Dictionary& dict)
{
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    const string original = word;
    set<string> ret;
    for (unsigned int i=0; i < original.length(); i++)
    {
        for (const char ch : alphabet)
        {
            word = original;
            word[i] = ch;
            if (dict.search(word))
                ret.insert(word);
        }
    }
    return ret;
}

set<string> check_insertion(string word, Dictionary& dict)
{
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    const string original = word;
    set<string> ret;
    for (unsigned int i=0; i < original.length() + 1; i++)
    {
        for (const char ch : alphabet)
        {
            word = original;
            word.insert(i, 1, ch);
            if (dict.search(word))
                ret.insert(word);
        }
    }
    return ret;
}


void lower(string& s)
{
    // Ensures that a word is lowercase
    for (unsigned int i = 0; i < s.length(); ++i)
    {
        s[i] = tolower(s[i]);
    }
}

string stripPunct(const string& s)
{
    // Remove any single trailing
    // punctuation character from a word.
    if (ispunct(s[s.length() - 1]))
        return s.substr(0, s.length() - 1);
    return s;
}
