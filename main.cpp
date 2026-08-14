#include <string>
#include "Controls.h"
#include "Administrator.h"
#include "Customer.h"

void logIn();

int main()
{
    logIn();
    return 0;
}

void logIn()
{
    std::string option[4]={"How would you like to login?",
                           "Administrator",
                           "Customer",
                           "Exit"};
    int selection=1;
    Controls controls;
    bool isDone=false;

    while(!isDone){
        controls.linearSelector(option, 4, selection);
        switch(selection)
        {
        case 1: //Administrator
            Administrator();
            break;
        case 2: //Customer
            Customer();
            break;
        case 0:
        case 3: //Exit
            isDone=true;
            break;
        }
    }
}
