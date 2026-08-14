#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include <vector>


class Display
{
    public:
        Display();

        void optionDisplay(std::string option[], int optionSize, int selection);
        void seatDisplay(std::vector<std::string> data, int row, int col);
        void comment(std::string _comment);

        ~Display();

    protected:

    private:
};

#endif // DISPLAY_H
