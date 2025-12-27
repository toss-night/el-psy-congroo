#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <chrono>

class FileHandle {
private:
    std::string fileName;   
    std::unique_ptr<std::ofstream> writerPtr;
    std::unique_ptr<std::ifstream> readerPtr;
    std::ifstream& getRead() {
        if (!readerPtr) {
            readerPtr = std::make_unique<std::ifstream>(fileName);
            if (!readerPtr->is_open()) {
                throw std::runtime_error("cannot open file\n");
            }
        }
        return *readerPtr;
    }
    std::ofstream& getWrite() {
        if (!writerPtr) {
            writerPtr = std::make_unique<std::ofstream>(fileName, std::ios::app);
            if (!writerPtr->is_open()) {
                throw std::runtime_error("cannot open file\n");
            }
        }
        return *writerPtr;
    }
    std::ofstream& getReWrite() {
        if (!writerPtr) {
            writerPtr = std::make_unique<std::ofstream>(fileName);
            if (!writerPtr->is_open()) {
                throw std::runtime_error("cannot open file\n");
            }
        }
        return *writerPtr;
    }
public:
    FileHandle()
        : fileName("unknown"), writerPtr(nullptr), readerPtr(nullptr) {}
    FileHandle(const std::string& nm)
        : fileName(!nm.empty() ? nm : "unknown"), writerPtr(nullptr), readerPtr(nullptr) {
    }
    ~FileHandle() {}
    void write(const std::string& text) {
        if (fileName == "unknown") {
            throw std::runtime_error("file dont have name!");
        }
        auto& writer = getWrite();       
        writer << text;
    }
    std::string getName() const { return fileName; }
    std::vector<std::string> readLines() {
        if (fileName == "unknown") {
            throw std::runtime_error("file dont have name!");
        }
        std::vector<std::string> lines;
        auto& reader = getRead();
        std::string line;
        while (std::getline(reader, line)) {           
            lines.push_back(line);
        }
        if (reader.fail() && !reader.eof()) {
            throw std::runtime_error("error reading file!");
        }
        return lines;
    }
    void clearFile() {
        if (fileName == "unknown") {
            throw std::runtime_error("file dont have name!");
        }
        auto& cleaner = getReWrite();
        cleaner << "";
    }
    void printFile() {
        if (fileName == "unknown") {
            throw std::runtime_error("file dont have name!");
        }
        std::vector<std::string>linez = readLines();
        for (std::string line : linez) {
            std::cout << line << "\n";
        }
    }
    std::string findStrByPartial(const std::string& text) {
        if (fileName == "unknown") {
            throw std::runtime_error("file dont have name!");
        }      
        std::vector<std::string> lines = readLines();
        auto it = std::find_if(lines.begin(), lines.end(), [&text](std::string line) { return line.find(text) != std::string::npos; });
        if (it != lines.end()) {
            return *it;
        }
        throw std::runtime_error("str not found!");
    }
    std::string readLinesInOneStr() {       
        if (fileName == "unknown") {
            throw std::runtime_error("file dont have name!");
        }
        auto& reader = getRead();     
        reader.seekg(0, std::ios::end);
        std::streampos posStr = reader.tellg();
        size_t sizeF = static_cast<size_t>(posStr);
        reader.seekg(0, std::ios::beg);
        std::string lines, line;
        if (sizeF > 0) {                   
            lines.reserve(sizeF + sizeF/5);
        }
        while (std::getline(reader, line)) {
            lines.append(line);
            lines.push_back('\n');
        }
        if (reader.fail() && !reader.eof()) {
            throw std::runtime_error("error reading file!");
        }
        reader.clear();
        return lines;
    }
    
};

auto timeNow() {
    return std::chrono::system_clock::now();
    
}
void command() {
    std::string com;
    std::map<std::chrono::time_point<std::chrono::system_clock>, std::string> history;
    std::vector<FileHandle> files;
    std::unordered_map<std::string, FileHandle> ffiles;
    while (com != "exit") {      
        std::cout << "enter command(write, read, open, list, history, exit): ";
        std::cin >> com;
        if (com == "write") {
            history[timeNow()] = "write";
            std::string name, text;
            std::cout << "\nenter name file for write: ";
            std::cin >> name;
            std::cout << "enter text for write in file: ";
            auto it = std::find_if(files.begin(), files.end(), [&name](const FileHandle& fh) {return fh.getName() == name; });
            
        }
        if (com == "read") {
            history[timeNow()] = "read";
            std::string name, text;
            std::cout << "\nenter name file for read: ";            
            std::cin >> name;
            
        }
        if (com == "open") {
            history[timeNow()] = "open";
            std::string name;
            std::cout << "\nenter name file for open: ";
            std::cin >> name;            
            FileHandle file(name);  
            files.push_back(file);
        }
        if (com == "list") {
            history[timeNow()] = "list";
            std::cout << "\nlist of open files:\n";
            for (FileHandle& file : files) {
                std::cout << file.getName() << "\n";
            }
        }
        if (com == "history") {           
            history[timeNow()] = "history";
            std::cout << "\nhistory of commands:\n";
            for (auto& [key, value] : history) {
                std::cout << key << " -> " << value << "\n";
            }
        }
        std::cout << "\n";
    }
}


int main() {        
    command();
   
    
    return 0;
}