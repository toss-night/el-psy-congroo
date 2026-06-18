#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

void parsFileInVector(std::vector<std::string>& points, const std::string& fileName) {
    std::ifstream file(fileName);
    std::vector<std::string> lines;
    std::string line;
    points.clear();
    if (!file.is_open()) throw std::runtime_error("cannot open file\n");
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        lines.push_back(line);
    }
    for (std::string line : lines) {
        size_t pos = line.find('.') + 1;
        if (pos != std::string::npos) {
            std::string point = line.substr(pos + 1);
            points.push_back(point);
        }
    }
}
void writeVectorInFile(std::vector<std::string>& points, const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) throw std::runtime_error("cannot open file\n");
    for (int i = 0; i < points.size(); ++i) {
        file << i << ". " << points[i] << "\n";
    }
}
void addPoint(std::vector<std::string>& points) {
    std::string name;
    int tier;
    std::cout << "название нового элемента: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    bool isExist = false;
    for (std::string point : points) {
        if (point == name) {
            isExist = true;
            break;
        }
    }
    if (isExist) {
        std::cout << "это название уже существует.\n";
    }
    else {
        std::cout << "номер элемента \"" << name << "\": ";
        std::cin >> tier;
        if (tier < 0) {
            points.insert(points.begin(), name);
            tier = 0;
        }
        else if (tier >= points.size()) {
            tier = points.size();
            points.insert(points.begin() + tier, name);
        }
        else {
            points.insert(points.begin() + tier, name);
        }
        std::cout << "элемент \"" << name << "\" успешно добавлен на " << tier << " место.\n";
    }
}
void deletePoint(std::vector<std::string>& points) {
    int id;
    std::string name;
    std::cout << "номер для удаления: ";
    std::cin >> id;
    if (id >= points.size() || id < 0) {
        std::cout << "этого названия не существует.\n";
    }
    else {
        name = points[id];
        points.erase(points.begin() + id);
        std::cout << "элемент \"" << name << "\" успешно удален.\n";
    }
}
void printTierList(std::vector<std::string>& points) {
    if (!points.empty()) {
        for (int i = 0; i < points.size(); ++i) {
            std::cout << i << ". " << points[i] << "\n";
        }
    }
    else {
        std::cout << "названий пока нет.\n";
    }
}
void commands(const std::string& fileName) {
    int command = -1;
    std::vector<std::string>points;
    parsFileInVector(points, fileName);
    while (command != 0) {
        std::cout << "доступные команды: вывести список(1), добавить название(2), удалить название(3), выход(0).\nвведите команду: ";
        std::cin >> command;
        switch (command) {
        case(1):
            printTierList(points);
            break;
        case(2):
            addPoint(points);
            break;
        case(3):
            deletePoint(points);
            break;
        case(0):
            break;
        default:
            std::cout << "command not found.\n";
            break;
        }
        std::cout << "\n";
        writeVectorInFile(points, fileName);
    }
}

int main() {

    return 0;
}