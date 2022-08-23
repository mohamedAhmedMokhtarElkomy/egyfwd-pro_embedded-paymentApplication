#include "card.h"
#include <stdio.h>
#include <string.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    // scanf("%3s", string);
    
    printf("Enter card holder name: ");
    scanf("%s", cardData->cardHolderName);

    if(strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24)
        return WRONG_NAME;

    return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("Enter card expiry date: ");
    scanf("%s", cardData->cardExpirationDate);
    
    if(strlen(cardData->cardExpirationDate) != 5 || cardData->cardExpirationDate[2] != '/')
        return WRONG_EXP_DATE;
    
    return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Enter card PAN: ");
    scanf("%s", cardData->primaryAccountNumber);

    if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
        return WRONG_PAN;

    return CARD_OK;
    
}
