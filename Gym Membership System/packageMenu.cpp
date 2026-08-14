#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// Package status enum
enum package_status {
    Active,
    Inactive
};

// Helper function to render enum as text
string statusToString (package_status status) {
    return (status == Active) ? "Active" : "Inactive";
}

// Package structure
struct GymPackage {
    string packageID;
    string packageName;
    double price;
    int durationDays;
    package_status packageStatus;
};

// Function prototypes
void displayHeader(string title);
void packageMenu();
void clearInputBuffer();
int getMenuChoice(int low, int high);

void addPackage();
void updatePackage();
void deletePackage();
void searchPackage();
void displayAllPackages();
void package();

// File I/O Function Prototypes
void loadPackageFromFile();
void savePackageToFile();

// Display header
void displayHeader(string title) {
    cout << "\n=====================================================================\n";
    cout << "\t\t\t" << title << endl;
    cout << "=====================================================================\n\n";
}

// Display package menu
void packageMenu() {
    cout << "1. Add Package" << endl;
    cout << "2. Update Package" << endl;
    cout << "3. Delete Package" << endl;
    cout << "4. Search Package" << endl;
    cout << "5. Display All Packages" << endl;
    cout << "6. Exit" << endl;
}

// clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// Input choice and validation
int getMenuChoice (int low, int high) {
    int choice;
    bool valid = false;
    while (!valid) {
        cout << "\nPlease enter your choice (" << low << "-" << high << "): ";
        cin >> choice;

        if (choice >= low && choice <= high) {
            valid = true;
        }
        else {
            cout << " Invalid Input ! Try again." << endl;
            clearInputBuffer();
        }
    }
    return choice;
}

// Static data structures
const int maxPackages = 50;
GymPackage packages [maxPackages];
int packageCount = 0;

void loadPackageFromFile() {
    ifstream inData;
    inData.open ("PackageData.txt");

    if (!inData) {
        packages[0] = {"1001", "BasicPackage", 29.99, 30, Active};
        packages[1] = {"1002", "StandardPackage", 49.99, 60, Active};
        packages[2] = {"1003", "PremiumPackage", 69.99, 90, Active};
        packages[3] = {"1004", "StudentPackage", 19.99, 30, Active};
        packageCount = 4;

        savePackageToFile();
        return;
    }

    packageCount = 0;
    int statusInt;

    inData >> packages[packageCount].packageID;
    while (!inData.eof() && packageCount < maxPackages) {
        inData.ignore();
        getline(inData, packages[packageCount].packageName);
        inData >> packages[packageCount].price;
        inData >> packages[packageCount].durationDays;
        inData >> statusInt;

        packages[packageCount].packageStatus = (statusInt == 0) ? Active : Inactive;
        packageCount++;

        inData >> packages[packageCount].packageID;
    }

    inData.close();
}

// Save data to file
void savePackageToFile() {
    ofstream outData;
    outData.open("PackageData.txt");

    if (!outData) {
        cout << "[ERROR] Error opening file ! " << endl;
        return;
    }

    for (int i = 0; i < packageCount; i++) {
        outData << packages[i].packageID << endl;
        outData << packages[i].packageName << endl;
        outData << packages[i].price << endl;
        outData << packages[i].durationDays << endl;
        outData << static_cast<int> (packages[i].packageStatus) << endl;
    }

    outData.close();
}

// Validation ID
bool isDuplicateID(string id) {
    for (int i = 0; i < packageCount; i++) {
        if (packages[i].packageID == id) {
            return true;
        }
    }
    return false;
}

// Add package
void addPackage() {
    displayHeader ("ADD NEW PACKAGE");
    if (packageCount >= maxPackages) {
        cout << "Cannot add more packages. Maximum limit reached." << endl;
        return;
    }
    GymPackage newPackage;

    // Validation Duplicate ID
    while (true) {
        cout << "Enter package ID : ";
        cin >> newPackage.packageID;
        if (isDuplicateID(newPackage.packageID)) {
            cout << "[ERROR] Duplicate Package ID ! Please Enter a unique ID." << endl;
        }
        else {
            break;
        }
    }

    clearInputBuffer();

    cout << "Enter package name : ";
    getline (cin, newPackage.packageName);

    // Validation price cant be negative
    do {
        cout << "Enter package price (RM) : ";
        if (!(cin >> newPackage.price) || newPackage.price < 0) {
            cout << "[ERROR] Invalid price ! Must be a non-negative number." << endl;
            clearInputBuffer();
        }
        else {
            break;
        }
    }
    while (true);

    // Validation Duration Day
    do {
        cout << "Enter package duration (Days) : ";
        if (!(cin >> newPackage.durationDays) || newPackage.durationDays <= 0) {
            cout << "[ERROR] Invalid duration ! Must be a greater than 0." << endl;
            clearInputBuffer();
        }
        else {
            break;
        }
    }
    while (true);
    
    // New package default active
    newPackage.packageStatus = Active;

    // Double confimation to save package in file
    char confirm;
    cout << "\nConfirm to save this new package ? (Y/N) : ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        packages[packageCount] = newPackage;
        packageCount++;

        savePackageToFile();

        cout << "[SUCCESS] Package Added Successfully !\n" << "Total Package count : " << packageCount << endl;
    }
    else {
        cout << "[CANCEL] Operation cancelled. Package was NOT saved." << endl;
    }
    
}

// Update package
void updatePackage() {
    displayHeader ("UPDATE PACKAGE");
    string id;
    cout << "Enter Package ID to update : ";
    cin >> id;

    for (int i = 0; i < packageCount; i++) {
        if (packages[i].packageID == id) {
            cout << "\nFound Package [" << packages[i].packageName << "]" << endl;

            cout << "Enter New Price (RM) : ";
            cin >> packages[i].price;

            cout << "Enter New Duration in Days : ";
            cin >> packages[i].durationDays;

            int statusInput;
            cout << "Set Status (0: Active, 1: Inactive) : ";
            cin >> statusInput;
            packages[i].packageStatus = (statusInput == 0) ? Active : Inactive;

            savePackageToFile();

            cout << "[SUCCESS] Package Updated Successfully ! " << endl;
            return;
        }
    }
    cout << "[ERROR] Package ID" << id << "Not Found." << endl;
}

// Delete Package
void deletePackage() {
    displayHeader ("DELETE PACKAGE");
    string id;
    cout << "Enter Package ID to Delete : ";
    cin >> id;

    for (int i = 0; i < packageCount; i++) {
        if (packages[i].packageID == id) {
            for (int j = i; j < packageCount - 1; j++) {
                packages[j] = packages[j + 1];
            }
            packageCount--;

            savePackageToFile();

            cout << "[SUCCESS] Package Deleted Successfully ! " << endl;
            return;
        }
    }
    cout << "[ERROR] Package ID" << id << "Not Found. " << endl;
}

// Search Package
void searchPackage() {
    displayHeader ("SEARCH PACKAGE");
    string id;
    cout << "Enter Package ID to Search : ";
    cin >> id;

    for (int i = 0; i < packageCount; i++) {
        if (packages[i].packageID == id) {
            cout << "\n----- Package Found -----\n";

            cout << "ID : " << packages[i].packageID << endl;
            cout << "Name : " << packages[i].packageName << endl;
            cout << "Price (RM) : " << packages[i].price << endl;
            cout << "Duration (Days) : " << packages[i].durationDays << endl;
            cout << "Status : " << statusToString(packages[i].packageStatus) << endl;
            return;
        }
    }
    cout << "[ERROR] Package ID " << id << " Not Found" << endl;
}

// Display All Package
void displayAllPackages() {
    displayHeader ("DISPLAY ALL PACKAGES");

    if (packageCount == 0) {
        cout << "No Package Available to Display." << endl;
        return;
    }

    cout << left << setw(8) << "ID"
        << setw(22) << "Name"
        << setw(14) << "Price (RM)"
        << setw(18) << "Duration (Days)"
        << setw(10) << "Status" << endl;
        cout << "---------------------------------------------------------------------" << endl;

        for (int i = 0; i < packageCount; i++) {
            cout << left << setw(8) << packages[i].packageID
                << setw(22) << packages[i].packageName
                << setw(14) << packages[i].price
                << setw(18) << packages[i].durationDays
                << setw(10) << statusToString(packages[i].packageStatus) << endl;
        }
}


// Main function
void package() {
    loadPackageFromFile();
    int packageChoice = 0;
    do {
        displayHeader ("GYM MEMBERSHIP SYSTEM");
        cout << "--------------------------- Package Menu ----------------------------\n";
        packageMenu();
        packageChoice = getMenuChoice(1, 6);

        // Choice 1 until Choice 6
        switch (packageChoice) {
            case 1 :
                addPackage();
                break;
            case 2 :
                updatePackage();
                break;
            case 3 :
                deletePackage();
                break;
            case 4 :
                searchPackage();
                break;
            case 5 :
                displayAllPackages();
                break;
            case 6 :
                cout << "\nExiting the menu. ThankYou !\n";
                return;
                break;
            default :
                cout << "\nInvalid choice. Please select 1-6.\n";
        }
    }
    while (packageChoice != 6);
}

int main() {
    package();
    return 0;
}