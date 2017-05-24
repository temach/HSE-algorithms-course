////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Реализация классов красно-черного дерева
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures"
///            provided by  the School of Software Engineering of the Faculty
///            of Computer Science at the Higher School of Economics.
///
/// "Реализация" (шаблонов) методов, описанных в файле rbtree.h
///
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>        // std::invalid_argument
// #include "rbtree.h"


namespace xi {


//==============================================================================
// class RBTree::node
//==============================================================================

template <typename Element, typename Compar >
RBTree<Element, Compar>::Node::~Node()
{
    if (_left)
        delete _left;
    if (_right)
        delete _right;
}



template <typename Element, typename Compar>
typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setLeft(Node* lf)
{
    // предупреждаем повторное присвоение
    if (_left == lf)
        return nullptr;

    // если новый левый — действительный элемент
    if (lf)
    {
        // если у него был родитель
        if (lf->_parent)
        {
            // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
            if (lf->_parent->_left == lf)
                lf->_parent->_left = nullptr;
            else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                lf->_parent->_right = nullptr;
        }

        // задаем нового родителя
        lf->_parent = this;
    }

    // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
    Node* prevLeft = _left;
    _left = lf;

    if (prevLeft)
        prevLeft->_parent = nullptr;

    return prevLeft;
}


template <typename Element, typename Compar>
typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setRight(Node* rg)
{
    // предупреждаем повторное присвоение
    if (_right == rg)
        return nullptr;

    // если новый правый — действительный элемент
    if (rg)
    {
        // если у него был родитель
        if (rg->_parent)
        {
            // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
            if (rg->_parent->_left == rg)
                rg->_parent->_left = nullptr;
            else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                rg->_parent->_right = nullptr;
        }

        // задаем нового родителя
        rg->_parent = this;
    }

    // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
    Node* prevRight = _right;
    _right = rg;

    if (prevRight)
        prevRight->_parent = nullptr;

    return prevRight;
}


//==============================================================================
// class RBTree
//==============================================================================

template <typename Element, typename Compar >
RBTree<Element, Compar>::RBTree()
{
    _nil = new Node();
    _nil->_left = _nil->_right = _nil->_parent = _nil;
    _root_parent = new Node();
    _root_parent->_left = _root_parent->_right = _root_parent->_parent = _nil;

    _dumper = nullptr;
}

template <typename Element, typename Compar >
RBTree<Element, Compar>::~RBTree()
{
    // грохаем пока что всех через корень
    if (_root_parent->_left)
        delete _root_parent;
}


template <typename Element, typename Compar >
void RBTree<Element, Compar>::deleteNode(Node* nd)
{
    // если переданный узел не существует, просто ничего не делаем, т.к. в вызывающем проверок нет
    if (nd == nullptr)
        return;

    // потомков убьет в деструкторе
    delete nd;
}

/***********************************************************************/
/*  FUNCTION:  TreeInsertHelp  */
/**/
/*  INPUTS:  z is the node to insert */
/**/
/*  OUTPUT:  none */
/**/
/**/
/*  EFFECTS:  Inserts z into the tree as if it were a regular binary tree */
/*            using the algorithm described in _Introduction_To_Algorithms_ */
/*            by Cormen et al.  This funciton is only intended to be called */
/*            by the Insert function and not by the user */
/***********************************************************************/


template <typename Element, typename Compar >
void RBTree<Element, Compar>::TreeInsertHelp(Node* z)
{
  //  This function should only be called by RBTree::insert
  Node* x;
  Node* y;

  //  Modifies Input:  this, z
  z->_left = z->_right = _nil;
  y = _root_parent;
  x = _root_parent->_left;
  while( x != _nil) {
    y = x;
    if ( x->_key > z->_key) {
      x = x->_left;
    } else { /* x->key <= z->key */
      x = x->_right;
    }
  }
  z->_parent = y;
  if ( (y == _root_parent) || (y->_key > z->_key) ) {
    y->_left = z;
  } else {
    y->_right = z;
  }
}




template <typename Element, typename Compar >
void RBTree<Element, Compar>::insert(const Element& key)
{
    // этот метод можно оставить студентам целиком
    Node* newNode;

    newNode = insertNewBstEl(key);
    newNode->_color = Color::RED;

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_BST_INS, this, newNode);

    rebalance(newNode);

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_INSERT, this, newNode);

}




template <typename Element, typename Compar>
const typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::find(const Element& key)
{
    Node* x = _root_parent->left;
    Node* lastBest = nullptr;
    Node* result = nullptr;

    while (_nil != x) {
        if ( x->_key > key ) {
            x = x->_left;
        } else {
            lastBest = x;
            x = x->_right;
        }
    }
    if ( (lastBest) && (key == lastBest->_key) ) {
        result = lastBest;
    }
    return result;
}

template <typename Element, typename Compar >
typename RBTree<Element, Compar>::Node*
        RBTree<Element, Compar>::insertNewBstEl(const Element& key)
{
    Node* x;
    x = new Node(key);
    TreeInsertHelp(x);
    return x;
}


template <typename Element, typename Compar >
typename RBTree<Element, Compar>::Node*
    RBTree<Element, Compar>::rebalanceDUG(Node* nd)
{
    // TODO: этот метод студенты могут оставить как есть и реализовать при декомпозиции балансировки дерева
    //
    // suppress unused variable warning
    (void) nd;
    return nullptr;
}


template <typename Element, typename Compar >
void RBTree<Element, Compar>::rebalance(Node* nd)
{
    Node* y;

    while(nd->_parent->_color) { /* use sentinel instead of checking for root */
        if (nd->_parent == nd->_parent->_parent->_left) {
            y = nd->_parent->_parent->_right;
            if (y->_color) {
                nd->_parent->_color = BLACK;
                y->_color = BLACK;
                nd->_parent->_parent->_color = RED;
                nd = nd->_parent->_parent;
                // отладочное событие
                if (_dumper)
                    _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR1, this, nd);
            } else {
                if (nd == nd->_parent->_right) {
                    nd = nd->_parent;
                    rotLeft(nd);
                }
                nd->_parent->_color = BLACK;
                nd->_parent->_parent->_color = RED;
                rotRight(nd->_parent->_parent);
            } 
        } else { /* case for nd->_parent == nd->_parent->_parent->_right */
            /* this part is just like the section above with */
            /* _left and _right interchanged */
            y = nd->_parent->_parent->_left;
            if (y->_color) {
                nd->_parent->_color = BLACK;
                y->_color = BLACK;
                nd->_parent->_parent->_color = RED;
                nd = nd->_parent->_parent;
                // отладочное событие
                if (_dumper)
                    _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3G, this, nd);
            } else {
                if (nd == nd->_parent->_left) {
                    nd = nd->_parent;
                    rotRight(nd);
                }
                nd->_parent->_color = BLACK;
                nd->_parent->_parent->_color = RED;
                rotLeft(nd->_parent->_parent);
                // отладочное событие
                if (_dumper)
                    _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3D, this, nd);
            }
        }
    }
    _root_parent->_left->_color = BLACK;
}



template <typename Element, typename Compar>
void RBTree<Element, Compar>::rotLeft(typename RBTree<Element, Compar>::Node* nd)
{
    // правый потомок, который станет после левого поворота "выше"
    Node* y = nd->_right;

    if (!y)
        throw std::invalid_argument("Can't rotate left since the right child is nil");

    /*  I originally wrote this function to use the sentinel for */
    /*  nil to avoid checking for nil.  However this introduces a */
    /*  very subtle bug because sometimes this function modifies */
    /*  the parent pointer of nil.  This can be a problem if a */
    /*  function which calls rotLeft also uses the nil sentinel */
    /*  and expects the nil sentinel's parent pointer to be unchanged */
    /*  after calling this function.  For example, when DeleteFixUP */
    /*  calls rotLeft it expects the parent pointer of nil to be */
    /*  unchanged. */

    y = nd->_right;
    nd->_right = y->_left;

    if (y->_left != _nil) y->_left->_parent = nd; /* used to use sentinel here */
    /* and do an unconditional assignment instead of testing for nil */

    y->_parent = nd->_parent;

    /* instead of checking if nd->_parent is the root as in the book, we */
    /* count on the root sentinel to implicitly take care of this case */
    if( nd == nd->_parent->_left) {
        nd->_parent->_left = y;
    } else {
        nd->_parent->_right = y;
    }
    y->_left = nd;
    nd->_parent = y;

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_LROT, this, nd);
}



template <typename Element, typename Compar>
void RBTree<Element, Compar>::rotRight(typename RBTree<Element, Compar>::Node* nd)
{
    Node* x;

    /*  I originally wrote this function to use the sentinel for */
    /*  nil to avoid checking for nil.  However this introduces a */
    /*  very subtle bug because sometimes this function modifies */
    /*  the parent pointer of nil.  This can be a problem if a */
    /*  function which calls rotLeft also uses the nil sentinel */
    /*  and expects the nil sentinel's parent pointer to be unchanged */
    /*  after calling this function.  For example, when DeleteFixUP */
    /*  calls rotLeft it expects the parent pointer of nil to be */
    /*  unchanged. */

    x = nd->_left;
    nd->_left = x->_right;

    if (_nil != x->_right)  x->_right->_parent = nd; /*used to use sentinel here */
    /* and do an unconditional assignment instead of testing for nil */

    /* instead of checking if nd->_parent is the root as in the book, we */
    /* count on the root sentinel to implicitly take care of this case */
    x->_parent = nd->_parent;
    if( nd == nd->_parent->_left) {
        nd->_parent->_left = x;
    } else {
        nd->_parent->_right = x;
    }
    x->_right = nd;
    nd->_parent = x;

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RROT, this, nd);
}


} // namespace xi

