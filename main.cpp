#include <iostream>
#include "funcs.cpp"
using namespace std;

int main()
{
    bool end = false;
    int mode_program;
    int prime_status;
    ifstream file("record.txt");
    if (!file)
        genrecord();        //generates a record text file at the start of program(funcs.cpp)
    
    while (end == false)
    {
        menu();             //prints out menu(funcs.cpp)
        cin >> mode_program;
        switch (mode_program)
        {
            case 1:
                int usr_num;
                cout << "Enter a natural number:\n";
                while(cin >> usr_num && usr_num < 0 || cin.fail())
                {
                    //ignore inputs that are not integers
                    cin.clear();    
                    cin.ignore();
                    cout << "input is invalid, try again!\n";
                }
                prime_status = prime(usr_num);      //stores values 0(for not prime) and 1(for prime)
                prime_file(usr_num, prime_status);
                  
                if (prime_status == 1)
                    cout << "Number is prime(saved in record)\n";
                else   
                    cout << "Number is not prime(saved in record)\n";
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                system("clear");    //clearing the screen for linux and mac terminals
                //system("cls")     //clearing the screen of the windows console
                break;
            case 5:
                end = true;
                break;
            default:
                //for ignoring invalid flag for cin due to possible data type inconsistency created by the user
                cin.clear();
                cin.ignore();                
                cout << "Your entry is unsupported\n";
        }
    }
}

