////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>


namespace xi {

    //==============================================================================
    // class PlusOp
    //==============================================================================

    // PlusOp
    int PlusOp::operation(char op, int a, int b, int c)
    {
        if(op != '+')
            throw std::logic_error("Operation other than Plus (+) are not supported");
        // here we just ignore unused operands
        return a + b;
    }

    //  Returns an arity of a given (as an IOperation-derived) object
    IOperation::Arity PlusOp::getArity() const
    {
        return arDue;
    }

    //==============================================================================
    // class AndOp
    //==============================================================================

    // AndOp
    int AndOp::operation(char op, int a, int b, int c)
    {
        if(op != '&')
            throw std::logic_error("Bad operation selected.");
        // here we just ignore unused operands
        return a & b;
    }

    // Returns an arity of a given (as an IOperation-derived) object
    IOperation::Arity AndOp::getArity() const
    {
        return arDue;
    }

    //==============================================================================
    // class PowerOp
    //==============================================================================

    // PowerOp
    int PowerOp::operation(char op, int a, int b, int c)
    {
        if(op != '^')
            throw std::logic_error("Bad operation selected.");
        // here we just ignore unused operands
        return std::pow(a, b);
    }

    // Returns an arity of a given (as an IOperation-derived) object
    IOperation::Arity PowerOp::getArity() const
    {
        return arDue;
    }



    //==============================================================================
    // class StackMachine
    //==============================================================================

    /** Register an operation object for a given symbol.
     *
     *  If the symbol is already registered, throws an exception.
     *
     */
    void StackMachine::registerOperation(char symb, IOperation* oper) {
        if (getOperation(symb) != nullptr) {
            throw std::logic_error("Operation already registered");
        }
        _opers[symb] = oper;
    }

    /** For a given symb returns an operation object.
     *
     *  If the given symbol is not mapped to any operation, a nullptr is returned.
     */
    IOperation* StackMachine::getOperation(char symb) {
        SymbolToOperMapConstIter it = _opers.find(symb);
        if(it != _opers.end())
        {
            return _opers[symb];
        }
        return nullptr;
    }

    /** Calculates given expression using the shared stack and returns the value on its top.
     *
     *  \param clearStack determines if a stack should be clear before parsing the expression.
     *  If one prefer not to clear stack before parsing, the results of previous calculations
     *  can be used further.
     *
     *  \param expr contains a string-based expression contains interger operands and one-symbol operators
     *  If an unrecognized symbol (or substring) is found, throws an exception.
     *  If given expression is not valid (e.g., in the case of lack of operands or similar),
     *  an exception is thrown.
     */
    int StackMachine::calculate(const std::string& expr, bool clearStack)
    {
        if (clearStack)
        {
            _s.clear();
        }
        std::string buffer;
        std::stringstream input_stringstream(expr);
        // loop to read characters separated by whitespace
        while (std::getline(input_stringstream, buffer, ' '))
        {
            // get the symbol
            char current = buffer[0];
            // check if it is a valid operation
            IOperation* op = getOperation(current);
            if (op != nullptr)
            {
                // result variable stores the calculation result
                int result = 0;
                // apply the operation, different calls based on Arity
                switch (op->getArity())
                {
                    // Note! We have to declare separate variables: a,b,c
                    // because order of evaluation for function parameters is undefined
                    case IOperation::arUno:
                    {
                        int a = _s.pop();
                        result = op->operation(current, a);
                        break;
                    }
                    case IOperation::arDue:
                    {
                        int a = _s.pop();
                        int b = _s.pop();
                        result = op->operation(current, a, b);
                        break;
                    }
                    case IOperation::arTre:
                    {
                        int a = _s.pop();
                        int b = _s.pop();
                        int c = _s.pop();
                        result = op->operation(current, a, b, c);
                        break;
                    }
                    default:
                    {
                        throw std::logic_error("Unsupported arity");
                        break;
                    }
                }
                // record result
                _s.push(result);
            } else {
                // assume it was a number, convert string to int
                int i = std::stoi(buffer);
                // push another int on the stack
                _s.push(i);
            }
        }
        return _s.top();
    }


} // namespace xi
