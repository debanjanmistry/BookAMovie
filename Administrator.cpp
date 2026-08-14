#include "Administrator.h"
#include <iostream>
#include <cstdio>
#include <conio.h>
#include "Controls.h"

Administrator::Administrator()
{
    std::string option[4]={"Welcome Administrator\n\n"
                           "What do you want to do?",
                           "Create a new show",
                           "Delete a show",
                           "Go Back"};
    int selection=1;
    Controls controls;
    bool isDone=false;

    while(!isDone){
        controls.linearSelector(option, 4, selection);
        switch(selection)
        {
        case 1: //New
            newShow();
            break;
        case 2: //Delete
            delShow();
            break;
        case 0:
        case 3: //Go Back
            isDone=true;
            break;
        }
        option[0]="What do you want to do, Administrator?";
    }
}

Administrator::~Administrator()
{
    //dtor
}

void Administrator::newShow()
{
    system("CLS");
    if(takeInput("Creating a new show\n\n"
                 "Name of the movie: ")) return;

    _movieName=_input;
    _fileName="./Movie/movie.log";
    _file.read(_fileName, _data);
    for(int i=0; i<(int)_data.size(); i++){
        if(_movieName==_data[i]){
            _display.comment("Movie already exits!\n");
            _data.clear();
            return;
        }
    }
    _data.clear();

    _fileName="./Movie/"+_movieName+".data";
    if(inputTime()) return;
    if(inputDate()) return;
    _file.write(_fileName, _data);
    _data.clear();
    createSeat();
    _fileName="./Movie/movie.log";
    _file.read(_fileName, _data);
    _data.push_back(_movieName);
    _file.write(_fileName, _data);
    _data.clear();
}

void Administrator::delShow()
{
    system("CLS");
    std::cout<<"Deleting a show\n\n";
    _fileName="./Movie/movie.log";
    _file.read(_fileName, _data);

    int optionSize=(int)_data.size()+1;
    if(optionSize==1){
        _display.comment("No movies registered!\n");
        return;
    }
    std::string option[optionSize];
    option[0]="Name of the movies:\n";
    for(int i=1; i<optionSize; i++){
        option[i]=_data[i-1];
    }
    int selection=1;
    Controls controls;

    controls.linearSelector(option, optionSize, selection);
    if(selection==0) return;
    _input=_data[selection-1];
    _data[selection-1]=_data.back();
    _data.pop_back();
    _file.write(_fileName, _data);
    _data.clear();

    std::vector<std::string> files;
    _fileName="./Movie/"+_input+".data";
    _file.read(_fileName, files);

    for(int i=0; i<7; i++){
        _fileName="./Movie/"+_input+" ("+files[i]+") ("+files[i+7]+").seat";
        remove(_fileName.c_str());
    }

    _fileName="./Movie/"+_input+".data";
    remove(_fileName.c_str());
}

int Administrator::takeInput(std::string question)
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

bool Administrator::inputTime()
{
    bool isDone = false;
    int inputSize;

    std::cout << "\nTime(24H format): ";

    while(!isDone){
        if(takeInput()) return true;
        inputSize = (int)_input.size();
        for(int i=0; i<inputSize; i++){
            if((_input[i]!='0' && _input[i]!='1' && _input[i]!='2' &&
                _input[i]!='3' && _input[i]!='4' && _input[i]!='5' &&
                _input[i]!='6' && _input[i]!='7' && _input[i]!='8' &&
                _input[i]!='9' && _input[i]!=':' && _input[i]!='-' &&
                _input[i]!=' ') || inputSize>13){

                std::cout << "\bTime(24H format): ";
                removeWrongInput(inputSize);
                break;
            }else if(i==inputSize-1){
                bool ok = true;
                for(int i=0; i<inputSize; i++){
                    if((i==2 || i==10) && _input[i]!=':') ok=false;
                    else if(i==6 && _input[i]!='-') ok=false;
                    else if((i==5 || i==7) && _input[i]!=' ') ok=false;
                    else if(i==0 || i==8){
                        if(_input[i]=='2' && _input[i+1]>'4') ok=false;
                        else if(_input[i]=='2' && _input[i+1]=='4' && _input[i+4]>'0') ok=false;
                        else if(_input[i+3]>'5') ok=false;
                    }
                }
                if(ok) isDone=true;
                else{
                    std::cout << "\bTime(24H format): ";
                    removeWrongInput(inputSize);
                }
            }
        }
    }
    int timeStart[2], timeEnd[2], timeDiff;
    timeStart[0]=((_input[0]-'0')*10) + (_input[1]-'0');
    timeStart[1]=((_input[3]-'0')*10) + (_input[4]-'0');
    timeEnd[0]=((_input[8]-'0')*10) + (_input[9]-'0');
    timeEnd[1]=((_input[11]-'0')*10) + (_input[12]-'0');
    timeDiff=timeEnd[0]-timeStart[0];
    for(int i=0; i<7; i++){
        std::string ss1[2], ss2[2];

        for(int j=0; j<2; j++){
            if(timeStart[j]<10) ss1[j]='0';

            if(timeEnd[j]<10) ss2[j]='0';
        }

        ss1[0]= ss1[0]+std::to_string(timeStart[0]);
        ss1[1]= ss1[1]+std::to_string(timeStart[1]);
        ss2[0]= ss2[0]+std::to_string(timeEnd[0]);
        ss2[1]= ss2[1]+std::to_string(timeEnd[1]);
        _input = ss1[0]+'_'+ss1[1]+'-';
        _input = _input + ss2[0]+'_'+ss2[1];
        _data.push_back(_input);

        timeStart[0]=timeEnd[0]+1;
        if(timeStart[0]>24) timeStart[0]=01;
        timeEnd[0]=timeStart[0]+timeDiff;
        if(timeEnd[0]>24) timeEnd[0]=01;
    }
    return false;
}

bool Administrator::inputDate()
{
    bool isDone = false;
    int inputSize, year, month, date;

    std::cout << "\nDate(DD/MM/YYYY): ";

    while(!isDone){
        if(takeInput()) return true;
        inputSize = (int)_input.size();
        for(int i=0; i<inputSize; i++){
            if((_input[i]!='0' && _input[i]!='1' && _input[i]!='2' &&
                _input[i]!='3' && _input[i]!='4' && _input[i]!='5' &&
                _input[i]!='6' && _input[i]!='7' && _input[i]!='8' &&
                _input[i]!='9' && _input[i]!='/')|| inputSize>10){

                std::cout << "\bDate(DD/MM/YYYY): ";
                removeWrongInput(inputSize);
                break;
            }else if(i==inputSize-1){
                bool ok = true;
                year = ((_input[6]-'0')*1000) + ((_input[7]-'0')*100) + ((_input[8]-'0')*10) + (_input[9]-'0');
                month = ((_input[3]-'0')*10) + (_input[4]-'0');
                date = ((_input[0]-'0')*10) + (_input[1]-'0');
                if(month > 12 || date > 31) ok=false;
                else if(((year%4==0) && (month==2) && (date>29)) || ((year%4!=0) && (month==2) && (date>28))) ok=false;
                else if((month<=7) && (month%2==0) && (date>30)) ok=false;
                else if((month>7) && (month%2!=0) && (date>30)) ok=false;
                if(ok) isDone=true;
                else{
                    std::cout << "\bDate(DD/MM/YYYY): ";
                    removeWrongInput(inputSize);
                }
            }
        }
    }

    for(int i=0; i<7; i++){
        std::string ss1, ss2, ss3;

        if(date<10) ss1='0';
        if(month<10) ss2='0';
        if(year<1000) ss3='0';

        _input = ss1+std::to_string(date)+'-'+ss2+std::to_string(month)+'-'+ss3+std::to_string(year);
        _data.push_back(_input);

        date++;
        if(((year%4==0) && (month==2) && (date>29)) || ((year%4!=0) && (month==2) && (date>28)) ||
           ((month<=7) && (month%2==0) && (date>30))|| ((month>7) && (month%2!=0) && (date>30)) ||
           ((month<=7) && (month%2!=0) && (date>31))|| ((month>7) && (month%2==0) && (date>31))){
            date=01;
            month++;
        }
        if(month>12){
            month=01;
            year++;
        }
    }
    return false;
}

void Administrator::createSeat()
{
    std::vector<std::string> files;
    _fileName="./Movie/"+_movieName+".data";
    _file.read(_fileName, files);

    for(int i=0; i<7; i++){
        _fileName="./Movie/"+_movieName+" ("+files[i]+") ("+files[i+7]+").seat";
        for(int j=0; j<18; j++){
            _data.push_back("00000000000000000000000000");
        }
        _file.write(_fileName, _data);
        _data.clear();
    }

}

void Administrator::removeWrongInput(int inputSize)
{
    for(int j=0; j<inputSize; j++){
        std::cout << " ";
    }
    for(int j=0; j<inputSize; j++){
        std::cout << "\b";
    }
}
