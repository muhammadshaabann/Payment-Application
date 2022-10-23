#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"server.h"


ST_transaction_t Transactions_DB[DataBase_Size] = { 0 };

ST_accountsDB_t ValidAccounts_DB[DataBase_Size] =
{
	{10000.0 ,  "1234 5678 1234 5678"},
	{4000.0  ,  "4321 8765 4321 8765"},
	{1000.0  ,  "0000 0000 0000 0000"},
	{500.0   ,  "5555 6666 7777 8888"},
};


EN_transStat_t recieveTransactionData(ST_transaction_t* transData)
{
	getTransactionDate(&(transData->terminalData));
	if (isCardExpired((transData->cardHolderData), (transData->terminalData)))
	{
		printf("Declined: Expired Card\n");
		return INTERNAL_SERVER_ERROR;
	}

	if (getTransactionAmount(&(transData->terminalData)))
	{
		return INTERNAL_SERVER_ERROR;
	}

	if (isBelowMaxAmount(&(transData->terminalData)))
	{
		printf("Declined: Amount Exceeding Limit\n");
		return INTERNAL_SERVER_ERROR;
	}

	uint8_t i = 0;
	for (i = 0; i < DataBase_Size; i++)
	{
		if (strcmp(transData->cardHolderData.primaryAccountNumber, ValidAccounts_DB[i].primaryAccountNumber))
		{
			if (i == 254)
			{
				return DECLINED_STOLEN_CARD;
			}
		}
		else
		{
			break;
		}
	}

	if (transData->terminalData.transAmount > ValidAccounts_DB[i].balance)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}

	ValidAccounts_DB[i].balance -= transData->terminalData.transAmount;
	printf("Your new balance = %f\n", ValidAccounts_DB[i].balance);
	return APPROVED;
}


EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	uint8_t i;
	for (i = 0; i < DataBase_Size; i++)
	{
		if (cardData->primaryAccountNumber == ValidAccounts_DB[i].primaryAccountNumber)
		{
			return SERVER_OK;
		}
	}
	return DECLINED_STOLEN_CARD;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	uint8_t i;
	for (i = 0; i < DataBase_Size; i++)
	{
		if (termData->transAmount > ValidAccounts_DB[i].balance)
		{
			return LOW_BALANCE;
		}
	}
	return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	transData->transactionSequenceNumber++;
	switch (recieveTransactionData(transData))
	{
	case APPROVED:
		printf("Approved. Transaction Saved.\n");
		break;

	case DECLINED_STOLEN_CARD:
		printf("Declined: DECLINED_STOLEN_CARD\n");
		return SAVING_FAILED;

	case DECLINED_INSUFFECIENT_FUND:
		printf("Declined: DECLINED_INSUFFECIENT_FUND\n");
		return SAVING_FAILED;

	case INTERNAL_SERVER_ERROR:
		printf("Declined: INTERNAL_SERVER_ERROR\n");
		return SAVING_FAILED;

	}
	return SERVER_OK;
}