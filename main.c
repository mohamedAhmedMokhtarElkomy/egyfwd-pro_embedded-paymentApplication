#include "Card/card.h"
#include <stdio.h>
#include "Terminal/terminal.h"
#include "Server/server.h"

void printfErrorMessage()
{
    printf("%s", "Error\n");
}

int main()
{
    ST_cardData_t card;
    ST_terminalData_t terminal;
    ST_transaction_t transaction;

    int errorMessage;

    errorMessage = getCardHolderName(&card);
    if (errorMessage != 0){
        printfErrorMessage();
        return 1;
    }
    

    errorMessage = getCardExpiryDate(&card);
    if (errorMessage != 0){
        printfErrorMessage();
        return 1;   
    }
    
    errorMessage = getCardPAN(&card);
    if (errorMessage != 0){
        printfErrorMessage();
        return 1;   
    }

    errorMessage = getTransactionDate(&terminal);
    if (errorMessage != 0){
        printf("error in card trans date");
        return 1;   
    }

    errorMessage = isCardExpired(card, terminal);
    if (errorMessage != 0){
        printf("error in card rxp date");
        return 1;   
    }

    errorMessage = isValidCardPAN(&card);
    if (errorMessage != 0){
        printf("error in card pan date");
        printfErrorMessage();
        return 1;   
    }

    errorMessage = getTransactionAmount(&terminal);
    if (errorMessage != 0){
        printf("error in card trans amount");
        printfErrorMessage();
        return 1;   
    }

    errorMessage = setMaxAmount(&terminal);
    if (errorMessage != 0){
        printf("error in card set max");
        printfErrorMessage();
        return 1;   
    }

    errorMessage = isBelowMaxAmount(&terminal);
    if (errorMessage != 0){
        printf("error in card below max");
        printfErrorMessage();
        return 1;   
    }


    transaction.cardHolderData = card;
    transaction.terminalData = terminal;
    transaction.transactionSequenceNumber = 0;

    if(recieveTransactionData(&transaction) != 0) 
        printf("failure in recieveTransaction");
    
    if(saveTransaction(&transaction) != 0)
        printf("can't save files");
    

}