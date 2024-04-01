#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <algorithm>
#include <vector>


class Transaction {
public:
    //ctor
    Transaction(unsigned int date, double fiat, double crypto, double rate,bool action, const char* n); 
    //getter
    unsigned int getDate() const;
    double getFiat() const;
    double getCrypto() const;
    double getRate() const;
    bool getAction() const;
    const char* getName() const;
    bool isTaxed() const;
    //setter
    void taxedIt();
    //methods
    static std::vector<Transaction> splitTransaction(Transaction t,double amount);
    //overloads
    friend std::ostream& operator<< (std::ostream& os, const Transaction& t);
    bool operator==(const Transaction& other) const {
        return (date == other.date && fiat == other.fiat && crypto == other.crypto && rate == other.rate && action == other.action && name == other.name && taxed == other.taxed);
    }

    
private:
    unsigned int date;
    double fiat;
    double crypto; //has potential to be updated using exponent short int and int instead of float with operator overrides
    double rate;
    bool action; //1 implies a buy Order, 0 a sell Order
    char name[5];
    bool taxed;
};
auto comp = [](const Transaction& a, const Transaction& b){ return a.getDate() < b.getDate();};

#endif
