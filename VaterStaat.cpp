#include "transaction.h"
#include "ConsoleHandler.h"
#include "VaterStaat.h"
#include  <stdexcept>
#include <algorithm>
#include <vector>
#include <iostream>
#include <conio.h> 


VaterStaat::VaterStaat(){};

double VaterStaat::calculateSteuern(std::vector<Transaction> v){
    double steuernToPay{0};
    double rawProfit{0};
    double profitMade{0};
    double taxWriteOff{0};
    
    //checking every sell Order
    for(auto t : v){
        //we are now at a sell order 
        if(t.getAction() == 0){
            bool paid = 0;
            //looking up the least recent buy order 
            std::for_each(v.begin(), v.end(), [&steuernToPay, &paid, &t , &v, &rawProfit, &profitMade, &taxWriteOff](Transaction& transac){
                if(!transac.isTaxed() && transac.getAction() == 1){

                    //if one buy transaction is big enough it is just splitted and done
                    if(transac.getCrypto() > t.getCrypto()){
                        std::vector<Transaction> transactionToInsert = Transaction::splitTransaction(transac, t.getCrypto());
                        //erase the old transaction and insert the two new one which are the equivalent                        
                        auto it = std::find(v.begin(), v.end(), transac);
                        if (it != v.end()) {
                            v.erase(it);
                        }
                        transactionToInsert.at(0).taxedIt();
                        auto insertPositionA = std::lower_bound(v.begin(), v.end(), transactionToInsert.at(0), comp);
                        v.insert(insertPositionA, transactionToInsert.at(0) );
                        auto insertPositionB = std::lower_bound(v.begin(), v.end(), transactionToInsert.at(1), comp);
                        v.insert(insertPositionA, transactionToInsert.at(1) );   

                        double soldFor = t.getFiat();
                        double boughtFor = transactionToInsert.at(0).getFiat();
                        if(boughtFor >= soldFor){
                            taxWriteOff += boughtFor - soldFor;
                        }else{
                            rawProfit = soldFor - boughtFor;

                            //tax write off is less than raw profit and we still have to pay some taxes
                            if(taxWriteOff > 0 && taxWriteOff < rawProfit){
                                rawProfit -= taxWriteOff;
                                taxWriteOff = 0;

                                steuernToPay += rawProfit * 0.275;
                                profitMade += rawProfit * (1-0.275);
                            //tax write off is bigger than raw profit and we dont pay any taxes on our profit
                            }else if(taxWriteOff > 0 && taxWriteOff > rawProfit){
                                taxWriteOff -= rawProfit;
                                profitMade += rawProfit;
                            }
                        }

                    }else if(transac.getCrypto() == t.getCrypto()){
                        std::vector<Transaction> transactionToInsert = Transaction::splitTransaction(transac, t.getCrypto());
                        //erase the old transaction and insert the two new one which are the equivalent                        
                        auto it = std::find(v.begin(), v.end(), transac);
                        if (it != v.end()) {
                            v.erase(it);
                        }
                        transactionToInsert.at(0).taxedIt();
                        auto insertPosition = std::lower_bound(v.begin(), v.end(), transactionToInsert.at(0), comp);
                        v.insert(insertPosition, transactionToInsert.at(0) );
                        double soldFor = t.getFiat();
                        double boughtFor = transactionToInsert.at(0).getFiat();
                        if(boughtFor >= soldFor){
                            taxWriteOff += boughtFor - soldFor;
                        }else{
                            rawProfit = soldFor - boughtFor;

                            //tax write off is less than raw profit and we still have to pay some taxes
                            if(taxWriteOff > 0 && taxWriteOff < rawProfit){
                                rawProfit -= taxWriteOff;
                                taxWriteOff = 0;

                                steuernToPay += rawProfit * 0.275;
                                profitMade += rawProfit * (1-0.275);
                            //tax write off is bigger than raw profit and we dont pay any taxes on our profit
                            }else if(taxWriteOff > 0 && taxWriteOff > rawProfit){
                                taxWriteOff -= rawProfit;
                                profitMade += rawProfit;
                            }
                        }
                    }
                    
                    
                    
                }
            });//for each end
        }
        
    }
    return steuernToPay;
}