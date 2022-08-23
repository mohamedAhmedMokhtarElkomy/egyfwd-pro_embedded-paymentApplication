#include "server.h"
#include <string.h>
#include <stdio.h>

int currentIndex = 0;
ST_accountsDB_t accounts[255];
ST_transaction_t transactions[255] = { 0 };

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    FILE *acc;
    acc = fopen ("output/accounts.txt", "w");
    //FILL dumb data for accounts
    
    for (int i = 0; i < 255; i++)
    {
        accounts[i].balance = 1000 + (i * 100);
        sprintf(accounts[i].primaryAccountNumber, "%ld", (1234567890123456789+i));

        fprintf(acc, "%f\t", accounts[i].balance);
        fprintf(acc, "%s\n", accounts[i].primaryAccountNumber);   
    }
      
    fclose (acc);

    if(isValidAccount(&transData->cardHolderData) != 0)
    {
        printf("FAILED: Account is not valid\n");
        return DECLINED_STOLEN_CARD;
    }

    if(isAmountAvailable(&transData->terminalData) != 0)
    {
        printf("FAILED: LOW_BALANCE\n");
        return DECLINED_INSUFFECIENT_FUND;
    }
    return SERVER_OK;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    for (int i = 0; i < 255; i++){
        if(strcmp(accounts[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0){
            currentIndex = i;
            return SERVER_OK;
        }
    }
    return DECLINED_STOLEN_CARD; // ACCOUNT_NOTFOUND
    
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    // printf("\n%f\n", accounts[currentIndex].balance);    
    if (accounts[currentIndex].balance < termData->transAmount)
        return LOW_BALANCE;
    return SERVER_OK;
    
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    FILE *transfile;
     
    transfile = fopen ("output/transactions.txt", "a");
    // if (transfile == NULL)
    // {
    //     fprintf(stderr, "\nError opened file\n");
    //     exit (1);
    // }
     
    if(transData->transactionSequenceNumber < 255)
    {

        transactions[transData->transactionSequenceNumber] = *transData;
        transData->transactionSequenceNumber++;

        fwrite (transData, sizeof(struct ST_transaction_t), 1, transfile);   
        fprintf(transfile, "\n"); 
        fclose (transfile);
        
        return SERVER_OK;
    }
    return SAVING_FAILED;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData){}