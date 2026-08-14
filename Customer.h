#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include "FileHandling.h"
#include "Display.h"
#include "Controls.h"

class Customer
{
    public:
        Customer();
        ~Customer();

    protected:
        void bookShow();
        std::string selectMovie();
        void selectTime(std::string timing[]);
        void selectSeat();
        int takeInput(std::string question = "");

    private:
        FileHandling _file;
        Display _display;
        Controls _controls;

        std::string _input, _fileName, _movieName, _timing[2], _customerName;
        std::vector<std::string> _data;
        int optionSize, selection;
};

#endif // CUSTOMER_H
