#include <iostream>
#include "kmp.h"

using namespace std;

void print(int* arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        //cout << arr[i] << ' ';
    }
    //cout << endl;
}

void copy_array_2(int *source, int *dest, int len) {
    while (len-- > 0) {
        dest[len] = source[len];
    }
}


int main()
{
    string source = "asdasdddasd";
    string pattern = "asd";
    vector<int>* matches = ::find_substrings(source, pattern);
    for (unsigned int i=0; i < matches->size(); i++) {
        cout << (*matches)[i] << endl;
    }
    return 0;
}
