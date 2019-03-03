/*  functions apperas in main*/


/*-----------------------------------------general functions-----------------------------------*/
void printMenu();
 char* getInput();
void updateCommands(ListCmd* long_term, char** short_term, char* str, int countCmd);
void makeArrayNull(char ** short_term_history);
char* strCopy(char* str);
void checkMemoryAllocation(void *ptr);
void doCommand(char * str, List* appList, char ** short_term_history, ListCmd* long_term_history, int* code, int*countCommand, char* freeMemoryPtr);
void readingFromFiles(List* appList, char* apparatmentFile, int *code, char* commandFile, ListCmd* long_term_history, char** short_term_history, int* countCommand);
 void writeToFile(List appList, char* appartmentFile, char* commandFile, ListCmd long_term_history, char** short_term_history, int countCommand);
 bool isFull(char** short_term);

/*------------------------functions for reading and writing from binary file------------------------*/
void writeToAppartmentFiLe(List appList, char *str);
Byte * compressRoomAndData(int numRooms, Date date);
List readFromFile(char* str, int* code);
ListNode* getNode(FILE* file);
Byte *compressEnterDateToStorage(Date enterDate);
void getDateAndNumRooms(int* numRooms, Date* date,FILE* file);
void getEnterDate(FILE* file, Date* date);

/*------------------------functions for reading and writing from command file------------------------*/

void readFromCommandFile(char* str, ListCmd* long_term_history, char **short_term_history, int *countCommands);
void writeToCommandFile(char* str, ListCmd long_term_history, char **short_term_history , int countCommand);
void insertCommandFromShortTerm(char** short_term_history, int countCommand, FILE* commandsFile);
void insertCommandFromLongTerm(ListCmd long_term_history,  FILE* commandFile);
void insertCommandFromLongTermHelper(ListNodeCmd* head,FILE* commandFile);
char*  getCommandFromFile(FILE *p);
void readCommandForStorage(ListCmd* long_term, char** short_term, char* str, int countCmd);
void readToArr(char* str, int countCmd, char** short_term);
void organizeShortTermHistoryArray(char** short_term);


/*------------------------functions for free memory--------------------------------------------------*/

void freeAll(char **short_term_history, ListCmd* long_term_history, List *appList, char* freeMemoryPtr);
void freeHelperShortTermHistory(char ** short_term_history); 
void freeHelperLongTermHistory(ListNodeCmd *head); 
void freeHelperAppList(ListNode *head); 




