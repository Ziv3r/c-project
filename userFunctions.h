
//------all the funcions of user's choice---------//


/*------------------------add&buy-----------------------*/
void addAnApp(char *str, List* lst, int code);
void buyAnAppartment(List * lst, char* str, int *code);
int findNumberFromStr(char *str);


/*------------------------delete----------------------*/
void updateListByDeleteDays(List* lst, int year, int month, int day);
void deleteAnAppartment(char *str, List* appList);


/*------------------------get-----------------------*/
void getAnAppartment(char * str, List lst);

void printByDemand(bool isUp, bool isDown, int MaximumNumRooms, int  MinimumNumRooms, int  MaximumPrice, int MinimumPrice, int specificDate, List lst);

void updateByDemandByDate(List* lst, int currentNum);
void updateByDemandMinRooms(List *lst, int minRooms);
void updateByDemandMaxRooms(List *lst, int maxRooms);
void updateByDemandMaxPrice(List *lst, int maxPrice);
void updateByDemandMinPrice(List *lst, int minPrice);

void sortFromMinToMax(List* appBydemand);
void sortFromMaxToMin(List* appBydemand);


void sortList(bool isUp, bool isDown, List *appBydemand);
void printAppartmentInThePeriod(ListNode* curr, int year, int month, int  day);

/*------------------------storages-----------------------*/
char* whichCommand(char *str, char ** short_term_history, ListCmd long_term_history);

char * lastCommand(char ** short_term_history);
char *findCommand(char* numCommand, char **short_term_history, ListCmd long_term_history);
bool findPower(char *str);
char *NewCommand(char *str, char ** short_term_history, ListCmd long_term_history);

void replaceCommand(char** placeInString, char* str1, char* str2, char ** newCommand);


void printShortTerm(char** short_term, ListCmd long_term_history);

void printAllCommands(char ** short_term_history, ListCmd long_term_history);

void printByEnterToTheStorage(List lst, int  currentNum);

