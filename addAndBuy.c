#include "mainHeader.h"

void addAnApp(char *str, List* lst, int code)
{
	char *str2;
	char * address;
	time_t * currTime;
	Appartment newApp;

    address = strtok(str, "'\"'");
	newApp.address = strCopy(address);

	newApp.code = code;

	str2 = strtok(NULL, "\0");

	sscanf(str2, "%d%hd%d%d%d", &newApp.price, &newApp.numRooms, &newApp.date.day, &newApp.date.month, &newApp.date.year);


	/*calculate the current time*/
	time(&currTime);
	struct tm* myTime = localtime(&currTime);

	newApp.enterDate.day = myTime->tm_mday;
	newApp.enterDate.month = myTime->tm_mon + 1;
	newApp.enterDate.year = myTime->tm_year + 1900;

	insertDataToEndlist(newApp, lst);
}

void buyAnAppartment(List * lst, char* str, int*code)
{
	ListNode* p = lst->head;
	ListNode *temp;

	int appartmentCode = findNumberFromStr(str);
	if (p == NULL)
	{
		printf("There is no appartment with the code of %d \n", appartmentCode);
		return;
	}


	/*check if the request delete appratment is the last one*/

	if (appartmentCode == (*code) - 1)
		(*code)--;

	/*if the specific appartment is the first one*/

	if (lst->head->app.code == appartmentCode)
	{
		if (lst->head->next == NULL)
		{
			makeEmptyList(lst);
		}
		else
		{
			lst->head = p->next;
		}
		free(p);
		return;
	}

	/*there is one appartment in the list and its code is not even to appartment code*/

	if ((p = lst->tail) && (appartmentCode != p->app.code))
	{
		printf("There is no appartment with the code of %d \n", appartmentCode);
		return;
	}

	while ((p->next->app.code != appartmentCode) && (p != NULL))
	{
		p = p->next;
	}

	/*the appartmentCode is not found in the list*/
	if (p == NULL)
	{
		printf("There is no appartment with the code of %d \n", appartmentCode);
		return;
	}

	/*if the specific appartment was the last one*/

	if (p->next->next == NULL)
	{
		p->next = NULL;
		free(p->next);
		lst->tail = p;
	}
	else
	{
		temp = p->next->next;
		free(p->next);
		p->next = temp;
	}
}

int findNumberFromStr(char *str)
{
	int numFromStr = 0 ;

	while (*str != '\0')
	{
		numFromStr = numFromStr * 10 + (*str) - '0';
		str += 1;
	}

	return numFromStr;
}