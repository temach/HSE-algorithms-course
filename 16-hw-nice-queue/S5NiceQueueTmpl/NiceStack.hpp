/*
 * =====================================================================================
 *
 *       Filename:  NiceStack.hpp
 *
 *    Description:  Implementation of NiceStach.hpp
 *
 *         Author:  Artem Abramov (aa), tematibr@gmail.com
 *
 * =====================================================================================
 */


#include <algorithm>
#include <stdexcept>
#include "NiceStack.h"

template <class T>
NiceStack<T>::NiceStack(size_t capacity)
{
    m_capacity = capacity;
    storage.reserve(capacity);
    iHead = 0;
}

template <class T>
size_t NiceStack<T>::size() const
{
    return iHead;
}

template <class T>
NiceStack<T>::~NiceStack(void)
{

}

template <class T>
void NiceStack<T>::push(T newelement) throw (out_of_range)
{
    if (iHead == m_capacity)
        throw std::out_of_range("No space");
    if (iHead == 0)
    {
        storage[iHead] = TypeElementStack{newelement, newelement};
        iHead++;
    }
    else
    {
        T prev = storage[iHead - 1].second;
        storage[iHead] = TypeElementStack{newelement, std::min(newelement, prev)};
        iHead++;
    }
}

template <class T>
T NiceStack<T>::pop (void) throw (out_of_range)
{
    if (iHead == 0)
        throw std::out_of_range("No elements");
    return storage[--iHead].first;
}

template <class T>
T NiceStack<T>::getMinimum(void) throw (out_of_range)
{
    if (iHead == 0)
        throw std::out_of_range("No elements");
    return storage[iHead - 1].second;
}
