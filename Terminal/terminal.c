#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    
    printf("Enter transaction date: ");
    scanf("%s", &termData->transactionDate);
    
    if(strlen(termData->transactionDate) != 10)
        return WRONG_DATE;
    
    return TER_OK;

}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    int num1;
    int num2;
    
    num1 = ( cardData.cardExpirationDate[3] - '0' ) * 10;
    num1 += cardData.cardExpirationDate[4] - '0';

    num2 = ( termData.transactionDate[8] - '0' ) * 10;
    num2 += termData.transactionDate[9] - '0';

    if(num1 < num2)
        return EXPIRED_CARD;
    else if(num1 == num2)
    {
        num1 = ( cardData.cardExpirationDate[0] - '0' ) * 10;
        num1 += cardData.cardExpirationDate[1] - '0';

        num2 = ( termData.transactionDate[3] - '0' ) * 10;
        num2 += termData.transactionDate[4] - '0';

        if(num1 < num2)
            return EXPIRED_CARD;
    }

    return TER_OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    return TER_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("Enter transaction amount: ");
    scanf("%f", &termData->transAmount);

    if(termData->transAmount <= 0 )
        return INVALID_AMOUNT;
    return TER_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if(termData->transAmount > termData->maxTransAmount)
        return EXCEED_MAX_AMOUNT;
    return TER_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    printf("Enter max amount");
    scanf("%f", &termData->maxTransAmount);

    if(termData->maxTransAmount <= 0)
        return INVALID_MAX_AMOUNT;
    return TER_OK;
}
