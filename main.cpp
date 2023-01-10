#include "elements.cpp"
//this program currently cannot read a number that was already evaluated for another status before
int main()
{
    bool end = false;     //a flag to determine the end of the program used in a while loop
    int mode_program;
    string num_state;     //to determine if number was read from file or written on file
    string filename = "record.txt";

    ifstream file(filename);
    if (!file)
        genrecord(filename);        //generates a record text file at the start of program(funcs.cpp)
    
    while (end == false)
    {
        menu();//prints out menu(funcs.cpp)
        cin >> mode_program;
        switch (mode_program)
        {
            case 1:
            {  
                number usr_num = createNum();   //for storing user number and its status
                while (usr_num.num != 0){
                usr_num.num = getNum();//to get user number and store it in num element of the number struct

                if (usr_num.num == 0)
                    continue;
                if (numCheck(usr_num.num) == 1)
                {
                    usr_num.prime = read_file(usr_num).prime;
                    if (usr_num.prime == -1)
                    {
                        usr_num.prime = prime(usr_num.num);
                        usr_num.perfect = read_file(usr_num).perfect;
                        edit_file(usr_num);
                        num_state = "edited record";
                    }
                    else
                        num_state = "read from record";
                }
              else
                {
                    usr_num.prime = prime(usr_num.num);//stores values 0(for not prime) and 1(for prime)
                    write_file(usr_num, filename);
                    num_state = "saved in record";
                }
                //showing the number's status to user
                if (usr_num.prime == 1)
                    cout << "Number is prime(" << num_state << ")\n";
                else   
                    cout << "Number is not prime(" << num_state << ")\n";
                }
                break;
            }
            case 2:
            {
                number usr_num = createNum();   //for storing user number and its status

                while (usr_num.num != 0){

                    usr_num.num = getNum();

                    if (usr_num.num == 0)
                    continue;

                    if (numCheck(usr_num.num) == 1)
                    {
                        usr_num.perfect = read_file(usr_num).perfect;
                        num_state = "read from record";
                    }
                    else
                    {
                        usr_num.perfect = perfect(usr_num.num);
                        write_file(usr_num, filename);
                        num_state = "saved in record";
                    }
                    if (usr_num.perfect == 1)
                        cout << "Number is perfect(" << num_state << ")\n";
                    else   
                        cout << "Number is not perfect(" << num_state << ")\n";
                }
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