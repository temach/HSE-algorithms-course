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
    id = "";
    number = 0;
    base = static_cast<DNAElement::DNABase>(0);
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

    if (description.size() < 4)
        throw invalid_argument("Element description string is too short");

    if (description.find(" ") != string::npos)
        throw invalid_argument("Element description contains a space");

    if (description.find(":") == string::npos)
        throw invalid_argument("Element description does not contain delimiter");

    if (description[0] < 'a' || description[0] > 'z')
        throw invalid_argument("Element invalid id");

    if (description[1] < '0' || description[1] > '9')
        throw invalid_argument("Element invalid id");

    char type_char = description[description.size() - 1];
    if (type_char != description[description.find(":") + 1])
        throw invalid_argument("Element type character should follow : and be last in element description");

    if (
        type_char != DNABase::A
        && type_char != DNABase::C
        && type_char != DNABase::T
        && type_char != DNABase::G
        )
        throw invalid_argument("Invalid element type");

    id = description[0];
    try
    {
        string number_string = description.substr(1, description.find(":") - 1);
        string::size_type first_not_converted;
        number = stoi(number_string, &first_not_converted, 10);
        if (number_string.substr(first_not_converted).size() > 0)
            throw invalid_argument("Element invalid number");
    }
    catch (...)
    {
        throw invalid_argument("Element invalid number");
    }
    base = static_cast<DNAElement::DNABase>(type_char);
}

