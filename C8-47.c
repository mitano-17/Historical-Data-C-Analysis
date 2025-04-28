/*
    LASTNAME1, FIRSTNAME1:  ERMITANO, KATE JUSTINE	SECTION1:  S14
    
	LASTNAME2, FIRSTNAME2:  KAWACHI, HIDEKI   		SECTION2:  S13 

	DATE SUBMITTED: 23/05/2021
	
	Do not forget to ENCODE your name/s, section/s and date on the space indicated above.
		
	CCPROG2 MP Solution for: Challenge #8 
	
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



/*
	Challenge #8 is not trivial.  
	
	Apply divide-and-conquer technique by breaking the logic of your C8 solution as a collection of functions.
	
	Define your helper functions after this comment.

	Make sure to include comments that indicate what each function is supposed to do.  

	Add sensible inline comments to help the checker understand the logic of your codes.
	
	Don't forget to encode the function prototypes in C6-NUMBER.h header file.
*/

/*
	
    DESCRIPTION: Searches for the text file of the country 
	PARAMETERS: *param_input_filename - contains the file where input comes from
				*Countries - array containing list of countries from the input file
				*all_countries - counts how many countries are read
	RETURN TYPE: Return 1 if successful. 0 otherwise.
	
*/

int Read_Countries(char *param_input_filename, String *Countries, int *all_countries){
	// declare counter or index
	int i = 0;
	// define file pointers both for input and output
	FILE *fp_input_file;

	// open the corresponding file in READ mode
	fp_input_file = fopen(param_input_filename, "r");
	
	// condition in case the file is not found
	if(fp_input_file == NULL){
		fprintf(stderr, "%s file not found.\n", param_input_filename);
		return 0;
	}
	
	// run loop to input data into the input file pointer
	while( (fscanf(fp_input_file, "%s", Countries[i])) == 1){
		
		// increment values
		i+=1;
		*all_countries+=1;
	}
	
	// close the input file
	fclose(fp_input_file);
	
	return 1;
}

/*
	
    DESCRIPTION: Copies data read to the members of the Stats_per_Country struct array
	PARAMETERS: *Stats_per_Country - struct array that will contain country statistics
				*Country_Data_Holder - temporary struct array where values are stored
				j - contains index
	RETURN TYPE: Return the index i(j)
	
*/

int Transfer_Data(Country_Stats *Stats_per_Country, Country_Stats *Country_Data_Holder, int j){
	// copy j to i
	int i = j;
	
	// set all structure array elements with the data found from Read_COVID_Data
	strcpy(Stats_per_Country[i].Country_Name, Country_Data_Holder->Country_Name);
	Stats_per_Country[i].Population = Country_Data_Holder->Population;
	Stats_per_Country[i].Total_Cases = Country_Data_Holder->Total_Cases;
	Stats_per_Country[i].Cases_Percent = Country_Data_Holder->Cases_Percent;
	Stats_per_Country[i].Total_Deaths = Country_Data_Holder->Total_Deaths;
	Stats_per_Country[i].Deaths_Percent = Country_Data_Holder->Deaths_Percent;
	
	// increment j by 1
	i+=1;
	
	return i;
}

/*
	
    DESCRIPTION: Swaps data between the first country and the second country
	PARAMETERS: *country1 - contains the new minimum country
				*country2 - contains the old minimum country
	RETURN TYPE: Not applicable
	
*/

void Swap(Country_Stats *country1, Country_Stats *country2){
	// declare a temporary struct
	Country_Stats temp;
	
	// swap country names
	strcpy(temp.Country_Name, country1->Country_Name);
	strcpy(country1->Country_Name, country2->Country_Name);
	strcpy(country2->Country_Name, temp.Country_Name);
	
	// swap population
	temp.Population = country1->Population;
	country1->Population = country2->Population;
	country2->Population = temp.Population;
	
	// swap total cases
	temp.Total_Cases = country1->Total_Cases;
	country1->Total_Cases = country2->Total_Cases;
	country2->Total_Cases = temp.Total_Cases;
	
	// swap percentage of cases
	temp.Cases_Percent = country1->Cases_Percent;
	country1->Cases_Percent = country2->Cases_Percent;
	country2->Cases_Percent = temp.Cases_Percent;
	
	// swap total deaths
	temp.Total_Deaths = country1->Total_Deaths;
	country1->Total_Deaths = country2->Total_Deaths;
	country2->Total_Deaths = temp.Total_Deaths;
	
	// swap percentage of deaths
	temp.Deaths_Percent = country1->Deaths_Percent;
	country1->Deaths_Percent = country2->Deaths_Percent;
	country2->Deaths_Percent = temp.Deaths_Percent;
}

/*
	
    DESCRIPTION: Arrange the countries in alphabetal order
	PARAMETERS: *Stats_per_Country - struct array that will contain country statistics
				n_countries - contains all countries read
	RETURN TYPE: Not applicable
	
*/

void Selection_Sort(Country_Stats *Stats_per_Country, int n_countries){
	int i, j, min, result = 0;
	String placeholder, minimum;
	
	for(i = 0; i < n_countries; i++){
		// set min as the first index
		min = i;
		
		// set the first country as the minimum
		strcpy(minimum, Stats_per_Country[i].Country_Name);
		
		for(j = i + 1; j < n_countries; j++){
			
			// set the second country as the placeholder for comparisons
			strcpy(placeholder, Stats_per_Country[j].Country_Name);
			
			// set result 
			result = strcmp(minimum, placeholder);
			
			// if the minimum is greater
			if(result > 0){
				min = j;
				
				// replace the minimum with the new country
				strcpy(minimum, Stats_per_Country[min].Country_Name);
			}
		}
		
		// call swap function
		Swap((Stats_per_Country + i), (Stats_per_Country + min));
	}

}

/*
	
    DESCRIPTION: Writes data to the given output file
	PARAMETERS: *Stats_per_Country - struct array that will contain country statistics
				n_countries - contains all countries read
				*param_output_filename - contains the file where data should be written
	RETURN TYPE: Not applicable
	
*/

void Output_Data(Country_Stats *Stats_per_Country, int n_countries, char *param_output_filename){
	int i;
	// declare output file pointer
	FILE *fp_output_file;
	
	// open file in WRITE mode
	fp_output_file = fopen(param_output_filename, "w");
	
	// write all contents in output file
	for(i = 0; i < n_countries; i++){	
		fprintf(fp_output_file, "%-32s %11lu %8d %10lf %8d %10lf \n", 
			Stats_per_Country[i].Country_Name, 
			Stats_per_Country[i].Population,
			Stats_per_Country[i].Total_Cases, 
			Stats_per_Country[i].Cases_Percent, 
			Stats_per_Country[i].Total_Deaths, 
			Stats_per_Country[i].Deaths_Percent);
	}
	
	// close the file
	fclose(fp_output_file); 
}


/*
	TO DO: Implement Stats_C8().  Call the helper functions that you defined above.
	
    DESCRIPTION: Reads data from the input file and writes them on the output file
	PARAMETERS: *param_output_filename - contains C8-47-OUTPUT1.txt / C8-47-OUTPUT2.txt
				*param_input_filename - contains COUNTRIES.txt / COUNTRIES-47.txt
	RETURN TYPE: Return 1 if successful. 0 otherwise.
	
*/
int 
Stats_C8(char *param_output_filename, char *param_input_filename) 
{
	/* Declare your own local variables. */
	/* Document your solution with sensible inline comments. */
	String Countries[60];
	Country_Stats Country_Data_Holder;
	Country_Stats *Stats_per_Country;

	// declare variables with values 0
	int i, n_countries = 0, result = 0, j = 0, all_countries = 0;
	
	// call Read_Countries to store all countries names from COUNTRIES.txt into the input pointer
	result = Read_Countries(param_input_filename, Countries, &all_countries);
	
	// allocate dynamic memory for Stats_per_Country to prevent segmentation fault
	Stats_per_Country = (Country_Stats*)malloc(all_countries * (sizeof(Country_Stats)) );
	
	for(i = 0; i < all_countries; i++){
		
		// call Read_COVID_Data to read each country's (stored in the Countries array) data
		result = Read_COVID_Data(Countries[i], &Country_Data_Holder);
		
		// condition if there is a file
		if(result == 1){
			
			// call Transfer_Data function
			j = Transfer_Data(Stats_per_Country, &Country_Data_Holder, j);
			
			// increment number of countries
			n_countries += 1;
		}
	}
	
	// perform selection sort in alphabetical order
	Selection_Sort(Stats_per_Country, n_countries);
	
	// call the function only if the txt file for the country exists
	if(n_countries > 0){
		// output data by calling the function below
		Output_Data(Stats_per_Country, n_countries, param_output_filename);
	}

   return 1;  /* Don't forget the return statement. Replace 888 with the appropriate value. */   
}



/*******************************************************************************
    WARNING!!!   WARNING!!!   WARNING!!!    
	
	YOU ARE NOT ALLOWED TO DEFINE the main() function in this file.  
   
	VIOLATION OF THIS RESTRICTION WILL RESULT TO A DEDUCTION OF 10 points!		 
********************************************************************************/

