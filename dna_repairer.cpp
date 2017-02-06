////////////////////////////////////////////////////////////////////////////////
// Module Name:  dna_repairer.h/cpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "dna_repairer.h"

#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;        // допустимо писать в глобальном пространстве только в cpp-файлах!
using namespace xi;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//  Очень важно!!
//  Этот файл является лишь примером-подсказкой, который
//  показывает как обращаться со списком имея доступ лишь
//  к pPreHead.
//  Вы должны опираясь на его реализовать свое правильное решение.
//  Например в методе readFile не проверяется формат и не
//  возбуждаются исключения, а repairDNA делает вообще
//  неизвестно что!!!
//  Кроме того этот пример будет работать только если у вас
//  правильно реализован linked_list.h

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




void DNARepairer::repairDNA()
{
    // Начало примера
    // ВАЖНО! Все содержимое этого метода всего лишь пример.
    // Удалите его и перепишите функцию repairDNA заново.

    Node<DNAElement>* it = DNAStorage.getPreHead();
    Node<DNA>* it1 = nullptr;
    Node<DNA>* it2 = nullptr;

    //Сохраняем указатель на первый узел с ДНК в it1
    it = it->next;
    it1 = it;

    //Сохраняем указатель на второй узел с ДНК в it2
    it = it->next;
    it2 = it;

    //Ищем элемент с id="a" во втором ДНК
    Node<DNAElement>* it3 = it2->value.getPreHead();
    while (it3->next != nullptr &&
        it3->next->value.id != "a")
    {
        it3 = it3->next;
    }

    //Перемещение одного элемента из второго списка в первый
    it1->value.moveNodeAfter(
        it1->value.getPreHead(),
        it3
        );
    // Конец примера

    // TODO: Write your code here...
    
    for (int i=0; i<_dnaStorage.
}

void DNARepairer::printDNAStorage()
{
    xi::Node<DNARepairer::DNAChain>* it1 = _dnaStorage.getPreHead();
    while (it1->next != nullptr)
    {
        it1 = it1->next;
        //итерация по списку хранилища

        NodeDNA* it2 = it1->value.getPreHead();
        while (it2->next != nullptr)
        {
            it2 = it2->next;
            //итерация по списку ДНК

            cout << it2->value.id << "" << it2->value.number << ":";
            cout << it2->value.base << "  ";
        }
        cout << endl;
    }
}

void DNARepairer::readFile(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
        throw std::runtime_error("Could not open file");


    // начинаем с головы
    NodeDNAChain* it = _dnaStorage.getPreHead();

    string line;    
    while (getline(fin,line))
    {        
        // Создаем узел ДНК на куче
        NodeDNAChain* pNewNode = new NodeDNAChain;                

        //Создаем строковый поток для разбора
        istringstream istr(line);
        
        string strTmp;
        while (istr >> strTmp)                                  // разбиваем поток на слова
        {
            DNAElement tmpDNAElement(strTmp);                   // каждое слово читаем в DNAElement
            pNewNode->value.addElementToEnd(tmpDNAElement);     // добавляем полученный DNAElement в ДНК            
        }
        it->next = pNewNode;
        it = it->next;
        
    }
}
