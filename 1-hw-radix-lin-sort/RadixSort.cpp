#include "LinearSort.h"
#include <cmath>

using namespace std;

/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup must_have_util_funcs Utility function documented in LinearSort.h that must be implemented.
 *  @{
 */

int get_digit(int number, int base, int digit)
{
    return ((int)(number / pow(base, digit)) ) % base;
}

int max_element(int * arr, int n)
{
    int max = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}

int min_element(int *arr, int n)
{
    int min = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (min > arr[i]) min = arr[i];
    }
    return min;
}

void copy_array(int *source, int *dest, int size)
{
    for (int i = 0; i < size; ++i)
    {
        dest[i] = source[i];
    }
}

/** @} */ // end doxygroup



/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup custom_util_funcs Custom utility functions, not for outside usage.
 *  @{
 */

/* -----------------------------------------------------------------------------*/
/**
 * @brief Returns max element when compare by digit.
 *
 * @param arr   Input array
 * @param n     Array length
 * @param base          Base for number
 * @param digit_index   Which digit is key
 *
 * @return Element with maximum digit in some position.
 */
int max_element_digit(int * arr, int n, int base, int digit_index)
{
    // here we think in terms of digit
    int max = get_digit(arr[0], base, digit_index);
    for (int i = 1; i < n; ++i)
    {
        int dig = get_digit(arr[i], base, digit_index);
        if (max < dig) {
            max = dig;
        }
    }
    return max;
}


/* -----------------------------------------------------------------------------*/
/**
 * @brief Returns min element when compared by certain digit.
 *
 * @param arr   Input array
 * @param n     Array length
 * @param base          Base for number
 * @param digit_index   Which digit is key
 *
 * @return Element with maximum digit in some position.
 */
int min_element_digit(int *arr, int n, int base, int digit_index)
{
    // here we think in terms of digit
    int min = get_digit(arr[0], base, digit_index);
    for (int i = 1; i < n; ++i)
    {
        int dig = get_digit(arr[i], base, digit_index);
        if (min > dig) {
            min = dig;
        }
    }
    return min;
}

/* -----------------------------------------------------------------------------*/
/**
 * @brief Return the maximum element in array by absolute value.
 *
 * @param arr   Input array
 * @param n     Array length
 *
 * @return Value of max element by abs comparison.
 */
int max_element_abs(int * arr, int n)
{
    // here we think in term of digit
    int max = abs(arr[0]);
    for (int i = 1; i < n; ++i)
    {
        int val = abs(arr[i]);
        if (max < val) {
            max = val;
        }
    }
    return max;
}

/* -----------------------------------------------------------------------------*/
/**
 * @brief Count the number of digits in number
 *
 * @param number    Numeric value
 * @param base      Base used to write the number
 *
 * @return          Number of digits needed to represent the number.
 */
int number_length(int number, int base)
{
    int count = 0;
    while (number)
    {
        number /= base;
        count++;
    }
    return count;
}

/** @} */ // end doxygroup


/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup main_interface Main interface functions. Documented in LinearSort.h
 *  @{
 */

void counting_sort(int * arr, int n)
{
    int max = max_element(arr, n);
    int min = min_element(arr, n);

    int *temp = new int[max - min + 1];
    for (int i = 0; i < max - min + 1; ++i) {
        temp[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        temp[arr[i] - min] = temp[arr[i] - min] + 1;
    }
    for (int i = 1; i < max - min + 1; ++i) {
        temp[i] = temp[i] + temp[i - 1];
    }

    int *output = new int[n];
    for (int i = 0; i < n; ++i) {
        output[i] = 0;
    }
    for (int i = n - 1; i >= 0; --i) {
        output[temp[arr[i] - min] - 1] = arr[i];
        temp[arr[i] - min] = temp[arr[i] - min] - 1;
    }
    copy_array(output, arr, n);
    delete[] temp;
    delete[] output;
}

void sort_at_digit(int * arr, int n, int base, int digit_index)
{
    int max_dig = max_element_digit(arr, n, base, digit_index);
    int min_dig = min_element_digit(arr, n, base, digit_index);

    int *temp = new int[max_dig - min_dig + 1];
    for (int i = 0; i < max_dig - min_dig + 1; ++i) {
        temp[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        temp[get_digit(arr[i], base, digit_index) - min_dig] = temp[get_digit(arr[i], base, digit_index) - min_dig] + 1;
    }
    for (int i = 1; i < max_dig - min_dig + 1; ++i) {
        temp[i] = temp[i] + temp[i - 1];
    }

    int *output = new int[n];
    for (int i = 0; i < n; ++i) {
        output[i] = 0;
    }
    for (int i = n - 1; i >= 0; --i) {
        output[temp[get_digit(arr[i], base, digit_index) - min_dig] - 1] = arr[i];
        temp[get_digit(arr[i], base, digit_index) - min_dig] = temp[get_digit(arr[i], base, digit_index) - min_dig] - 1;
    }
    copy_array(output, arr, n);
    delete[] temp;
    delete[] output;
}


void radix_sort(int * arr, int n, int base)
{
    int len = number_length(max_element_abs(arr, n), base);
    int digit = 0;
    while (digit < len)
    {
        sort_at_digit(arr, n, base, digit);
        digit++;
    }
}

/** @} */ // end doxygroup

