#include "server.h"
#include <string.h>
#include <stdio.h>

ST_accountsDB_t accounts[255];
ST_transaction_t transactions[255] = { 0 };
uint8_t blockedAccounts[255][25];

void dummyValues(){
    for (int i = 0; i < 10; i++)
    {
        accounts[i].balance = 1000 + (i * 100);
        sprintf(accounts[i].primaryAccountNumber, "%ld", (1234567890123456789+i));
    }
}

void dummyFile()
{
    FILE *acc;
    acc = fopen ("output/accounts.txt", "w");
    //FILL dumb data for accounts
    
    for (int i = 0; i < 10; i++)
    {
        fprintf(acc, "%f\t", accounts[i].balance);
        fprintf(acc, "%s\n", accounts[i].primaryAccountNumber);   
    }
      
    fclose (acc);
}

void updateBalance(ST_accountsDB_t *accountRefrence, int amount){ 
    accountRefrence->balance -= amount;
}

EN_transState_t checkBlockList(ST_cardData_t cardData)
{
    printf("REACHED\n");
    for (int i = 0; i < 255; i++)
    {
        if(strcmp(blockedAccounts[i], cardData.primaryAccountNumber) == 0)
            return DECLINED_STOLEN_CARD;
    }
    
    return SERVER_OK;
}

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    strcpy(blockedAccounts[0], "1234567890123456790");
    dummyValues();
    // dummyFile();

    ST_accountsDB_t *accountRefrence;

    if(checkBlockList != 0)
    {
        printf("FAILED: DECLINED_STOLEN_CARD");
        return DECLINED_STOLEN_CARD;
    }
    if(isValidAccount(&transData->cardHolderData, &accountRefrence) != 0)
    {
        printf("FAILED: Account is not valid\n");
        return ACCOUNT_NOT_FOUND;
    }
  

    if(isAmountAvailable(&transData->terminalData, accountRefrence) != 0)
    {
        printf("FAILED: LOW_BALANCE\n");
        return DECLINED_INSUFFECIENT_FUND;
    }
    // else
    //     updateBalance(accountRefrence, transData->terminalData.transAmount);
    
    
    return SERVER_OK;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountRefrence)
{
    for (int i = 0; i < 255; i++){
        if(strcmp(accounts[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0){

            *accountRefrence = &accounts[i];
            return SERVER_OK;
        }
    }
    return DECLINED_STOLEN_CARD; // ACCOUNT_NOTFOUND
    
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{

    if (accountRefrence->balance < termData->transAmount)
        return LOW_BALANCE;

    accountRefrence->balance -= termData->transAmount;
    
    return SERVER_OK;

    
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{    
    dummyFile();

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