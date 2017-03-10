/*
 * =====================================================================================
 *
 *       Filename:  heapSort.cpp
 *
 *    Description:  : Implementation of heap sort algorithm.
 *
 *        Version:  1.0
 *        Created:  10/03/2016 09:37:15 PM
 *       Revision:  none
 *       Compiler:  g++ (GCC) 6.2.1 20160830
 *
 *         Author:  Artem Abramov (aa), tematibr@gmail.com
 *
 * =====================================================================================
 */

#include "heapSort.h"
#include <stdexcept>

using namespace std;

/* =============================================================================*/
/**
 *  @defgroup util_funcs Utility functions
 *  @{
 */

/* -----------------------------------------------------------------------------*/
/**
 * @brief Get parent indexin array
 *
 * @param i index of current position
 *
 * @return index of parent.
 */
int iparent(int i) {
    if (i == 0) {
        return -1;
    }
    return i >> 1;
}

/* -----------------------------------------------------------------------------*/
/**
 * @brief Get left child index in array
 *
 * @param i Index of current position
 *
 * @return  index of left child.
 */
int ileft(int i) {
    if (i == 0) {
        return 1;
    }
    return i << 1;
}

/* -----------------------------------------------------------------------------*/
/**
 * @brief Get right child index in array
 *
 * @param i Index of current position
 *
 * @return index of right child
 */
int iright(int i) {
    if (i == 0) {
        return 2;
    }
    return (i << 1) + 1;
}

/* -----------------------------------------------------------------------------*/
/**
 * @brief Swap two integers via pointers.
 *
 * @param a pointer to first int
 * @param b pointer to second int
 */
void swp(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


/** @} */ // end doxygroup



/* =============================================================================*/
/**
 *  @defgroup heapsort_class Implementation of Heapsort class
 *  @{
 */

/* -----------------------------------------------------------------------------*/
void Heapsort::heapSort(int *arr, int n) {
    Heap myheap(arr, n);
    // note: i > 0
    for (int i=0; i < n; i++) {
        arr[i] = myheap.extractMin();
    }
}

/** @} */ // end doxygroup


/* =============================================================================*/
/**
 *  @defgroup heap_class Implementation of Heap class
 *  @{
 */

/* -----------------------------------------------------------------------------*/
Heap::Heap(const int *source, const int n) : capacity(n) {
    currentSize = 0;
    storage = new int[n];
    for (int i=0; i < n; i++) {
        Heap::insert(source[i]);
    }
}

/* -----------------------------------------------------------------------------*/
Heap::~Heap() {
    delete[] storage;
}

/* -----------------------------------------------------------------------------*/
int Heap::getMin() {
    return storage[0];
}

/* -----------------------------------------------------------------------------*/
int Heap::extractMin() {
    if (Heap::currentSize <= 0) {
        throw std::length_error("heap is empty");
    }
    // save the smallest
    int ret = Heap::getMin();
    // overwrite smallest with one of the end (big) ones
    Heap::storage[0] = Heap::storage[Heap::currentSize-1];
    // we have one less element.
    Heap::currentSize--;
    // let the big one float down
    Heap::heapifyDown(0);
    return ret;
}

/* -----------------------------------------------------------------------------*/
void Heap::heapifyDown(int i) {
    int l = ileft(i);
    int r = iright(i);
    // index of max value
    int imin;
    // check left
    if (l <= currentSize && storage[l] < storage[i]) {
        imin = l;
    } else {
        imin = i;
    }
    // check right
    if (r <= currentSize && storage[r] < storage[imin]) {
        imin = r;
    }
    if (imin != i) {
        swp(&storage[i], &storage[imin]);
        heapifyDown(imin);
    }
}


/* -----------------------------------------------------------------------------*/
void Heap::insert(const int value) {
    if (Heap::currentSize >= Heap::capacity) {
        throw std::length_error("heap is already full");
    }
    Heap::storage[Heap::currentSize++] = value;
    Heap::heapifyUp(Heap::currentSize-1);
}

/* -----------------------------------------------------------------------------*/
void Heap::heapifyUp(int i) {
    int p = iparent(i);
    // check left
    if (p > -1 && storage[p] > storage[i]) {
        swp(&storage[i], &storage[p]);
        heapifyUp(p);
    }
}

/** @} */ // end doxygroup
