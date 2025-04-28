/*
    LASTNAME1, FIRSTNAME1:  ERMITANO, KATE JUSTINE	SECTION1:  S14
    
	LASTNAME2, FIRSTNAME2:  KAWACHI, HIDEKI   		SECTION2:  S13  

	DATE SUBMITTED: 23/05/2021
	
	Do not forget to ENCODE your name/s, section/s and date on the space indicated above.
		
	CCPROG2 MP Solution for: Challenge #9 
	
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
	Challenge #9 is not trivial.  
	
	Apply divide-and-conquer technique by breaking the logic of your C9 solution as a collection of functions.
	
	Define your helper functions after this comment.  
	
	Make sure to include comments that indicate what each function is supposed to do.  

	Add sensible inline comments to help the checker understand the logic of your codes.
	
	Don't forget to encode the function prototypes in C6-NUMBER.h header file.
*/

/*
	
    DESCRIPTION: Copies all continents from the Continents array/list
	PARAMETERS: *Stats_per_Continent - struct array that will contain continent statistics
				*Continents - array containing all the continents
	RETURN TYPE: Not applicable
	
*/

void Copy_Continents(Country_Stats *Stats_per_Continent, String *Continents){
	int i;
	
	// copy continents to members of Stats_per_Continent
	for(i = 0; i < 6; i++){
		strcpy(Stats_per_Continent[i].Continent, Continents[i]);
	}
	
}

/*
	
    DESCRIPTION: Searches for the text file of the country 
	PARAMETERS: *param_input_filename - contains the file where input comes from
				*Countries - array containing list of countries from the input file
				*n_countries - counts how many countries are read
	RETURN TYPE: Return 1 if successful. 0 otherwise.
	
*/

int Open_File(char *param_input_filename, String *Countries, int *n_countries){
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
	
	// read and count all countries from COUNTRIES.txt
	while( (fscanf(fp_input_file, "%s", Countries[i])) == 1){
		// increment values
		i+=1;
		*n_countries+=1;
	}
	
	// close the input file
	fclose(fp_input_file);
	
	return 1;
}

/*
	
    DESCRIPTION: Scans data from CONTINENT-COUNTRY.txt to the file pointer
	PARAMETERS: *Stats_per_Country - struct array that will contain country statistics
				*all_countries - total number of countries (173)
	RETURN TYPE: Not applicable
	
*/

void Read_Continent_Country(Country_Stats *Stats_per_Country, int *all_countries){
	int i = 0;
	char directory[100];
	
	// declare file pointer for CONTINENT-COUNTRY.txt
	FILE *fp_continent_country;
	
	// open CONTINENT-COUNTRY.txt in READ mode
	strcpy(directory, "CHD/");
	strcat(directory, "CONTINENT-COUNTRY.txt");
	fp_continent_country = fopen(directory, "r");
	
	// read data from CONTINENT-COUNTRY.txt
	while( (fscanf(fp_continent_country, "%s %s", Stats_per_Country[i].Continent, Stats_per_Country[i].Country_Name)) == 2){
		i+=1;
		*all_countries+=1;
	}
	
	// close the file pointer
	fclose(fp_continent_country);
}

/*
	
    DESCRIPTION: Reads and transfers data to the members of Country_Placeholder struct array
	PARAMETERS: n_countries - total number of countries from the COUNTRIES.txt/COUNTRIES-47.txt
				*Countries - array containing all the countries
				*Country_Data_Holder - contains data after calling the Read_COVID_Data function
				*Country_Placeholder - placeholder to contain data
				*n_countries_placeholder - number of countries read
	RETURN TYPE: Returns the amount of data not read
	
*/

int Read_Data(int n_countries, String *Countries, Country_Stats *Country_Data_Holder, 
						Country_Stats *Country_Placeholder, int *n_countries_placeholder){
	int i, j = 0, result, no_data = 0;
							
	// read all data 
	for(i = 0; i < n_countries; i++){
		
		// call the Read_COVID_Data function
		result = Read_COVID_Data(Countries[i], Country_Data_Holder);
		
		// only count for the countries with their txt files
		if(result == 1){
			
			// set all structure array elements with the data found from Read_COVID_Data
			strcpy(Country_Placeholder[j].Country_Name, Country_Data_Holder->Country_Name);
			Country_Placeholder[j].Population = Country_Data_Holder->Population;
			Country_Placeholder[j].Total_Cases = Country_Data_Holder->Total_Cases;
			Country_Placeholder[j].Cases_Percent = Country_Data_Holder->Cases_Percent;
			Country_Placeholder[j].Total_Deaths = Country_Data_Holder->Total_Deaths;
			Country_Placeholder[j].Deaths_Percent = Country_Data_Holder->Deaths_Percent;
			
			// increment values
			j+=1;
			n_countries_placeholder += 1;
		}
		
		// failed 
		else{
			// count the times data failed to be read
			no_data += 1;
		}
	}
	
	// return the number of failed attempts
	return no_data;
}

/*
	
    DESCRIPTION: Set all members to 0 
	PARAMETERS: *Stats_per_Continent - struct array that will contain continent statistics
	RETURN TYPE: Not applicable
	
*/

void Initialize_Members(Country_Stats *Stats_per_Continent){
	int i;
	
	// initiliaze members to 0
	for(i = 0; i < NUM_CONTINENTS; i++){
		Stats_per_Continent[i].Cases_Percent = 0.00;
		Stats_per_Continent[i].Deaths_Percent = 0.00;
		Stats_per_Continent[i].Population = 0;
		Stats_per_Continent[i].Total_Cases = 0;
		Stats_per_Continent[i].Total_Deaths = 0;
	}
}

/*
	
    DESCRIPTION: Searches for the index of the corresponding country to find its continent
	PARAMETERS: *Stats_per_Continent - struct array that will contain continent statistics
				Country_Holder - holds the name of the country
				*Continents - array containing all the continents
				*Stats_per_Country - struct array that will contain country statistics
				all_countries - total countries (173)
	RETURN TYPE: Return the mid index. -1 otherwise.
	
*/

int Binary_Search(Country_Stats *Stats_per_Continent, String Country_Holder, String *Continents, 
						Country_Stats *Stats_per_Country, int all_countries){
				
	int mid, low = 0, high = all_countries - 1;
	int result;
	String placeholder1;
	
	// search from the whole list of CONTINENT-COUNTRY.txt
	while(low <= high){
		
		// calculate the midpoint
		mid = low + (high - low)/2;
		
		// copy the country name to placeholder1
		strcpy(placeholder1, Stats_per_Country[mid].Country_Name);
		
		// get the result
		result = strcmp(Country_Holder, placeholder1);
		
		// country found
		if(result == 0){
			return mid;
		}
		
		// placeholder2 is above placeholder1 EX: GERMANY > FRANCE
		else if(result > 0){
			low = mid + 1;
		}
		
		// placeholder2 is below placeholder1 EX: GERMANY < INDONESIA
		else{
			high = mid - 1;
		}
	}
	
	// failed
	return -1;
}

/*
	
    DESCRIPTION: Finds the continent of the country
	PARAMETERS: continent_index - index directing to the continent of a country
				*Stats_per_Continent - struct array that will contain continent statistics
				*Country_Placeholder - placeholder to contain data
				*Continents - array containing list of continents from the input file
				n_countries2 - number of countries read
				*Stats_per_Country - struct array that will contain country statistics
				i - counter to determine how many times Continent_Data is being called
	RETURN TYPE: Not applicable
	
*/

void Continent_Data(int continent_index, Country_Stats *Stats_per_Continent, Country_Stats *Country_Placeholder, String *Continents,
			int n_countries2, Country_Stats *Stats_per_Country, int i){
	int j, result;
	String Continent_Holder1;
	String Continent_Holder2;
	String Country_Holder;
	
	// place continent and country name to the placeholders
	strcpy(Continent_Holder1, Stats_per_Country[continent_index].Continent);
	strcpy(Country_Holder, Stats_per_Country[continent_index].Country_Name);
	
	// find matching continent
	for(j = 0; j < 6; j++){
		
		// copy the continent to the placeholder
		strcpy(Continent_Holder2, Stats_per_Continent[j].Continent);
		
		// compare and get the result
		result = strcmp(Continent_Holder1, Continent_Holder2);
		
		// in case the continents are the same
		if(result == 0){
			
			// compute for the sums
			Stats_per_Continent[j].Population = Stats_per_Continent[j].Population + Country_Placeholder[i].Population;
			Stats_per_Continent[j].Total_Cases = Stats_per_Continent[j].Total_Cases + Country_Placeholder[i].Total_Cases;
			Stats_per_Continent[j].Total_Deaths = Stats_per_Continent[j].Total_Deaths + Country_Placeholder[i].Total_Deaths;
		}
	}
}

/*
	
    DESCRIPTION: Computes for the percentage of the total cases and deaths
	PARAMETERS:  population_holder - holds the population of a country
				*Stats_per_Continent - struct array that will contain continent statistics
	RETURN TYPE: Not applicable
	
*/

void Percentage_Calc(double population_holder, Country_Stats *Stats_per_Continent){
	int i;
	
	// compute for the percentages
	for(i = 0; i < NUM_CONTINENTS; i++){
		// multiply by a floating-point 
		population_holder = (Stats_per_Continent[i].Population) * 1.00;
		
		// calculate the percentage
		Stats_per_Continent[i].Cases_Percent = (Stats_per_Continent[i].Total_Cases)/(population_holder) * 100;
		Stats_per_Continent[i].Deaths_Percent = (Stats_per_Continent[i].Total_Deaths)/(population_holder) * 100;
	}
}

/*
	
    DESCRIPTION: Writes data to the given output file
	PARAMETERS: *Stats_per_Continent - struct array that will contain continent statistics
				*param_output_filename - contains the file where data should be written
	RETURN TYPE: Not applicable
	
*/

void Output_Data2(Country_Stats *Stats_per_Continent, char *param_output_filename){
	int i;
	FILE *fp_output_file;
	
	// open output file in WRITE mode
	fp_output_file = fopen(param_output_filename, "w");
	
	// output to the output file pointer six times
	for(i = 0; i < NUM_CONTINENTS; i++){
		fprintf(fp_output_file, "%-16s %12lu %12d %12lf %12d %12lf\n", Stats_per_Continent[i].Continent, Stats_per_Continent[i].Population, 
		Stats_per_Continent[i].Total_Cases, Stats_per_Continent[i].Cases_Percent,
		Stats_per_Continent[i].Total_Deaths, Stats_per_Continent[i].Deaths_Percent);
	}
	
	// close the output file pointer
	fclose(fp_output_file);
}


/*
	TO DO: Implement Stats_C9().  Call the helper functions that you defined above.
	
    DESCRIPTION: Reads data from the input file and writes them on the output file
	PARAMETERS: *param_output_filename - contains C9-47-OUTPUT1.txt / C9-47-OUTPUT2.txt
				*param_input_filename - contains COUNTRIES.txt / COUNTRIES-47.txt
	RETURN TYPE: Return 1 if successful. 0 otherwise.
	
*/

int 
Stats_C9(char *param_output_filename, char *param_input_filename)
{
	/* Declare your own local variables. */
	/* Document your solution with sensible inline comments. */
	String Continents[NUM_CONTINENTS+1] = {"AFRICA", "ASIA", "EUROPE", "NORTH-AMERICA", "OCEANIA", "SOUTH-AMERICA"};
	String Countries[60];
	String Country_Holder;
	
	// le structures
	Country_Stats Stats_per_Country[175];
	Country_Stats Stats_per_Continent[7];
	Country_Stats Country_Data_Holder;
	Country_Stats *Country_Placeholder;
	
	// NOTE: all_countries counts countries from CONTINENT-COUNTRY.txt 
	//			while n_countries counts those from COUNTRIES.txt
	int i = 0, 
		all_countries = 0, 
		n_countries = 0, 
		n_countries2 = 0, 
		result, 
		continent_index, 
		no_data = 0;
	
	// copy continents to member continent of Stats_per_Continent array
	Copy_Continents(Stats_per_Continent, Continents);
	
	// call the function the open the input file
	result = Open_File(param_input_filename, Countries, &n_countries);
	
	// condition in case of failure to retrieve data
	if(result == 0){
		return 0;
	}
	
	// call function to read data from CONTINENT-COUNTRY.txt
	Read_Continent_Country(Stats_per_Country, &all_countries);
	
	// copy number of countries to the placeholder
	int n_countries_placeholder = n_countries;
	
	// allocate dynamic memory for Country_Placeholder
	Country_Placeholder = (Country_Stats*)malloc(n_countries_placeholder * (sizeof(Country_Stats)) );
	
	// read data from countries on the COUNTRIES.txt/COUNTRIES-47.txt
	no_data = Read_Data(n_countries, Countries, &Country_Data_Holder, Country_Placeholder, &n_countries_placeholder);
	
	// subtract the count of data not being read from the total countries listed 
	// to get the number of countries that have their txt files
	n_countries2 = n_countries - no_data;
	
	// initialize members function
	Initialize_Members(Stats_per_Continent);
	
	// perform binary search to categorize countries into respective continents
	for(i = 0; i < n_countries2; i++){
		
		// copy the country name to the placeholder
		strcpy(Country_Holder, Country_Placeholder[i].Country_Name);
		
		// call the binary search function to find the index
		continent_index = Binary_Search(Stats_per_Continent, Country_Holder, Continents, Stats_per_Country, all_countries);
		
		// call the function to find its continent and copy the data
		Continent_Data(continent_index, Stats_per_Continent, Country_Placeholder, Continents, n_countries2, Stats_per_Country, i);
	}
	
	// set to double for calculations
	double population_holder = 0.00;
	
	// calculate percentage
	Percentage_Calc(population_holder, Stats_per_Continent);
	
	// call the function only if the txt file for the country exists
	if(result != 0){
		// output data
		Output_Data2(Stats_per_Continent, param_output_filename);
	}

   return 1;  /* Don't forget the return statement. Replace 888 with the appropriate value. */  
}



/*******************************************************************************
    WARNING!!!   WARNING!!!   WARNING!!!    
	
	YOU ARE NOT ALLOWED TO DEFINE the main() function in this file.  
   
	VIOLATION OF THIS RESTRICTION WILL RESULT TO A DEDUCTION OF 10 points!		 
********************************************************************************/

