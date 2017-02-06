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

// Конструктор копирования.
// Реализовал Артем Абрамов БПИ151
// "other" can not be a "const" reference because we use getPreHead function which is not "const"
template <class T>
LinkedList<T>::LinkedList(LinkedList<T>& other)
{
    // create preHead node
    _preHead = new Node<T>();
    // copy values
    Node<T>* cur = other.getPreHead()->next;
    while (cur)
    {
        addElementToEnd(cur->value);
        cur = cur->next;
    }
}


// Оператор присваивания
// Реализовал Артем Абрамов БПИ151
// "other" can not be a "const" reference because we use getPreHead function which is not "const"
template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>& other)
{
    if (this == &other)
        return *this;
    // clear this list, does not delete _preHead
    deleteNodes(_preHead, getEndNode(_preHead));
    // copy values
    Node<T>* cur = other.getPreHead()->next;
    while (cur)
    {
        addElementToEnd(cur->value);
        cur = cur->next;
    }
    return *this;
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
    return cur_data->value;
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
    Node<T>* end = getEndNode(_preHead);
    end->next = tmp;
}

/// Удаляет все узлы в диапазоне \c pNodeBefore->next ... \с pNodeLast (включительно).
template <class T>
void LinkedList<T>::deleteNodes(Node<T>* pNodeBefore, Node<T>* pNodeLast)
{
    if (! pNodeBefore || ! pNodeLast)
        throw std::invalid_argument("Invalid pNodeBefore pointer");
    while (pNodeBefore->next != pNodeLast)
    {
        // if we travelled whole list, but did not find end node
        if (! pNodeBefore->next)
            throw std::invalid_argument("Invalid pNodeLast pointer");
        deleteNextNode(pNodeBefore);
    }
    // only when they pNodeBefore->next == pNodeLast are equal
    deleteNextNode(pNodeBefore);
}

/// Находит последний узел в списке.
/// Реализовал Артем Абрамов БПИ151
template <class T>
Node<T>* LinkedList<T>::getEndNode(Node<T>* node)
{
    Node<T>* end_node = node ? node : _preHead;
    while (end_node->next)
        end_node = end_node->next;
    return end_node;
}

/// Отсоединяет узел из списка и возвращает ссылку на него
/// Реализовал Абрамов Артем БПИ 151
template <class T>
Node<T>* LinkedList<T>::unlinkNextNode(Node<T>* pNodeBefore)
{
    if (! pNodeBefore || ! pNodeBefore->next)
        throw std::invalid_argument("Unexpected nullptr");
    Node<T>* tmp = pNodeBefore->next;
    pNodeBefore->next = pNodeBefore->next->next;
    return tmp;
}

/// Удаляет узел \c pNodeBefore->next.
template <class T>
void LinkedList<T>::deleteNextNode(Node<T>* pNodeBefore)
{
    delete unlinkNextNode(pNodeBefore);
}

/// Перемещает узлы \c pNodeBefore->next ... \c pNodeLast другого списка в конец текущего списка. 
/// Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
template <class T>
void LinkedList<T>::moveNodesToEnd(Node<T>* pNodeBefore, Node<T>* pNodeLast)
{
    moveNodesAfter(getEndNode(_preHead), pNodeBefore, pNodeLast);
}

/// Перемещает узел pNodeBefore->next из другого списка в конец текущего списка. 
/// После перемещения из другого списка этот узел исключается.
template <class T>
void LinkedList<T>::moveNodeToEnd(Node<T>* pNodeBefore)
{
    moveNodeAfter(getEndNode(_preHead), pNodeBefore);
}

/// Перемещает узлы \c pNodeBefore->next ... \c pNodeLast другого списка в текущий список
/// после узла \c pNode.
/// Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
template <class T>
void LinkedList<T>::moveNodesAfter(Node<T>* pNode, Node<T>* pNodeBefore, Node<T>* pNodeLast)
{
    // create pointer to our list tail
    Node<T>* this_tail = pNode;
    // choose first node form other list
    Node<T>* other_cur = pNodeBefore;
    // if data node in other list is not empty
    while (other_cur->next != pNodeLast)
    {
        if (! other_cur->next)
            throw std::invalid_argument("Unexpected nullptr");
        moveNodeAfter(this_tail, other_cur);
        this_tail = this_tail->next;
    }
    // need to do it one more time to move the pNodeLast
    moveNodeAfter(this_tail, other_cur);
}

/// Перемещает узел pNodeBefore->next из другого списка в текущий список после узла pNode.
/// После перемещения из другого списка этот узел исключается.
template <class T>
void LinkedList<T>::moveNodeAfter(Node<T>* pNode, Node<T>* pNodeBefore)
{
    // unlink other node from other list
    Node<T>* other_node = unlinkNextNode(pNodeBefore);
    // remember the tail
    Node<T>* our_tail = pNode->next;
    // plug in to our list
    pNode->next = other_node;
    other_node->next = our_tail;
}

} // namespace xi
