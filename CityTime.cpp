#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>      /* puts, printf */
#include <time.h>       /* time_t, struct tm, time, gmtime */
#include <cstdlib>
#include <cstring>

using namespace std;

// Author: Sarabjit Bakshi
// Date:   10/6/2016
// Purpose: I've created a small program that displays the time in 30 different cities.
//			I used the abstract idea of a city and continent to implement the program.

// The README.TXT explains how to compile and run the code on a linux x86_64 system


/*********************  structs & classes *******************************/

// the city struct: each city has a name, and an hour and minute offset from UTC
struct city{
	string name;
	int houroffset;   // houroffset could be negative, positive, or 0
	int minuteoffset; // minuteoffset >=0 .. so -7.5 hour offset---> houroffset= -7, minuteoffset= 30
};


// the continent class: each continent has a name, a certain # of cities whose time I've made available
// for viewing, and each continent actually contains those cities and their information.
class continent{
	
public:
	string name;	// each continent has a name
	city citiesd[6]; //-> each continent has cities; and each city has a name, hour, and minute offset
	int numbercities; // each continent only has a couple available cities that I've entered

	// constructor: Instantiate the continent, fill the 3 fields above ^
	continent(string n, city ccc[6], int nc)
	{
		name=n; // get the name of the continent
		int i=0;
		while(i<6) // transfer all 6 of the potential cities and their data for the continent
		{
			citiesd[i]=ccc[i];
			i++;
		}
		numbercities=nc; // get the number of cities that are availble for the continent
	}
 };
////////////////////////////// end structs & classes //////////////////////////////////////////////



/////////////////////// global variables //////////////////////////////////////

/* here I initialize a list of cities that are located within each continent */
// what I did here was find cities in each continent, then found their hour and 
// minute offset from UTC, and stored them all in the city struct. ie. Nairobi in Africa has offset=+3 hours from UTC
//	* for synchronicity I've made all of the arrays of cities size 6 *
city AfricaCities[6]={{"Nairobi",3,0},{"Lagos",+1,0},{"Accra",0,0},{"Luanda",+1,0},{},{}};
city AntarcCities[6]={{"Davis Station",7,0},{"Esperanza Base",-3,0},{},{},{},{}};
city AsiaCities[6]={{"Bangkok",7,0},{"Tokyo",9,0},{"Mumbai",5,30}, {"New Dehli",5,30},{"Dhaka",6,0},{}};
city AustrCities[6]={{"Sydney",11,0},{"Perth",8,0},{"Darwin",9,30},{},{},{}};
city EuropeCities[6]={{"London",1,0},{"Prague",2,0},{"Rome",2,0},{"Budapest",2,0},{"Madrid",2,0},{}};
city NAmericaCities[6]={{"Toronto, Canada",-4,0},{"San Diego, CA",-7,0},{"Olney, MD",-4,0},{"Boston, MA",-4,0},
								{"New York City, NY",-4,0},{"Houston, TX",-5,0}};
city SAmericaCities[6]={{"Buenos Aires",-3,0},{"Santiago",-3,0},{"Lima",-5,0},{"Quito",-5,0},{"Cusco",-5,0},{}};

// global continent array, containing pointers to continents
continent* Continents[7];
////////////////////  end global variable declarations /////////////////////////



///////////////////// function declarations ////////////////////////////////////

void displaytime(int choice, int citychoice);

void DisplayAllTimes();

void createcontinents();
//////////////////// end function declarations ///////////////////////




// main: topmost function, instantiates continents and makes the call to display all times
// inputs: user input
// outputs: 0
int main ()
{
	cout << "Time Around The World" << endl;

	createcontinents(); // this fills my global array: Continents[7], which holds pointers to continents

	DisplayAllTimes(); // this function iterates through the continents, and displays
						// the time in each city that I've implemented into the program
	return 0;
}




// this function instantiates each of the 7 continents, alphabetically
//	inputs: -the empty global continent array, Continents[7]
//			-the global list of cities I created for each continent, AfricaCities, AntarcCities...
//  outputs: a filled array of continents, stored alphabetically in Continents[7]
void createcontinents()
{
	// fill each spot with a continent, the list of cities I've stored for that continent, and
	// the number of cities i've stored for that continent
	Continents[0] = new continent("Africa", AfricaCities , 4);
	Continents[1]  = new continent("Antarctica", AntarcCities,2);
	Continents[2]  = new continent("Asia", AsiaCities , 5);
	Continents[3]   = new continent("Australia", AustrCities, 3);
	Continents[4]   = new continent("Europe", EuropeCities, 5);
	Continents[5] = new continent("North America", NAmericaCities, 6);
	Continents[6]  = new continent("South America", SAmericaCities,5);
}



// this function displays the time of all of the cities, continent by continent.
// This function calls to displaytime function to actually display the times
// inputs: the global var, Continents[7], the array of continents
// outputs: The time in all 30 cities
void DisplayAllTimes()
{
	cout << endl;
	int i=0;
	// iterate through the continents
	while( i < 7)
	{
		int j=0;
		// iterate through the cities of the continent, display the time there
		while(j < Continents[i]->numbercities)
		{
			displaytime(i,j); // displaytime takes in the choices for cont. and city, and displays the time the
			j++;	// next city
		}

		i++; // next continent
	}
}


//  this function takes in the continent# and city #, gets the time offset of the city, adds it 
// with the time obtained from the system
// inputs: the global array of continents, Continents[7]
//	outputs: the time in the desired city is displayed to console
void displaytime(int cont, int city)
{
	time_t rawtime;
  struct tm * ptm;
  
	// grab the time from the system
  time ( &rawtime );
  ptm = gmtime ( &rawtime );

  // grab the offsets from my structs
  int houroffset = Continents[cont]->citiesd[city].houroffset;
  int minuteoffset= Continents[cont]->citiesd[city].minuteoffset;

 string AMPM="AM"; // init to AM

// calculate the minute, might roll over to hour
 int hr=0;
 int min = (ptm->tm_min) + minuteoffset;

 if(min>=60)
 {
	 hr=1;
	 min=min-60;
 }

 //  get current hour from ptm struct, add cities houroffset, as well as possible rollover from minute offset
 hr = hr + ptm->tm_hour + houroffset;
 
 // hr can be a value from -7 to 34. as largest offset is +11 hours, 
 // smallest offset is -7 hours, and ptm->hour ranges from 0 to 23.

 if(hr < 1) // if hr is negative..
 {
	 hr = hr + 12; // go backward toward the end of last day ( -1 + 24 = 23 ) .. but bring down to 1-12 scale
	 // so is PM
	 AMPM = "PM";
 }
 else if(hr>24) // else if hr is past 24, is the next morning(25->1am).restart the clock(AM).
 {
		hr = hr - 24; // roll over to start of new day..
		// is AM
 }
 else if(hr==24)
 {
	 hr=hr-12; // 24->0 is the exception.. 24 actually becomes 12. unlike 25->1
	// is AM
 }
 else if(hr>=12) // else if hour>=12, it must be PM by process of elimination
 {
		if(hr!=12)
		{
			hr = hr - 12; // bring back down to 1-12 scale
		}
		AMPM = "PM";
 }
 // else 1<=hr<=11.. and its AM


 // now display what we've obtained
   cout << "The current time in " << Continents[cont]->citiesd[city].name << " is: " ;
   cout << hr<< ":";
   printf("%02d ",min); // display minute as 2 digit number
   cout <<AMPM << endl;
}



