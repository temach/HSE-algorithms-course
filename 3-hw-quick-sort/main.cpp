#include <iostream>
#include "quick_sort.h"

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

int HoarePartition (int a[],int p, int r) {
    int x=a[p],i=p-1,j=r;
    while (1) {
        do  j--; while (a[j] > x);
        do  i++; while (a[i] < x);
        if  (i < j)
            do_swap(&a[i],&a[j]);
        else
            return j;
    }
}

void QuickSort(int a[],int start,int end) {
    int q=HoarePartition(a,start,end);
    if (end<=start) return;
    QuickSort(a,q+1,end);
    QuickSort(a,start,q);
}

void quicksort(int list[],int m,int n)
{
    int key,i,j,k;
    if( m < n)
    {
        k = (m + n) / 2;
        do_swap(&list[m],&list[k]);
        key = list[m];
        i = m+1;
        j = n;
        while(i <= j)
        {
            while((i <= n) && (list[i] <= key))
                i++;
            while((j >= m) && (list[j] > key))
                j--;
            if( i < j)
                do_swap(&list[i],&list[j]);
        }
        /* swap two elements */
        do_swap(&list[m],&list[j]);
 
        /* recursively sort the lesser list */
        quicksort(list,m,j-1);
        quicksort(list,j+1,n);
    }
}

int main()
{
    int N = 10;
    int a[N];

    int min = -50000;
    int max = 50000;
    int sort_loops = 100;

    q_sort mysorter;

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
        mysorter.quick_sort_rand(a, N);
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
    mysorter.quick_sort_last(d, nd);
    print(d, nd);

    // check for 4
    int nb = 4;
    int b[] = {29003,18291,-49727,-18839};
    mysorter.quick_sort_middle(b, nb);
    print(b, nb);

    // check for two elements
    int nc = 3;
    int ccc[] = {11715,-28874,9758};
    int c[] = {12343,-43545,-4682};
    // QuickSort(ccc, 0, nc);
    print(c, nc);
    mysorter.quick_sort_middle(c, nc);
    print(c, nc);
    print(ccc, nc);
    mysorter.quick_sort_middle(ccc, nc);
    print(ccc, nc);

    // // this has ELEVEN elements
    // int check_merge[] = { 7, 1, 3, 5, 7, 2, 4, 6, 1, 5, 4};
    // mysorter.(check_merge, 1, 5, 8);
    // print(check_merge, 11);
    // // should be [ 7, 1, 2, 3, 4, 5, 6, 7, 1, 5, 4]

    return 0;
}
