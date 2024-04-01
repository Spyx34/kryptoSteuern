#include <iostream>
#include "transaction.h"

#include "ConsoleHandler.h"

#include <vector>


int main(void){
    std::vector<Transaction> v = ConsoleHandler::takeIn();

    std::sort(v.begin(),v.end(), comp);

    /*for(auto t : v){
        std::cout << t << "\n";
    }
    */

   ConsoleHandler::printStats(v);


   
    
}