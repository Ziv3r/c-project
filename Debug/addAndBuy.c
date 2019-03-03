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

	time(&currTime);
	struct tm* myTime = localtime(&currTime);

	newApp.enterDate.day = myTime->tm_mday;
	newApp.enterDate.month = myTime->tm_mon + 1;
	newApp.enterDate.year = myTime->tm_year + 1900;

	insertDataToEndlist(newApp, lst);
}

void buyAnAppartment(List * lst, char* str, int *code)
{
	ListNode* p = lst->head;
	ListNode *temp;

	int codeApartment = (int)str[0] - '0';

	if (codeApartment == (*code)-1)
		(*code)--;

	if (lst->head->app.code == codeApartment)
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
	while (p->next->app.code != codeApartment)
	{
		p = p->next;
	}

	free(p->next);

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