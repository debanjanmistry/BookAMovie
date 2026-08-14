#include "Customer.h"
#include <iostream>
#include <conio.h>

Customer::Customer()
{
    system("CLS");
    if(takeInput("What is your name?: ")) return;
    _customerName=_input;
    std::string option[3]={"Welcome "+_customerName+"\n\n"
                           "What do you want to do?",
                           "Book a show",
                           "Go Back"};
    int selection=1;
    Controls controls;
    bool isDone=false;

    while(!isDone){
        controls.linearSelector(option, 3, selection);
        switch(selection)
        {
        case 1: //Book
            bookShow();
            break;
        case 0:
        case 2: //Go Back
            isDone=true;
            break;
        }
        option[0]="What do you want to do, "+_customerName+"?";
    }
}

Customer::~Customer()
{
    //dtor
}

void Customer::bookShow()
{
    system("CLS");
    std::cout<<"Booking a show\n\n";
    _fileName="./Movie/movie.log";
    _data.clear();
    _file.read(_fileName, _data);

    optionSize=(int)_data.size()+1;
    if(optionSize==1){
        _display.comment("No movies available!\n");
        return;
    }

    _movieName=selectMovie();
    if(_movieName=="\0") return;
    selectTime(_timing);
    if(_timing[0]=="\0") return;
    _fileName="./Movie/"+_movieName+" ("+_timing[0]+") ("+_timing[1]+").seat";
    _data.clear();
    _file.read(_fileName, _data);
    system("CLS");
    int numSeat, row=1, col=1;
    double price=0;
    std::vector<std::string> seatNos;
    std::cout<<"No. of seats: ";
    std::cin>>numSeat;
    while(numSeat>0){
        _controls.seatSelector(_data, row, col);
        if(row == 0 && col == 0) return;
        seatNos.push_back(std::string(std::to_string(row)+","+std::to_string(col)));
        if(row>0 && row<6) price+=100;
        else if(row>5 && row<14) price+=70;
        else if(row>13 && row<19) price+=50;
        numSeat--;
    }
    _file.write(_fileName, _data);
    _fileName="./Ticket/"+_customerName+".data";
    _data.clear();
    int ticketNo;
    _file.read(_fileName, _data);
    ticketNo=_data.size()+1;
    _data.push_back((std::to_string(ticketNo))+_movieName+" ("+_timing[0]+") ("+_timing[1]+")");
    _file.write(_fileName, _data);
    _data.clear();
    _fileName="./Ticket/"+(std::to_string(ticketNo))+_movieName+" ("+_timing[0]+") ("+_timing[1]+").ticket";
    _data.push_back(std::to_string(price));
    for(int i=0; i<(int)seatNos.size(); i++){
        _data.push_back(seatNos[i]);
    }
    _file.write(_fileName, _data);
    system("CLS");
    std::vector<std::string> ticket;
    std::string tempString;

    std::cout << "*****BookAMovie*****";
    ticket.push_back("*****BookAMovie*****");

    std::cout << "\nName: " << _customerName;
    ticket.push_back("Name: "+_customerName);

    std::cout << "\nMovie: " << _movieName;
    ticket.push_back("Movie: "+_movieName);

    std::cout << "\nDate: " << _timing[1];
    ticket.push_back("Date: "+_timing[1]);

    tempString.clear();
    for(int i=0; i<(int)_timing[0].size(); i++){
        if(_timing[0][i]=='_') tempString = tempString + ":";
        else tempString = tempString + _timing[0][i];
    }
    std::cout << "\nTime: " << tempString;
    ticket.push_back("Time: "+tempString);

    tempString.clear();
    for(int i=1; i<(int)_data.size(); i++){
        if(i!=1) tempString = tempString + ", ";
        if(i%3==0) tempString = tempString + "\n       ";
        for(int j=0; j<(int)_data[i].size(); j++){
            if(_data[i][j]==',') tempString = tempString + "-";
            else tempString = tempString + _data[i][j];
        }
    }
    std::cout << "\nSeats: " << tempString;
    ticket.push_back("Seats: "+tempString);

    std::cout << "\nPrice: " << _data[0] << "/-";
    ticket.push_back("Price: "+_data[0]+"/-");

   std::cout << "\n********************";
   ticket.push_back("********************");

   std::cout << "\n\nPlease enter the directory where you want to save the ticket or simply press Enter";
   std::cout << "\nDirectory: ";
   std::ofstream fileout;
   int fileNameSize;

   while(true){
        if(takeInput()) return;
        _fileName = _input;
        fileNameSize=(int)_fileName.size();
        for(int i=0; i<fileNameSize; i++){
            if(_fileName[i]=='\\') _fileName[i]='/';
        }
        if(_fileName[fileNameSize-1]!='/') _fileName.push_back('/');
        _fileName = _fileName + _customerName +"-"+ _movieName +".txt";

        fileout.open(_fileName);
        if(fileout.fail()){
            std::cout << "\nDirectory not found!";
            std::cout << "\nPlease enter the directory again: ";
        }else{
            fileout.close();
            break;
        }
   }
   _file.write(_fileName,ticket);
}

std::string Customer::selectMovie()
{
    std::string option[optionSize];
    option[0]="Name of the movies:\n";
    for(int i=1; i<optionSize; i++){
        option[i]=_data[i-1];
    }
    selection=1;

    _controls.linearSelector(option, optionSize, selection);
    if(selection==0) return "\0";
    return option[selection];
}

void Customer::selectTime(std::string timing[])
{
    _fileName="./Movie/"+_movieName+".data";
    _data.clear();
    _file.read(_fileName, _data);
    optionSize=8;
    std::string option[optionSize];
    option[0]="Timings available: ";
    for(int i=1; i<optionSize; i++){
        option[i]=_data[i-1]+": "+_data[i+6];
    }
    for(int i=1; i<optionSize; i++){
        for(int j=0; j<(int)option[i].size(); j++){
            if(option[i][j]=='_') option[i][j]=':';
        }
    }
    selection=1;
    _controls.linearSelector(option, optionSize, selection);
    if(selection==0)timing[0]="\0";
    else{
        timing[0]=_data[selection-1];
        timing[1]=_data[selection+6];
    }
}

int Customer::takeInput(std::string question)
{
    char ch;
    std::cout<<question;
    _input.clear();
    while((ch=getche())!=13){
        if(ch=='\b'){
            std::cout<<" \b";
            _input.pop_back();
        }else if(ch==27){
            return 1;
        }else{
            _input+=ch;
        }
    }
    return 0;
}
