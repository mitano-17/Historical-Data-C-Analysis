/*
    LASTNAME1, FIRSTNAME1:  ERMITANO, KATE JUSTINE	SECTION1:  S14
    
	LASTNAME2, FIRSTNAME2:  KAWACHI, HIDEKI   		SECTION2:  S13  

	DATE SUBMITTED: 23/05/2021
	
	Do not forget to ENCODE your name/s, section/s and date on the space indicated above.
		
	CCPROG2 MP Solution for: Challenge #7 
	
	Note that if you compile JUST this file only, you will get an error that says "undefined
	reference to WinMain" (for DEVCPP users).  	  
	
	You'll have to include this file first in main-NUMBER.c via #include, and then it is the 
	main-NUMBER.c that you you should compile to produce main-NUMBER.exe file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    TO DO: change the #include below to your own file/solution. You are not allowed to include other files.
*/
#include "C6-47.h"


/*****************************************************************************************************
    WARNING!!!   WARNING!!!   WARNING!!!    
	
	YOU ARE NOT ALLOWED TO DEFINE the other functions aside from Read_COVID_Data() in this file.
	
	VIOLATION OF THIS RESTRICTION WILL RESULT TO A DEDUCTION OF 10 points!		 
*****************************************************************************************************/



/*
	TO DO: Implement Read_COVID_Data().
	
	DESCRIPTION: Opens a txt file corresponding to *param_country and reads all data into stdin before closing
	PARAMETERS: char* param_country - the character array that makes up the country's name
				Country_Stats *ptrData - the structure pointer that will contain all necessary data
	RETURN TYPE: Return 1 if reading is successful and the file is found. Return 0 otherwise.
*/
int
Read_COVID_Data(char *param_country, Country_Stats *ptrData)  /* TO DO: fill up the parameter data type. */
{
	/* Declare your own local variables. */	
	char filename[60], directory[150];
	int i;
	double population_holder; // holds long population into double to compute for the percentage
	FILE *fp; // my file pointer
	
	// initialize members to 0
	ptrData->Total_Cases = 0;
	ptrData->Total_Deaths = 0;
	
	/* 
		NOTES: param_country contains the country's name 
		INPUT THE FF: country name, population, life_expectancy, last row of data
	*/

	/* Document your solution with sensible inline comments. */ 
	// okay sir
	
	// copy the key to the member
	strcpy(ptrData->Country_Name, param_country);
	// copy the key to the file name
	strcpy(filename, param_country);
	// append .txt to the filename
	strcat(filename, ".txt");
	
	// open the corresponding file in READ mode
	strcpy(directory, "CHD/");
	strcat(directory, filename);
	fp = fopen(directory, "r");
	
	// condition in case the file is not found
	if(fp == NULL){
		fprintf(stderr, "No data for %s.\n", filename);
		return 0;
	}
	
	// set the variable i back to 0
	i = 0;
	
	// find total number of data
	while( fscanf(fp, "%s %d %d %lu %f", ptrData->Country_Daily_Data[i].Date, &ptrData->Country_Daily_Data[i].New_Cases,
			&ptrData->Country_Daily_Data[i].New_Deaths, &ptrData->Population, &ptrData->Life_Expectancy) == 5){
		
		// add all cases and deaths
		ptrData->Total_Cases = (ptrData->Total_Cases) + (ptrData->Country_Daily_Data[i].New_Cases);
		ptrData->Total_Deaths = (ptrData->Total_Deaths) + (ptrData->Country_Daily_Data[i].New_Deaths);
		
		// turn data into double type for calculation
		population_holder = ptrData->Population * 1.00;
		
		// Increment the number of data being input into the program
		i+=1;
		
		// set member to the increment value or counter
		ptrData->Number_of_Daily_Data = i;
	}
	
	// multiply values by 100 to get the percentage value
	ptrData->Cases_Percent = (ptrData->Total_Cases)/(population_holder) * 100;
	ptrData->Deaths_Percent = (ptrData->Total_Deaths)/(population_holder) * 100;
	
	// close the file
	fclose(fp);
	
   return 1;  /* Don't forget the return statement. Replace 888 with the appropriate value. */   
}






/*******************************************************************************
    WARNING!!!   WARNING!!!   WARNING!!!    
	
	YOU ARE NOT ALLOWED TO DEFINE the main() function in this file.  
   
	VIOLATION OF THIS RESTRICTION WILL RESULT TO A DEDUCTION OF 10 points!		 
********************************************************************************/


