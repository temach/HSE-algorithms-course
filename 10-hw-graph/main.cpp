#include <iostream>
#include "bellman_ford.h"

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

    int e1[] = {1,2,1};
    int e2[] = {2,3,2};
    int e3[] = {3,4,3};
    int e4[] = {1,3,2};
    int* graph[4] = {
        e1
        , e2
        , e3
        , e4
    };
    BellmanFord bl;
    bl.initialize(graph, 4, 4, 1);
    bl.solve();
    vector<int>* res = bl.getPath();
    for (int i=0; i<4; i++) {
        for (const auto& v : res[i]) {
            cout << v << ' ';
        }
        cout << endl;
    }

    return 0;
}
