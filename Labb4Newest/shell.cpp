#include <iostream>
#include <sstream>
#include "filesystem.h"
#include <crtdbg.h>
#include <regex>
const int MAXCOMMANDS = 8;
const int NUMAVAILABLECOMMANDS = 15;

std::string availableCommands[NUMAVAILABLECOMMANDS] = {
    "quit","format","ls","create","cat","save","read",
    "rm","copy","append","rename","mkdir","cd","pwd","help"
};

/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
int parseCommandString(const std::string &userCommand, std::string strArr[]);
int findCommand(std::string &command);

/* Splits a filepath into multiple strings */
std::vector<std::string> split(const std::string &filePath, const char delim = '/');

std::string help();

int main(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
/*	std::string Str1;
	Str1.resize(512);
	
	for (int i = 0; i < 25; i++)
	{
		Str1[i] =  47;
	}
	
	

	
	char const *c = Str1.c_str();
	std::cout << "Str1 bytes; " << (Str1.substr(0,25));*/
    std::string userCommand, commandArr[MAXCOMMANDS];
    std::string user = "user@DV1492";    // Change this if you want another user to be displayed
    std::string currentDir = "/";    // current directory, used for output
	FileSystem fileSystem;
	std::string name = "";
	std::string path = "/";
    bool bRun = true;

    do {
        std::cout <<user << ":" << currentDir << "$ ";
        getline(std::cin, userCommand);

        int nrOfCommands = parseCommandString(userCommand, commandArr);
        if (nrOfCommands > 0) {

            int cIndex = findCommand(commandArr[0]);
            switch(cIndex) {

            case 0: // quit
                bRun = false;
                std::cout << "Exiting" << std::endl;
                break;
            case 1: // format
                // Call fileSystem.format()
                std::cout << "Formated" << std::endl;
                fileSystem.format();
                break;
            case 2: // ls
                std::cout << "Listing directory" << std::endl;
                cout << fileSystem.ls(currentDir) << endl;
                break;
			case 3: // create 
			{
						std::string fileName = userCommand.substr(7, userCommand.length() - 7);
						fileSystem.create(currentDir, fileName, "Content"); 
			}
                break;
			case 4: // cat
			{
						std::string fileName1 = userCommand.substr(4, userCommand.length() - 4);
						cout << fileSystem.cat(fileName1, currentDir) << endl ;
			}
                break;
            case 5: // save
				fileSystem.save("ok");
                break;
            case 6: // read
			{
				fileSystem.read("saved.txt");
			}
                break;
			case 7: // rm
			{
						std::string fileName2 = userCommand.substr(3, userCommand.length() - 3);
						fileSystem.rm(currentDir, fileName2);
			}
                break;

            case 8: // copy
			{
				std::smatch m;
				std::regex e("copy ([a-z]*) ([a-z/]*)|[/][a-z]*");
				std::regex se("[/][a-z]*");
				string q, w, r, c, s;
				s = userCommand;
				while (std::regex_search (s, m, e)) {
					for (auto x : m) //std::cout << x << " ";
					q = m[1].str();
					w = m[2].str();
					c =  w;
					s = m.suffix().str();
				}
				while (std::regex_search(c, m, se)) {
					for (auto x : m) //std::cout << x << " ";
					r = m[0].str();
					c = m.suffix().str();
				}
				cout << "R:" << r << endl;
				r = r.substr(1, r.length() - 1);
				w = w.substr(0, w.length() - r.length());
				fileSystem.copy(currentDir, q, w, r);
			}

                break;

            case 9: // append

                break;

            case 10: // rename

                break;

			case 11: // mkdir
			{
						 std::string name = userCommand.substr(6, userCommand.length() - 6);
						 cout << fileSystem.mkdir(currentDir, name) << ". The sub'd string:" << name << endl;
			}
                break;

            case 12: // cd
			{
				std::string subStr = currentDir + userCommand.substr(3, userCommand.length() - 3);
				std::string subStr2 = userCommand.substr(3, userCommand.length() - 3);

				if (subStr2 == "..") {
					std::string sub = currentDir.substr(0, currentDir.length() - name.length());
					currentDir = sub;
					//std::cout << "Substr" << subStr << endl;
					std::cout << "Going back directory...\n";
				}
				else if (fileSystem.cd(subStr)) {
					name = userCommand.substr(3, userCommand.length() - 3);
					currentDir = subStr;
					std::cout << "Entering directory...\n" << endl;
				}
				
				}
                break;

            case 13: // pwd
				std::cout << "Printing working directory\n" << currentDir << std::endl;
                break;

            case 14: // help
                std::cout << help() << std::endl;
                break;

            default:
                std::cout << "Unknown command: " << commandArr[0] << std::endl;

            }
        }
    } while (bRun == true);

    return 0;
}

int parseCommandString(const std::string &userCommand, std::string strArr[]) {
    std::stringstream ssin(userCommand);
    int counter = 0;
    while (ssin.good() && counter < MAXCOMMANDS) {
        ssin >> strArr[counter];
        counter++;
    }
    if (strArr[0] == "") {
        counter = 0;
    }
    return counter;
}
int findCommand(std::string &command) {
    int index = -1;
    for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
        if (command == availableCommands[i]) {
            index = i;
        }
    }
    return index;
}

std::vector<std::string> split(const std::string &filePath, const char delim) {
    std::vector<std::string> output;
    std::string cpy = filePath;
    size_t end = cpy.find_last_of(delim);
    if (cpy.length() > end+1)
        output.insert(output.begin(), cpy.substr(end+1, cpy.length()));

    while (end != 0 && end!= std::string::npos) {
        cpy = cpy.substr(0, cpy.find_last_of(delim));
        end = cpy.find_last_of(delim);
        output.insert(output.begin(), cpy.substr(end+1, cpy.length()));
    }
    return output;
}

std::string help() {
    std::string helpStr;
    helpStr += "OSD Disk Tool .oO Help Screen Oo.\n";
    helpStr += "-----------------------------------------------------------------------------------\n" ;
    helpStr += "* quit:                             Quit OSD Disk Tool\n";// Klar
    helpStr += "* format;                           Formats disk\n";//Klar
    helpStr += "* ls     <path>:                    Lists contents of <path>.\n";// Klar
    helpStr += "* create <path>:                    Creates a file and stores contents in <path>\n"; // Klar
    helpStr += "* cat    <path>:                    Dumps contents of <file>.\n"; // Klar
    helpStr += "* save   <real-file>:               Saves disk to <real-file>\n";
    helpStr += "* read   <real-file>:               Reads <real-file> onto disk\n";
    helpStr += "* rm     <file>:                    Removes <file>\n"; 
    helpStr += "* copy   <source>    <destination>: Copy <source> to <destination>\n";
    helpStr += "* append <source>    <destination>: Appends contents of <source> to <destination>\n";
    helpStr += "* rename <old-file>  <new-file>:    Renames <old-file> to <new-file>\n";
    helpStr += "* mkdir  <directory>:               Creates a new directory called <directory>\n"; // Klar
    helpStr += "* cd     <directory>:               Changes current working directory to <directory>\n"; // Klar
    helpStr += "* pwd:                              Get current working directory\n"; // Klar
    helpStr += "* help:                             Prints this help screen\n"; // Klar
    return helpStr;
}
