#include <iostream>
#include <fstream>
using namespace std;
//function for checking if a positive integer is a perfect number, returns 0 if false and 1 if true
int perfect(int x)
{
	int sum = 1;
	if (x % 2 != 0)
		return 0;
	for(int i = 2; i <= x/2;i++)
		if(x % i == 0)
			sum += i;
	if (sum == x)
		return 1;
	else 
		return 0;
}
//function for checking if an integer is prime, returns 0 if false and 1 if true
int prime(int x)
{
int remainder{0};
switch (x)
{
	case 0:
		return 0;
		break;
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
if (x % 2 == 0)
	return 0;
for (int i = 2; i <= x/2; i++)
{
    remainder = x % i;
	if (remainder == 0)
		break;
}
if (remainder != 0)
	return 1;
else
	return 0;
}
//add number and its prime status to file
void write_primefile(int num, int p, int perfect)
{
	perfect = -1;
	fstream record("record.txt", ios::app);
	record << num << '\t' << '\t' << p << '\t' << '\t' << perfect << '\n';
	record.close();
}
//read number and its prime status from file
//this function is broken
int read_primefile(int n)
{
	int prime_status;
	int perfect_status;
	fstream record("record.txt", ios::in);
	if (!record)
		cout << "Error! Record could not be found\n";
	while(!(record.eof()))
	{
		int record_num;
		record >> record_num >> prime_status >> perfect_status;
		if (record_num == n){
			break;
		}
		else
			prime_status = -2;
	}
	record.close();
	return prime_status;
}
//generates new record.txt
void genrecord()
{
	fstream record("record.txt", ios::out);
	record << 0 << '\t' << '\t' << 0 << '\t' << '\t' << 0 << '\n';
	record.close();
}
//get a natural number from user and return it
int getNum()
{
    int usr_num;
	cout << "Enter a natural number:\n";
    while(cin >> usr_num && usr_num <= 0 || cin.fail())
    {
    	//ignore inputs that are not integers
    	cin.clear();    
    	cin.ignore();
        cout << "input is invalid, try again!\n";
    }
	return usr_num;
}
//checks if a number exists in record. 0 for (not in record) and 1 for (in record)
int numCheck(int num)
{
	int record_num;
	int prime_status;
	int perfect_status;
	fstream record("record.txt", ios::in);
	if (!record)
		cout << "Error! Can not find record in directory";
	while(!record.eof())
	{
		record >> record_num >> prime_status >> perfect_status;
		if (record_num == num)
			break;
	}
	record.close();
	if (record_num != num)
		return 0;
	else
		return 1;
}
//generates 10 random numbers and saves them in record with their prime and perfect status checked
void numGenerate()
{
	const int range = 1000;
	int num{};
	srand((unsigned) time(NULL));
	fstream record("record.txt", ios::app);

	if (!record)
	{
		cout << "Error! Couldn't find file in directory";
	}

	for (int i = 1; i <= 10; i++)
	{
		num = rand() % range;
		while (numCheck(num) == 1)
			num = rand() % range;
		record << num << '\t' << '\t' << prime(num) << '\t' << '\t' << perfect(num) << '\n';
	}
	record.close();
	//possible bug: generating numbers that exist
}
//print main menu
void menu()
{
cout << "1.Check if a number is prime\n";
cout << "2.Check if a number is perfect\n";
cout << "3.Generate 10 random numbers\n";
cout << "4.Clear screen\n";
cout << "5.End program\n";
}