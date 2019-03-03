#include "mainHeader.h"

//------------------print the storgages ---------------/
void printShortTerm(char** short_term, ListCmd long_term_history)
{
	int countCommands = 1;
	int i = 0;

	ListNodeCmd* curr = long_term_history.head;

	while (curr != NULL)
	{
		countCommands++;

		curr = curr->next;
	}
	while (short_term[i] != NULL && i < N)
	{
		printf("%d. %s\n", countCommands++, short_term[i]);
		i++;
	}
}

void printAllCommands(char ** short_term_history, ListCmd long_term_history)
{
	int countCommands = 1;
	int i = 0;

	ListNodeCmd* curr = long_term_history.head;

	while (curr != NULL)
	{
		printf("%d. %s\n", countCommands++, curr->cmd);

		curr = curr->next;
	}
	while (short_term_history[i] != NULL && i < N)
	{
		printf("%d. %s\n", countCommands++, short_term_history[i]);
		i++;
	}
}

//----------------------- functions---------------------//
char* whichCommand(char *str, char ** short_term_history, ListCmd long_term_history)
{
	int numCommand;
	char *saveLocation;
	char * returnStr;

	if (strcmp(str, "!!") == 0)
	{
		free(str);
		return lastCommand(short_term_history);
	}

	/*from the kind of !<num>^str1^str2   */
	if (findPower(str))
	{

		returnStr = NewCommand(str + 1, short_term_history, long_term_history);
		free(str);

		return returnStr;
	}
	/*from the kind of !<num>   */
	else  
	{

		returnStr = findCommand(str + 1, short_term_history, long_term_history);
		free(str);

		return returnStr;
	}
}

/*function that allocate the last command and return it in new allocation*/
char * lastCommand(char ** short_term_history)

{
	char *str;

	int i = 0;

	while (i < N && short_term_history[i] != NULL)
		i++;

	str = strCopy(short_term_history[i - 1]);

	return str;
}

/*function that ger numCommand that represent a number and return the cpmmand it represent*/
char *findCommand(char* numCommand, char **short_term_history, ListCmd long_term_history)
{
	int count = 0;

	ListNodeCmd* curr = long_term_history.head;

	int numOfCommand = 0;
	int i = 0;

	numOfCommand = findNumberFromStr(numCommand);

	while (curr != NULL)
	{
		if (count == numOfCommand)
			return strCopy(curr->cmd);

		count++;
		curr = curr->next; 
	}

	while (count < numOfCommand)
	{
		i++;
		count++;
	}

	return strCopy(short_term_history[i - 1]);

}

/*get str and divide it to 3 parts and return the new command following the instructions*/
char * NewCommand(char* str, char ** short_term_history, ListCmd long_term_history)
{
	char* numCommand;
	char* str1, *str2;
	char* newCommand, *saveBegin;
	char *placeInString;

	numCommand = strtok(str, "^");

	str1 = strtok(NULL, "^");
	str2 = strtok(NULL, "\0");

	newCommand = findCommand(numCommand, short_term_history, long_term_history);
	saveBegin = newCommand;
	
	/*placeInString always procceed till findStrInStr return NULL and doesn't find a place in str
	that str1 perform*/
	
	placeInString = strstr(newCommand, str1);

	while (placeInString != NULL)
	{
		replaceCommand(&placeInString, str1, str2, &newCommand);

		placeInString = strstr(placeInString + strlen(str2), str1);
	}
	return newCommand;
}

/*get placeInString and replace str1 with str2 in newCommand on this specific place*/
void replaceCommand(char** placeInString, char* str1, char* str2, char ** newCommand)
{
	char *newString;
	int lenAfter, lenBefore = strlen(*newCommand);
	char saveCh = **placeInString;

	**placeInString = '\0';
	lenAfter = strlen(*newCommand);

	(*placeInString) += strlen(str1);

	newString = strCopy(*placeInString);

	*newCommand = (char*)realloc(*newCommand, lenBefore - strlen(str1) + strlen(str2) + 1);


	strcat(*newCommand, str2);

	strcat(*newCommand, newString);
	*placeInString = *newCommand + lenAfter;

	free(newString);

}

bool findPower(char *str)
{
	while (*str != '\0')
	{
		if (*str == '^')
			return true;

		str++;
	}

	return false;

}
