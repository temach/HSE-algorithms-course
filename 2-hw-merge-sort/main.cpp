#include <iostream>
#include "merge_sort.h"

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

int main()
{
    int N = 10;
    int a[N];

    int min = -50000;
    int max = 50000;
    int sort_loops = 100;

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
        merge_sort(a, N);
        // check that its correct
        bool res = check_sort(a, N);
        if (! res) {
            print(safe_orig, N);
            print(a, N);
            cout << "\n\n" << endl;
        }
    }

    int nd = 10;
    int d[] = {-18388,41158,46298,-31830,-6998,-15039,-16054,9173,40927,3986};
    merge_sort(d, nd);
    print(d, nd);

    // check for 4
    int nb = 4;
    int b[] = {-18388,41158,-6998,-15039};
    merge_sort(b, nb);
    print(b, nb);

    // check for two elements
    int nc = 2;
    int c[] = {18388,-41158};
    merge_sort(c, nc);
    print(c, nc);

    // this has ELEVEN elements
    int check_merge[] = { 7, 1, 3, 5, 7, 2, 4, 6, 1, 5, 4};
    merge(check_merge, 1, 5, 8);
    print(check_merge, 11);
    // should be [ 7, 1, 2, 3, 4, 5, 6, 7, 1, 5, 4]

    return 0;
}
