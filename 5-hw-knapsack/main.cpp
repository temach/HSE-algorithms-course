#include <iostream>
#include "knapsack.h"

using namespace std;

bool sorted(int *arr, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void print(int *arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void gprint(int** arr, int rows, int cols) {
    for ( int i=0; i < rows; i++ ) {
        for ( int k = 0; k < cols; k++ ) {
            cout << arr[i][k] << ", ";
        }
        cout << endl;
    }
}

bool check_sort(int *arr, int n) {
    for (int i=0; i < n - 1; i++) {
        if (arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}


void copy_array_2(int *source, int *dest, int len) {
    while (len-- > 0) {
        dest[len] = source[len];
    }
}

void do_swap(int *a, int*b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main()
{
4 5
1 8
2 4
3 0
2 5
2 3
    Knapsack ks = {};
     int n = 4;
    int weights[] = {1, 2, 3, 4};
    int costs[] = {32, 50, 90, 3};
    int bpCapac = 4;
    ks.initialize(bpCapac, weights, costs, n);
    ks.solveRecursively();

    return 0;
}
