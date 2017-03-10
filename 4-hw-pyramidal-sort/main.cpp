#include <iostream>
#include "heapSort.h"

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
    int N = 10;
    int a[N];

    int min = -50000;
    int max = 50000;
    int sort_loops = 100;

    Heapsort hs;

    for (int i=0; i < sort_loops; i++) {
        int N = (rand() % (int)(15));
        int safe_orig[N];
        // fill array
        for (int j=0; j < N; j++) {
            a[j] = min + (rand() % (int)(max - min + 1));
        }
        // backup for debug
        copy_array_2(a, safe_orig, N);
        // try sorting it
        Heapsort::heapSort(a, N);
        // check that its correct
        bool res = check_sort(a, N);
        if (! res) {
            print(safe_orig, N);
            print(a, N);
            cout << "\n\n" << endl;
        }
    }



    int nd = 10;
    int d[] = {12, 87, 31, 42, 38, 18, 35, 46, 28, 41};
    Heapsort::heapSort(d, nd);
    print(d, nd);

    // check for 4
    int nb = 4;
    int b[] = {29003,18291,-49727,-18839};
    Heapsort::heapSort(b, nb);
    print(b, nb);

    // check for two elements
    int nc = 3;
    int ccc[] = {11715,-28874,9758};
    int c[] = {12343,-43545,-4682};
    print(c, nc);
    Heapsort::heapSort(c, nc);
    print(c, nc);
    // --
    print(ccc, nc);
    Heapsort::heapSort(ccc, nc);
    print(ccc, nc);

    return 0;
}
