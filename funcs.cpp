#include <iostream>
#include <fstream>
using namespace std;
//function for checking if a positive integer is a perfect number, returns 0 if false and 1 if true
int perfect(int x)
{
	int sum = 1;
	if (x % 2 != 0)
	{
		return 0;
	}
	for(int i = 2; i <= x/2;i++)
	{
		if(x % i == 0)
		{
			sum += i;
		}
	}
	if (sum == x)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
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
{
	return 1;
}
else
{
	return 0;
}

}
//add number and its prime status to file
void prime_file(int num, int p)
{
	fstream record("record.txt", ios::app);
	record << num << '\t' << '\t' << p << '\t' << '\t' << -1 << '\n';
	record.close();
}
//generates new record.txt
void genrecord()
{
	fstream record("record.txt", ios::out);
	record << "num" << '\t' << '\t' << "pr" << '\t' << '\t' << "per" << '\n';
	record.close();
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
