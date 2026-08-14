#ifndef CONTROLS_H
#define CONTROLS_H
#include <string>
#include "Display.h"

class Controls
{
    public:
        Controls();

        void linearSelector(std::string option[], int optionSize, int &selection);
        void seatSelector(std::vector<std::string> &data, int &row, int &col);

        ~Controls();

    protected:

    private:
        Display display;
};

#endif // CONTROLS_H
