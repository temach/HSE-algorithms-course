////////////////////////////////////////////////////////////////////////////////
// Module Name:  linked_list.h/cpp
// Authors:      Sergey Shershakov, Leonid Dworzanski
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
//
// Отделенная часть заголовка шаблона класса "Связанный список"
//
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

namespace xi {

template <class T>
LinkedList<T>::LinkedList() 
{
    //Creation of the dummy/sentinel element
    _preHead = new Node<T>;
    _preHead->next = nullptr;

    // TODO: Write your code here
    // ...
}

template <class T> 
LinkedList<T>::~LinkedList()
{
    // TODO: Write your code here

    // ...

    // на забудьте удалить иск. элемент, например так:
    delete _preHead;
}


// TODO: Write your code here


} // namespace xi