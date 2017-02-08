////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "dna_repairer.h"

using namespace std;
using namespace xi;

// TODO: укажите здесь абсолютный путь к файлу с кусочками ДНК для восстановления
// static const char* INP_FILENAME = "../../../res/test.in";
// static const char* INP_FILENAME = "../../../res/test2.in";
// static const char* INP_FILENAME = "../../../res/test3.in";
// static const char* INP_FILENAME = "./test5.in";
static const char* INP_FILENAME = "./test6.in";
//
static string def = "";

template <class T>
void printLinkedList(LinkedList<T> list, string msg = def)
{
    if (msg.size() > 0)
        cout << msg << endl;
    Node<T>* p = list.getPreHead()->next;
    while (p)
    {
        cout << p->value << ", ";
        p = p->next;
    }
    cout << endl;
}

int main (int argc, char* argv[])
{
    try{
        DNARepairer dnarepairer;
        dnarepairer.readFile(INP_FILENAME);
        cout << "Broken DNAs" << endl;
        dnarepairer.printDNAStorage();
        dnarepairer.repairDNA();
        cout << "\nGood as it is" << endl;
        dnarepairer.printDNAStorage();
    }
    catch(exception &e) {
        cout << e.what();
    }
    catch (...){
        cout << "Something wrong happend." << endl;
    }
    cout << endl;
    return 0;
}

