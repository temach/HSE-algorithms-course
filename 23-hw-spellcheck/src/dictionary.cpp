#include <fstream>
#include <stdexcept>

#include "dictionary.h"

using namespace std;

Dictionary::Dictionary(string words_file)
{
    string word;
    ifstream myfile{words_file};
    if (myfile.is_open())
    {
        while(myfile >> word)
        {
            // cout << word << endl;
            this->insert(word);
        }
        myfile.close();
    }
    else
    {
        throw invalid_argument("Unable to open word list file.");
    }
}



