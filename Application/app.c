#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "app.h"

ST_transaction_t transactions_DB[DataBase_Size];

void appStart(void)
{
	setMaxAmount(&(transactions_DB[0].terminalData));

	getCardHolderName(&(transactions_DB[0].cardHolderData));
	getCardExpiryDate(&(transactions_DB[0].cardHolderData));
	getCardPAN(&(transactions_DB[0].cardHolderData));

	saveTransaction(&transactions_DB[0]);
}
