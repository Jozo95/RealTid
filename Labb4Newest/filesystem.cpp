#include "filesystem.h"


/*
Filesystem-class
*/
FileSystem::FileSystem() {
this->root = Directory();
mMemblockDevice = MemBlockDevice(250);
}

string FileSystem::format() {
	return "1";
}

string FileSystem::ls(std::string currDir)
{
	string all = this->root.printAll(currDir);
	return all;
}

std::string FileSystem::create(const std::string & filePath, std::string name, std::string content)
{
	int counter = mMemblockDevice.counter;
	this->root.addFile(filePath, name, counter);
	content.resize(512);
	cout << "conetent: " << content << endl;
	mMemblockDevice.writeBlock(counter, content);
	return std::string();
}

std::string FileSystem::mkdir(const std::string &path, std::string &name){
	
	return "Bool-status " + root.addDirectory(path, name);
}

bool FileSystem::cd(std::string & path)
{
	if (root.enterDirectory(path) == true) {
		return true;
	}

	return false;
}

string FileSystem::cat(std::string &fileName, std::string filePath)
{
	int blockNr = int(this->root.getFileText(filePath, fileName));

	if (blockNr != -1)
	{
		Block block;
		block = mMemblockDevice.readBlock(blockNr);
		return (block.toString().substr(0, 7));
	}
	return "No such file";

}
std::string FileSystem::rm(const std::string &filePath, std::string &fileName){
	int blockNr = root.getFileText(filePath, fileName);
	if (blockNr != -1){
		Block block;
		Block block2 = mMemblockDevice.readBlock(mMemblockDevice.counter-1);
		block = mMemblockDevice.readBlock(blockNr);
		mMemblockDevice.writeBlock(blockNr, block2.toString());
		mMemblockDevice.counter--;
		this->root.removeFile(filePath, fileName, blockNr);

	}
	return "";
}


std::string FileSystem::save(const std::string &saveFile)
{
	ofstream myfile;
	myfile.open("saved.txt");
	this->root.save(myfile);
	myfile.close();
	return "a";
}

std::string FileSystem::read(const std::string &saveFile) {

	ifstream quq("saved.txt");
	root.loadSystem(quq);
	return "ok";
}