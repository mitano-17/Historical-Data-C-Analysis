/*
    LASTNAME1, FIRSTNAME1:  ERMITANO, KATE JUSTINE	SECTION1:  S14
    
	LASTNAME2, FIRSTNAME2:  KAWACHI, HIDEKI   		SECTION2:  S13 

	DATE SUBMITTED: 23/05/2021
	
	Do not forget to ENCODE your name/s, section/s and date on the space indicated above.
		
	CCPROG2 MP Solution for: Challenge #6 
*/


/*
	Do NOT edit/remove the lines of codes containing #ifndef  #endif pair, and #define C6 (1).

*/
#ifndef C6

	#define C6 (1)
   
   	/*
   		TO DO: change the string "88" in Line 27 to your own MP group number enclosed in a pair of double quotes. For single 
		   	   digit group number, encode it with a leading 0.  For example, if your are group number 8, then Line 27
   			   should become #define GROUP_NUMBER "08".
   	*/
   	#define GROUP_NUMBER  "47"


	/* 
		You may use the NUM_COUNTRIES and NUM_CONTINENTS in your solution.
	*/	
	
	// There are 173 countries/locations with corresponding COVID data text file in CHD folder
	#define NUM_COUNTRIES  (173)
		  
	// There are 6 continents considered in this MP, namely: ASIA, AFRICA, EUROPE, NORTH-AMERICA, SOUTH-AMERICA, OCEANIA	
	#define NUM_CONTINENTS  (6)
  
   
	/*
		You may add your own macro definitions right after this comment.
	*/




	/*
		You are REQUIRED to use the StrDate alias as data type for an entity to be used for storing
		date as a string, ex.  "2021-03-21" (string length of 10).
	*/
	typedef char StrDate[11];  


	/*
		You may add your own typedef for OTHER  string aliases right after this comment.	
	*/
	typedef char String[50];


	/*
		Add codes from your C2-NUMBER.h header file right after this comment.  Note that you may still 
		edit/change the copied contents as you deem fit for your solutions to Challenges C7 to C9. 
	*/

	#define MAXIMUM 500
	
	struct Daily_COVID_Data_Structure{
		
		// char Date[11];
		StrDate Date; // member for dates
		int New_Cases; // member for daily new cases
		int New_Deaths; // member for daily deaths
		
	};
	
	// new data type name will be Daily_data
	typedef struct Daily_COVID_Data_Structure Daily_Data;
	
	struct Statistics{
		
		char Country_Name[40]; //member that holds the country's name
		unsigned long Population; //member for the overall population of a country
		float Life_Expectancy; //member for life expectancy 
		Daily_Data Country_Daily_Data[MAXIMUM]; //member holding a structure consisting of daily COVID-19 data
		int Number_of_Daily_Data; //member of total data
		int Total_Cases; // member that holds the total number of cases (for convenience)
		int Total_Deaths; // member that holds the total number of deaths (for convenience)
		double Cases_Percent; // member that holds the ratio of total cases to population (for convenience)
		double Deaths_Percent; // member that holds the ratio of total deaths to population (for convenience)
		char Continent[10]; // member that holds the continent the country is in (for convenience)
		
	};
	
	// new data type name will be Country_Stats
	typedef struct Statistics Country_Stats;

	/*
		You may add other structure data type declarations and optionally their corresponding 
		typedef declarations (aliases) right after this comment.		
	*/	

	
	/*
		TO DO: add the function prototypes for all functions that you defined in order accomplish to Challenges C7 to C9.
	*/
	
	/* C7 FUNCTION PROTOTYPES ------------------------------------- */
	int Read_COVID_Data(char* param_country, Country_Stats* ptrData);
	
	
	/* C8 FUNCTION PROTOTYPES ------------------------------------- */
	int Read_Countries(char *param_input_filename, String *Countries, int *all_countries);
	
	int Transfer_Data(Country_Stats *Stats_per_Country, Country_Stats *Country_Data_Holder, int j);
	
	void Swap(Country_Stats *country1, Country_Stats *country2);
	
	void Selection_Sort(Country_Stats Stats_per_Country[], int n_countries);
	
	void Output_Data(Country_Stats Stats_per_Country[], int n_countries, char *param_output_filename);
	
	int Stats_C8(char* param_output_filename, char* param_input_filename);
	
	
	/* C9 FUNCTION PROTOTYPES ------------------------------------- */
	void Copy_Continents(Country_Stats *Stats_per_Continent, String *Continents);
	
	int Open_File(char *param_input_filename, String *Countries, int *n_countries);
	
	void Read_Continent_Country(Country_Stats *Stats_per_Country, int *all_countries);
	
	int Read_Data(int n_countries, String *Countries, Country_Stats *Country_Data_Holder, 
						Country_Stats *Country_Placeholder, int *n_countries_placeholder);
						
	void Initialize_Members(Country_Stats *Stats_per_Continent);
	
	int Binary_Search(Country_Stats *Stats_per_Continent, String Country_Holder, String *Continents, 
						Country_Stats *Stats_per_Country, int all_countries);
						
	void Continent_Data(int continent_index, Country_Stats *Stats_per_Continent, Country_Stats *Country_Placeholder, 
						String *Continents, int n_countries2, Country_Stats *Stats_per_Country, int i);
	
	void Percentage_Calc(double population_holder, Country_Stats *Stats_per_Continent);
	
	void Output_Data2(Country_Stats *Stats_per_Continent, char *param_output_filename);
						
	int Stats_C9(char* param_output_filename, char* param_input_filename);


#endif

/*--- THE END ---*/



