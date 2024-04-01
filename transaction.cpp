#include "transaction.h"
#include  <stdexcept>
#include <algorithm>
#include <vector>
#include <iostream>

using amt = unsigned int;

//constructor
Transaction::Transaction(unsigned int date, double fiat, double crypto, double rate,bool action, const char* n){
    if(date > 21000000 || fiat > 10000){
        throw std::runtime_error("Error initializing transaction\nQuitting...\n");
    }
    if (strlen(n) == 3 || strlen(n) == 4) {
            strcpy(name, n); // Copy the name into the array
        } else {
            throw std::runtime_error("Name must be exactly 3 or 4 characters long.") ;
        }

    this->date = date;
    this->fiat = fiat;
    this->crypto = crypto;
    this->rate = rate;
    this->action = action;
    this->taxed = 0;
}

//getter
unsigned int Transaction::getDate() const{
    return this->date;
}
double Transaction::getFiat() const{
    return this->fiat;
}
double Transaction::getCrypto() const{
    return this->crypto;
}
double Transaction::getRate() const{
    return this->rate;
}
bool Transaction::getAction() const{
    return this->action;
}
const char* Transaction::getName() const{
    return this->name;
}
bool Transaction::isTaxed() const{
    return this->taxed;
}

//setter
void Transaction::taxedIt(){
    if(!this->action){
        throw std::runtime_error("cant tax a sell order\nQuitting...\n");
    }
    this->taxed = 1;
}


//methods
std::vector<Transaction> Transaction::splitTransaction(Transaction t,double amount){

    if(!t.getAction()){
        throw std::runtime_error("Cannot Split a \"Sell\"-Order\nQuitting...\n");
    }else if(amount > t.getCrypto()){
        throw std::runtime_error("Cannot Split an Order with less Crypto than the amount to split\nQuitting...\n");
    }

    if(amount == t.getCrypto()){
        std::vector<Transaction> a{t};
        return a;
    }

    std::vector<Transaction> ret_v{};

    amt date = t.getDate();
    double newFiat;
    double newCrypto = amount;
    double rate = t.getRate();
    const char* n = t.getName();
    //  float percentageCrypto = static_cast<float>(amount) / static_cast<float>(t.getCrypto());
    newFiat = amount * rate;

    Transaction a{date, newFiat, newCrypto, rate, 1, n};

    Transaction b{date, t.getFiat()-newFiat, t.getCrypto()-newCrypto, rate, 1, n};
    
    ret_v.push_back(a);
    ret_v.push_back(b);
    //the first transaction is the one equal to the splitted amount thus the one that is going to be taxed

    return ret_v;
}


//overlaods
std::ostream& operator<< (std::ostream& os, const Transaction& t){
    os << "----------------------------------------\n";
    amt date = t.getDate();
    amt year = date / 10000;
    amt month = (date - year * 10000) / 100;
    amt day = (date - year*10000 - month*100) ;
    os << "Date of Transaction  : " << day << "." << month << "."  << year << "\n";
    os << "Amount               : " << t.getCrypto() << t.getName() << "\n";
    os << "Price                : " << t.getFiat() << "EUR\n";

    os << (t.getAction() ? "Bought  " : "Sold   "); 
    os << " at          : " << t.getRate() << "EUR/"<< t.getName() << "\n";
    os << "----------------------------------------\n";


    return os;
}

