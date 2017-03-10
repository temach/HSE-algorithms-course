#include <iostream>
#include "binary_tree.h"

using namespace std;

bool sorted(int *arr, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        if (arr[i] > arr[i + 1]) return false;
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
    BinaryTree<double> btree;
    btree.insert(15, 34.4);
    btree.insert(16, 34.4);
    btree.insert(5, 34.4);
    btree.insert(3, 4.4);
    btree.insert(12, 34.4);
    btree.insert(10, 34.4);
    btree.insert(13, 34.4);
    btree.insert(6, 34.4);
    btree.insert(7, 34.4);
    btree.insert(20, 34.4);
    btree.insert(18, 34.4);
    btree.insert(23, 34.4);

    btree.find(3);

    btree.remove(5);
    btree.remove(16);
    btree.remove(13);
    btree.remove(6);

    return 0;
}
