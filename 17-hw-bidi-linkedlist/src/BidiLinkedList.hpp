///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains pseudo-implementation part of bidirectional list structure
/// template declared in the file's h-counterpart
///
/// © Sergey Shershakov 2015–2016
///
/// No part of this code can be used without an explicit permission of the author.
/// The exception is done for educational goals of the course "Algorithms and Data
/// Structures" provided by the School of Software Engineering of the Faculty
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////
#define IWANNAGET10POINTS

#include <stdexcept>


//==============================================================================
// class BidiList<T>::Node
//==============================================================================


template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::Node::insertAfterInternal(Node* insNode)
{
    // here we use "this" keyword for enhancing the fact we deal with curent node!
    Node* afterNode = this->_next;      // an element, which was after node
    // relink this node
    this->_next = insNode;
    // relink other node
    insNode->_prev = this;
    insNode->_next = afterNode;
    // optionally relink afterNode
    if (afterNode)
        afterNode->_prev = insNode;
    return insNode;
}

//==============================================================================
// class BidiList<T>
//==============================================================================


// следующий метод полностью реализован
template <typename T>
BidiLinkedList<T>::~BidiLinkedList()
{
    clear();
}


template <typename T>
void BidiLinkedList<T>::clear()
{
    Node* cur = _head;
    while (cur)
    {
        Node* kill = cur;
        cur = cur->getNext();
        delete kill;
    }
    invalidateSize();
}

template <typename T>
size_t BidiLinkedList<T>::getSize()
{
    if (_size == NO_SIZE)
        calculateSize();

    return _size;
}


template <typename T>
void BidiLinkedList<T>::calculateSize()
{
    _size = 0;
    Node* cur = _head;
    while (cur)
    {
        cur = cur->getNext();
        _size++;
    }
}



template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::getLastNode() const
{
    if (! _head)
        return nullptr;
    Node* cur = _head;
    while (cur->getNext())
    {
        cur = cur->getNext();
    }
    return cur;
}


template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::appendEl(const T& val)
{
    Node* newNode = new Node(val);
    // inserts after last node, size is going to be invalidated there
    return insertNodeAfter(getLastNode(), newNode);
}


// следующий метод полностью реализован, на него можно смотреть, как на образец и "делать два раза ку!" (с)
// не надо изменять его, если нет желания сделать какую-то специальную супер-оптимизацию
template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::insertNodeAfter(Node* node, Node* insNode)
{
    if (!insNode)
        throw std::invalid_argument("insNode is nullptr");

    if (!node)
        node = getLastNode();

    // if last node is nullptr itself, it means that no elements in the list at all
    if (!node)
        _head = insNode;
    else
        node->insertAfterInternal(insNode);

    invalidateSize();

    return insNode;
}


// !...
// Здесь должна быть реализация метода BidiLinkedList<T>::insertNodesAfter().
// В отличие от других методов, здесь не представлен даже заголовок, поэтому придется потрудиться!
// !...
template <typename T>
void BidiLinkedList<T>::insertNodesAfter(Node* node, Node* beg, Node* end)
{
    if (! beg || ! end)
        throw std::invalid_argument("Unexpected nullptr");

    if (! node)
        node = getLastNode();

    if (! node)
    {
        // if list is empty
        _head = beg;
    }
    else
    {
        // cache our tail
        Node* our_next = node->_next;
        // relink ours
        node->_next = beg;
        // relink theirs
        beg->_prev = node;
        end->_next = our_next;
        // optionally relink our_next
        if (our_next)
            our_next->_prev = end;
    }
    invalidateSize();
}



// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS


template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::insertNodeBefore(Node* node, Node* insNode)
{
    if (! insNode)
        throw std::invalid_argument("Unexpected nullptr");
    if (! node)
        node = _head;

    if (! node)
    {
        // if list is empty
        _head = insNode;
    }
    else
    {
        // cache before node
        Node* our_before = node->getPrev();
        // relink our node
        node->_prev = insNode;
        // relink other node
        insNode->_next = node;
        insNode->_prev = our_before;
        // optionally relink our_before
        if (our_before)
            our_before->_next = insNode;
    }
    // if you were inserting before _head
    if (node == _head)
        _head = insNode;

    invalidateSize();

    return insNode;
}


template <typename T>
void BidiLinkedList<T>::insertNodesBefore(Node* node, Node* beg, Node* end)
{
    if (! beg || ! end)
        throw std::invalid_argument("Unexpected nullptr");
    if (! node)
        node = _head;

    if (! node)
    {
        // if list is empty
        _head = beg;
    }
    else
    {
        // cache our before
        Node* our_before = node->getPrev();
        // relink our node
        node->_prev = end;
        // relink their node
        end->_next = node;
        beg->_prev = our_before;
        // optionally relink our_before
        if (our_before)
            our_before->_next = beg;
    }
    if (node == _head)
        // if you were inserting before _head
        _head = beg;
    invalidateSize();
}



#endif // IWANNAGET10POINTS


template <typename T>
void BidiLinkedList<T>::cutNodes(Node* beg, Node* end)
{
    if (! beg || ! end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr");

    Node* after_end = end->getNext();
    Node* before_beg = beg->getPrev();
    // check if relink is needed. Some may be nullptr
    if (before_beg)
        before_beg->_next = after_end;
    if (after_end)
        after_end->_prev = before_beg;
    // if we deleted head node, assign nullptr
    if (_head == beg)
    {
        if (after_end)
            _head = after_end;
        else
            _head = nullptr;
    }
    invalidateSize();
}


template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::cutNode(Node* node)
{
    if (! node)
        throw std::invalid_argument("Unexpected nullptr");
    Node* after = node->getNext();
    Node* before = node->getPrev();
    // check if relink is needed. Some may be nullptr
    if (before)
        before->_next = after;
    if (after)
        after->_prev = before;
    // if we deleted head node, assign nullptr
    if (_head == node)
    {
        if (after)
            _head = after;
        else
            _head = nullptr;
    }
    invalidateSize();
    return node;
}


template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::findFirst(Node* startFrom, const T& val)
{
    if (!startFrom)
        return nullptr;
    // iterate over list
    while (startFrom)
    {
        if (startFrom->getValue() == val)
        {
            // if match is found return
            return startFrom;
        }
        // else continue to next node
        startFrom = startFrom->getNext();
    }
    return nullptr;     // not found
}



template <typename T>
typename BidiLinkedList<T>::Node**
    BidiLinkedList<T>::findAll(Node* startFrom, const T& val, int& size)
{
    if (! startFrom)
        return nullptr;

    // try not to use any standard containers. create an array only when found a first occurence
    Node** res = nullptr;
    size = 0;

    while (startFrom)
    {
        if (startFrom->getValue() == val)
        {
            if (res)
            {
                res[size] = startFrom;
            }
            else
            {
                // create array first time
                res = new Node*[ getSize() ];
                res[size] = startFrom;
            }
            size++;
        }
        startFrom = startFrom->getNext();
    }

    // recreates array if created
    if (res)
    {
        Node** tmp = new Node*[size];
        for (int i=0; i < size; i++)
            tmp[i] = res[i];
        delete[] res;
        res = tmp;
    }

    return res;
}

// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS

template <typename T>
typename BidiLinkedList<T>::Node**
BidiLinkedList<T>::cutAll(Node* startFrom, const T& val, int& size)
{

    if (! startFrom)
        return nullptr;

    // try not to use any standard containers. create an array only when found a first occurence
    Node** cut = nullptr;
    size = 0;

    while (startFrom)
    {
        if (startFrom->getValue() == val)
        {
            if (cut)
            {
                // just remember the nodes that should be cut
                cut[size] = startFrom;
            }
            else
            {
                // create array first time
                cut = new Node*[ getSize() ];
                cut[size] = startFrom;
            }
            size++;
        }
        startFrom = startFrom->getNext();
    }

    // recreates array if created
    if (cut)
    {
        Node** tmp = new Node*[size];
        for (int i=0; i < size; i++)
        {
            tmp[i] = cut[i];
            // also actually cut the nodes here
            cutNode(cut[i]);
        }
        delete[] cut;
        cut = tmp;
    }

    invalidateSize();

    return cut;
}

#endif // IWANNAGET10POINTS
