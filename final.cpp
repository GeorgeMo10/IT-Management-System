// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits> // For std::numeric_limits
#include <fstream>
#include <sstream>

// location class handles different locations of company IT
class Location {
private:
    int locationID;
    std::string name;
    std::string address;
    std::string type; // Physical, Virtual, Cloud-based

public:
    // Constructor 
    Location(int id, std::string n, std::string addr, std::string t)
        : locationID(id), name(std::move(n)), address(std::move(addr)), type(std::move(t)) {}

    // Accessor methods
    int getID() const { return locationID; }
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getType() const { return type; }

    // Method to display location details
    void displayDetails() const {
        std::cout << "Location ID: " << locationID << ", Name: " << name
            << ", Address: " << address << ", Type: " << type << std::endl;
    }

    // Static methods for managing locations
    static void addLocation(std::vector<Location>& locations);
    static void updateLocation(std::vector<Location>& locations);
    static void removeLocation(std::vector<Location>& locations);
    static void listLocations(const std::vector<Location>& locations);
};

//add location to list of locations
void Location::addLocation(std::vector<Location>& locations) {
    int id;
    std::string name, address, type;
    std::cout << "Enter Location ID: ";
    std::cin >> id;
    std::cout << "Enter Location Name: ";
    std::cin.ignore(); // ignore newline left in the input buffer
    std::getline(std::cin, name);
    std::cout << "Enter Address: ";
    std::getline(std::cin, address);
    std::cout << "Enter Type (Physical, Virtual, Cloud-based): ";
    std::getline(std::cin, type);

    locations.emplace_back(id, name, address, type);
    std::cout << "Location added successfully.\n";
}

//update locations 
void Location::updateLocation(std::vector<Location>& locations) {
    int id;
    std::cout << "Enter Location ID to update: ";
    std::cin >> id;
    for (auto& location : locations) {
        if (location.getID() == id) {
            std::cout << "Enter new Name: ";
            std::cin.ignore();
            std::getline(std::cin, location.name);
            std::cout << "Enter new Address: ";
            std::getline(std::cin, location.address);
            std::cout << "Enter new Type: ";
            std::getline(std::cin, location.type);
            std::cout << "Location updated successfully.\n";
            return;
        }
    }
    std::cout << "Location not found.\n";
}
//remove locations
void Location::removeLocation(std::vector<Location>& locations) {
    int id;
    std::cout << "Enter Location ID to remove: ";
    std::cin >> id;
    auto it = std::remove_if(locations.begin(), locations.end(),
        [id](const Location& location) { return location.getID() == id; });
    if (it != locations.end()) {
        locations.erase(it, locations.end());
        std::cout << "Location removed successfully.\n";
    }
    else {
        std::cout << "Location not found.\n";
    }
}

//list current locaitons

void Location::listLocations(const std::vector<Location>& locations) {
    std::cout << "Listing all locations:\n";
    for (const auto& location : locations) {
        location.displayDetails();
    }
}
// Role class
class Role {
private:
    std::string title;
    int level;

public:
    //construct
    Role(std::string title, int level) : title(std::move(title)), level(level) {}

    std::string getTitle() const { return title; }
    int getLevel() const { return level; }

    // Overloaded output operator for displaying Role information
    friend std::ostream& operator<<(std::ostream& os, const Role& role) {
        os << "Role: " << role.title << ", Level: " << role.level;
        return os;
    }
};

// Template class for Users
template<typename T>
class User {
private:
    std::string name;
    T role;

public:
    //construct
    User(std::string name, T role) : name(std::move(name)), role(std::move(role)) {}

    std::string getName() const { return name; }
    T getRole() const { return role; }

    // Overloaded output operator for User objects
    friend std::ostream& operator<<(std::ostream& os, const User<T>& user) {
        os << "User: " << user.name << ", " << user.role;
        return os;
    }

    // Comparison operator for sorting
    bool operator<(const User& other) const {
        return name < other.name;
    }
};
//vector to store
//standard temp libary 
std::vector<User<Role>> users;

// Function to add a new user
void addUser() {
    std::string name, title;
    int level;
    std::cout << "Enter user's name: ";
    std::cin >> name;
    std::cout << "Enter role title: ";
    std::cin >> title;
    std::cout << "Enter role level: ";
    std::cin >> level;

    User<Role> newUser(name, Role(title, level));
    users.push_back(newUser);
    std::cout << "User added successfully.\n";
}

//sorting algo
//sorts users
//sorting function
void bubbleSortUsers() {
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 0; i < users.size() - 1; i++) {
            if (users[i].getName() > users[i + 1].getName()) {
                std::swap(users[i], users[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

//lists users and calls sorting function

void listUsers() {
    bubbleSortUsers();  // Using custom Bubble Sort instead of std::sort()
    std::cout << "Listing all users:\n";
    for (const auto& user : users) {
        std::cout << user << std::endl;
    }
}
//update user 
//performs seraching
void updateUser() {
    std::string name, title;
    int level;
    std::cout << "Enter the name of the user to update: ";
    std::cin >> name;
    for (auto& user : users) {
        if (user.getName() == name) {
            std::cout << "Enter new role title: ";
            std::cin >> title;
            std::cout << "Enter new role level: ";
            std::cin >> level;
            user = User<Role>(name, Role(title, level));
            std::cout << "User updated successfully.\n";
            return;
        }
    }
    std::cout << "User not found.\n";
}
//disable user
void deactivateUser() {
    std::string name;
    std::cout << "Enter the name of the user to deactivate: ";
    std::cin >> name;
    auto it = std::remove_if(users.begin(), users.end(), [&name](const User<Role>& user) {
        return user.getName() == name;
        });
    if (it != users.end()) {
        users.erase(it, users.end());
        std::cout << "User deactivated successfully.\n";
    }
    else {
        std::cout << "User not found.\n";
    }
}




// Forward declaration of Software class

class Software;

// Global storage for all software licenses

std::vector<std::shared_ptr<Software>> softwareLicenses;

//Base class for all software/licnese
class Software {
protected:
    int licenseID;
    std::string name;
    bool isActive;

public:
    Software(int id, std::string n, bool active) : licenseID(id), name(std::move(n)), isActive(active) {}
    virtual ~Software() {}

    virtual void displayDetails() const = 0; // Pure virtual function for displaying details
    int getLicenseID() const { return licenseID; }
    void setActive(bool active) { isActive = active; }  // Setter for isActive

};
// Derived class for Operating Systems
//polymorphism
class OperatingSystem : public Software {
public:
    OperatingSystem(int id, std::string n, bool active) : Software(id, n, active) {}

    void displayDetails() const override {
        std::cout << "Operating System ID: " << licenseID << ", Name: " << name << ", Status: " << (isActive ? "Active" : "Inactive") << std::endl;
    }
};
// Derived class for Business Applications

class BusinessApplication : public Software {
public:
    BusinessApplication(int id, std::string n, bool active) : Software(id, n, active) {}

    void displayDetails() const override {
        std::cout << "Business Application ID: " << licenseID << ", Name: " << name << ", Status: " << (isActive ? "Active" : "Inactive") << std::endl;
    }
};
// Derived class for Utility Software

class UtilitySoftware : public Software {
public:
    UtilitySoftware(int id, std::string n, bool active) : Software(id, n, active) {}

    void displayDetails() const override {
        std::cout << "Utility Software ID: " << licenseID << ", Name: " << name << ", Status: " << (isActive ? "Active" : "Inactive") << std::endl;
    }
};
// Function to register new software
//exception handling
void registerSoftware() {
    try {
        int type, id;
        std::string name;
        bool active;
        std::cout << "Enter software type (1-Operating System, 2-Business Application, 3-Utility Software): ";
        std::cin >> type;
        if (std::cin.fail() || type < 1 || type > 3) throw std::invalid_argument("Invalid software type entered.");

        std::cout << "Enter License ID: ";
        std::cin >> id;
        if (std::cin.fail()) throw std::invalid_argument("Invalid License ID format.");

        std::cout << "Enter Name: ";
        std::cin >> name;
        if (name.empty()) throw std::invalid_argument("Name cannot be empty.");

        std::cout << "Is active (1 for Yes, 0 for No): ";
        std::cin >> active;
        if (std::cin.fail()) throw std::invalid_argument("Invalid active status entered.");

        // Based on the type, create the appropriate software instance
        switch (type) {
        case 1:
            softwareLicenses.push_back(std::make_shared<OperatingSystem>(id, name, active));
            break;
        case 2:
            softwareLicenses.push_back(std::make_shared<BusinessApplication>(id, name, active));
            break;
        case 3:
            softwareLicenses.push_back(std::make_shared<UtilitySoftware>(id, name, active));
            break;
        default:
            std::cout << "Invalid software type!" << std::endl;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to the next line
    }
}

//list current software
void listSoftwareLicenses() {
    std::cout << "Listing all registered software licenses:\n";
    for (const auto& software : softwareLicenses) {
        software->displayDetails();
        std::cout << std::endl;
    }
}
// Function to update details of a software license
void updateSoftwareLicense(int licenseId) {
    bool found = false;
    for (auto& software : softwareLicenses) {
        if (software->getLicenseID() == licenseId) {
            std::cout << "Current Details of Software:\n";
            software->displayDetails();

            // Update active status
            bool newActiveStatus;
            std::cout << "Enter new active status (1 for active, 0 for inactive): ";
            std::cin >> newActiveStatus;
            software->setActive(newActiveStatus);



            std::cout << "Software details updated successfully!\n";
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "No software found with ID: " << licenseId << std::endl;
    }
}
// Function to remove expired licenses
void removeSoftwareLicense() {
    int licenseIdToRemove;
    bool found = false;

    // List all software licenses with their details
    std::cout << "Here are all registered software licenses:\n";
    for (auto& software : softwareLicenses) {
        software ->displayDetails();
    }

    // Ask user for the ID of the software license to remove
    std::cout << "Enter the License ID of the software you want to remove: ";
    std::cin >> licenseIdToRemove;

    // Attempt to find and remove the specified license

    //memory  allocation
    auto it = std::remove_if(softwareLicenses.begin(), softwareLicenses.end(),
        [licenseIdToRemove](const std::shared_ptr<Software>& software) {
            return software->getLicenseID() == licenseIdToRemove;
        });

    if (it != softwareLicenses.end()) {
        softwareLicenses.erase(it, softwareLicenses.end());
        std::cout << "Software license removed successfully.\n";
        found = true;
    }

    // If no software is found with the given ID, inform the user
    if (!found) {
        std::cout << "No software found with ID: " << licenseIdToRemove << std::endl;
    }
}

// Base class for all assets
class Asset {
protected:
    int assetID;
    std::string name;
    bool isActive;

public:

    //construct
    Asset(int id, std::string n, bool active) : assetID(id), name(std::move(n)), isActive(active) {}
    virtual ~Asset() {}

    virtual void displayDetails() const = 0;
    int getAssetID() const { return assetID; }
    const std::string& getName() const { return name; }
    bool getIsActive() const { return isActive; }
};
//comp

class Specifications {
public:
    std::string processor;
    int memory;
    int storage;

    Specifications(std::string proc, int mem, int stor) : processor(std::move(proc)), memory(mem), storage(stor) {}

    void displaySpecs() const {
        std::cout << "Processor: " << processor << ", Memory: " << memory << " GB, Storage: " << storage << " GB" << std::endl;
    }
};

//derived 
class Computer : public Asset {
private:
    Specifications specs;

public:
    //construct
    Computer(int id, std::string name, bool active, Specifications spec)
        : Asset(id, std::move(name), active), specs(std::move(spec)) {}

    void displayDetails() const override {
        std::cout << "Computer ID: " << getAssetID() << "\nName: " << getName() << "\nStatus: " << (getIsActive() ? "Active" : "Inactive") << std::endl;
        specs.displaySpecs();
    }

    const Specifications& getSpecs() const { return specs; }

    void updateSpecs(const std::string& processor, int memory, int storage) {
        specs = Specifications(processor, memory, storage);
    }
};

class Printer : public Asset {
private:
    std::string type;

public:
    Printer(int id, std::string name, bool active, std::string type)
        : Asset(id, std::move(name), active), type(std::move(type)) {}

    void displayDetails() const override {
        std::cout << "Printer ID: " << getAssetID() << "\nName: " << getName() << "\nType: " << type << "\nStatus: " << (getIsActive() ? "Active" : "Inactive") << std::endl;
    }

    const std::string& getType() const { return type; }
};

class Router : public Asset {
public:
    Router(int id, std::string name, bool active) : Asset(id, std::move(name), active) {}

    void displayDetails() const override {
        std::cout << "Router ID: " << getAssetID() << "\nName: " << getName() << "\nStatus: " << (getIsActive() ? "Active" : "Inactive") << std::endl;
    }
};

// Global storage for all assets, licenses
std::vector<std::shared_ptr<Asset>> assets;



// Function to register new hardware
void registerHardware() {
    int type, id;
    std::string name, processor, typeStr;
    int memory, storage;
    bool active;

    std::cout << "Enter hardware type (1-Computer, 2-Printer, 3-Router): ";
    std::cin >> type;
    std::cout << "Enter ID: ";
    std::cin >> id;
    std::cout << "Enter Name: ";
    std::cin >> name;
    std::cout << "Is active (1 for Yes, 0 for No): ";
    std::cin >> active;

    switch (type) {
    case 1: // Computer
        std::cout << "Enter Processor: ";
        std::cin >> processor;
        std::cout << "Enter Memory (GB): ";
        std::cin >> memory;
        std::cout << "Enter Storage (GB): ";
        std::cin >> storage;
        assets.push_back(std::make_shared<Computer>(id, name, active, Specifications(processor, memory, storage)));
        break;
    case 2: // Printer
        std::cout << "Enter Type (e.g., Laser, Inkjet): ";
        std::cin >> typeStr;
        assets.push_back(std::make_shared<Printer>(id, name, active, typeStr));
        break;
    case 3: // Router
        assets.push_back(std::make_shared<Router>(id, name, active));
        break;
    default:
        std::cout << "Invalid hardware type!" << std::endl;
    }
}

// Function to update specifications of a computer
void updateSpecifications(int assetId) {
    for (auto& asset : assets) {
        if (auto comp = std::dynamic_pointer_cast<Computer>(asset)) {
            if (comp->getAssetID() == assetId) {
                std::string processor;
                int memory, storage;
                std::cout << "Enter new Processor: ";
                std::cin >> processor;
                std::cout << "Enter new Memory (GB): ";
                std::cin >> memory;
                std::cout << "Enter new Storage (GB): ";
                std::cin >> storage;
                comp->updateSpecs(processor, memory, storage);
                std::cout << "Specifications updated successfully!" << std::endl;
                return;
            }
        }
    }
    std::cout << "Computer with ID " << assetId << " not found." << std::endl;
}

// Function to decommission an asset
void decommissionAsset(int assetId) {
    auto it = std::remove_if(assets.begin(), assets.end(), [assetId](const std::shared_ptr<Asset>& asset) {
        return asset->getAssetID() == assetId;
        });
    assets.erase(it, assets.end());
    std::cout << "Asset decommissioned successfully!" << std::endl;
}

// Function to list all assets
void listAllAssets() {
    std::cout << "Listing all registered assets:\n";
    for (const auto& asset : assets) {
        asset->displayDetails();
        std::cout << std::endl;
    }
}

//save txt to file
void saveHardwareToFile() {
    std::ofstream file("C:\Users\15869\Desktop\ConsoleApplication2\hardware.txt", std::ios::trunc); // Open in truncate mode to overwrite
    for (const auto& asset : assets) {
        if (auto comp = std::dynamic_pointer_cast<Computer>(asset)) {
            file << "Computer," << comp->getAssetID() << "," << comp->getName() << ","
                << comp->getIsActive() << "," << comp->getSpecs().processor << ","
                << comp->getSpecs().memory << "," << comp->getSpecs().storage << "\n";
        }
        else if (auto printer = std::dynamic_pointer_cast<Printer>(asset)) {
            file << "Printer," << printer->getAssetID() << "," << printer->getName() << ","
                << printer->getIsActive() << "," << printer->getType() << "\n";
        }
        else if (auto router = std::dynamic_pointer_cast<Router>(asset)) {
            file << "Router," << router->getAssetID() << "," << router->getName() << ","
                << router->getIsActive() << "\n";
        }
    }
    file.close();
}
//reading and writing data to file
// Function to load hardware from a file
void loadHardwareFromFile(std::vector<std::shared_ptr<Asset>>& assets) {
    std::ifstream file("C:\Users\15869\Desktop\ConsoleApplication2\hardware.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> parts;
        std::string part;
        while (std::getline(iss, part, ',')) {
            parts.push_back(part);
        }

        int id = std::stoi(parts[1]);
        std::string name = parts[2];
        bool isActive = parts[3] == "1";
        if (parts[0] == "Computer") {
            Specifications specs(parts[4], std::stoi(parts[5]), std::stoi(parts[6]));
            assets.push_back(std::make_shared<Computer>(id, name, isActive, specs));
        }
        else if (parts[0] == "Printer") {
            assets.push_back(std::make_shared<Printer>(id, name, isActive, parts[4]));
        }
        else if (parts[0] == "Router") {
            assets.push_back(std::make_shared<Router>(id, name, isActive));
        }
    }
    file.close();
}

// Main function with nested menu-driven interface 
int main() {
    int mainChoice = 0;
    loadHardwareFromFile(assets);


    while (mainChoice != 5) {  
        std::cout << "Select category:\n";
        std::cout << "1-Hardware\n";
        std::cout << "2-Software\n";
        std::cout << "3-User Account Management\n";
        std::cout << "4-Location Management\n";  
        std::cout << "5-Exit\n";  // Ensuring Exit remains the last option
        std::cin >> mainChoice;

        switch (mainChoice) {
        case 1: {
            int hardwareChoice = 0;
            while (hardwareChoice != 5) {
                std::cout << "Hardware Management:\n";
                std::cout << "1-Register Hardware\n";
                std::cout << "2-Update Hardware\n";
                std::cout << "3-Decommission Hardware\n";
                std::cout << "4-List All Hardware\n";
                std::cout << "5-Return to Main Menu\n";
                std::cin >> hardwareChoice;
                switch (hardwareChoice) {
                case 1:
                    registerHardware();
                    break;
                case 2:
                    listAllAssets();
                    int idToUpdate;
                    std::cout << "Enter the Hardware ID to update: ";
                    std::cin >> idToUpdate;
                    updateSpecifications(idToUpdate);
                    break;
                case 3:
                    listAllAssets();
                    int idToDecommission;
                    std::cout << "Enter the Hardware ID to decommission: ";
                    std::cin >> idToDecommission;
                    decommissionAsset(idToDecommission);
                    break;
                case 4:
                    listAllAssets();
                    break;
                case 5:
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }
            }
            break;
        }
        case 2: {
            int softwareChoice = 0;
            while (softwareChoice != 5) {
                std::cout << "Software License Management:\n";
                std::cout << "1-Register Software\n";
                std::cout << "2-Update Software Details\n";
                std::cout << "3-Remove Expired Licenses\n";
                std::cout << "4-List All Software\n";
                std::cout << "5-Return to Main Menu\n";
                std::cin >> softwareChoice;

                switch (softwareChoice) {
                case 1:
                    registerSoftware();
                    break;
                case 2:
                    listSoftwareLicenses();
                    int licenseToUpdate;
                    std::cout << "Enter the Software License ID to update: ";
                    std::cin >> licenseToUpdate;
                    updateSoftwareLicense(licenseToUpdate);
                    break;
                case 3:
                    removeSoftwareLicense();
                    break;
                case 4:
                    listSoftwareLicenses();
                    break;
                case 5:
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }
            }
            break;
        }
        case 3: {
            int userChoice = 0;
            while (userChoice != 5) {
                std::cout << "User Account Management:\n";
                std::cout << "1-Add User\n";
                std::cout << "2-Update User\n";
                std::cout << "3-Deactivate User\n";
                std::cout << "4-List All Users\n";
                std::cout << "5-Return to Main Menu\n";
                std::cin >> userChoice;

                switch (userChoice) {
                case 1:
                    addUser();
                    break;
                case 2:
                    updateUser();
                    break;
                case 3:
                    deactivateUser();
                    break;
                case 4:
                    listUsers();
                    break;
                case 5:
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }
            }
            break;
        }
case 4: {
    int locationChoice = 0;
    std::vector<Location> locations;  // Vector to store locations
    while (locationChoice != 5) {
        std::cout << "Location Management:\n";
        std::cout << "1-Add Location\n";
        std::cout << "2-Update Location\n";
        std::cout << "3-Remove Location\n";
        std::cout << "4-List All Locations\n";
        std::cout << "5-Return to Main Menu\n";
        std::cin >> locationChoice;

        switch (locationChoice) {
            case 1:
                Location::addLocation(locations);
                break;
            case 2:
                Location::updateLocation(locations);
                break;
            case 3:
                Location::removeLocation(locations);
                break;
            case 4:
                Location::listLocations(locations);
                break;
            case 5:
                break;  // Correctly returns to the main menu
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    break;
}
        case 5:
            saveHardwareToFile();
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    return 0;
}

