#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "memblockdevice.h"
#include <vector>
#include <stdlib.h>
#include "FileStructure.h"
using namespace std;

class FileSystem
{
private:
    
    MemBlockDevice mMemblockDevice;
    
    //Filesystem
    Directory root;
public:
    FileSystem();
    /* These commands needs to implemented */
    /*
     * However, feel free to change the signatures, these are just examples.
     * Remember to remove 'const' if needed.
     */
    string format();
    std::string ls(std::string currDir);// Klar
    //std::string ls(const std::string &path) const;  // optional
	std::string create(const std::string &filePath, std::string name, std::string content);// Klar
    
	std::string cat(std::string &fileName, std::string filePath); // Klar
    std::string save(const std::string &saveFile);
    std::string read(const std::string &saveFile);
    std::string rm(const std::string &filePath , std::string &fileName); //klar
	std::string mkdir(const std::string &path, std::string &name);// Klar
    std::string copy(const std::string &source, const std::string &dest);

    /* Optional */
    std::string append(const std::string &source, const std::string &app);
    std::string rename(const std::string &source, const std::string &newName);
    std::string chmod(int permission, const std::string &file);
    std::string findDirectory(std::string quq);
	bool cd(std::string &path);// Klar
	std::string save2(const std::string &saveFile);

    /* Add your own member-functions if needed */
};

#endif // FILESYSTEM_H
