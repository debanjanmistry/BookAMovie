#include "FileHandling.h"

FileHandling::FileHandling()
{
    //ctor
}

void FileHandling::read(std::string fileName, std::vector<std::string> &data)
{
    _fileIn.open(fileName);
    if(_fileIn.fail()){
        write(fileName, data);
        _fileIn.open(fileName);
    }

    std::string line;
    while(std::getline(_fileIn, line)){
        data.push_back(line);
    }

    _fileIn.close();
}

void FileHandling::write(std::string fileName, std::vector<std::string> data)
{
    _fileOut.open(fileName);

    for(int i=0; i<(int)data.size(); i++){
        _fileOut<<data[i]<<"\n";
    }

    _fileOut.close();
}

FileHandling::~FileHandling()
{
    //dtor
}
