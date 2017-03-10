/**@file
 * =====================================================================================
 *
 *       Filename:  eight_queen.cpp
 *
 *    Description:  Implementation for QueenProblem
 *
 *        Version:  1.0
 *        Created:  10/22/2016 12:29:30 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Artem Abramov (aa), tematibr@gmail.com
 *
 * =====================================================================================
 */


#include "eight_queen.h"
#include <stdexcept>
#include <cmath>



/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup must_implement_funcs Functions that must be implemented from header.
 *  See header file for their documentation.
 *  @{
 */

void QueenProblem::initialize(const int size) {
    // check old values
    if (board != nullptr) {
        for ( int i=0; i < QueenProblem::size; i++) {
            delete[] QueenProblem::board[i];
        }
        delete[] QueenProblem::board;
    }
    // constants
    QueenProblem::size = size;
    QueenProblem::solved = false;
    QueenProblem::numberOfSolutions = 0L;
    // make board
    QueenProblem::board = new int*[size];
    for ( int i=0; i < size; i++) {
        board[i] = new int[size];
        for ( int k=0; k < size; k++) {
            board[i][k] = 0;
        }
    }
    // all done
    QueenProblem::initialized = true;
}

bool QueenProblem::isInitialized() {
    return initialized;
}

bool QueenProblem::isSolved() {
    return solved;
}

void QueenProblem::backtracking(int queen) {
    if (! isInitialized() ) {
        throw std::logic_error("problem is not initialised");
    }
    // if we can keep going
    if (queen < size) {
        for (int i = 0; i < size; i++) {
            //check
            if (isInserted(queen, i)) {
                // take the square
                board[queen][i] = 1;
                // solve for left branch, we take
                backtracking(queen + 1);
                // solve for right branch, we dont take
                board[queen][i] = 0;
            }
        }
        if (queen == 0) {
            // if this is the first depth of recursion
            solved = true;
        }
    } else {
        // solution finished, add it
        numberOfSolutions++;
    }
}


bool QueenProblem::isInserted(int queen_row, int queen_col) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (board[row][col] == 1) {
                if (queen_col == col
                        || std::abs(queen_row - row) == std::abs(queen_col - col)) 
                {
                    return false;
                }
            }
        }
    }
    return true;
}

long QueenProblem::getNumberOfSolutions() {
    if ( ! isSolved() ) {
        throw std::logic_error("problem is not solved");
    }
    return numberOfSolutions;
}

QueenProblem::~QueenProblem() {
    for ( int i=0; i < QueenProblem::size; i++) {
        delete[] QueenProblem::board[i];
    }
    delete[] QueenProblem::board;
}



/** @} */ // end doxygroup
