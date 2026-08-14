#include "Controls.h"
#include <conio.h>

Controls::Controls()
{
    //ctor
}

void Controls::linearSelector(std::string option[], int optionSize, int &selection)
{
    char input;
    bool isDone = false;
    while(!isDone){
        display.optionDisplay(option, optionSize, selection);
        while((input = getch())==-32);
        switch(input)
        {
        case 72:    //UP
            if(selection > 1) selection--;
            break;
        case 80:    //DOWN
            if(selection < optionSize-1) selection++;
            break;
        case 13:    //Enter
            isDone = true;
            break;
        case 27:    //Esc
            selection=0;
            isDone = true;
            break;
        }
    }
}

void Controls::seatSelector(std::vector<std::string> &data, int &row, int &col)
{
    int maxRow = (int)data.size(), maxCol = (int)data[0].size();
    char input;
    bool isDone = false;
    while(!isDone){
        display.seatDisplay(data, row, col);
        while((input = getch())==-32);
        switch(input)
        {
        case 72:    //UP
            if(row > 1) row--;
            break;
        case 80:    //DOWN
            if(row < maxRow) row++;
            break;
        case 75:    //LEFT
            if(col > 1) col--;
            break;
        case 77:    //RIGHT
            if(col < maxCol) col++;
            break;
        case 13:    //Enter
            if(data[row-1][col-1]=='0'){
                data[row-1][col-1]='1';
                isDone = true;
            }
            break;
        case 27:    //Esc
            row=col=0;
            isDone = true;
            break;
        }
    }
}

Controls::~Controls()
{
    //dtor
}
