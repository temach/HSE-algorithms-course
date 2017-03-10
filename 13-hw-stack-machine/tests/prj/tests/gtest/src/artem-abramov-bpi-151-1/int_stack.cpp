////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Artem Abramov
////////////////////////////////////////////////////////////////////////////////


#include "int_stack.h"
#include <stdexcept>


namespace xi {

        /** Declares a stack of integers.  */
        // static const int STACK_SIZE = 1024;     ///< Defines a maximum number of stack elements

        // Constructors
        IntStack::IntStack(size_t sz) {
                _ssize = sz;
                _stack = new int[_ssize];
                _head = 0;
        }

        IntStack::~IntStack() {
                delete _stack;
                _head = 0;
        }

        //----<Main ADT interface>----
        /** Pushes a given element onto the stack.
         *
         *  If no more elements can be placed onto the stack due to its overflow an std::logic_error is thrown.
         */
        void IntStack::push(int el) {
                if (_head >= _ssize) {
                        throw std::logic_error("stack overflow");
                }
                _stack[_head++] = el;
        }

        /** Pops an element from the stack and returns its value.
         *
         *  If no elements stored in the stack, a std::logic_error is thrown.
         */
        int IntStack::pop() {
                if (_head < 1) {
                        throw std::logic_error("stack underflow");
                }
                return _stack[--_head];
        }

        /** Looks up an element from the top of the stack and returns its value.
         *
         *  If no elements stored in the stack, a std::logic_error is thrown.
         */
        int IntStack::top() {
                if (_head < 1) {
                        throw std::logic_error("stack underflow");
                }
                return _stack[_head - 1];
        }

        /** Clears the stack and makes it empty.
         *
         *  Often named as makeEmpty or similar
         */
        void IntStack::clear() {
                _head = 0;
        }

        // Non classic ADT helper methods
        /** Returns true if the stack is empty, false otherwise */
        bool IntStack::isEmpty() const {
                return _head == 0;
        }

        /** Returns true if the stack is full, false otherwise */
        bool IntStack::isFull() const {
                return _head >= _ssize;
        }


} // namespace xi
