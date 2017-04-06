// Артем Абрамов БПИ 151
#include <cstdlib>
#include <random>
#include <stdexcept>

std::random_device rd{};
std::mt19937 mt{rd()};
std::uniform_real_distribution<double> dist{0.0, 1.0};

//=============================================================================
//== NodeSkipList =============================================================
//=============================================================================

template <class Value, class Key, int numLevels>
void NodeSkipList<Value,Key,numLevels>::clear(void)
{
    for (int i = 0; i < numLevels; ++i)
    {
        this->m_nextjump[i] = 0;
    }
    this->m_levelHighest = -1;
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(void)
{
    clear();
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key)
{
    clear();

    this->m_key = key;
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key, Value value)
{
    clear();

    this->m_key = key;
    this->m_value = value;
}
//=============================================================================
//== End of: NodeSkipList =====================================================
//=============================================================================

//=============================================================================
//== SkipList =================================================================
//=============================================================================
template <class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(double probability)
{
    m_probability = probability;
    this->m_pPreHead->m_next = this->m_pPreHead;
    for (int i = 0; i < numLevels; ++i)
    {
        // Lets use m_pPreHead as a final sentinel element
        this->m_pPreHead->m_nextjump[i] = this->m_pPreHead;
    }
    this->m_pPreHead->m_levelHighest = numLevels-1;
}

template <class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::insert(Value value, Key key)
{
    TypeNode* last_smaller = this->m_pPreHead;
    // array to remember all the last_smaller nodes except the one in the base layer
    TypeNode* arr[this->m_pPreHead->m_levelHighest + 1];
    // search via levels
    int level = this->m_pPreHead->m_levelHighest;
    // note: >=
    while (level >= 0)
    {
        while (last_smaller->m_nextjump[level] != this->m_pPreHead
                && last_smaller->m_nextjump[level]->m_key < key
              )
        {
            last_smaller = last_smaller->m_nextjump[level];
        }
        arr[level] = last_smaller;
        level--;
    }
    // find smallest outside of level
    while (last_smaller->m_next != this->m_pPreHead
            && last_smaller->m_next->m_key < key
          )
    {
        last_smaller = last_smaller->m_next;
    }
    // create new node
    TypeNode* created = new TypeNode(key, value);
    // insert it
    TypeNode* remember = last_smaller->m_next;
    last_smaller->m_next = created;
    created->m_next = remember;
    // propage to higher levels
    level = -1;
    while (level < this->m_pPreHead->m_levelHighest)
    {
        // if probability fails, stop making skip levels
        double p = dist(mt);
        if (p > this->m_probability)
            break;
        level++;
        // insert it at level
        TypeNode* last_smaller_level = arr[level];
        TypeNode* remember_on_level = last_smaller_level->m_nextjump[level];
        last_smaller_level->m_nextjump[level] = created;
        created->m_nextjump[level] = remember_on_level;
    }
    created->m_levelHighest = level;
}

template <class Value, class Key, int numLevels>
typename SkipList<Value, Key, numLevels>::TypeNode * SkipList<Value, Key, numLevels>::findFirst(Key key) const
{
    TypeNode* last_smaller = findLastLessThan(key);
    if (last_smaller->m_next != this->m_pPreHead
        && last_smaller->m_next->m_key == key
       )
    {
        // if the next node after last_smaller is equal to key return it
        return last_smaller->m_next;
    }
    // otherwise the next after last_smaller is bigger
    // so no such key exists
    return 0;
}

template <class Value, class Key, int numLevels>
typename SkipList<Value, Key, numLevels>::TypeNode * SkipList<Value, Key, numLevels>::findLastLessThan(Key key) const
{
    TypeNode* last_smaller = this->m_pPreHead;
    if (last_smaller->m_next == this->m_pPreHead)
    {
        // if the list is empty
        return this->m_pPreHead;
    }
    // search via levels
    int level = this->m_pPreHead->m_levelHighest;
    // note: >=
    while (level >= 0)
    {
        while (last_smaller->m_nextjump[level] != this->m_pPreHead
                && last_smaller->m_nextjump[level]->m_key < key
              )
        {
            last_smaller = last_smaller->m_nextjump[level];
        }
        level--;
    }
    // find smallest outside of level
    while (last_smaller->m_next != this->m_pPreHead
            && last_smaller->m_next->m_key < key
          )
    {
        last_smaller = last_smaller->m_next;
    }
    return last_smaller;
}

template <class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::remove(TypeNode * node)
{
    TypeNode* last_smaller = this->m_pPreHead;
    if (last_smaller->m_next == this->m_pPreHead)
    {
        // list is empty, nothing to remove
        throw std::invalid_argument("Invalid node");
    }
    // search via levels
    int level = this->m_pPreHead->m_levelHighest;
    // note: >=
    while (level >= 0)
    {
        // go over ususal level search
        while (last_smaller->m_nextjump[level] != this->m_pPreHead
                && last_smaller->m_nextjump[level]->m_key < node->m_key
              )
        {
            last_smaller = last_smaller->m_nextjump[level];
        }
        // set to first node with equal key at current sparse level
        TypeNode* eq_search = last_smaller;
        // search within equal keys
        while (eq_search->m_nextjump[level] != this->m_pPreHead
                && eq_search->m_nextjump[level]->m_key == node->m_key
              )
        {
            // if found exactly it erase
            if (eq_search->m_nextjump[level] == node)
            {
                // now we skip the node at this sparse level
                eq_search->m_nextjump[level] = eq_search->m_nextjump[level]->m_nextjump[level];
                break;
            }
        }
        // go down one level
        level--;
    }
    // find smallest outside of level
    while (last_smaller->m_next != this->m_pPreHead
            && last_smaller->m_next->m_key < node->m_key
          )
    {
        last_smaller = last_smaller->m_next;
    }
    // set to first node with equal key at base
    TypeNode* eq_search = last_smaller;
    // search within equal keys
    while (eq_search->m_next != this->m_pPreHead
            && eq_search->m_next->m_key == node->m_key
            )
    {
        // if found exactly it erase
        if (eq_search->m_next == node)
        {
            // now we skip the node at base level
            eq_search->m_next = eq_search->m_next->m_next;
            node->m_levelHighest = -1;
            return;
        }
    }
    throw std::invalid_argument("Invalid node");
}
//=============================================================================
//== End of: SkipList =========================================================
//=============================================================================
