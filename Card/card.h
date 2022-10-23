#ifndef CARD_H
#define CARD_H

#include "../Utilities/types.h"

#define Max_Size_Name 24
#define Min_Size_Name 20
#define NULL_Size_Name 0

#define Max_Exp_Date 5
#define NULL_Exp_Date 0 

#define Max_PAN 19
#define Min_PAN 16
#define NULL_PAN 0

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;


typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;


EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif