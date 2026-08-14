#ifndef FILEHANDLING_H
#define FILEHANDLING_H
#include <fstream>
#include <string>
#include <vector>

class FileHandling
{
    public:
        FileHandling();

        void read(std::string fileName, std::vector<std::string> &data);
        void write(std::string fileName, std::vector<std::string> data);

        ~FileHandling();

    protected:

    private:
        std::ifstream _fileIn;
        std::ofstream _fileOut;
};

#endif // FILEHANDLING_H
