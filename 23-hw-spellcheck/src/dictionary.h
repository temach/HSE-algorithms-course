// Артем Абрамов БПИ151
//

#ifndef  _DICTIONARY_H_
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>

#include <functional>

#include "hashset.h"
#include "hashset.cpp"

class hash_function {
public:
    hash_function() {}

    unsigned int operator()(const std::string& s) const;
};

class equality {
public:
    equality() {}
    bool  operator()(const std::string& a, const std::string& b)  const
    {
        return  (a == b);
    }
};


class Dictionary : public HashSet<std::string, hash_function, equality>
{
public:
    Dictionary(string words_file);

    // TODO: Complete definition
};

#endif
