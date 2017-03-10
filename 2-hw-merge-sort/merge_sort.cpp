/**
 * @file merge_sort.cpp
 * @brief Implementation of merge sort. Compiler g++ (GCC) 6.2.1 20160830
 * @author Artem Abramov
 * @date 2016-09-23
 */

#include "merge_sort.h"
#include <cmath>

using namespace std;

/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup must_have_util_funcs Utility function documented in merge_sort.h that must be implemented.
 *  @{
 */

/* -----------------------------------------------------------------------------*/
/**
 * @brief Find min value of two integers
 *
 * @param a element one.
 * @param b element two.
 *
 * @return Returns the smallest integer.
 */
int min(int a, int b) {
    return a < b ? a : b;
}

/* -----------------------------------------------------------------------------*/
/**
 * @brief Copy values between source indexed from 0 into the middle of another array.
 *
 * @param source Source array.
 * @param dest Destination array.
 * @param start Start of copy in the dest array.
 * @param end End of copy index in the dest array.
 */
void copy_array_part(int *source, int *dest, int start, int end) {
    int index = 0;
    for (int i=start; i < end; i++) {
        dest[i] = source[index++];
    }
}

/** @} */ // end doxygroup


/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup must_implement_funcs Functions that must be impelmented. Their docs are in merge_sort.h
 *  @{
 */

void merge_sort(int *arr, int n) {
    divide_and_merge(arr, 0, n);
}


void merge(int* arr, int start_first, int start_second, int end) {
    int *scratch = new int[end - start_first];
    int index = 0;
    int one = start_first;
    int two = start_second;
    // start taking one by one, when we must compare
    while ((one < start_second) && (two < end)) {
        if (min(arr[one], arr[two]) == arr[one]) {
            scratch[index++] = arr[one];
            one++;
        }
        else {
            scratch[index++] = arr[two];
            two++;
        }
    }
    // only one the while cycles will trigger
    while (one < start_second) {
        scratch[index++] = arr[one];
        one++;
    }
    // only one the while cycles will trigger
    while (two < end) {
        scratch[index++] = arr[two];
        two++;
    }
    copy_array_part(scratch, arr, start_first, end);
    delete[] scratch;
}

void divide_and_merge(int *arr, int left, int right) {
    if (left+1 < right) {
        int mid = (left+right) / 2;
        divide_and_merge(arr, left, mid);
        divide_and_merge(arr, mid, right);
        merge(arr, left, mid, right);
    }
}

/** @} */ // end doxygroup
