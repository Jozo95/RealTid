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

bool Directory::addFile(const std::string &path, std::string &name, int blockNr)
{


	//vector<Directory> root = this->directories;
	//vector<Directory> temp;

	//temp = findDirectory(path, 2);
	////vector<Directory> *temptemp = new vector<Directory>(*this->directories);



	//
	//temp.at(currentPos).files.push_back(File(name, blockNr));

	//directories = root;

	////Directory hej = this->directories[0].directories[0].directories[0];	
	//cout << " ADded FILE !!! " << endl;

	//pathExists = false;

	return true;
}

/*
Directory-class
*/
  
Directory::Directory()
{
	counter = 0;
	name = "Undefined";
	pathExists = false;
	touchedEndl = false;

	this->directories.push_back(Directory("/"));
	//this->directories.at(0).directories = new vector<Directory>();

	counter++;
	counter++;
	this->directories.at(0).directories.push_back(Directory("usr/"));
	//this->directories.at(0).directories.at(0).directories = new vector<Directory>();
	this->directories.at(0).directories.at(0).counter++;
	this->directories.at(0).directories.at(0).directories.push_back(Directory("bajs/"));
	//this->directories.at(0).directories.at(0).directories.at(0).directories = new vector<Directory>();
	//this->directories.at(0).directories.at(0).counter++;
	this->directories.at(0).counter++;
	this->directories.at(0).directories.push_back(Directory("local/"));
	//this->directories.at(0).directories.at(1).directories = new vector<Directory>();
	this->directories.at(0).counter++;
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
	Directory *root = findDirectory(currDir, this->directories);

	//cout << "ANTALET:::" + root->getName();
	
	//cout << "DIR: " << Directory(root).getName(); << endl;
	string all = "";
	for (int i = 0; i < root->getCounter() ; i++){
		all = all + "\n" + root->directories.at(i).getName();
	}	

	return all;
}

int Directory::getFileText(const std::string &path, std::string fileName)
{
	//vector<Directory> tempPtr;


	//tempPtr = findDirectory(path, 2);
	//for (int i = 0; i < tempPtr.at(currentPos).files.size(); i++){
	//	if (tempPtr.at(currentPos).files.at(i).getName() == fileName)
	//	{
	//		return int(tempPtr.at(currentPos).files.at(i).getBlockNr());
	//	}
	//}
	return -1;
}
    	
Directory::~Directory()
{
}

bool Directory::addDirectory(const std::string &path, std::string &dirName) {
	//pathExists = false;
	Directory *tempPtr;
	tempPtr = findDirectory(path, this->directories);
	if (pathExists == true) {
		tempPtr->directories.push_back(dirName);
		tempPtr->counter++;
		return true;
	}
	else {
		return false;
	}
	return false;
}

Directory* Directory::findDirectory(const std::string &path, vector<Directory> &myVector){
	string pathToFind = path;
	int startPos = 0;
	int endPos = 0;
	bool exist = false;
	vector<Directory> *secWalker = nullptr;
	vector<Directory> *walker = nullptr;
	walker = &this->directories;
	Directory *dir;
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
	tempPtr = findDirectory(path, this->directories);
	if (pathExists == true) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool Directory::removeFile(const std::string &path, std::string &name, int blockNr){
	vector<Directory> tempPtr;


	//tempPtr = findDirectory(path, 2);
	//for (int i = 0; i < tempPtr.at(currentPos).files.size(); i++){
	//	if (tempPtr.at(currentPos).files.at(i).getName() == name)
	//	{
	//		File l = tempPtr.at(currentPos).files.at(i);
	//		tempPtr.at(currentPos).files.erase(tempPtr.at(currentPos).files.begin() + i);
	//		return true;
	//	}
	//}
	return false;
}


void Directory::recurs(vector<Directory> vec, ofstream &fileStream, string &path)
{
	vector<Directory> temp = vec;
	string pathBefore = path;
	//std::cout << "SIZE " << temp.size

	for (int i = 0; i < temp.size(); i++){
		if (touchedEndl) {
			fileStream << endl <<  temp.at(i).getName();
			fileStream << endl << "F:" + path;
			path = path + temp.at(i).getName();
			recurs(temp.at(i).directories, fileStream, path);
			path = pathBefore;
		}
		else {
			touchedEndl = true;
			fileStream << temp.at(i).getName() << endl;;
			fileStream << "F:" + path;
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
	string path = "";
	int counter = 0;
	string dirName, filePath;



	while (!fileStream.eof()) {
		filePath = "";
		fileStream >> dirName;
		fileStream >> filePath;
		if (filePath.size() == 2) {
			cout << "Empty path found" << endl;
			filePath = "/";
		}
		else {
			if (!filePath.size() == 0) {
				if (filePath.size() > 4) {
					cout << filePath << endl;
					filePath = filePath.substr(2, filePath.length() - 2);
				}
				else {
					cout << filePath << endl;
					filePath = filePath.substr(2, filePath.length() - 2);
				}
			}
		}
		cout << "Dir name:" <<  dirName << endl << "FilePath:" << filePath << endl;
		if (counter == 0) {
			//returned = findDirectory(filePath, this->directories);
			directories.push_back(Directory(dirName));
			
			//directories.at(temp.size() - 1).directories = new vector<Directory>();

		}
		else {
			returned = findDirectory(filePath, this->directories);
			returned->directories.push_back(Directory(dirName));
			returned->counter++;
			//returned.at(returned.size() - 1).directories = new vector<Directory>();

		}
		//returned = findDirectory(filePath, 1);

		counter++;
	}

	cout << "rREMOVED ALL BITCHES" << counter << endl;
}