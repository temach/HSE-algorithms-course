#include <iostream>
#include "SCCSolver.h"

using namespace std;

bool sorted(int *arr, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

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
    vector<int> graph[] = {
        { 1 }          // a
        , { 2,4,5 }        // b
        , { 3,6 }        // c
        , { 2,7 }        // d
        , { 0,5 }        // e
        , { 6 }        // f
        , { 5,7 }        // g
        , { 7 }        // h
    };
    SCCSolver scc;
    scc.initialize(graph, 8);
    scc.solve();
    vector<vector<int>> res = scc.getResult();
    for (const auto& comp : res) {
        for (const auto& v : comp) {
            cout << v << ' ';
        }
        cout << endl;
    }

    return 0;
}
