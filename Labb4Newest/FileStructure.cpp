#include "FileStructure.h"

/*
File-class
*/


File::File(string name, int blockNr)
{
	this->name = name;
	this->blockNr = blockNr;
}

File::File()
{
	this->name = "None";
	this->blockNr = -1;
}

std::string File::getName() const
{
	return this->name;
}

File::~File(){}

int File::getBlockNr() const
{
	return this->blockNr;
}


/*
Directory-class
*/
int Directory::copy(const std::string &currDir, const std::string &source, const std::string &dest, const std::string &name) {
	Directory *tempPtr;
	//File newFile(name, blockNr);
	tempPtr = findDirectory(currDir );
	for (int i = 0; i < tempPtr->files.size(); i++) {
		if (source == tempPtr->files.at(i).getName()) {
			return tempPtr->files.at(i).getBlockNr();
			
		}
	}
	return -1;
}
bool Directory::addFile(const std::string &currDir, std::string &name, int blockNr)
{
	//pathExists = false;
	Directory *tempPtr;
	File newFile(name, blockNr);
	tempPtr = findDirectory(currDir );
	if (pathExists == true) {
		tempPtr->files.push_back(newFile);
		return true;
	}
	else {
		return false;
	}
}

bool Directory::format()
{
	vector<Directory> newRoot;
	this->directories = newRoot;
	vector<File> newFileRoot;
	this->files = newFileRoot;
	this->directories.push_back(Directory("/"));
	return true;
}


  
Directory::Directory()
{
	counter = 0;
	name = "Undefined";
	pathExists = false;
	touchedEndl = false;

	this->directories.push_back(Directory("/"));
	//this->directories.at(0).directories = new vector<Directory>();

	//counter++;
	//counter++;
	//this->directories.at(0).directories.push_back(Directory("usr/"));
	////this->directories.at(0).directories.at(0).directories = new vector<Directory>();
	//this->directories.at(0).directories.at(0).counter++;
	//this->directories.at(0).directories.at(0).directories.push_back(Directory("deep/"));
	////this->directories.at(0).directories.at(0).directories.at(0).directories = new vector<Directory>();
	////this->directories.at(0).directories.at(0).counter++;
	//this->directories.at(0).counter++;
	//this->directories.at(0).directories.push_back(Directory("local/"));
	////this->directories.at(0).directories.at(1).directories = new vector<Directory>();
	//this->directories.at(0).counter++;
}  
  
Directory::Directory(string name)
{
	this->name = name;
	pathExists = false;
	this->counter = 0;
}

string Directory::getName() const
{
	return this->name;
}

int Directory::getCounter() {
	return this->counter;
}

string Directory::printAll(std::string &currDir) {
	Directory *root = findDirectory(currDir );

	//cout << "ANTALET:::" + root->getName();
	
	//cout << "DIR: " << Directory(root).getName(); << endl;
	string all = "";
	for (int i = 0; i < root->directories.size() ; i++){
		all = all + "\n" + root->directories.at(i).getName();
	}
	for (int i = 0; i < root->files.size(); i++) {
		all = all + "\n" + root->files.at(i).getName();
	}

	return all;
}

int Directory::getFileText(const std::string &path, std::string fileName)
{
	Directory* tempPtr;


	tempPtr = findDirectory(path );
	for (int i = 0; i < tempPtr->files.size(); i++){
		if (tempPtr->files.at(i).getName() == fileName)
		{
			return int(tempPtr->files.at(i).getBlockNr());
		}
	}
	return -1;
}
    	
Directory::~Directory()
{
}

bool Directory::addDirectory(const std::string &path, std::string &dirName) {
	//pathExists = false;
	Directory *tempPtr;
	tempPtr = findDirectory(path);
	if (pathExists == true) {
		tempPtr->directories.push_back(dirName+"/");
		tempPtr->counter++;
		return true;
	}
	else {
		return false;
	}
	return false;
}

Directory* Directory::findDirectory(const std::string &path){
	string pathToFind = path;
	int startPos = 0;
	int endPos = 0;
	bool exist = false;
	vector<Directory> *secWalker = nullptr;
	vector<Directory> *walker = nullptr;
	walker = &this->directories;
	Directory *dir = nullptr;
	string pathFound = "";

	for (int i = 0; i < path.length(); i++)
	{
		int pos = 0;
		if (pathToFind[i] == 47)
		{
			string currentDir;
			endPos = i + 1;
			for (int k = startPos; k < endPos; k++)
			{
				currentDir = currentDir + pathToFind[k];
			}
			startPos = endPos;

			for (int k = 0; k < walker->size(); k++)
			{
				//cout << "CURRENT DIR: " + currentDir << endl;
				//cout << "CURRENT WALKER: " + walker->at(k).getName() << endl;
				if (walker->at(k).getName() == currentDir)
				{
					exist = true;
					pos = k;
					currentPos = k;
					pathFound = pathFound + walker->at(k).getName();
				}
			}
			if (exist == true)
			{
				//dir = walker->at(pos);
				//walker = &dir.directories;
				exist = false;

				if (pathFound == pathToFind) {
					pathExists = true;
					return &walker->at(pos);
				}
				walker = &walker->at(pos).directories;
				//cout << "HIT" << endl;
			}
			else{
				//myVector = *walker;
				dir = &walker->at(pos);
				return dir;
			}
		}
	}
}

bool Directory::enterDirectory(const std::string &path)
{
	pathExists = false;
	Directory *tempPtr;
	tempPtr = findDirectory(path );
	if (pathExists == true) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool Directory::removeFile(const std::string &path, std::string &name, int blockNr){
	Directory* tempPtr;


	tempPtr = findDirectory(path );
	for (int i = 0; i < tempPtr->files.size(); i++){
		if (tempPtr->files.at(i).getName() == name)
		{
			File l = tempPtr->files.at(i);
			tempPtr->files.erase(tempPtr->files.begin() + i);
			return true;
		}
	}
	return false;
}


void Directory::recurs(vector<Directory> vec, ofstream &fileStream, string &path)
{
	vector<Directory> temp = vec;
	string pathBefore = path;
	//std::cout << "SIZE " << temp.size
	bool fileInFirst = false;
	for (int i = 0; i < temp.size(); i++){
		if (touchedEndl) {
			if(fileInFirst)
				fileStream <<  temp.at(i).getName();
			else
				fileStream << endl << temp.at(i).getName();
			fileStream << endl << "F:" + path;
			for (int k = 0; k < temp.at(i).files.size(); k++) {
				fileStream << endl << "File:" + temp.at(i).files.at(k).getName();
				fileStream << endl << temp.at(i).files.at(k).getBlockNr();

			}
			path = path + temp.at(i).getName();
			recurs(temp.at(i).directories, fileStream, path);
			path = pathBefore;
		}
		else {
			touchedEndl = true;
			fileStream << temp.at(i).getName() << endl;
			fileStream << "F:" + path;
			for (int k = 0; k < temp.at(i).files.size(); k++) {
				fileStream << endl << "File:" + temp.at(i).files.at(k).getName() << endl;
				fileInFirst = true;
				fileStream << temp.at(i).files.at(k).getBlockNr();
			}
			path = path + temp.at(i).getName();
			recurs(temp.at(i).directories, fileStream, path);
			path = pathBefore;
		}
	}
	//touchedEndl = false;
	//return temp;
}

void Directory::save(ofstream &fileStream) {

	string path = "";
	recurs(this->directories, fileStream, path);
	ifstream fileStreamz("saved.txt");
	fileStreamz.close();
}

void Directory::loadSystem(ifstream &fileStream) {
	//vector<Directory> temp;
	//this->directories = temp;
	Directory *returned;
	vector<Directory> root;
	this->directories = root;
	vector<File> rootFiles;
	this->files = rootFiles;
	//apeka dir till ny files?
	string path = "";
	int counter = 0;
	string dirName, filePath, fileName;
	int memBlockNr;
	bool copiedDirName = false;

	while (!fileStream.eof()) {
		filePath = "";
		if (!copiedDirName) {
			fileStream >> dirName;
		}
		else {
			dirName = fileName;
		}
		fileStream >> filePath;
		if (filePath.size() == 2) {
			filePath = "/";
		}
		else {
			if (!filePath.size() == 0) {
				if (filePath.size() > 4) {
					filePath = filePath.substr(2, filePath.length() - 2);
				}
				else {
					filePath = filePath.substr(2, filePath.length() - 2);
				}
			}
		}
		if (counter == 0) {
			//returned = findDirectory(filePath );
			directories.push_back(Directory(dirName));
			fileStream >> fileName;
			
			while (fileName.substr(0,5) == "File:") {
				fileStream >> memBlockNr;
				directories.at(0).files.push_back(File((fileName.substr(5, fileName.size())), memBlockNr));
				fileStream >> fileName;
			}
			copiedDirName = true;
			//directories.at(temp.size() - 1).directories = new vector<Directory>();

		}
		else {
			returned = findDirectory(filePath);
			returned->directories.push_back(Directory(dirName));
			fileStream >> fileName;
			while (fileName.substr(0, 5) == "File:") {
				fileStream >> memBlockNr;

				returned->directories.at(returned->directories.size()-1).files.push_back(File((fileName.substr(5, fileName.size())), memBlockNr));
				//returned->files.push_back(File((fileName.substr(5,fileName.size())), memBlockNr));
				fileStream >> fileName;
			}
			copiedDirName = true;
			returned->counter++;
			//returned.at(returned.size() - 1).directories = new vector<Directory>();

		}
		//returned = findDirectory(filePath, 1);

		counter++;
	}
}