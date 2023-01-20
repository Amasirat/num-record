#include "elements.cpp"
int main()
{
    bool end = false;     //a flag to determine the end of the program used in a while loop condition
    int mode_program;     //determine mode of the program, checking prime or perfect numbers mode or else
    string num_state;     //to determine if number was read from file or written on file

    ifstream file(filename);
    if (!file)
        genrecord(filename);        //generates a record text file at the start of program(funcs.cpp)
    
    while (end == false)
    {
        menu();       //prints out menu
        cin >> mode_program;
        switch (mode_program)
        {
            case 1:
            {
                clrscreen();  
                int ender{1};
                while (ender != 0){
                number usr_num = createNum();   //initializing a var for storing user's number
                usr_num.num = getNum("Prime mode)");     //get number and store it in num element of the number struct

                if (usr_num.num == 0)       //give user the ability to quit modes
                {  
                    ender = usr_num.num;
                    continue;
                }       
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
                clrscreen();
                int ender{1};       //used as condition checker for the while loop
                while (ender != 0){
                    number usr_num = createNum();   //initializing var for user number and its status
                    usr_num.num = getNum("Perfect mode)");         //obtain user number

                    if (usr_num.num == 0)
                    {
                        ender = usr_num.num;    //for ending the while loop
                        continue;
                    }

                if (numCheck(usr_num.num) == 1)
                {
                    usr_num.perfect = read_file(usr_num).perfect;
                    if (usr_num.perfect == -1)
                    {
                        usr_num.perfect = perfect(usr_num.num);
                        usr_num.prime = read_file(usr_num).prime;

                        edit_file(usr_num);
                        num_state = "edited record";
                    }
                    else
                        num_state = "read from record";
                }
              else
                {
                    usr_num.perfect = perfect(usr_num.num);//stores values 0(for not prime) and 1(for prime)
                    write_file(usr_num, filename);
                    num_state = "saved in record";
                }
                //showing the number's status to user
                if (usr_num.perfect == 1)
                    cout << "Number is perfect(" << num_state << ")\n";
                else   
                    cout << "Number is not perfect(" << num_state << ")\n";
                }
                break;
            }
            case 3:
                clrscreen();
                numGenerate();
                cout << "Generated 10 numbers and added them to record\n";
                break;
            case 4:
                clrscreen();
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