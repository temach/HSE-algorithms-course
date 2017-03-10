#include <iostream>
#include "eight_queen.h"

using namespace std;

#define QUEEN 0
#define BAD (-1)
#define FREE (-2)

void printmatrix(int **a, int n) {
    int i, j;
    cout << endl;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int val = a[i][j];
            if (val == QUEEN) {
                cout << "Q\t";
            }
            else {
                cout << ".\t";
            }
            cout << "\n\n" << endl;
        }
    }
}

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
    QueenProblem q;
    q.initialize(4);
    q.backtracking(0);
    cout << q.getNumberOfSolutions() <<endl;

    q.initialize(1);
    q.backtracking(0);
    cout << q.getNumberOfSolutions() <<endl;

    q.initialize(2);
    q.backtracking(0);
    cout << q.getNumberOfSolutions() <<endl;

    q.initialize(3);
    q.backtracking(0);
    cout << q.getNumberOfSolutions() <<endl;


    q.initialize(5);
    q.backtracking(0);
    cout << q.getNumberOfSolutions() <<endl;
    return 0;
}
