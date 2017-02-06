////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     DNAElement class definition
/// \authors   Sergey Shershakov, Leonid Dworzanski
/// \version   0.2.0
/// \date      06.02.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Определение класса "Элемент ДНК", DNAElement.
///
////////////////////////////////////////////////////////////////////////////////

#include "dna_element.h"

std::string trim(const std::string& str)
{
    using namespace std;
    string::size_type first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    string::size_type last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

DNAElement::DNAElement()
{

}

DNAElement::DNAElement(const std::string& description)
{
    readFromString(description);
}

/**
* \brief Инициализирует объект на основе переданной строки.
*
* Fill the fields id, number, base from a description in the format [name][number]:[type] where
* [id] - a..z
* [number] - the number of this element in the DNA sequence a1 a2 a3 a4 a5...
* [base] - biological component of the element (A, C, T or G)
*
* So for description "a1:G"
* name = "a";
* number = 1;
* type = "G";
*
* Throws invalid_argument if the format is wrong
*                      or if the type of element is not in [A, C, T, G]
*/
void DNAElement::readFromString(const std::string& description)
{
    using namespace std;
    if (description[0] < 'a' || description[0] > 'z')
    {
        throw invalid_argument("Invalid id");
    }
    if (description.find(" ") != string::npos)
    {
        throw invalid_argument("Description contains a space");
    }
    if (description.find(":") == string::npos)
    {
        throw invalid_argument("Description does not contain delimiter");
    }
    char type_char = description[description.size() - 1];
    if (type_char != 'A' && type_char != 'C' && type_char != 'T' && type_char != 'G')
    {
        throw invalid_argument("Invalid element type");
    }
    id = description[0];
    number = std::stoi(description.substr(1));
    base = type_char;
}

