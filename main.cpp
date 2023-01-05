#include <iostream>
#include "funcs.cpp"
using namespace std;
void menu();

int main()
{
    bool end = false;
    int mode_program{};
    while (end == false)
    {
        menu();
        cin >> mode_program;
        switch (mode_program)
        {
            case 1:
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

