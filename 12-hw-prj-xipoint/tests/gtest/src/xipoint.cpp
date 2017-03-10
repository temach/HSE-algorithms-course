////////////////////////////////////////////////////////////////////////////////
// Module Name:  xipoint.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         14.01.2017
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "xipoint.h"

#include <stdexcept>
#include <algorithm>        // min

#include <cstring>
#include <cstdlib>

namespace xi {

/*=============================================================================*/
/**
    *  @defgroup point_funcs Define all Point functions.
    *  @{
    */

/* -----------------------------------------------------------------------------*/
Point::Point(int x, int y) {
    _x = x;
    _y = y;
}

/* -----------------------------------------------------------------------------*/
void Point::shift(int shf) {
    _x += shf;
    _y += shf;
}

/* -----------------------------------------------------------------------------*/
void Point::shift(int xSh, int ySh) {
    _x += xSh;
    _y += ySh;
}

/* -----------------------------------------------------------------------------*/
void Point::shift(const Point& pt) {
    _x += pt.getX();
    _y += pt.getY();
}

/* -----------------------------------------------------------------------------*/
///< Gets x-coordinate
int Point::getX () const {
    return _x;
}

/* -----------------------------------------------------------------------------*/
///< Gets y-coordinate
int Point::getY () const {
    return _y;
}

/* -----------------------------------------------------------------------------*/
///< Sets x-coordinate
void Point::setX(int x) {
    _x = x;
}

/* -----------------------------------------------------------------------------*/
///< Sets y-coordinate
void Point::setY(int y) {
    _y = y;
}

/** @} */ // end doxygroup


/*=============================================================================*/
/**
*  @defgroup point_array_funcs Define all PointArray functions
*  @{
*/


/* -----------------------------------------------------------------------------*/
PointArray::PointArray() {
    _size=0;
    _arr = nullptr;
}

/* -----------------------------------------------------------------------------*/
/*
* Documentation for the constructor explicitly states
* "Initialiaze an object with c-style array", hence we
* make use of malloc, memmove, realloc.
*/
PointArray::PointArray(const Point points[], const PointArray::Uint n) {
    _size = n;
    _arr = (Point*) std::malloc(sizeof(Point) * n);
    std::memmove(_arr, points, n * sizeof(Point));
}

/* -----------------------------------------------------------------------------*/
PointArray::PointArray(const PointArray& pv) : PointArray(pv.getRawPtr(), pv.getSize()) {
}

/* -----------------------------------------------------------------------------*/
PointArray::~PointArray() {
    clear();
}

/* -----------------------------------------------------------------------------*/
void PointArray::append(const Point& pt) {
    resize(_size + 1);
    _arr[_size-1] = pt;
}

/* -----------------------------------------------------------------------------*/
void PointArray::insert(const Point& pt, PointArray::Uint pos) {
    if (pos > _size) { pos = _size; };
    if (pos < _size) { pos = 0; }
    // resize will make _size >= 1
    resize(_size + 1);
    if (_size-1 > pos) {
        memmove(_arr+pos, _arr+pos+1, _size-pos-1);
    }
    _arr[pos] = pt;
}

/* -----------------------------------------------------------------------------*/
void PointArray::remove(const PointArray::Uint pos) {
    if (_arr == nullptr || pos > _size-1) {
        return;
    }
    memmove(_arr+pos+1, _arr+pos, _size-pos-1);
    resize(_size-1);
}

/* -----------------------------------------------------------------------------*/
void PointArray::clear() {
    if (_arr == nullptr) {
        return;
    }
    // realloc with 0 = free
    resize(0);
}

/* -----------------------------------------------------------------------------*/
const PointArray::Uint PointArray::getSize() const {
    return _size;
}

/* -----------------------------------------------------------------------------*/
Point* PointArray::get(PointArray::Uint pos) {
    if (_arr == nullptr || pos > _size) {
        return nullptr;
    }
    return _arr + pos;
}

/* -----------------------------------------------------------------------------*/
const Point* PointArray::get(PointArray::Uint pos) const {
    if (_arr == nullptr || pos > _size) {
        return nullptr;
    }
    return _arr + pos;
}

/* -----------------------------------------------------------------------------*/
void PointArray::resize(PointArray::Uint n) {
    // if we need to get more memory, realloc
    Point* tmp = (Point*) std::realloc(_arr, n * sizeof(Point));
    if (! tmp && n>0) {
        throw std::runtime_error("Can not allocate memory");
    }
    _arr = tmp;
    _size = n;
}

/** @} */ // end doxygroup

} // namespace xi {
