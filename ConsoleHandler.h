#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include <algorithm>
#include <vector>
#include "transaction.h"

class ConsoleHandler{

    public:
        ConsoleHandler();
        static std::vector<Transaction> takeIn();
        static void printStats(std::vector<Transaction> v);
    private:


};

#endif
