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


void DNARepairer::repairDNA()
{
    Id2DnaMap idmap {};
    // while partial dna chains exist
    while (_dnaStorage.getPreHead()->next)
    {
        // examine the first partial chain
        DNAChain& partial_chain = _dnaStorage.getPreHead()->next->value;
        // examine the first element in partial chain
        NodeDNA* partial_chain_head = partial_chain.getPreHead()->next;
        if ( idmap.find(partial_chain_head->value.id) == idmap.end() )
        {
            // If the map is empty
            DNAChain* ordered_chain = new DNAChain{};
            idmap.insert({partial_chain_head->value.id, ordered_chain});
            // move nodes to its end
            ordered_chain->moveNodesToEnd(partial_chain.getPreHead(), partial_chain.getEndNode());
        }
        else
        {
            // If the map is NOT empty
            // find where to insert it into good_chain
            DNAChain* ordered_chain = idmap[partial_chain_head->value.id];
            // iterate already sorted DNA elements
            NodeDNA* prev_elem = ordered_chain->getPreHead();
            // map not empty, so there is at least one element (elem != nullptr)
            NodeDNA* elem = prev_elem->next;
            while (elem)
            {
                // if we must insert before the elem (after prev_elem)
                if (elem->value.number > partial_chain_head->value.number)
                {
                    break;
                }
                prev_elem = elem;
                elem = elem->next;
            }
            ordered_chain->moveNodesAfter(prev_elem, partial_chain.getPreHead(), partial_chain.getEndNode());
        }
        // after move, erase the partial_chain that was just moved
        _dnaStorage.deleteNextNode(_dnaStorage.getPreHead());
    }
    // place results from Id2DNA map into _dnaStorage variable
    for (auto const& dna_id : idmap)
    {
        DNAChain* good_elements = idmap[dna_id.first];
        // add via copy
        _dnaStorage.addElementToEnd(*good_elements);
        // free memory
        delete good_elements;
    }
}

void DNARepairer::printDNAStorage()
{
    Node<DNARepairer::DNAChain>* chain = _dnaStorage.getPreHead();
    while (chain->next != nullptr)
    {
        // choose next chain
        chain = chain->next;
        // iter over DNA elements in the chain
        Node<DNAElement>* element = chain->value.getPreHead();
        while (element->next != nullptr)
        {
            element = element->next;
            cout << element->value.id << "" << element->value.number << ":";
            cout << static_cast<char>(element->value.base) << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void DNARepairer::readFile(const string& filename)
{
    ifstream fin(filename);
    if (!fin)
        throw std::runtime_error("Could not open file");
    // chain of sequental DNA elements that should not be cut
    DNAChain cur_chain {};
    // previous element read from file
    DNAElement prev_element{};
    // description of element read from file
    string description;
    // skip whitespace and read words separated by whitespace
    while (fin >> std::ws && fin >> description)
    {
        // read element
        DNAElement current {description};
        // check if we need to start a new chain
        // if this is NOT a subsequent DNA element and the current chain has at least one element
        if (
            (current.id != prev_element.id || current.number != (prev_element.number+1))
            && cur_chain.size() > 0
           )
        {
            // add chain to list via copy
            _dnaStorage.addElementToEnd(cur_chain);
            // clear chain to prepare for new elements
            cur_chain.deleteNodes(cur_chain.getPreHead(), cur_chain.getEndNode());
        }
        cur_chain.addElementToEnd(current);
        // remember the previous element
        prev_element = current;
    }
    // if the last chain contains no elements
    if (cur_chain.size() < 1)
        throw runtime_error("File is badly formatted");
    // add the last chain to list
    _dnaStorage.addElementToEnd(cur_chain);
    cur_chain.deleteNodes(cur_chain.getPreHead(), cur_chain.getEndNode());
}
