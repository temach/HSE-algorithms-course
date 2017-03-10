/*
 * =====================================================================================
 *
 *       Filename:  quick_sort.cpp
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  09/28/2016 12:24:53 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Artem Abramov (aa), tematibr@gmail.com
 *
 * =====================================================================================
 */

#include "quick_sort.h"
#include <cstdlib>

using namespace std;

/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup util_funcs Utility functions. Not in the header.
 *  @{
 */

/* -----------------------------------------------------------------------------*/
/**
 * @brief Swaps two elements of array in place.
 *
 * @param a Pointer to first element.
 * @param b Pointer to second element.
 */
void doswap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/** @} */ // end doxygroup


/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup public_funcs Public functions that must be implemented
 *  @{
 */

void q_sort::quick_sort_middle(int* arr, int n) {
    q_sort::quick_sort(arr, 0, n-1, q_sort::get_middle_pivot);
}

void q_sort::quick_sort_last(int* arr, int n) {
    q_sort::quick_sort(arr, 0, n-1, q_sort::get_last_pivot);
}

void q_sort::quick_sort_rand(int* arr, int n) {
    q_sort::quick_sort(arr, 0, n-1, q_sort::get_rand_pivot);
}

/** @} */ // end doxygroup


/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup private_must_implement_funcs Private functions that must be implemented.
 *  @{
 */

int q_sort::get_middle_pivot(int from, int to) {
    return (from + to - 1) / 2;
}

int q_sort::get_last_pivot(int from, int to) {
    return to - 1;
}

int q_sort::get_rand_pivot(int from, int to) {
    return from + (rand() % (int)(to - from));
}

void q_sort::quick_sort(int* arr, int from, int to, pivot_chooser pivot_chooser) {
    if (from < to) {
        int pivot = pivot_chooser(from, to);
        pivot = q_sort::rearrange_array_with_pivot(arr, from, to, pivot);
        q_sort::quick_sort(arr, from, pivot, pivot_chooser);
        q_sort::quick_sort(arr, pivot+1, to, pivot_chooser);
    }
}

int q_sort::rearrange_array_with_pivot(int* arr, int from, int to, int pivot_index) {
    // swap pivot away to save it
    int p = arr[pivot_index];
    int left = from-1;
    int right = to+1;
    while(true) {
        // find left bad element
        do {
            left++;
        } while (arr[left] < p);
        do {
            right--;
        } while (arr[right] > p);
        if(left >= right) {
            return right;
        } else {
            // if its ok, then swap
            doswap(&arr[left], &arr[right]);
        }
    }
}

/** @} */ // end doxygroup

