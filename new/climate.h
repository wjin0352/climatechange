#pragma once
#include<fstream>

using namespace std;


class climate{

public:

	static const int MAXROWS = 3;
	static const int MAXCOLS = 3;
	
	void menu();
	void highAvgTemp(int);
	void avgTemp(int,int);
	void lowAvgTemp(int);
	void avgTempYear(int);
	float getAns(int, int);


	climate(void); 
	climate(int, int);
	climate(const climate& otherObject);
	~climate();
private:
	int months;
	int years;
	float **matrix;
	float ans;
};