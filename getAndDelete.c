#include "mainHeader.h"


/*-----------------------------------functions of "get" user's choice ----------------------------*/
void getAnAppartment(char * str, List lst)
{
	//str = MinimumNumRooms 3 - MaximumNumRooms 6 

	char * wholeCommand;

	int currentNum;

	char str1[100];

	strcpy(str1, str);

	wholeCommand = strtok(str1, "-");

	char temp[20];
	int specificDate = -1;
	int MaximumNumRooms = -1;
	int MinimumNumRooms = -1;
	int MaximumPrice = -1;
	int MinimumPrice = -1;
	bool isUp = false;
	bool isDown = false;

	while ((wholeCommand != NULL) && (*wholeCommand != 's'))
	{
		sscanf(wholeCommand, "%s%d", temp, &currentNum);
		wholeCommand = temp;

		if (strcmp(wholeCommand, "Enter") == 0)
		{
			printByEnterToTheStorage(lst, currentNum);
			return;
		}
		if (strcmp(wholeCommand, "Date") == 0)
		{
			specificDate = currentNum;
		}
		if (strcmp(wholeCommand, "MaximumNumRooms") == 0)
		{
			MaximumNumRooms = currentNum;
		}
		if (strcmp(wholeCommand, "MinimumNumRooms") == 0)
		{
			MinimumNumRooms = currentNum;
		}
		if (strcmp(wholeCommand, "MaximumPrice") == 0)
		{
			MaximumPrice = currentNum;
		}
		if (strcmp(wholeCommand, "MinimumPrice") == 0)
		{
			MinimumPrice = currentNum;
		}

		wholeCommand = strtok(NULL, "-\0");
	}

	if (wholeCommand != NULL)
	{
		if (strcmp(wholeCommand, "sr") == 0)
		{
			isDown = true;
		}
		else
		{
			isUp = true;
		}
	}

	printByDemand(isUp, isDown, MaximumNumRooms, MinimumNumRooms, MaximumPrice, MinimumPrice, specificDate, lst);

}

/*update the appListByDemand by deleting specific nodes following the request of thr user*/

void updateByDemandMinRooms(List *lst, int minRooms)
{
	ListNode* curr = lst->head;
	ListNode* next;

	while (curr != NULL)
	{
		if (curr->app.numRooms < minRooms)
		{
			next = curr->next;

			deleteNodeFromList(lst, curr);

			curr = next;
		}
		else
		{
			curr = curr->next;
		}
	}
}

void updateByDemandMaxRooms(List *lst, int maxRooms)
{
	ListNode* curr = lst->head;
	ListNode* next;

	while (curr != NULL)
	{
		if (curr->app.numRooms > maxRooms)
		{
			next = curr->next;

			deleteNodeFromList(lst, curr);

			curr = next;
		}
		else
			curr = curr->next;
	}
}

void updateByDemandMaxPrice(List *lst, int maxPrice)
{
	ListNode* curr = lst->head;
	ListNode* next;

	while (curr != NULL)
	{
		if (curr->app.price > maxPrice)
		{
			next = curr->next;

			deleteNodeFromList(lst, curr);

			curr = next;
		}
		else
			curr = curr->next;
	}
}

void updateByDemandMinPrice(List *lst, int minPrice)
{
	ListNode* curr = lst->head;
	ListNode* next;

	while (curr != NULL)
	{
		if (curr->app.price < minPrice)
		{
			next = curr->next;

			deleteNodeFromList(lst, curr);

			curr = next;
		}
		else

			curr = curr->next;
	}
}

//------------------------------------------------------------------------------

void printByDemand(bool isUp, bool isDown, int MaximumNumRooms, int  MinimumNumRooms, int  MaximumPrice, int MinimumPrice, int specificDate, List lst)
{

	/*using helper list to focus all the demands by decreasing appartments following the requests*/

	List appBydemand = CopyList(&lst);

	if (MinimumNumRooms != -1)
	{
		updateByDemandMinRooms(&appBydemand, MinimumNumRooms);
	}
	if (MaximumNumRooms != -1)
	{
		updateByDemandMaxRooms(&appBydemand, MaximumNumRooms);
	}
	if (MaximumPrice != -1)
	{
		updateByDemandMaxPrice(&appBydemand, MaximumPrice);
	}
	if (MinimumPrice != -1)
	{
		updateByDemandMinPrice(&appBydemand, MinimumPrice);
	}
	if (specificDate != -1)
	{
		updateByDemandByDate(&appBydemand, specificDate);
	}

	if (!isEmpty(appBydemand))
	{
		if (isUp || isDown)
		{
			sortList(isUp, isDown, &appBydemand);
		}
	}

	printList(appBydemand);

	freeList(&appBydemand);


}

void sortList(bool isUp, bool isDown, List *appBydemand)
{
	if (isUp)
		sortFromMinToMax(appBydemand);

	if (isDown)
		sortFromMaxToMin(appBydemand);

}

void sortFromMaxToMin(List* appBydemand)
{
	bool swapped = true;
	ListNode* sortedNode = NULL;
	ListNode* curr;

	while (swapped)
	{
		swapped = false;
		curr = appBydemand->head;

		while (curr->next != sortedNode)
		{
			if (curr->app.price < curr->next->app.price)
			{
				swapNodesApp(curr, curr->next);
				swapped = true;
			}

			curr = curr->next;
		}
		sortedNode = curr;
	}
}

void sortFromMinToMax(List* appBydemand)
{
	bool swapped = true;
	ListNode* sortedNode = NULL;
	ListNode* curr;

	while (swapped)
	{
		swapped = false;
		curr = appBydemand->head;

		while (curr->next != sortedNode)
		{
			if (curr->app.price > curr->next->app.price)
			{
				swapNodesApp(curr, curr->next);
				swapped = true;
			}

			curr = curr->next;
		}
		sortedNode = curr;
	}
}

void swapNodesApp(ListNode* curr, ListNode* next)
{
	Appartment temp;

	temp = curr->app;
	curr->app = next->app;
	next->app = temp;
}

void updateByDemandByDate(List* lst, int currentNum)
{
	/*calculate the year month and the day*/

	int year = currentNum % 100;
	int month = currentNum / 10000 % 100;
	int day = currentNum / 1000000;

	ListNode* curr = lst->head;
	ListNode* next;

	while (curr != NULL)
	{
		if (curr->app.date.year < year)
		{
			curr = curr->next;
		}
		else if (curr->app.date.year == year)
		{
			if (curr->app.date.month < month)
			{
				curr = curr->next;
			}
			else if (curr->app.date.month == month)
			{
				if (curr->app.date.day < day)
				{
					curr = curr->next;
				}
				else
				{
					next = curr->next;

					deleteNodeFromList(lst, curr);
					curr = next;
				}
			}
			else
			{
				next = curr->next;

				deleteNodeFromList(lst, curr);
				curr = next;
			}
		}
		else
		{
			next = curr->next;

			deleteNodeFromList(lst, curr);
			curr = next;
		}
	}

}

void printByEnterToTheStorage(List lst, int  currentNum)
{

	/*calculate the current time*/
	time_t currTime;

	time(&currTime);
	struct tm* myTime = localtime(&currTime);
	myTime->tm_mday -= currentNum;
	mktime(myTime);

	int year = myTime->tm_year + 1900;
	int month = myTime->tm_mon + 1;
	int day = myTime->tm_mday;

	ListNode* curr = lst.head;


	printAppartmentInThePeriod(curr, year, month, day);

}

void printAppartmentInThePeriod(ListNode* curr, int year, int month, int  day)
{
	while (curr != NULL)
	{
		if (curr->app.enterDate.year < year)
		{
			curr = curr->next;
		}
		else if (curr->app.enterDate.year == year)
		{
			if (curr->app.enterDate.month < month)
			{
				curr = curr->next;
			}
			else if (curr->app.enterDate.month == month)
			{
				if (curr->app.enterDate.day < day)
				{
					curr = curr->next;
				}
				else
				{
					printNodeApp(curr);
					curr = curr->next;
				}
			}
			else
			{
				printNodeApp(curr);
				curr = curr->next;
			}
		}
		else
		{
			printNodeApp(curr);
			curr = curr->next;
		}

	}
}


/*-----------------functions of the "delete" choice--------------------*/
void deleteAnAppartment(char *str, List* appList)
{
	char temp[ENTER_SIZE];
	int numOfDays;

	sscanf(str, "%s %d", temp, &numOfDays);

	/*calculate current time*/
	time_t currTime;

	time(&currTime);
	struct tm* myTime = localtime(&currTime);
	myTime->tm_mday -= numOfDays;
	mktime(myTime);


	int year = myTime->tm_year + 1900;
	int month = myTime->tm_mon + 1;
	int day = myTime->tm_mday;


	updateListByDeleteDays(appList, year, month, day);

}

void updateListByDeleteDays(List* lst, int year, int month, int day)
{
	ListNode* curr = lst->head;
	ListNode* next;

	while (curr != NULL)
	{
		if (curr->app.enterDate.year < year)
		{
			curr = curr->next;
		}
		else if (curr->app.enterDate.year == year)
		{
			if (curr->app.enterDate.month < month)
			{
				curr = curr->next;
			}
			else if (curr->app.enterDate.month == month)
			{
				if (curr->app.enterDate.day < day)
				{
					curr = curr->next;
				}
				else
				{
					next = curr->next;
					deleteNodeFromList(lst, curr);
					curr = next; 
				}
			}
			else
			{
				next = curr->next;
				deleteNodeFromList(lst, curr);
				curr = next;
			}
		}
		else
		{
			next = curr->next;
			deleteNodeFromList(lst, curr);
			curr = next;
		}
	}
}