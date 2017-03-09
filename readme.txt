Задание выполнил Артем Абрамов БПИ151
В архиве помимо обязательных с сдаче файлов содержаться модифицированные файлы dna_element.h & dna_linkedlist.h

В файле dna_element.h был добавлен enum DNABase:
enum DNABase : char {
    A = 'A'
    , C = 'C'
    , T = 'T'
    , G = 'G'
};

В файле dna_linkedlist.h были добавлены следующие 4 функции:

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



