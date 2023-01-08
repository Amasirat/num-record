#include <iostream>
#include "funcs.cpp"
#include <string>
using namespace std;

int main()
{
    bool end = false;
    int mode_program;
    int prime_status;
    int perfect_status;


    ifstream file("record.txt");
    if (!file)
        genrecord();        //generates a record text file at the start of program(funcs.cpp)
    
    while (end == false)
    {
        menu();//prints out menu(funcs.cpp)
        cin >> mode_program;
        switch (mode_program)
        {
            case 1:
            {
                string num_state;
                int usr_num;
                usr_num = getNum();
                if (numCheck(usr_num) == 1)
                {
                    prime_status = read_primefile(usr_num);
                    num_state = "read from record";
                }
              else
                {
                    prime_status = prime(usr_num);//stores values 0(for not prime) and 1(for prime)
                    perfect_status = -1;
                    write_primefile(usr_num, prime_status, perfect_status);
                    num_state = "saved in record";
                }
                
                if (prime_status == 1)
                    cout << "Number is prime(" << num_state << ")\n";
                else   
                    cout << "Number is not prime(" << num_state << ")\n";
                break;
            }
            case 2:
            {
                string num_state;
                int usr_num;
                usr_num = getNum();

                break;
            }
            case 3:
                numGenerate();
                cout << "Generated 10 numbers and added them to record\n";
                break;
            case 4:
                system("clear");    //clearing the screen for linux and mac terminals
                //system("cls")     //clearing the screen of the windows console
                break;
            case 5:
                end = true;
                break;
            default:
            //for ignoring invalid flag for cin due to possible data type error created by the user
                cin.clear();
                cin.ignore();                
                cout << "Your entry is unsupported\n";
        }
    }
    return 0;
}

