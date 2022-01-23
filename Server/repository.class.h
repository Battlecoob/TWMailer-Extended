#include <mutex>
#include <iostream>
#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <dirent.h>

#include "../Other/message.class.h"

class Repository
{
private:
    std::string _rootDirectory;

public:
    Repository();

    bool List(const std::string&); // LIST: Not Implemented
    bool Delete(const std::string&, const int&); // DELETE
    std::string Read(const std::string&, const int&); // READ
    
    const bool Exists(const std::string&);
    const std::string ReadFile(const std::string&);
    std::vector<Message> GetMessages(const std::string&);
    const std::vector<std::string> GetFileVector(const std::string&);
};
