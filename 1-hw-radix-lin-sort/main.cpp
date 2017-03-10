#include <iostream>
#include "LinearSort.h"

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

bool check_sort(int *arr, int n) {
    for (int i=0; i < n - 1; i++) {
        if (arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}

int main()
{
    int N = 10;
    int a[] = {-533, 745, -3, -85, -6, 9, -9, 9, 6, 10};

    int min = -50000;
    int max = 50000;
    int sort_loops = 100;
    int numbase = 10;

    for (int i=0; i < sort_loops; i++) {
        // fill array
        for (int j=0; j < N; j++) {
            a[j] = min + (rand() % (int)(max - min + 1));
        }
        // try sorting it
        radix_sort(a, N, numbase);
        // check that its correct
        bool res = check_sort(a, N);
        if (! res) {
            print(a, N);
        }
    }

    // int b[] = { -9306,-38944,-48611,-38475,-37899,-6391,-31297,-311,6110,9052 };
    // radix_sort(b, N, 10);
    // print(b, N);

    // radix_sort(a, N, numbase);
    // print(a, N);

    // counting_sort(a, N);
    // print(a, N);


    return 0;
}
