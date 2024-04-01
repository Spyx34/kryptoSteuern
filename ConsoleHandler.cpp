#include "transaction.h"
#include "ConsoleHandler.h"
#include "VaterStaat.h"
#include  <stdexcept>
#include <algorithm>
#include <vector>
#include <iostream>
#include <conio.h> 


ConsoleHandler::ConsoleHandler(){}



std::vector<Transaction> ConsoleHandler::takeIn(){
    std::vector<Transaction> ret_v{};
    bool another = true;
    //    Transaction(unsigned int date, double fiat, double crypto, double rate,bool action, const char* n); 
    char name[4];
    std::cout << "Starting input...\nName of the Coin: ";
    std::cin >> name;
    std::cout << "\n";
    while(another){
        double fiat,crypto,rate;
        bool action;
        unsigned int date;
        std::cout << "\nWhen did you buy the coins Format\"YYYYMMDD\": "; std::cin >> date;
        std::cout << "\nAt what rate: "; std::cin >> rate;
        std::cout << "\nHow much did you pay: "; std::cin >> fiat;
        std::cout << "\nDid you buy[1] or sell[0] them: "; std::cin >> action;        
        std::cout << "\nHow many coins was it: "; std::cin >> crypto;        

        ret_v.push_back(Transaction(date,fiat,crypto, rate, action, name));
        std::cout << "\nMaked down, do you want to continue? 0/1: "; std::cin >> another; std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";

    }
    return ret_v;
}

void ConsoleHandler::printStats(std::vector<Transaction> v){
    std::vector<Transaction> sells{};

    double spent{0};
    double bought{0};


    //calculating all bought ones
    for(const Transaction& t : v){
        if(!t.getAction()){
            sells.push_back(t);
            continue;
        }
        spent += t.getFiat();
        bought += t.getCrypto();
    }

    double averageBuyPrice = spent/bought;
    


    double got{0};
    double sold{0};
    //calculating all sold ones
    for(const Transaction& t : sells){
        
        got += t.getFiat();
        sold += t.getCrypto();
    }

    double averageSellPrice = sold == 0 ? 0 : got/sold;



    std::cout << "----------------------------------------\n"
    << "Shitty Stats:\n" 
    << "You bought " << v.at(0).getName() << " at an average price of " << averageBuyPrice << " EUR/" << v.at(0).getName() << "\n"
    << "You sold " << v.at(0).getName() << " at an average price of " << averageSellPrice << " EUR/" << v.at(0).getName() << "\n"
    << "You're over all untaxed profit is " << got - spent << " EUR with " << bought - sold  << " " <<  v.at(0).getName() << " left unsold\n"
    << "Real Stats: \n"
    << "Taxes to pay: " << VaterStaat::calculateSteuern(v) << " EUR\n" 
    << "----------------------------------------\n";


}