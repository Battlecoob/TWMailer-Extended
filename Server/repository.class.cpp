#include "repository.class.h"
#include <fstream>

using std::string;

Repository::Repository()
{
    _rootDirectory = "./Database/";
}

const bool Repository::Exists(const string& path)
{
    struct stat attributes;
    /*
    stat() can obtain information about a file. return 0 if it exists and -1 if it doesn't
    https://pubs.opengroup.org/onlinepubs/009695399/functions/stat.html
    */
    if(stat(path.data(), &attributes) == 0)
        return true;
    return false;
}

std::string Repository::Read(const string& username, const int& number)
{
    std::string path = "";
    path += _rootDirectory;
    path += username + "/";

    if(!Exists(path))
        return "ERR";

    auto files = GetFileVector(path);
    std::string path2Read = path;
    path2Read += files.at(number - 1);

    if(!Exists(path2Read))
        return "ERR";
    
    std::string text = "OK\n";
    text += ReadFile(path2Read);
    return text;
}

bool Repository::Delete(const string& username, const int& number)
{
    std::string path = "";
    path += _rootDirectory;
    path += username + "/";

    if(!Exists(path))
        return false;

    std::cout << "Directory " << path << " exists" << std::endl;
    auto files = GetFileVector(path);

    std::string path2Delete = path;

    path2Delete += files.at(number - 1);
    std::cout << path2Delete << std::endl;

    if(!Exists(path2Delete))
        return false;
        
    remove(path2Delete.data());

    return true;

}

const string Repository::ReadFile(const string& path)
{
    string line;
    string content;
    std::ifstream file(path);

    if(file.is_open())
    {
        while(!file.eof())
        {
            std::getline(file, line);
            content.append(line).append("\n");
        }
    }

    return content;
}

const std::vector<string> Repository::GetFileVector(const string& path)
{
    struct dirent *file;
    DIR* directory = opendir(path.data());
    std::vector<string> fileVector;

    if(directory)
    {
        while ((file = readdir(directory)) != NULL)
        {
            if(file->d_type == DT_REG)
            {
                std::string tmp = file->d_name; // typecasten ganz wichtig...
                if(strcmp(tmp.data(), ".") && strcmp(tmp.data(), ".."))
                    fileVector.emplace_back(tmp);
            }
        }
    }
    
    closedir(directory);
    return fileVector;
}

std::vector<Message> Repository::GetMessages(const std::string& username)
{
    std::vector<Message> messages;
    std::string path = _rootDirectory + "/" + username;

    if(Exists(path))
    {
        std::cout << "Directory exists" << std::endl;
        auto files = GetFileVector(path);

        for(auto filePath : files)
        {
            std::string text = ReadFile(path + filePath);
            messages.emplace_back(text);
        }
    }

    return messages;
}