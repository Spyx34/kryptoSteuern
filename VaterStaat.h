#ifndef VATERSTAAT_H
#define VATERSTAAT_H

#include <algorithm>
#include <vector>
#include "transaction.h"
#include "ConsoleHandler.h"

class VaterStaat{

    public:
        VaterStaat();
        static double calculateSteuern( std::vector<Transaction> v);
        
    private:
        

};

#endif
