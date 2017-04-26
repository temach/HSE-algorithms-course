// Артем Абрамов БПИ151
//

#include <fstream>
#include <stdexcept>

#include "dictionary.h"

using namespace std;

// implementing CRC32 - Q
unsigned int hash_function::operator()(const string& s) const
{
    uint32_t remainder = 0;
    // iterate over all chars in the string
    for (char ch : s)
    {
        // Get the next byte into the remainder
        // 24 = 32 - 8
        remainder ^= (ch << (24));

        // step over every bit in byte
        for (uint8_t bit = 8; bit > 0; --bit)
        {
            // try to devide by the top most bit of the data
            // 31 = 32 - 1
            if (remainder & (1U << 31))
                remainder = (remainder << 1) ^ 0x814141ABU; // append "U" for unsigned
            else
                remainder = (remainder << 1);
        }
    }
    // final remainder is the checksum
    return remainder;
}

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



