#include "mainHeader.h"

//-------------------------------------functions to List----------------------//

bool isEmpty(List lst)
{
	if (lst.head == NULL)
		return true;
	else
		return false;
}

void makeEmptyList(List *lst)
{
	lst->head = lst->tail = NULL;
}

void insertDataToEndlist(Appartment app, List *lst)
{
	ListNode* newNode;

	newNode = createNewNode(app, NULL);

	insertNodeTotail(newNode, lst);
}

ListNode* createNewNode(Appartment app, ListNode* next)
{
	ListNode* newNode;

	newNode = (ListNode*)malloc(sizeof(ListNode));

	newNode->app = app;

	newNode->next = next;

	return newNode;
}

void insertNodeTotail(ListNode* newTail, List *lst)
{
	if (isEmpty(*lst) == true)
	{
		lst->tail = lst->head = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void printList(List lst)
{
	ListNode* curr = lst.head;

	while (curr != NULL)
	{
		printNodeApp(curr);

		curr = curr->next;
	}
}

void freeList(List* lst)
{
	freeListRec(lst->head);
}

void freeListRec(ListNode* head)
{
	if (head == NULL)
		return;

	freeListRec(head->next);
	free(head->app.address);
	free(head);

}

List CopyList(List* lst)
{
	List newList;
	makeEmptyList(&newList);

	ListNode* curr = lst->head;

	while (curr != NULL)
	{
		insertDataToEndlist(curr->app, &newList);
		curr = curr->next;
	}

	return newList;
}


//-------------------------------------functions to Cmd List----------------------//

void makeEmptyListCmd(ListCmd *lst)
{
	lst->head = lst->tail = NULL;
}

bool isEmptyCmd(ListCmd lst)
{
	if (lst.head == NULL)
		return true;
	else
		return false;
}

void insertDataToEndListCmd(char * data, ListCmd* lst)
{
	ListNodeCmd* newTail;

	newTail = createNewNodeCmd(data, NULL);

	insertNodeTotailCmd(newTail, lst); 
}

ListNode* createNewNodeCmd(char * newTail, ListNode * next)
{
	ListNodeCmd* res = (ListNodeCmd*)malloc(sizeof(ListNodeCmd));

	res->cmd = newTail;
	res->next = next;

	return res; 
}

void insertNodeTotailCmd(ListNodeCmd * newTail, ListCmd* lst)
{
	if (isEmptyCmd(*lst))
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void printListCmd(ListCmd lst)
{
	ListNodeCmd* curr = lst.head;

	while (curr != NULL)
	{
		printf("%s", curr->cmd); 
		curr = curr->next;
	}
}

void freeListCmd(ListCmd lst)
{
	freeListRecCmd(lst.head); 
}

void freeListRecCmd(ListNodeCmd * head)
{
	if (head == NULL)
		return;
	
	freeListRecCmd(head->next);
	free(head); 
}

void deleteNodeFromList(List *lst, ListNode* curr)
{
	ListNode* p = lst->head;
	ListNode *temp;

	if (p == curr)
	{
		lst->head = p->next;
		free(p);
	}
	else
	{
		while (p->next != curr)
		{
			p = p->next;
		}

		p->next = curr->next;
		free(curr);
	}
}

void printNodeApp(ListNode* curr)
{
	printf("\nApt details:\n");
	printf("Code: %d\n", curr->app.code);
	printf("Address: %s\n", curr->app.address);
	printf("Number of rooms: %d\n", curr->app.numRooms);
	printf("Price: %d\n", curr->app.price);
	printf("Entry date: %d.%d.%d\n", curr->app.date.day, curr->app.date.month, curr->app.date.year);
	printf("Database entry date: %d.%d.%d\n", curr->app.enterDate.day, curr->app.enterDate.month, curr->app.enterDate.year); 

}

void insertDataToHeadList(List* lst, char* str)
{
	ListNode* newHead = createNewNodeCmd(str, lst->head);

	if (isEmpty(*lst))
		lst->head = lst->tail = newHead;
	else
		lst->head = newHead;
}