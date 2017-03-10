/*
 * =====================================================================================
 *
 *       Filename:  NiceQueue.hpp
 *
 *    Description:  Implementation of NiceQueue.h
 *
 *         Author:  Artem Abramov (aa), tematibr@gmail.com
 *
 * =====================================================================================
 */

#include <algorithm>
#include "NiceQueue.h"

template <class T>
NiceQueue<T>::NiceQueue(size_t capacity) : inStack(capacity), outStack(capacity)
{
    m_capacity = capacity;
}

template <class T>
size_t NiceQueue<T>::size(void) const
{
    return inStack.size() + outStack.size();
}

template <class T>
void NiceQueue<T>::enq(T newelement) throw (out_of_range)
{
    // If input Stack is full, but output Stack is empty, transfer
    // input data into output stack to free space.
    if (inStack.size() >= m_capacity && outStack.size() == 0) {
        while (inStack.size() > 0) {
            outStack.push(inStack.pop());
        }
    }
    // will generate out_of_range if no space
    inStack.push(newelement);
}

template <class T>
T NiceQueue<T>::deq(void) throw (out_of_range)
{
    // If output Stack is empty, but input Stack is full, transfer
    // input data into output stack to fill space.
    if (outStack.size() == 0 && inStack.size() > 0) {
        while (inStack.size() > 0) {
            outStack.push(inStack.pop());
        }
    }
    // will generate out_of_range if no element
    return outStack.pop();
}

template <class T>
T NiceQueue<T>::getMinimum(void) throw (out_of_range)
{
    if (inStack.size() == 0)
        return outStack.getMinimum();
    else if (outStack.size() == 0)
        return inStack.getMinimum();
    else
        return std::min(inStack.getMinimum(), outStack.getMinimum());
}


