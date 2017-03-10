////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Safearray class methods definition
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// This file contains templates of the method of the class Safearray.
/// This file is not going to be used w/o its main counterpart, safearray.h.
/// Since the file is used only through safearray.h, which has its own "include 
/// watcher", we add no addition "watcher" here.
///
////////////////////////////////////////////////////////////////////////////////

// #ifndef    // No need to have a watcher here!


#include "safearray.h"


// we have to indicate that methods of the class Safearray are also inside the namespace xi
namespace xi {


template <class T>
SafeArray<T>::SafeArray(size_t cap)
{
    _storage = new T[cap];
    _capacity = cap;
}

// Copy constructor
template <class T>
SafeArray<T>::SafeArray(const SafeArray<T>& other)
{
    _capacity = other._capacity;
    _storage = new T[_capacity];
    for (size_t i=0; i<_capacity; i++)
    {
        _storage[i] = other[i];
    }
}


// Copy assignemnt operator =
template <class T>
SafeArray<T>& SafeArray<T>::operator=(const SafeArray<T>& other)
{
    if (this != &other)
    {
        // first try to allocate memory
        T local_store[] = new T[other._capacity];
        for (size_t i=0; i<other._capacity; i++)
        {
            local_store[i] = other[i];
        }
        // clear old and assign new data
        delete[] _storage;
        _storage = local_store;
        _capacity = other._capacity;
    }
    return *this;
}


template <class T>
SafeArray<T>::~SafeArray()
{
    _capacity = 0;
    delete[] _storage;
}

template <class T>
T& SafeArray<T>::operator[] (size_t k)
{
    checkBounds(k);
    return _storage[k];
}

template <class T>
const T& SafeArray<T>::operator[] (size_t k) const
{
    checkBounds(k);
    return (const T&)_storage[k];
}


template <class T>
size_t SafeArray<T>::getCapacity() const
{
    return _capacity;
}


template <class T>
void SafeArray<T>::checkBounds(size_t index) const
{
    if (index >= _capacity)
    {
        throw std::out_of_range("index out of range");
    }
}


} // namespace xi
