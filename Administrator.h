#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include <string>
#include <vector>
#include "FileHandling.h"
#include "Display.h"

class Administrator
{
    public:
        Administrator();
        ~Administrator();

    protected:
        void newShow();
        void delShow();
        int takeInput(std::string question = "");
        bool inputTime();
        bool inputDate();
        void createSeat();
        void removeWrongInput(int inputSize);

    private:
        FileHandling _file;
        Display _display;

        std::string _input;
        std::string _fileName;
        std::string _movieName;
        std::vector<std::string> _data;
};

#endif // ADMINISTRATOR_H
