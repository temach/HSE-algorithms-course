////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Sergey Shershakov
// Version:      0.1.0
// Date:         01.05.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "rbtree.h"

// #include "../tests/gtest/src/def_dumper.h"

using namespace std;


template <typename Element, typename Compar>
class RBTreeDefDumper : public xi::IRBTreeDumper<Element, Compar> {
public:
    RBTreeDefDumper() //;
    {

    }

    ~RBTreeDefDumper() //;
    {
    }

public:

    virtual void rbTreeEvent(typename xi::IRBTreeDumper<Element,Compar>::RBTreeDumperEvent ev
                            , typename xi::IRBTreeDumper<Element,Compar>::TTree* tr
                            , typename xi::IRBTreeDumper<Element,Compar>::TTreeNode* nd) override
    {
    } // rbTreeEvent()

protected:

}; // class RBTreeDefDumper 



void simplestTest()
{
    using namespace xi;

    RBTree<int> tree1;
    // tree1.setDumper(nullptr);
    IRBTreeDumper<int, std::less<int> >* rbTreeDefDumper = new RBTreeDefDumper<int, std::less<int> >();
    tree1.setDumper(rbTreeDefDumper);

    tree1.insert(5);
    tree1.insert(8);
    tree1.insert(10);
    tree1.insert(29);
}


int main()
{
    cout << "Hello, World!" << endl;

    simplestTest();

    return 0;
}
