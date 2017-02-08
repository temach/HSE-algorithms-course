////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     LinkedList-related classes definition
/// \authors   Sergey Shershakov, Leonid Dworzanski
/// \version   0.2.0
/// \date      06.02.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Определение классов связанного списка и его узла.
///
////////////////////////////////////////////////////////////////////////////////

#ifndef BROKENDNA_LINKEDLIST_H_
#define BROKENDNA_LINKEDLIST_H_


/// Так как классы связанного списка являются типами общего назначения и подходят
/// для решения не только частной задачи с починкой ДНК, мы их заключаем в пространство
/// имен нашей рабочей группы, чтобы снизить вероятность конфликта имен при включении
/// этих типов в другие проекты.
namespace xi {



/** \brief Узел связного списка.
 *
 *  Класс узла является оберткой для элементов типа \c T, которые хранятся в списке.
 */
template <class T>
class Node {
public:
    /// Конструктор
    Node() : next(nullptr) { }

public:
    /// Собственно значение элемента.
    T value;
    
    /// Указатель на узел-обертку следующего элемента
    Node* next;
}; // class Node




/** \brief Шаблон класса связного списка.
 *
 *  Односвязный список. Особенность такого списка — практически все операции с «текущим элементом»
 *  выполняются через указатель на его предшественника.
 */
template <class T> 
class LinkedList { 

public:
    /// Конструктор по умолчанию
    LinkedList();

    /// Деструктор
    ~LinkedList();

    /**
     * @brief Конструктор копирования.
     * Реализовал Артем Абрамов БПИ151
     *
     * @param other Другой экземпляр типа SafeArray<T>. Не может быть "const" так 
     *              как в функции на нем вызываеться метод getPreHead() который не "const"
     */
    LinkedList(const LinkedList<T>& other);


    /**
     * @brief Оператор присваивания
     * Реализовал Артем Абрамов БПИ151
     *
     * @param other Другой экземпляр типа SafeArray<T>. Не может быть "const" так 
     *              как в функции на нем вызываеться метод getPreHead() который не "const"
     *
     * @return Ссылку на rhs объект.
     */
    LinkedList<T>& operator= (const LinkedList<T>& other);


public:
    /// Возвращаем псевдо-нулевой элемент PreHead
    Node<T>* getPreHead();

    /// Возвращает элемент по индексу. Операция дорогая, сложность — ...
    T& operator[] (int i);


    /// Возвращает размер списка (число элементов). Операция дорогая, ...
    int size();


    /// Создает и добавляет новый узел, несущий значение \c value, в конец текущего списка.
    void addElementToEnd(T& value);

    /// Удаляет все узлы в диапазоне \c pNodeBefore->next ... \с pNodeLast (включительно).
    void deleteNodes(Node<T>* pNodeBefore, Node<T>* pNodeLast);

    /// Удаляет узел \c pNodeBefore->next.
    void deleteNextNode(Node<T>* pNodeBefore);

    /// Перемещает узлы \c pNodeBefore->next ... \c pNodeLast другого списка в конец текущего списка. 
    /// Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
    void moveNodesToEnd(Node<T>* pNodeBefore, Node<T>* pNodeLast);

    /// Перемещает узел pNodeBefore->next из другого списка в конец текущего списка. 
    /// После перемещения из другого списка этот узел исключается.
    void moveNodeToEnd(Node<T>* pNodeBefore);

    /// Перемещает узлы \c pNodeBefore->next ... \c pNodeLast другого списка в текущий список
    /// после узла \c pNode.
    /// Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
    void moveNodesAfter(Node<T>* pNode, Node<T>* pNodeBefore, Node<T>* pNodeLast);

    /// Перемещает узел pNodeBefore->next из другого списка в текущий список после узла pNode.
    /// После перемещения из другого списка этот узел исключается.
    void moveNodeAfter(Node<T>* pNode, Node<T>* pNodeBefore);

    /**
     * @brief Находит последний узел в списке.
     * Реализовал Артем Абрамов БПИ151
     *
     * @param node Опциональный параметр указывает на список по которому надо пройти.
     *             Если равен nullptr, проход начинаеться с указателя _preHead.
     *
     * @return Указатель на последний узел в списке.
     */
    Node<T>* getEndNode(Node<T>* node = nullptr);

    /**
     * @brief Отсоединяет узел из списка и возвращает ссылку на него.
     * Реализовал Артем Абрамов БПИ151
     *
     * @param pNodeBefore Указатель на узел до.
     *
     * @return Указатель на узел который был вынут из списка.
     */
    Node<T>* unlinkNextNode(Node<T>* pNodeBefore);


protected:

    /// Вспомогательный элемент — псевдонулевой элемент списка.
    /// Тип \c T должен поддерживать конструктор по умолчанию.
    Node<T>* _preHead;
    // Вспомогательный элемент

};

} // namespace xi

#include "linked_list.hpp"

#endif // BROKENDNA_LINKEDLIST_H_

