#include<iostream>
#include<fstream>
#include"climate.h"
#include<iomanip>
#include<Windows.h>
#include<iomanip>

using namespace std;


climate::climate(void):years(MAXROWS), months(MAXCOLS)
{
	matrix = new float*[years];
		for(int i = 0; i<years; i++){
			matrix[i]=new float[months];
			}
	
		for(int i = 0; i<years; i++){
			for(int j = 0; j<months; j++){
				matrix[i][j] = 0;
			}
		}
		


}

//constructor with parameters
climate::climate(int y, int m)
{
	years = y;
	months = m;
	
	//dynamically allocates 2d matrix years by months
	matrix = new float*[years];
		for(int i = 0; i<years; i++)
			matrix[i] = new float [months];
		
		
	 
	ifstream infile;
	infile.open("C:\\Users\\won\\Documents\\climatetext.txt");
		if(!infile){
			cout<<"Can't locate your file! "<<endl;
			exit (1);
		}
		else {
			cout<<"The file is located! "<<endl;
			cout<<endl;
		 }
	
 //
	while(!infile.eof()){
	    for(int i = 0; i<years; i++){
			for(int j=0; j<months; j++){
				infile >> matrix[i][j];
			}
		}
	} 
	infile.close();


/*	//prints out matrix 
	for(int i = 0; i<years; i++){
		for(int j = 0; j<months; j++){
			cout<<setprecision(1)<<fixed<<left<<matrix[i][j]<<"  ";
		}
		cout<<endl;
	}
*/	
	menu();

	system("pause"); 


}
		

	


//copy constructor
climate::climate(const climate&  otherObject){
	years = otherObject.years;
	months = otherObject.months;

	matrix = new float *[years];
	for(int i = 0; i<years; i++)
		matrix[i] = new float [months];

	
	for(int row = 0; row<years; row++){
		for(int col = 0; col<months; col++){
			matrix[row][col] = otherObject.matrix[row][col];
		}
	}

	


}


climate::~climate(){
	for(int i = 0; i<years;i++){
		delete [] matrix[i];
	}
	delete [] matrix;
}

void climate::menu(){
	cout<<"Welcome \n\n"<<"Look at the list and choose an option number \n"
		<<"Then press enter.\n\n"
		<<"-1- Find the AVERAGE month temperature for a given year \n"
		<<"-2- Find the LOWEST average month temperature for a given year \n"
		<<"-3- Find the HIGHEST average month temperature for a given year\n"
		<<"-4- Find the TOTAL average temperature for a certain given year \n\n"
		<<" PRESS 0 TO QUIT! "
		<<"\nNow enter a number choice below \n";
	int choice;
	cin>>choice;

	switch(choice){

		case 0:
			{
			cout<<"goodbye!"<<endl;
			Sleep(1000);
			exit(1);
		}
		case 1://avg month temp for given year
			{
			cout<<"\nPlease enter which year you would like to see. \n";
			int yr;
			cin>>yr;

			if((yr<1869)||(yr>2012)){
				cout<<"\nYour out of bounds.  Start over and pick a year between 1869 and 2012.\n "<<endl;
				cout<<"\n\n\n\n\n\n\n\n";
				menu();
				break;
			}
			
			cout<<"\nNow enter the month. \n";
			int m;
			cin>>m;
			cout<<endl;

			if((m<1)||(m>12)){
				cout<<"\nYour out of bounds.  Start over and pick a month between 1 and 12.\n "<<endl;
				cout<<"\n\n\n\n\n\n\n\n";
				menu();
				break;
			}

			avgTemp(yr, m);
			break;
		}

		case 2://lowest avg month temp for a given yr
			{
			cout<<"\nPlease enter which year you would like to see. \n";
			int yr;
			cin>>yr;
			
			if((yr<1869)||(yr>2012)){
				cout<<"\nYour out of bounds.  Start over and pick a year between 1869 and 2012.\n "<<endl;
				cout<<"\n\n\n\n\n\n\n\n";
				menu();
				break;
			}
			
			lowAvgTemp(yr);

			break;
		}
		
		case 3://highest avg month temp for a given yr
			{
			cout<<"\nPlease enter which year you would like to see. \n";
			int yr;
			cin>>yr;

			if((yr<1869)||(yr>2012)){
				cout<<"\nYour out of bounds.  Start over and pick a year between 1869 and 2012.\n "<<endl;
				cout<<"\n\n\n\n\n\n\n\n";
				menu();
				break;
			}

			cout<<endl;

			highAvgTemp(yr);
			break;
		}

		case 4://total monthly avg for a given year
			{
			cout<<"\nPlease enter the year you would like to see the total average of\n"
				<<"monthly temperatures. \n";
			int yr;
			cin>>yr;
			if((yr<1869)||(yr>2012)){
				cout<<"\nYour out of bounds.  Start over and pick a year between 1869 and 2012.\n "<<endl;
				cout<<"\n\n\n\n\n\n\n\n";
				menu();
				break;
			}

			avgTempYear(yr);
				break;
			}

		
		
	}

}
//gets and changes yr, month to get the correct coordinates for 2d array answer
float climate::getAns(int year, int month){
	
	year=year-1869;
	--month;
	//month = month -1;
	ans = matrix[year][month];
	return ans;
}

//avg temp for month for a given year
void climate::avgTemp(int year, int month){
	
	getAns(year, month);
	
	cout<<"\nThe average temperature for month "<<month<<"\nOf the year "<<year
		<<" is: "<<setprecision(1)<<fixed<<ans<<" degrees\n\n\n";
}


void climate::lowAvgTemp(int year){
	
	year=year-1869;
	float SMALLEST=200;
	float ans;
	int j;

	for(j=0;j<12;j++){
		if(matrix[year][j]<SMALLEST)
			SMALLEST=matrix[year][j];
	}

	ans = SMALLEST;
	
	year=year+1869;
	cout<<"\nThe lowest average temperature for the year "<<year
		<<" is: "<<setprecision(1)<<fixed<<ans<<" degrees\n\n\n";
	
}


void climate::highAvgTemp(int year){
	year = year-1869;
	float LARGEST=0;

	int j;

	for(j=0;j<12;j++){
		if(matrix[year][j]>LARGEST)
		LARGEST=matrix[year][j];
	}
	ans = LARGEST;

	year = year+1869;
	cout<<"\nThe highest average temperature for the year "<<year
		<<" is: "<<setprecision(1)<<fixed<<ans<<" degrees\n\n\n";

}


void climate::avgTempYear(int year){

	float SUM = 0;
	float avg;
	int j;
	year=year-1869;

	for(j=0; j<12; j++){
		matrix[year][j];
		SUM = SUM + matrix[year][j];
		
	}
	
	
	avg = SUM/12;
	
	year = year+1869;
	cout<<"\nThe Average total temperature for the year "<<year
		<<" is: "<<setprecision(1)<<fixed<<avg<<" degrees\n\n\n";

}

