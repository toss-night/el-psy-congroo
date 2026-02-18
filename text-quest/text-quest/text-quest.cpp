#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

class Item {
private:
    std::string name, description;
    bool isInInventory;
    int id;
public:    
    Item(int i, const std::string nm, const std::string ds) 
        :name(nm.empty() ? "unknown" : nm), description(ds.empty() ? "unknown" : ds), isInInventory(false), id(i) {}

    virtual ~Item() = default;

    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    int getId() const { return id; }
    bool getIsInInventory() { return isInInventory; }

    void setName(const std::string& n) {
        if (!n.empty()) {
            name = n;
        }
    }
    void setDescription(const std::string& ds) {
        if (!ds.empty()) description = ds;
    }
    void setId(int i) { id = i; }
    void setIsInInventory(bool z) { isInInventory = z; }

    virtual std::string getType() const = 0;
    virtual int getDmg() const = 0;
    virtual int getHeal() const = 0;
          
    virtual void info() const {
        std::cout << "id: " << getId() << "\nname: " << getName() << "\ndescription: "
            << getDescription() << "\n";
    }    
};

class Weapon : public Item {
private:
    int dmg;   
public:   
    Weapon(int i, int dm, const std::string nm, const std::string ds) 
        :Item(i, nm, ds), dmg(dm) {}

    std::string getType() const override { return "weapon"; }
    int getDmg() const override { return dmg; }
    int getHeal() const override { return 0; }

    void setDamage(int i) { dmg = i; }

    void info() const {
        Item::info();
        std::cout <<"damage: " << getDmg() << "\n";
    }
};

class Potion : public Item {
private:
    int healHp;
public:
    Potion(int i,int hh, const std::string nm, const std::string ds) 
        :Item(i+1000, nm, ds), healHp(hh) {}

    std::string getType() const override { return "potion"; }
    int getDmg() const override { return 0; }
    int getHeal() const override { return healHp; }

    void setHeal(int h) { healHp = h; }

    void info() const {
        Item::info();
        std::cout << "heal: " << getHeal() << "\n";
    }
};

class Location {
private:
    int id;   
    std::string name, description;
public:
    Location() :name("unknown") {}
    Location(int i, const std::string& n, const std::string d) 
        : id(i), name(n.empty() ? "unknown" : n), description(d.empty() ? "unknown" : d) {}

    int getId() const { return id; }
    std::string getName() { return name; }
    std::string getDescription() { return description; }

    void setId(int i) { id = i; }
    void setName(const std::string& n) { 
        if (!n.empty()) {
            name = n;
        }
    } 
    void setDescription(const std::string& ds) {
        if (!ds.empty()) description = ds;
    }
};

class Player {
private:
    std::string name;
    int hp, maxHp, dmg;    
    std::vector<std::shared_ptr<Item>> inventory;  
    Location locaNow;
    Weapon useWeapon;
public:
    Player(const std::string& nm)
        : name(nm.empty() ? "unknown" : nm), hp(100), dmg(5), useWeapon(0, 5, "nothing", "nothing"),
        locaNow(0, "old battlefield", "old battlefield."), maxHp(100) { }

    std::string getName() { return name; }
    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getDmg() const { return dmg; }
    const std::vector<std::shared_ptr<Item>> getInventory() { return inventory; }
    Location getLocaNow() { return locaNow; }
    Weapon getWeapon() { return useWeapon; }
    
    void setName(const std::string& nm) {
        if (!nm.empty()) {
            name = nm;
        }
    }
    void setHp(const int& h) {
        hp = h;
    }
    void setMaxHp(const int& h) {
        maxHp = h;
    }
    void setDmg(const int& dm) {
        dmg = dm;
    }   
    void setLocaNow(const Location& loca) {
        locaNow = loca;
    }
    void setWeapon(std::shared_ptr<Item> wp) {
        Weapon* weapon = dynamic_cast<Weapon*>(wp.get());
        useWeapon = *weapon;
    }

    void addItem(std::shared_ptr<Item> item) {
       
        inventory.push_back(std::move(item));
        
    }
    bool selectWeapon(int i) {
        bool isSelected = false;
        for (auto& item : inventory) {
            if (item->getType()=="weapon" && item->getId() == i) {
                std::cout <<"you selected |" << item->getName() << "|.\n";
                isSelected = true;
                setWeapon(item);               
            }           
        }
        return isSelected;
    }
    bool usePotion(int i) {
        bool isSelected = false;
        for (auto& item : inventory) {
            if (item->getType() == "potion" && item->getId() == i) {
                std::cout << "you drink |" << item->getName() << "|...\n";
                isSelected = true;               
                setHp(getHp() + item->getHeal());
                std::cout << "you get " << item->getHeal() << " hp.\n";              
            }
        }     
        return isSelected;
    }
    void displayInv() {
        std::cout << "your inventory: \nweapons:\n";
        for (const auto &item : inventory) {
            if (item->getType() == "weapon") {
                std::cout << "[" << item->getId() << "] |" << item->getName() << "| " << item->getDescription() << item->getDmg() << " damage.\n";
            }
        }
        std::cout << "potions:\n";
        for (const auto& item : inventory) {
            if (item->getType() == "potion") {
                std::cout << "[" << item->getId() << "] |" << item->getName() << "| " << item->getDescription() << item->getHeal() << " hp.\n";
            }
        }
        std::cout << "=====================\n";
    }
    void takeDamage(int dm) {
        setHp(getHp() - dm);
        if (getHp() < 0) setHp(0);
    }
    void heal(int hl) {
        setHp(getHp() + hl);
        if (getHp() > getMaxHp()) setHp(getMaxHp());
    }
};

class Enemy {
private:
    int id, hp, dmg;
    std::string name, description;    
public:
    Enemy(int i, const std::string& nm, int h, int dm, const std::string& ds)
        :id(i), dmg(dm), hp(h), name(nm.empty() ? "unknown" : nm), description(ds.empty() ? "unknown" : ds) {}

    int getId() const { return id; }
    std::string getName() { return name; }
    std::string getDescription() { return description; }
    int getHp() const { return hp; }
    int getDmg() const { return dmg; }

    void setId(int i) { id = i; }
    void setName(const std::string& nm) {
        if (!nm.empty()) {
            name = nm;
        }
    }
    void setHp(const int& h) {
        hp = h;
    }
    void setDmg(const int& dm) {
        dmg = dm;
    }
    void setDescription(const std::string& ds) {
        if (!ds.empty()) description = ds;
    }

    void takeDamage(int dm) {
        setHp(getHp() - dm);
        if (getHp() < 0) setHp(0);
    }
    void heal(int hl) {
        setHp(getHp() + hl);       
    }

    bool randDoge() {

    }
};

void getLocationsFromFile(const std::string& filename, std::vector<Location>&locas) {
    std::ifstream file(filename);   
    std::string line, name, description;
    if (!file.is_open()) {
        throw std::runtime_error("file not open.");
    }         
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line == "end") break;
        try {
            int id;
            size_t pip1 = line.find('|');
            if (pip1 == std::string::npos) continue;
            size_t pip2 = line.find('|', pip1 + 1);
            if (pip2 == std::string::npos) continue;
            id = std::stoi(line.substr(0, pip1));
            name = line.substr(pip1 + 1, pip2 - pip1 - 1);
            description = line.substr(pip2 + 1);
            locas.emplace_back(id, name, description);
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка парсинга строки: \"" << line << "\". " << e.what() << std::endl;
            continue;
        }
    }
}
void getWeaponsFromFile(const std::string& filename, std::vector<Weapon>& weapons) {
    std::ifstream file(filename);
    std::string line, name, description; 
    if (!file.is_open()) {
        throw std::runtime_error("file not open.");
    }      
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line == "end") break;
        try {
            int id, damage;
            size_t pip1 = line.find('|');
            if (pip1 == std::string::npos) continue;
            size_t pip2 = line.find('|', pip1+1);
            if (pip2 == std::string::npos) continue;
            size_t pip3 = line.find('|', pip2+1);
            if (pip3 == std::string::npos) continue;            
            id = std::stoi(line.substr(0, pip1));
            damage = std::stoi(line.substr(pip1 + 1, pip2 - pip1 - 1));            
            name = line.substr(pip2 + 1, pip3 - pip2 - 1);
            description = line.substr(pip3 + 1);
            weapons.emplace_back(id, damage, name, description);
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка парсинга строки: \"" << line << "\". " << e.what() << std::endl;
            continue; 
        }
    }
}
void getPotionsFromFile(const std::string& filename, std::vector<Potion>& potions) {
    std::ifstream file(filename);
    std::string line, name, description;
    if (!file.is_open()) {
        throw std::runtime_error("file not open.");
    }
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line == "end") break;
        try {
            int id, heal;
            size_t pip1 = line.find('|');
            if (pip1 == std::string::npos) continue;
            size_t pip2 = line.find('|', pip1 + 1);
            if (pip2 == std::string::npos) continue;
            size_t pip3 = line.find('|', pip2 + 1);
            if (pip3 == std::string::npos) continue;
            id = std::stoi(line.substr(0, pip1));
            heal = std::stoi(line.substr(pip1 + 1, pip2 - pip1 - 1));
            name = line.substr(pip2 + 1, pip3 - pip2 - 1);
            description = line.substr(pip3 + 1);
            potions.emplace_back(id, heal, name, description);
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка парсинга строки: \"" << line << "\". " << e.what() << std::endl;
            continue;
        }
    }
}
void getDataFromLocalFiles(std::vector<Location>& locations, std::vector<Weapon>& weapons, std::vector<Potion>& potions) {        
    getLocationsFromFile("data/locations.txt", locations);
    getWeaponsFromFile("data/weapons.txt", weapons);
    getPotionsFromFile("data/potions.txt", potions);
}

void game() {

}



int main() {
    setlocale(LC_ALL, "ru");
    std::vector<Weapon>aaa;
    getWeaponsFromFile("data/weapons.txt", aaa);
    for (Weapon www : aaa) {
        std::cout << www.getName() << "\n";
    }
}

