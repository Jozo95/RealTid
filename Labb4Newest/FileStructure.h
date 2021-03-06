#include <vector>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class File
{
private:
    string name;
    int blockNr;
public:
    File();
    File(string name, int blockNr);
	std::string getName() const;
	int getBlockNr() const;
    ~File();
};
    
class Directory
{
private:
    string name;
    vector<File> files;
	vector<Directory> directories;
    int counter;
	bool pathExists;
	bool touchedEndl;
	int currentPos;
public:
	bool format();
	Directory();
	Directory(string name);
	string getName() const;
	void save(ofstream &fileStream);
	int copy(const std::string &currDir, const std::string &source, const std::string &dest, const std::string &name);
	string printAll(std::string &currDir);
	bool addDirectory(const std::string &path, std::string &dirName);
	bool addFile(const std::string &path, std::string &name, int blockNr);
	bool removeFile(const std::string &path, std::string &name, int blockNr);
	Directory* findDirectory(const std::string &path); // /hejsan/b/bla
	int getFileText(const std::string &path, std::string fileName);
	bool enterDirectory(const std::string &path);
	int getCounter();
	void recurs(vector<Directory> vec, ofstream &fileStream, string &path);
	//void recurs(vector<File> vec, ofstream &fileStream, string &path);
	void loadSystem(ifstream &fileStream);
    virtual ~Directory();
};