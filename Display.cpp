#include "Display.h"
#include <iostream>

Display::Display()
{
    //ctor
}

void Display::optionDisplay(std::string option[], int optionSize, int selection)
{
    system("CLS");
    for(int i=0; i<optionSize; i++){
        std::cout<<option[i];
        if(selection == i) std::cout<<" <";
        std::cout<<std::endl;
    }
}

void Display::seatDisplay(std::vector<std::string> data, int row, int col)
{
    system("CLS");

    int maxRow = (int)data.size(), maxCol;
    for(int i=0; i<maxRow; i++){
        if(i==0) std::cout << "\n\tPremium\n";
        else if(i==5) std::cout << "\n\tExecutive\n";
        else if(i==13) std::cout << "\n\tNormal\n";
        maxCol = (int)data[i].size();
        if(row == i+1) std::cout<<std::endl;
        for(int j=0; j<maxCol; j++){
            if((col == j+1) && (row == i+1)) std::cout<<">";
            else if(col == j+1) std::cout << " ";
            if(data[i][j] == '0') std::cout << "O";
            else std::cout << " ";
            if((col == j+1) && (row == i+1)) std::cout<<"<";
            else if(col == j+1) std::cout << " ";
        }
        std::cout<<std::endl;
        if(row == i+1) std::cout<<std::endl;
    }
}

void Display::comment(std::string _comment)
{
    system("CLS");
    std::cout<<_comment;
    system("PAUSE");
}

Display::~Display()
{
    //dtor
}
