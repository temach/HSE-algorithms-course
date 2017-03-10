////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Артем Абрамов БПИ 151
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>


namespace xi {
    //==============================================================================
    // Helper functions
    //==============================================================================

    /* -----------------------------------------------------------------------------*/
    /**
     * @brief Applies the operator to the stack and records the result back into the
     * stack.
     *
     * @param op_char   Char that symbolises the operation.
     * @param op        Pointer to operator class.
     * @param st        Reference to stack of the StackMachine that calls this function.
     */
    void apply_operation(char op_char, IOperation* op, IntStack& st)
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
                int a = st.pop();
                result = op->operation(op_char, a);
                break;
            }
            case IOperation::arDue:
            {
                int a = st.pop();
                int b = st.pop();
                result = op->operation(op_char, b, a);
                break;
            }
            case IOperation::arTre:
            {
                int a = st.pop();
                int b = st.pop();
                int c = st.pop();
                result = op->operation(op_char, c, b, a);
                break;
            }
            default:
            {
                throw std::logic_error("Unsupported arity");
                break;
            }
        }
        // record result
        st.push(result);
    }


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
    // class MulOp
    //==============================================================================

    // MulOp
    int MulOp::operation(char op, int a, int b, int c)
    {
        if(op != '*')
            throw std::logic_error("Bad operation selected.");
        // here we just ignore unused operands
        return a * b;
    }

    // Returns an arity of a given (as an IOperation-derived) object
    IOperation::Arity MulOp::getArity() const
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
    void StackMachine::registerOperation(char symb, IOperation* oper)
    {
        if (getOperation(symb) != nullptr)
        {
            throw std::logic_error("Operation already registered");
        }
        _opers[symb] = oper;
    }

    /** For a given symb returns an operation object.
     *
     *  If the given symbol is not mapped to any operation, a nullptr is returned.
     */
    IOperation* StackMachine::getOperation(char symb)
    {
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
            if (buffer.empty())
            {
                // if there is consequtive whitespace, skip it
                continue;
            }
            // get the symbol
            char current = buffer[0];
            // check if it is a valid operation
            IOperation* op = getOperation(current);
            if (op != nullptr)
            {
                // if it is a registered operation
                apply_operation(current, op, _s);
            }
            else
            {
                // its not a registered operation, assume it is a number
                int i = 0;
                try {
                    // convert string to int
                    i = std::stoi(buffer);
                } catch (...) {
                    throw std::logic_error("Invalid operation/number input");
                }
                // push this int on the stack
                _s.push(i);
            }
        }
        return _s.top();
    }


} // namespace xi
