#ifndef FILE_H
#define FILE_H


#include "filesystem.h"

class File
{
protected:
    string filename;
    int blockNr;
public:
	File(int blockNr = 0);
	~File();
};

#endif
