typedef struct listnode
{
	Appartment app;
	struct listnode* next;
}ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
}List;

typedef struct listNodeCmd
{
	char * cmd;
	struct listNodeCmd* next;
}ListNodeCmd;

typedef struct listCmd
{
	ListNodeCmd *head;
	ListNodeCmd *tail;
}ListCmd;

/*----------------------------------Appartment List--------------------------------------------------*/
void makeEmptyList(List *lst);
bool isEmpty(List lst); 
void insertDataToEndlist(Appartment app, List *lst); 
ListNode* createNewNode(Appartment app, ListNode* next);
void insertNodeTotail(ListNode* newTail, List *lst); 
void printList(List lst);
void freeList(List *lst); 
void freeListRec(ListNode* head); 
void printNodeApp(ListNode* curr);
void deleteNodeFromList(List *lst, ListNode* curr);
List CopyList(List* lst);
void swapNodesApp(ListNode* curr, ListNode* next);


/*----------------------------------Command List--------------------------------------------------*/

void makeEmptyListCmd(ListCmd *lst);
bool isEmptyCmd(ListCmd lst);
void insertDataToEndListCmd(char * data, ListCmd* lst); 
ListNode* createNewNodeCmd(char * newTail, ListNode * next); 
void insertNodeTotailCmd(ListNodeCmd * newTail, ListCmd* lst ); 
void insertDataToHeadList(List* lst, char* str);
void printListCmd(ListCmd lst);
void freeListCmd(ListCmd lst);
void freeListRecCmd(ListNodeCmd * head);


