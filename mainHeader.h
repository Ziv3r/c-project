#define _CRT_SECURE_NO_WARNINGS

#define N 7
#define ENTER_SIZE 6

typedef struct date
{
	int year;
	int month;
	int day;
}Date;

typedef struct appartment
{
	int code;
	char * address;
	int price;
	short int numRooms;
	Date date;
	Date enterDate;

}Appartment;

typedef unsigned char Byte; 

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


#include "list.h"
#include "mainFunctions.h"
#include "userFunctions.h"

