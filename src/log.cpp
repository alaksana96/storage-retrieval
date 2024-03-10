#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

class SimpleLogDatabase
{
public:
    void load_file()
    {
        std::ifstream fileIn("log.txt");
        std::string line;
        while (std::getline(fileIn, line))
        {
            std::string key = line.substr(0, line.find("|") - 1);
            index[key] = latestOffset;
            latestOffset += line.size() + 1;
        }
        fileIn.close();

        print_index();
    }

    void print_index()
    {
        for (auto const &x : index)
        {
            std::cout << x.first << " " << x.second << std::endl;
        }
    }

    void set_key(std::string key, std::string value)
    {
        std::ofstream fileOut("log.txt", std::ios::app);
        std::string line = key + " | " + value;
        fileOut << line << std::endl;

        index[key] = latestOffset;
        latestOffset += line.size() + 1;

        fileOut.close();
    }

    void get_key(std::string key)
    {
        if (index.find(key) == index.end())
        {
            std::cout << "Key not found" << std::endl;
            return;
        }

        std::ifstream fileIn("log.txt");
        std::string line;

        fileIn.seekg(index[key]);
        std::getline(fileIn, line);

        std::cout << line << std::endl;

        fileIn.close();
    }

private:
    int latestOffset = 0;
    std::unordered_map<std::string, int> index;
};

int main()
{
    SimpleLogDatabase log;
    log.load_file();

    log.set_key("bigKey", "Hello This is  really long value!");

    log.get_key("key1");
    log.get_key("key2");
    log.get_key("bigKey");

    log.set_key("bigKey", "New Value for the Big Key");
    log.get_key("bigKey");
}