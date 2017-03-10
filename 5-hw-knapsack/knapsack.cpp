/** @file
 * =====================================================================================
 *
 *       Filename:  knapsack.cpp
 *
 *    Description:  Implementation file for the knapsack algorithm
 *
 *        Version:  1.0
 *        Created:  10/14/2016 09:20:26 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Artem Abramov (aa), tematibr@gmail.com
 *
 * =====================================================================================
 */

#include "knapsack.h"
#include <stdexcept>
#include <utility>


/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup public_funcs Public functions to be implemented
 *  @{
 */


//-----------------------------------------------------------------------------
void Knapsack::initialize(const int capacity, const int* weights, const int* costs, const int n) {
    // free old memory
    if (grid != nullptr) {
        for ( int i=0; i < Knapsack::nItems+1; i++ ) {
            delete[] Knapsack::grid[i];
        }
        delete[] Knapsack::grid;
    }
    if (weights != nullptr) {
        delete[] Knapsack::weights;
    }
    if (costs != nullptr) {
        delete[] Knapsack::costs;
    }
    if (itemset != nullptr) {
        delete[] Knapsack::itemset;
    }
    Knapsack::maxCapacity = capacity;
    Knapsack::nItems = n;
    Knapsack::weights = new int[n];
    for ( int i=0; i < n; i++ ) {
        Knapsack::weights[i] = weights[i];
    }
    Knapsack::costs = new int[n];
    for ( int i=0; i < n; i++ ) {
        Knapsack::costs[i] = costs[i];
    }
    bpCost = 0;
    bpWeight = 0;
    Knapsack::itemset = new bool[n];
    Knapsack::initialized = true;
}


//-----------------------------------------------------------------------------
bool Knapsack::isInitialized() {
    return Knapsack::initialized;
}

//-----------------------------------------------------------------------------
bool Knapsack::isSolved() {
    return Knapsack::solved;
}

//-----------------------------------------------------------------------------
void Knapsack::solveRecursively() {
    if (! Knapsack::isInitialized() ) {
        throw std::logic_error("initialize not called!");
    }
    // free old memory
    if (grid != nullptr) {
        for ( int i=0; i < Knapsack::nItems+1; i++ ) {
            delete[] Knapsack::grid[i];
        }
        delete[] Knapsack::grid;
    }
    if (itemset != nullptr) {
        delete[] Knapsack::itemset;
    }
    // start solution
    Knapsack::buildGrid();
    grid[nItems][maxCapacity] = Knapsack::getFromGrid(Knapsack::nItems, Knapsack::maxCapacity);
    Knapsack::backtrack();
    Knapsack::solved = true;
}

//-----------------------------------------------------------------------------
void Knapsack::solveIteratively() {
    if (! Knapsack::isInitialized() ) {
        throw std::logic_error("initialize not called!");
    }
    // free old memory
    if (grid != nullptr) {
        for ( int i=0; i < Knapsack::nItems+1; i++ ) {
            delete[] Knapsack::grid[i];
        }
        delete[] Knapsack::grid;
    }
    if (itemset != nullptr) {
        delete[] Knapsack::itemset;
    }
    // solve the problem
    Knapsack::buildGrid();
    for (int j = 1; j <= nItems; j++) {
        for (int w = 1; w <= maxCapacity; w++) {
            if (weights[j - 1] <= w) {
                int left = grid[j - 1][w];
                int took = grid[j - 1][w - weights[j-1]] + Knapsack::costs[j - 1];
                grid[j][w] = std::max(left, took);
            }
            else {
                grid[j][w] = grid[j - 1][w];
            }
        }
    }
    Knapsack::backtrack();
    Knapsack::solved = true;
}



//-----------------------------------------------------------------------------
void Knapsack::solveGreedy() {
    if (! Knapsack::isInitialized() ) {
        throw std::logic_error("initialize not called!");
    }
    // free old memory
    if (itemset != nullptr) {
        delete[] Knapsack::itemset;
    }
    typedef std::pair<double,int> k2i;
    k2i* approximate = new k2i[nItems];
    for ( int i = 0; i < nItems; i++ ) {
        approximate[i] = std::make_pair(costs[i] / (double)weights[i], i);
    }
    // sort by koefficient
    for ( int i = 0; i < nItems; i++) {
        for ( int k = 0; k < nItems; k++ ) {
            if (approximate[i].first < approximate[k].first) {
                k2i tmp = approximate[i];
                approximate[i] = approximate[k];
                approximate[k] = tmp;
            }
        }
    }
    bpCost = 0;
    bpWeight = 0;
    itemset = new bool[nItems];
    for ( int i =0; i < nItems; i++ ) {
        itemset[i] = false;
    }
    for ( int i = nItems-1; i > 0; i-- ) {
        int index = approximate[i].second;
        if (weights[index] < (maxCapacity - bpWeight) ) {
            bpWeight += weights[index];
            bpCost += costs[index];
            itemset[index] = true;
        }
    }
    Knapsack::solved = true;
}

//-----------------------------------------------------------------------------
int Knapsack::getWeight() {
    if (! isSolved() ) {
        throw std::logic_error("problem is not solved yet.");
    }
    return Knapsack::bpWeight;
}

//-----------------------------------------------------------------------------
int Knapsack::getCost() {
    if (! isSolved() ) {
        throw std::logic_error("problem is not solved yet.");
    }
    return Knapsack::bpCost;
}

//-----------------------------------------------------------------------------
bool* Knapsack::getItemset() {
    if (! isSolved() ) {
        throw std::logic_error("problem is not solved yet.");
    }
    bool* set_copy = new bool[nItems];
    for ( int i=0; i < nItems; i++ ) {
        set_copy[i] = itemset[i];
    }
    return set_copy;
}

//-----------------------------------------------------------------------------
Knapsack::~Knapsack() {
    for ( int i=0; i < Knapsack::nItems+1; i++ ) {
        delete[] Knapsack::grid[i];
    }
    delete[] Knapsack::grid;
    delete[] Knapsack::weights;
    delete[] Knapsack::costs;
    delete[] Knapsack::itemset;
}


/** @} */ // end doxygroup



/* -----------------------------------------------------------------------------*/
/**
 *  @defgroup private_funcs Private functions
 *  @{
 */

//-----------------------------------------------------------------------------
void Knapsack::buildGrid() {
    Knapsack::grid = new int*[Knapsack::nItems+1];
    for ( int i=0; i < Knapsack::nItems+1; i++ ) {
        grid[i] = new int[Knapsack::maxCapacity + 1];
        for ( int k = 0; k < Knapsack::maxCapacity+1; k++ ) {
            if (k == 0 || i == 0) {
                grid[i][k] = 0;
            }
            else {
                grid[i][k] = -1;
            }
        }
    }
}


//-----------------------------------------------------------------------------
int Knapsack::getFromGrid(int item, int capacity) {
    if (item < 1 || capacity < 1) {
        return 0;
    }
    if (grid[item][capacity] != -1) {
        return grid[item][capacity];
    }
    if (weights[item-1] > capacity) {
        // if we can not take this
        grid[item][capacity] = getFromGrid(item-1, capacity);
        return grid[item][capacity];
    } else {
        // if we can take this
        int left = getFromGrid(item-1, capacity);
        int took = getFromGrid(item-1, capacity - weights[item-1]) + costs[item-1];
        grid[item][capacity] = std::max(left, took);
        return grid[item][capacity];
    }
}

//-----------------------------------------------------------------------------
void Knapsack::backtrack() {
    bpCost = grid[nItems][maxCapacity];
    bpWeight = 0;
    itemset = new bool[nItems];
    for ( int i =0; i < nItems; i++ ) {
        itemset[i] = false;
    }
    int max_i;
    int max_value = -1;
    int cur_capacity = maxCapacity;
    while (cur_capacity > 0) {
        max_value = 0;
        for (int row=0; row < nItems+1; row++) {
            // note: strictly >
            if (grid[row][cur_capacity] > max_value) {
                max_value = grid[row][cur_capacity];
                max_i = row;
            }
        }
        itemset[max_i - 1] = true;
        bpWeight += weights[max_i - 1];
        cur_capacity -= weights[max_i - 1];
    }
}


/** @} */ // end doxygroup


