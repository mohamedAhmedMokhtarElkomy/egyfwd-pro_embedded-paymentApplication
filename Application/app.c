#include "app.h"
#include "../Card/card.h"
#include <stdio.h>
#include "../Terminal/terminal.h"
#include "../Server/server.h"

void appStart(void)
{
    ST_cardData_t card;
    ST_terminalData_t terminal;
    ST_transaction_t transaction;

    if (getCardHolderName(&card) != 0){
        printf("FAILED: WRONG_NAME\n");
        return 1;
    }
    
    if (getCardExpiryDate(&card) != 0){
        printf("FAILED: WRONG_EXP_DATE\n");
        return 1;   
    }
    
    if (getCardPAN(&card) != 0){
        printf("FAILED: WRONG_PAN\n");
        return 1;   
    }

    if (getTransactionDate(&terminal) != 0){
        printf("FAILED: WRONG_DATE\n");
        return 1;   
    }

    if (isCardExpired(card, terminal) != 0){
        printf("FAILED: EXPIRED_CARD\n");
        return 1;   
    }

    if (isValidCardPAN(&card) != 0){
        printf("FAILED: INVALID_PAN\n");
        return 1;   
    }

    if (getTransactionAmount(&terminal) != 0){
        printf("FAILED: INVALID_AMOUNT\n");
        return 1;   
    }

    if (setMaxAmount(&terminal) != 0){
        printf("FAILED: INVALID_MAX_AMOUNT\n");
        return 1;   
    }

    if (isBelowMaxAmount(&terminal) != 0){
        printf("FAILED: EXCEED_MAX_AMOUNT\n");
        return 1;   
    }


    transaction.cardHolderData = card;
    transaction.terminalData = terminal;
    transaction.transactionSequenceNumber = 0;

    if(recieveTransactionData(&transaction) != 0){
        printf("FAILED: transaction failed\n");
        return 1;
    }

    printf("PASSED\n");
        
    if(saveTransaction(&transaction) != 0)
        printf("FAILED: SAVING_FAILED\n");
    else
        printf("transaction is saved sucessfully\n");

}
