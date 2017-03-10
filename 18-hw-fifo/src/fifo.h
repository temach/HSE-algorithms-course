//
// Выполнил Абрамов Артем БПИ 151
// g++ (GCC) 6.3.1 20170109
//

#ifndef FIFO_H
#define FIFO_H

#include "simulator.h"

class fifo : public simulator {

public:
    // public constructor
    fifo(int seconds_per_page);

    // implemented pure virtual function
    void simulate(string file);
};


#endif // FIFO_H
