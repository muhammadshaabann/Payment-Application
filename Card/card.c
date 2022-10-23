#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please Enter Card Holder's Name:\n");
	gets((cardData->cardHolderName));
	if ((strlen(cardData->cardHolderName) > Max_Size_Name) || (strlen(cardData->cardHolderName) < Min_Size_Name) || (strlen(cardData->cardHolderName) == NULL_Size_Name))
	{
		return WRONG_NAME;
	}
	return CARD_OK;

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Please Enter Card Expiry Date:\n");
	gets((cardData->cardExpirationDate));
	if ((strlen(cardData->cardExpirationDate) != Max_Exp_Date) || (strlen(cardData->cardExpirationDate) == NULL_Exp_Date))
	{
		return WRONG_EXP_DATE;
	}
	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please Enter Card PAN:\n");
	gets((cardData->primaryAccountNumber));
	if ((strlen(cardData->primaryAccountNumber) > Max_PAN) || (strlen(cardData->primaryAccountNumber) < Min_PAN) || (strlen(cardData->primaryAccountNumber) == NULL_PAN))
	{
		return WRONG_PAN;
	}
	return CARD_OK;
}

