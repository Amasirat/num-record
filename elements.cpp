#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;		//std namespace is the only namespace used in the scope of this project
const char filename[] = "record.txt";		//global record name
//struct of type number containing three elements
struct number{
    int num;
    int prime;
    int perfect;
};
//print main menu
void menu()
{
	cout << "1.Check if a number is prime\n";
	cout << "2.Check if a number is perfect\n";
	cout << "3.Generate 10 random numbers\n";
	cout << "4.Clear screen\n";
	cout << "5.End program\n";
}
void clrscreen()
{
	#ifdef WINDOWS
		system("cls");
	#else
		system("clear");
	#endif
}
//initializing variable of type number to store user number and its status
number createNum()
{
    number usr_num;
    
    usr_num.num = -1;       //to reduce the possibility of compiler initilizing variable to zero 
    usr_num.prime = -1;     //Default unknown state
    usr_num.perfect = -1;   //Default unknown state

	return usr_num;
}
//get a natural number from user and return it
int getNum(string mode)
{
    int num;
	cout << mode << " Enter a natural number(0 to exit mode):\n";
    while(cin >> num && num < 0 || cin.fail())
    {
    	//ignore inputs that are not integers
    	cin.clear();    
    	cin.ignore();
        cout << "input is invalid, try again!\n";
    }
	return num;
}
//generates new record.txt
void genrecord(string name)
{
	fstream record(name, ios::out);
	record << 0 << '\t' << '\t' << 0 << '\t' << '\t' << 0;
	record.close();
}
//function for checking if a positive integer is a perfect number, returns 0 if false and 1 if true
int perfect(int x)
{
	if (x % 2 != 0)		//perfect numbers can not be odd so we get that out of the way first
		return 0;

	int sum = 1;	//1 will always be in the sum of all numbers' divisions
	for(int i = 2; i <= x/2;i++)
		if(x % i == 0)
			sum += i;

	if (sum == x)
		return 1;		//1 means perfect
	else 
		return 0;		//0 means not perfect
}
//function for checking if an integer is prime, returns 0 if false and 1 if true
int prime(int x)
{
int remainder{};
switch (x)		//to get the first three numbers out of the way because I start checking from 2
{
	case 1:
		return 0;
		break;
	case 2:
		return 1;
		break;
	case 3:
		return 1;
		break;
}
//for getting even numbers out of the way
if (x % 2 == 0)
	return 0;
for (int i = 2; i <= x/2; i++)
{
    remainder = x % i;
	if (remainder == 0)
		break;
}
if (remainder != 0)
	return 1;		//1 means prime
else
	return 0;		//0 means not prime
}
//checks if a number exists in record. 0 for (not in record) and 1 for (in record)
int numCheck(int num)
{
	number record_num;
	fstream record(filename, ios::in);
	if (!record)
		cout << "Error! Can not find record in directory";
	while(!record.eof())
	{
		record >> record_num.num >> record_num.prime >> record_num.perfect;
		if (record_num.num == num)
			break;
	}
	record.close();
	if (record_num.num != num)
		return 0;
	else
		return 1;
}
//read number and its status from file
number read_file(number num)
{
	fstream record(filename, ios::in);
	if (!record)
		cout << "Error! Record could not be found\n";
	while(!(record.eof()))
	{
		int record_num;
		record >> record_num >> num.prime >> num.perfect;
		if (record_num == num.num)
			break;
	}
	record.close();
	return num;
}
//add number and its status to file
void write_file(number usr_num , string name)
{
	fstream record(name, ios::app);
	if (!record)
		cout << "Error! could not open record\n";
	record << '\n' << usr_num.num << '\t' << '\t' << usr_num.prime << '\t' << '\t' << usr_num.perfect;
	record.close();
}
//find index of number with unknown perfect status
int find_index(number usr_num)
{
	number record_num;
	fstream record(filename, ios::in);
	if (!record)
		cout << "Error! Could not open record\n";
	int index = 1;
	while (!record.eof())
	{
		record >> record_num.num >> record_num.prime >> record_num.perfect;
		if (record_num.num == usr_num.num)
			break;
		index++;
	}
	record.close();
	return index;
}
//edit a number with unknown status
void edit_file(number usr_num)
{
	const char tempfilename[] = "temprecord.txt";
	number record_num;

	int index = find_index(usr_num);
	genrecord(tempfilename);
	fstream record(filename, ios::in);
	if (!record)
		cout << "Error! Could not open record\n";
		
	for (int i = 1;!record.eof();i++)
	{
		record >> record_num.num >> record_num.prime >> record_num.perfect;
		if (record_num.num == 0)
			continue;

		if (i == index)	
			write_file(usr_num, tempfilename);
		else
			write_file(record_num, tempfilename);
	}
	record.close();
	rename(tempfilename, filename);
}
//generates 10 random numbers and saves them in record with their prime and perfect status checked
void numGenerate()
{
	const int range = 1000;		//generated number can not exceed 999
	number num;
	srand((unsigned) time(NULL));

	for (int i = 1; i <= 10; i++)
	{
		num.num = rand() % range;
		while (numCheck(num.num) == 1)		//to make sure that random number does not already exist in record
			num.num = rand() % range;
		num.prime = prime(num.num);
		num.perfect = perfect(num.num);
		write_file(num,filename);
	}
}