#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	time_t t;
	t = time(NULL);
	struct tm tm = *localtime(&t);

	uint8_t day[3];
	uint8_t month[3];
	uint8_t year[5];
	uint8_t* delimiter = "/";
	uint8_t* zero = "0";

	uint8_t x_day = tm.tm_mday;
	uint8_t x_month = tm.tm_mon + 1;
	uint16_t x_year = tm.tm_year + 1900;

	itoa(x_day, day, 10);
	itoa(x_month, month, 10);
	itoa(x_year, year, 10);

	if (x_month < 10 || x_day < 10)
	{
		if (x_day < 10)
		{
			strcat(termData->transactionDate, zero);
		}
		strcat(termData->transactionDate, day);
		strcat(termData->transactionDate, delimiter);
		if (x_month < 10)
		{
			strcat(termData->transactionDate, zero);
		}
		strcat(termData->transactionDate, month);
		strcat(termData->transactionDate, delimiter);
		strcat(termData->transactionDate, year);
	}
	else
	{
		strcat(termData->transactionDate, day);
		strcat(termData->transactionDate, delimiter);
		strcat(termData->transactionDate, month);
		strcat(termData->transactionDate, delimiter);
		strcat(termData->transactionDate, year);
	}
	printf("Transaction Date: %s\n", termData->transactionDate);
	return TERMINAL_OK;
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	uint8_t Date_terminal[4]={ termData.transactionDate[3],termData.transactionDate[4],termData.transactionDate[8],termData.transactionDate[9] }, Date_card[4] = { cardData.cardExpirationDate[0] ,cardData.cardExpirationDate[1] ,cardData.cardExpirationDate[3] ,cardData.cardExpirationDate[4] };

	uint8_t month_transaction[3] = { Date_terminal[0] , Date_terminal[1] , '\0' };
	uint8_t month_expiration[3] = { Date_card[0] , Date_card[1] , '\0' };
	uint8_t year_transaction[3] = { Date_terminal[2] , Date_terminal[3] , '\0' };
	uint8_t year_expiration[3] = { Date_card[2] , Date_card[3] , '\0' };

	if (atoi(year_transaction) > atoi(year_expiration))
	{
		return EXPIRED_CARD;
	}
	else if ((atoi(year_transaction) == atoi(year_expiration)) && (atoi(month_transaction) > atoi(month_expiration)))
	{
		return EXPIRED_CARD;
	}
	return TERMINAL_OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please Enter Transaction Amount:\n");
	scanf("%f", &(termData->transAmount));
	if (termData->transAmount <= No_Amount)
	{
		return INVALID_AMOUNT;
	}
	return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	termData->maxTransAmount = Terminal_Max_Amount;
	if ((termData->maxTransAmount) <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{

	if ((termData->transAmount) > (termData->maxTransAmount))
	{
		return EXCEED_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}