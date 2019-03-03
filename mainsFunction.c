#include "mainHeader.h"

void printMenu()
{
	printf("Please enter one of the following commands :\nadd - an - ");
	printf("apt, get - an - apt, buy - an - apt or delete - an - apt\n");
	printf("For reconstruction commands, please enter :\n");
	printf("!!, !num, history, short_history or !num^str1^str2\n");
	printf("To exit, enter exit.\n");

	printf("<< ");
}

char* getInput()
{
	int phSize = 2;
	int logicSize = 0;
	char ch;

	char *str = (char*)calloc(phSize + 1, sizeof(char));

	ch = getchar();

	while (ch != '\n')
	{
		if (logicSize == phSize)
		{
			phSize *= 2;
			str = (char*)realloc(str, phSize + 1);
		}

		str[logicSize++] = ch;

		ch = getchar();

	}

	if (phSize > logicSize)
	{
		str = (char*)realloc(str, logicSize + 1);
	}

	str[logicSize] = '\0';

	return str;
}

void makeArrayNull(char ** short_term_history)
{
	for (int i = 0; i < N; i++)
	{
		short_term_history[i] = NULL;
	}
}

/*copy str to newone and return it by newAllocation Memory*/
char* strCopy(char* str)
{
	char* saveStr = (char*)malloc(strlen(str) + 1);

	strcpy(saveStr, str);

	return saveStr;

}

/*get command and update the storages*/
void updateCommands(ListCmd* long_term, char** short_term, char* str, int countCmd)
{
	char *newStr = (char*)malloc(strlen(str) + 1);

	int i = 0;

	strcpy(newStr, str);

	if (countCmd <= 7)
	{
		short_term[countCmd - 1] = newStr;
	}
	else
	{
		insertDataToEndListCmd(short_term[i], long_term);

		while (i < 6)
		{
			short_term[i] = short_term[i + 1];
			i++;
		}
		short_term[i] = newStr;
	}
}

void readingFromFiles(List* appList, char* apparatmentFile, int *code, char* commandFile, ListCmd* long_term_history, char** short_term_history, int* countCommand)
{
	(*appList) = readFromFile(apparatmentFile, code);
	readFromCommandFile(commandFile, long_term_history, short_term_history, countCommand);

}

bool isFull(char** short_term)
{
	int i;

	for (i = 0; i < N; i++)
	{
		if (short_term[i] == NULL)
			return false;
	}

	return true;
}

//----------------------functions for Binary Command FIle---------------------------//
void writeToAppartmentFiLe(List appList, char *str)
{
	short int lenghStr;
	Byte * numRoomsAndDateCompress;
	Byte *enteryDateCompress;

	ListNode*curr = appList.head;

	FILE *p;
	p = fopen(str, "wb");
	checkMemoryAllocation(p);

	while (curr != NULL)
	{
		fwrite(&(curr->app.code), sizeof(short int), 1, p);

		lenghStr = strlen(curr->app.address);

		fwrite(&lenghStr, sizeof(short int), 1, p);

		fwrite(curr->app.address, sizeof(char), lenghStr, p);

		fwrite(&(curr->app.price), sizeof(int), 1, p);

		numRoomsAndDateCompress = compressRoomAndData(curr->app.numRooms, curr->app.date);

		fwrite(numRoomsAndDateCompress, sizeof(Byte), 3, p);

		enteryDateCompress = compressEnterDateToStorage(curr->app.enterDate);

		fwrite(enteryDateCompress, sizeof(Byte), 2, p);

		curr = curr->next;
	}
	fclose(p);
}

/*making array of Byte* and return it by thhe info on numRooms and date  */
Byte * compressRoomAndData(int numRooms, Date date)
{
	Byte *RoomAndData;

	Byte char1, char2, char3;
	Byte rooms;
	Byte days1, days2;
	Byte month;
	Byte year1, year2;

	RoomAndData = (Byte *)malloc(sizeof(Byte) * 3);

	rooms = numRooms;

	rooms <<= 4;

	days1 = days2 = date.day;

	days1 >>= 1;
	days2 <<= 7;

	month = date.month;
	month <<= 3;

	year1 = year2 = date.year;

	year1 >>= 4;
	year2 <<= 4;

	char1 = rooms | days1;
	char2 = (days2 | month) | year1;
	char3 = year2;

	RoomAndData[0] = char1;
	RoomAndData[1] = char2;
	RoomAndData[2] = char3;

	return RoomAndData;
}

/*making array of Byte* and return it by thhe info on enterDate*/
Byte *compressEnterDateToStorage(Date enterDate)
{
	Byte * EnterDateToStorage;

	Byte char1;
	Byte char2;

	Byte day;
	Byte month1, month2;
	Byte year;

	EnterDateToStorage = (Byte *)malloc(sizeof(Byte) * 2);

	day = enterDate.day;

	day <<= 3;

	month1 = month2 = enterDate.month;

	month1 >>= 1;
	month2 <<= 7;

	year = enterDate.year - 2000;

	char1 = day | month1;
	char2 = month2 | year;

	EnterDateToStorage[0] = char1;
	EnterDateToStorage[1] = char2;

	return EnterDateToStorage;
}

void checkMemoryAllocation(void *ptr)
{
	if (ptr == NULL)
	{
		printf("error in aloocating memory");
		exit(1);
	}
}

List readFromFile(char* str, int* code)
{
	FILE* file;
	List appList;
	makeEmptyList(&appList);
	ListNode* curr;

	int sizeOfFile = 0;

	file = fopen(str, "rb");

	if (file == NULL)
		return appList;

	fseek(file, 0, SEEK_END);
	sizeOfFile = ftell(file);
	fseek(file, 0, SEEK_SET);


	if (sizeOfFile == 0)
		return appList;

	curr = getNode(file);

	while (curr != NULL)
	{

		insertNodeTotail(curr, &appList);

		curr = getNode(file);

	}
	appList.tail->next = NULL;

	fclose(file);

	*code = appList.tail->app.code + 1;
	return appList;
}

/*reading the info from the file to new node*/
ListNode* getNode(FILE* file)
{
	int flag = 0;
	short int code = 0;
	short int len_address;
	ListNode* newNode = malloc(sizeof(ListNode));

	flag = fread(&code, sizeof(short int), 1, file);

	if (flag == 0)
		return NULL;

	newNode->app.code = code;

	fread(&len_address, sizeof(short int), 1, file);
	newNode->app.address = (char*)calloc(len_address + 1, sizeof(char));
	fread(newNode->app.address, sizeof(char), len_address, file);
	newNode->app.address[len_address] = '\0';

	fread(&newNode->app.price, sizeof(int), 1, file);

	getDateAndNumRooms(&newNode->app.numRooms, &newNode->app.date, file);

	getEnterDate(file, &newNode->app.enterDate);

	return newNode;
}

void getEnterDate(FILE* file, Date* date)
{
	Byte bytes[2];
	Byte month1, month2, day, year;

	fread(bytes, sizeof(Byte), 2, file);
	day = bytes[0];
	day >>= 3;

	date->day = day;

	month1 = bytes[0];
	month1 <<= 5;
	month1 >>= 4;

	month2 = bytes[1];
	month2 >>= 7;


	date->month = month1 | month2;

	year = bytes[1];
	year <<= 1;
	year >>= 1;

	date->year = year;
	date->year += 2000;
}

void getDateAndNumRooms(int* numRooms, Date* date, FILE* file)
{
	Byte bytes[3];
	Byte day1, day2, year1, year2, month;

	fread(bytes, sizeof(Byte), 3, file);

	*numRooms = bytes[0] >> 4;

	day1 = bytes[0];
	day1 <<= 4;
	day1 >>= 3;

	day2 = bytes[1];
	day2 >>= 7;

	month = (bytes[1]);
	month <<= 1;
	month >>= 4;
	date->month = month;

	year1 = (bytes[1] << 5) >> 1;
	year2 = (bytes[2] >> 4);

	date->day = day1 | day2;
	date->year = year1 | year2;
}




//----------------------functions for Text Command FIle---------------------------//


void readFromCommandFile(char* str, ListCmd* long_term_history, char **short_term_history, int *countCommands)
{
	char ch;
	char *currCommand;
	int phSize = 2;
	int logiSize = 0;
	int numCommands = 0;

	makeArrayNull(short_term_history);
	makeEmptyListCmd(long_term_history);

	FILE * commandFile = fopen(str, "rt");
	//check if the file is exist but not read well .

	if (commandFile == NULL)
	{
		printMenu();
		return;
	}

	currCommand = getCommandFromFile(commandFile);

	while (currCommand != NULL)
	{
		readCommandForStorage(long_term_history, short_term_history, currCommand, ++numCommands);

		//updateCommands(long_term_history, short_term_history, currCommand, ++numCommands);

		currCommand = getCommandFromFile(commandFile);
	}

	*countCommands = numCommands;

	organizeShortTermHistoryArray(short_term_history);

	printMenu();
}

/*In case of that short_term is not full the function will set all strings into the begining*/
void organizeShortTermHistoryArray(char** short_term)
{
	if (short_term[0] != NULL)
		return;

	int writeInd = 0;
	int readInd = 0;

	char*temp[N];

	for (int i = 0; i < N; i++)
	{
		if (short_term[i] != NULL)
			temp[writeInd++] = short_term[i];
	}

	makeArrayNull(short_term);

	for (int i = 0; i < writeInd; i++)
		short_term[i] = temp[readInd++];
}

/*get a command(Str) and allocate it to the fit place short_term or long_term following the countCmd*/
void readCommandForStorage(ListCmd* long_term, char** short_term, char* str, int countCmd)
{
	if (isFull(short_term))
		insertDataToHeadList(long_term, str);
	else
		readToArr(str, countCmd, short_term);

}

/*read a command from the specific place in file till arrive to '/n'*/
char*  getCommandFromFile(FILE *p)
{
	int phSize = 2;
	int logicSize = 0;

	char ch = fgetc(p);

	if (ch == EOF)
		return NULL;

	char *str = (char*)malloc(phSize + 1);

	while (ch != '\n')
	{
		if (phSize == logicSize)
		{
			phSize *= 2;
			str = (char *)realloc(str, sizeof(char)*phSize + 1);
		}
		str[logicSize++] = ch;

		ch = fgetc(p);
	}

	if (phSize > logicSize)
	{
		str = (char *)realloc(str, sizeof(char)*logicSize + 1);
	}
	str[logicSize] = '\0';

	return str;
}

void writeToCommandFile(char* str, ListCmd long_term_history, char **short_term_history, int countCommand)
{
	FILE * commandsFile = fopen(str, "wt");

	if (countCommand <= 7)
		insertCommandFromShortTerm(short_term_history, countCommand, commandsFile);

	else
	{
		insertCommandFromShortTerm(short_term_history, countCommand, commandsFile);
		insertCommandFromLongTerm(long_term_history, commandsFile);
	}

}

void insertCommandFromShortTerm(char** short_term_history, int countCommand, FILE* commandsFile)
{
	int i;
	if (countCommand > 7)
		countCommand = 7;

	for (int i = countCommand - 1; i >= 0; i--)
	{
		fprintf(commandsFile, "%s\n", short_term_history[i]);
	}
}

void insertCommandFromLongTerm(ListCmd long_term_history, FILE* commandFile)
{
	insertCommandFromLongTermHelper(long_term_history.head, commandFile);
}

void insertCommandFromLongTermHelper(ListNodeCmd* head, FILE* commandFile)
{
	if (head == NULL)
		return;

	insertCommandFromLongTermHelper(head->next, commandFile);
	fprintf(commandFile, "%s\n", head->cmd);
}

/*insert str command to short_term following countCmd*/
void readToArr(char* str, int countCmd, char** short_term)
{
	int i;
	int placeToInsert = N - countCmd;

	short_term[placeToInsert] = str;

}

//----------------------------functions for free memory------------------------------------//
void freeAll(char **short_term_history, ListCmd* long_term_history, List *appList, char* freeMemoryPtr)
{
	freeHelperShortTermHistory(short_term_history);
	freeHelperLongTermHistory(long_term_history->head);
	freeHelperAppList(appList->head);
	free(freeMemoryPtr);
}

void freeHelperShortTermHistory(char ** short_term_history)
{
	for (int i = 0; i < N && short_term_history[i] != NULL; i++)
	{
		free(short_term_history[i]);
	}
}

void freeHelperLongTermHistory(ListNodeCmd *head)
{
	if (head == NULL)
		return;

	freeHelperLongTermHistory(head->next);
	free(head);
}

void freeHelperAppList(ListNode *head)
{

	if (head != NULL)
	{
		freeHelperAppList(head->next);
		free(head->app.address);
		free(head);
	}
}

/*the main function that get str of the input's command and proccess it by the instructions and
save it in the storages if neccesary*/
void doCommand(char * str, List* appList, char ** short_term_history, ListCmd* long_term_history, int* code, int*countCommand, char* freeMemoryPtr)
{
	char* saveStr;
	char* str2;

	freeMemoryPtr = str;

		if (str[0] == '!')
	{
		str = whichCommand(str, short_term_history, *long_term_history);
		freeMemoryPtr = str;
	}

	saveStr = strCopy(str);

	if (strcmp(str, "short_history") == 0)
	{
		printShortTerm(short_term_history, (*long_term_history));
	}
	if (strcmp(str, "history") == 0)
	{
		printAllCommands(short_term_history, (*long_term_history));
	}
	else
	{
		str = strtok(str, " ");		//get the command . 

		str2 = strtok(NULL, "\0");		//get the information of the string after the command . 

		if (strcmp(str, "add-an-apt") == 0)
		{
			addAnApp(str2 + 1, appList, (*code)++);
		}

		if (strcmp(str, "buy-an-apt") == 0)
		{
			buyAnAppartment(appList, str2, code);
		}

		if (strcmp(str, "get-an-apt") == 0)
		{
			getAnAppartment(str2 + 1, *appList);
		}

		if (strcmp(str, "delete-an-apt") == 0)
		{
			deleteAnAppartment(str2+1, appList);
		}
	}

	if ((strcmp(str, "history") != 0) && (strcmp(str, "short_history") != 0))
		updateCommands(long_term_history, short_term_history, saveStr, ++(*countCommand));
	else
		free(saveStr);

	printf("\n<< ");

	free(freeMemoryPtr);
}

/*function that writing all the information that was process during the program*/
void writeToFile(List appList, char* appartmentFile, char* commandFile, ListCmd long_term_history, char** short_term_history, int countCommand)
{
	writeToAppartmentFiLe(appList, appartmentFile);
	writeToCommandFile(commandFile, long_term_history, short_term_history, countCommand);
}