#include <iostream>
#include <fstream>
using namespace std;
string filename = "record.txt";
//struct of type number containing three elements
struct number{
    int num;
    int prime;
    int perfect;
};
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
int remainder{};
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
//initializing variable of type number to store user number and its status
number createNum()
{
    number usr_num;
    //an effort to reduce the possibility of compiler initilizing variable to zero
    usr_num.num = -1;  

    usr_num.prime = -1;     //Default unknown state
    usr_num.perfect = -1;   //Default unknown state

	return usr_num;
}
//add number and its prime status to file
void write_file(number usr_num , string name)
{
	fstream record(name, ios::app);
	record << '\n' << usr_num.num << '\t' << '\t' << usr_num.prime << '\t' << '\t' << usr_num.perfect;
	record.close();
}
//read number and its prime status from file
number read_file(number num)
{
	fstream record("record.txt", ios::in);
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
//checks if a number exists in record. 0 for (not in record) and 1 for (in record)
int numCheck(int num)
{
	number record_num;
	fstream record(filename, ios::in);
	//if (!record)
	//	cout << "Error! Can not find record in directory"; //needs a better way of handling this possibility
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
//generates 10 random numbers and saves them in record with their prime and perfect status checked
void numGenerate()
{
	const int range = 1000;
	number num;
	srand((unsigned) time(NULL));
	fstream record(filename, ios::app);

	if (!record)
		cout << "Error! Couldn't find file in directory";
	for (int i = 1; i <= 10; i++)
	{
		num.num = rand() % range;
		while (numCheck(num.num) == 1)		//to make sure that random number does not already exist in record
			num.num = rand() % range;
		num.prime = prime(num.num);
		num.perfect = perfect(num.num);
		write_file(num,"record.txt");
	}
	record.close();
}
int find_index(number usr_num)
{
	number record_num;
	fstream record("record.txt", ios::in);
	int index = 1;
	while (!record.eof())
	{
		record >> record_num.num >> record_num.prime >> record_num.perfect;
		if (record_num.num == usr_num.num && record_num.prime || record_num.perfect == -1)
			break;
		index++;
	}
	record.close();
	return index;
}
void edit_file(number usr_num)
{
	number record_num;
	string checker;
	int index = find_index(usr_num);
	genrecord("temprecord.txt");
	fstream record("record.txt", ios::in);
	fstream newrecord("temprecord.txt",ios::app);
	for (int i = 1;!record.eof();i++)
	{
		record >> record_num.num >> record_num.prime >> record_num.perfect;
		if (record_num.num == 0)
			continue;
		cout << record_num.num << '\n';

		if (i == index)	
			write_file(usr_num, "temprecord.txt");
		else
			write_file(record_num, "temprecord.txt");
	}
	record.close();
	newrecord.close();
	rename("temprecord.txt", "record.txt");
}
//get a natural number from user and return it
int getNum()
{
    int num;
	cout << "Enter a natural number(0 to exit mode):\n";
    while(cin >> num && num < 0 || cin.fail())
    {
    	//ignore inputs that are not integers
    	cin.clear();    
    	cin.ignore();
        cout << "input is invalid, try again!\n";
    }
	return num;
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