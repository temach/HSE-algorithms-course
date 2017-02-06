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
#include "linked_list.h"

namespace xi {

template <class T>
LinkedList<T>::LinkedList()
{
    //Creation of the dummy/sentinel element
    _preHead = new Node<T>();
    _preHead->next = nullptr;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* cur = _preHead;
    while (cur->next)
    {
        Node<T>* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    delete cur;
}

// Copy constructor
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
    // create preHead node
    _preHead = new Node<T>();
    // create pointer to our list tail
    Node<T>* this_tail = _preHead;
    // choose first node with data form other list
    Node<T>* other_cur = other.getPreHead()->next;
    // if data node in other list is not empty
    while (other_cur)
    {
        // make floating node (data node)
        Node<T>* new_our = new Node<T>();
        new_our->value = other_cur->value;
        // plug in out list
        this_tail->next = new_our;
        // advance our list end
        this_tail = new_our;
        // advance their list current
        other_cur = other_cur->next;
    }
}


// Copy assignemnt operator =
template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
    if (this == &other)
        return *this;

    // create preHead node
    _preHead = new Node<T>();
    // create pointer to our list tail
    Node<T>* this_tail = _preHead;
    // choose first node with data form other list
    Node<T>* other_cur = other.getPreHead()->next;
    // if data node in other list is not empty
    while (other_cur)
    {
        // make floating node (data node)
        Node<T>* new_our = new Node<T>();
        new_our->value = other_cur->value;
        // plug in out list
        this_tail->next = new_our;
        // advance our list end
        this_tail = new_our;
        // advance their list current
        other_cur = other_cur->next;
    }
}


/// Возвращаем псевдо-нулевой элемент PreHead
template <class T>
Node<T>* LinkedList<T>::getPreHead()
{
    return _preHead;
}

/// Возвращает элемент по индексу. Операция дорогая, 
/// сложность — N (надо пройти от начала списка до элемента с индексом i, зависит от колличества элементов N)
template <class T>
T& LinkedList<T>::operator[] (int i)
{
    using namespace std;
    // if index < 0 or list is empty
    if (i < 0 || ! _preHead->next)
        throw out_of_range("Index must be >= 0");
    Node<T>* cur_data = _preHead->next;
    while (i > 0)
    {
        if (! cur_data)
            throw out_of_range("Index too big");
        i--;
        cur_data = cur_data->next;
    }
    // we can guarantee that cur_data != nullptr
    return *cur_data;
}


/// Возвращает размер списка (число элементов). Операция дорогая, 
/// сложность = N (надо пройти от начала списка до элемента с индексом i, зависит от колличества элементов N)
template <class T>
int LinkedList<T>::size()
{
    int i = 0;
    Node<T>* cur = _preHead;
    while (cur->next)
    {
        i++;
        cur = cur->next;
    }
    return i;
}


/// Создает и добавляет новый узел, несущий значение \c value, в конец текущего списка.
template <class T>
void LinkedList<T>::addElementToEnd(T& value)
{
    Node<T>* tmp = new Node<T>();
    tmp->value = value;
    // get last node
    Node<T>* end_node = _preHead;
    while (end_node->next)
    {
        end_node = end_node->next;
    }
    end_node->next = tmp;
}

/// Удаляет все узлы в диапазоне \c pNodeBefore->next ... \с pNodeLast (включительно).
template <class T>
void LinkedList<T>::deleteNodes(Node<T>* pNodeBefore, Node<T>* pNodeLast)
{
    if (! pNodeBefore)
        throw std::invalid_argument("Invalid pNodeBefore pointer");
    Node<T>* cur = pNodeBefore->next;
    while (cur != pNodeLast)
    {
        // if we travelled whole list, but did not find end node
        if (! cur)
            throw std::invalid_argument("Invalid pNodeLast pointer");
        Node<T>* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    Node<T>* tmp = cur->next;
    pNodeBefore->next = tmp;
    delete cur;
}

/// Удаляет узел \c pNodeBefore->next.
template <class T>
void LinkedList<T>::deleteNextNode(Node<T>* pNodeBefore)
{
    if (! pNodeBefore || ! pNodeBefore->next)
        throw std::invalid_argument("Unexpected nullptr");
    Node<T>* tmp = pNodeBefore->next->next;
    delete pNodeBefore->next;
    pNodeBefore->next = tmp;
}

/// Перемещает узлы \c pNodeBefore->next ... \c pNodeLast другого списка в конец текущего списка. 
/// Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
template <class T>
void LinkedList<T>::moveNodesToEnd(Node<T>* pNodeBefore, Node<T>* pNodeLast)
{
}

/// Перемещает узел pNodeBefore->next из другого списка в конец текущего списка. 
/// После перемещения из другого списка этот узел исключается.
template <class T>
void LinkedList<T>::moveNodeToEnd(Node<T>* pNodeBefore)
{
}

/// Перемещает узлы \c pNodeBefore->next ... \c pNodeLast другого списка в текущий список
/// после узла \c pNode.
/// Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
template <class T>
void LinkedList<T>::moveNodesAfter(Node<T>* pNode, Node<T>* pNodeBefore, Node<T>* pNodeLast)
{
}

/// Перемещает узел pNodeBefore->next из другого списка в текущий список после узла pNode.
/// После перемещения из другого списка этот узел исключается.
template <class T>
void LinkedList<T>::moveNodeAfter(Node<T>* pNode, Node<T>* pNodeBefore)
{
}

} // namespace xi
