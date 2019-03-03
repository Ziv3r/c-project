/*----------------------------Names: Sahar Hagbi & Ziv Halzband-----------------------------------------------*/

#include "mainHeader.h"

void main(int argc, char **argv)
{
	char *str, *str2, *saveStr;
	char *short_term_history[N];
	List appList;
	int countCommand = 0, code = 1;
	ListCmd long_term_history;
	char *freeMemoryPtr;

	/*reading the commands and the appartments that allocated in argv[1] and argv[2]*/
	readingFromFiles(&appList, argv[1], &code, argv[2], &long_term_history, short_term_history, &countCommand);
	
	str = getInput();
	freeMemoryPtr = str;

	
	while (strcmp(str, "exit") != 0)
	{
		/*do the command and update the list and array commands and appList if neccesary*/
		doCommand(str, &appList, short_term_history, &long_term_history, &code, &countCommand, freeMemoryPtr);
		
		str = getInput();
		
	}

	/*write to file all the commands and the appartments that were in thr program*/
	writeToFile(appList, argv[1], argv[2], long_term_history, short_term_history, countCommand);
	
	/*free all the memory used during the program*/
	freeAll(short_term_history, &long_term_history, &appList, str);
	printf("good-Bye! :)\n");

}