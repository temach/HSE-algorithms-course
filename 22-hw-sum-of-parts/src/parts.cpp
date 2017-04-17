
#include "parts.h"
#include <iostream>

using namespace std;

void Part::describe() const
{
    cout << "Part " << name << " subparts are:" << endl;
    for (auto iter = subparts.begin(); iter != subparts.end(); ++iter)
    {
        cout << "    " << iter->second << " " << iter->first->name << endl;
    }
}

int Part::countHowMany(const Part* p) const
{
    // we are one level above
    // OR this is the part
    // if (subparts.count(p))
    //     return subparts[p];
    if (p == this)
        return 1;

    // we need to ask recursively
    int n = 0;
    for (auto& part : subparts)
    {
        n += part.first->countHowMany(p) * part.second;
    }
    return n;
}

Part* NameContainer::lookup(const string& name)
{
    if (_nameMap.count(name))
        return _nameMap[name];
    else {
        _nameMap[name] = new Part(name);
        return _nameMap[name];
    }
}



