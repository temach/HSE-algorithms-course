////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Definition of some methods for class Subject
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
///
////////////////////////////////////////////////////////////////////////////////


#include "subject.h"
#include <iostream>



namespace xi {


std::ostream& operator<<(std::ostream& outs, const Subject& subj)
{   
    outs << subj.name << ": " << subj.title << "\n";
   
    int index = 0;
    while (subj.description[index] != "") 
        outs << subj.description[index++] << "\n";

    return outs;
}



std::istream& operator>>(std::istream& ins, Subject& subj)
{
    // read name and title
    std::getline(ins, subj.name);
    std::getline(ins, subj.title);
    // get long description
    std::string buffer;
    for (size_t i=0; std::getline(ins, buffer); i++)
    {
        if (buffer == "")
        {
            // if empty
            break;
        }
        subj.description[i] = buffer;
    }
    return ins;
}


} // namespace xi

