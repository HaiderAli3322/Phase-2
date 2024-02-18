#include "Transaction.h"
    bool Transaction::parse(){
        string digitCode = transactionCode.substr(0,2);
        if (digitCode.length() != 2){
            return false;
        }
        //create
        if (digitCode == "01") {
            //sentence structure XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
        string gameName = transactionCode.substr(3, 16);
        string sellerName = transactionCode.substr(19, 13);
        string price = transactionCode.substr(32, 6);
            if (gameName.length() != 16 || sellerName.length() != 13 || price.length() != 6){
                return false;
            }
            cout << "Transaction: " << digitCode << "_" << gameName << "_" << sellerName << "_" << price << endl;
            return true;

        }
            //delete
        else if(digitCode =="02"){
            //sentence structure XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
            string gameName = transactionCode.substr(3, 16);
            string sellerName = transactionCode.substr(19, 13);
            string price = transactionCode.substr(32, 6);
            if (gameName.length() != 16 || sellerName.length() != 13 || price.length() != 6){
                return false;
            }
            cout << "Transaction: " << digitCode << "_" << gameName << "_" << sellerName << "_" << price << endl;
            return true;

        }
        //sell
        else if (digitCode =="03") {
            //XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSS_PPPPPP. xx=transaction code, ii=game name, ss=seller name, pp=price
            string gameName = transactionCode.substr(3, 19);
            string sellerName = transactionCode.substr(21, 13);
            string price = transactionCode.substr(32, 6);
            if (gameName.length() != 16 || sellerName.length() != 13 || price.length() != 6) {
                return false;
            }
            cout << "Transaction: " << digitCode << "_" << gameName << "_" << sellerName << "_" << price << endl;
            return true;

        }
        //buy
        else if(digitCode =="04"){
            //XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP, xx=transaction code, ii=game name, ss=seller name, uu=buyer name, pp=price
            string gameName = transactionCode.substr(3, 16);
            string sellerName = transactionCode.substr(19, 13);
            string buyerName = transactionCode.substr(32, 16);
            string price = transactionCode.substr(48, 6);
            if (gameName.length() != 16 || sellerName.length() != 13 || buyerName.length() != 16 || price.length() != 6) {
                return false;
            }
            cout << "Transaction: " << digitCode << "_" << gameName << "_" << sellerName << "_" << buyerName << "_" << price << endl;
            return true;

        }
            // refund
        else if (digitCode =="05") {
            //sentence structure XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC, XX=transaction code, UUUUUUUUUUUUUUU=buyer name, SSSSSSSSSSSSSS=seller name, CCCCCCCCCC=Refund credit
            string buyerName = transactionCode.substr(3, 16);
            string sellerName = transactionCode.substr(19, 13);
            string price = transactionCode.substr(32, 6);
            if (buyerName.length() != 16 || sellerName.length() != 13 || price.length() != 6) {
                return false;
            }
            cout << "Transaction: " << digitCode << "_" << buyerName << "_" << sellerName << "_" << price << endl;
            return true;
        }
        //add credit
        else if(digitCode =="06"){
            //XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
            string gameName = transactionCode.substr(3, 16);
            string sellerName = transactionCode.substr(19, 13);
            string price = transactionCode.substr(32, 6);
            if (gameName.length() != 16 || sellerName.length() != 13 || price.length() != 6){
                return false;
            }


        }
        //end of session
        else if(digitCode =="00"){
            //XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
            string gameName = transactionCode.substr(3, 16);
            string sellerName = transactionCode.substr(19, 13);
            string price = transactionCode.substr(32, 6);
            if (gameName.length() != 16 || sellerName.length() != 13 || price.length() != 6){
                return false;
            }
            cout << "Transaction: " << digitCode << "_" << gameName << "_" << sellerName << "_" << price << endl;
            return true;


        }




    }

