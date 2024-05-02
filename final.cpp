// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits> // For std::numeric_limits




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

void registerSoftware() {
    int type, id;
    std::string name;
    bool active;
    std::cout << "Enter software type (1-Operating System, 2-Business Application, 3-Utility Software): ";
    std::cin >> type;
    std::cout << "Enter License ID: ";
    std::cin >> id;
    std::cout << "Enter Name: ";
    std::cin >> name;
    std::cout << "Is active (1 for Yes, 0 for No): ";
    std::cin >> active;

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
    Asset(int id, std::string n, bool active) : assetID(id), name(std::move(n)), isActive(active) {}
    virtual ~Asset() {}

    virtual void displayDetails() const = 0; // Pure virtual function for displaying details
    int getAssetID() const { return assetID; }
};

// Class to handle specifications for computers
class Specifications {
private:
    std::string processor;
    int memory; // in GB
    int storage; // in GB

public:
    Specifications(std::string proc, int mem, int stor) : processor(std::move(proc)), memory(mem), storage(stor) {}

    void displaySpecs() const {
        std::cout << "Processor: " << processor << ", Memory: " << memory << " GB, Storage: " << storage << " GB" << std::endl;
    }
};

// Derived class from Asset for Computers
class Computer : public Asset {
private:
    Specifications specs;

public:
    Computer(int id, std::string name, bool active, Specifications spec)
        : Asset(id, std::move(name), active), specs(std::move(spec)) {}

    void displayDetails() const override {
        std::cout << "Computer ID: " << assetID << "\nName: " << name << "\nStatus: " << (isActive ? "Active" : "Inactive") << std::endl;
        specs.displaySpecs();
    }

    void updateSpecs(const std::string& processor, int memory, int storage) {
        specs = Specifications(processor, memory, storage);
    }
};

// Derived class from Asset for Printers
class Printer : public Asset {
private:
    std::string type; // e.g., Laser, Inkjet

public:
    Printer(int id, std::string name, bool active, std::string type)
        : Asset(id, std::move(name), active), type(std::move(type)) {}

    void displayDetails() const override {
        std::cout << "Printer ID: " << assetID << "\nName: " << name << "\nType: " << type << "\nStatus: " << (isActive ? "Active" : "Inactive") << std::endl;
    }
};

// Derived class from Asset for Routers
class Router : public Asset {
public:
    Router(int id, std::string name, bool active) : Asset(id, std::move(name), active) {}

    void displayDetails() const override {
        std::cout << "Router ID: " << assetID << "\nName: " << name << "\nStatus: " << (isActive ? "Active" : "Inactive") << std::endl;
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


// Main function with nested menu-driven interface
int main() {
    int mainChoice = 0;
    while (mainChoice != 3) {
        std::cout << "Select category:\n";
        std::cout << "1-Hardware\n2-Software\n3-Exit\n";
        std::cin >> mainChoice;

        switch (mainChoice) {
        case 1: {
            int hardwareChoice = 0;
            while (hardwareChoice != 5) {
                std::cout << "Hardware Management:\n";
                std::cout << "1-Register Hardware\n2-Update Hardware\n3-Decommission Hardware\n4-List All Hardware\n5-Return to Main Menu\n";
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
                std::cout << "1-Register Software\n2-Update Software Details\n3-Remove Expired Licenses\n4-List All Software\n5-Return to Main Menu\n";
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
        case 3:
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
