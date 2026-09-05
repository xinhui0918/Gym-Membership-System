#include <iostream> 
#include <string> 
#include <cstdlib> 
#include <fstream> 
#include <iomanip> 

using namespace std;
// Forward declarations of structs so prototypes can use them
struct GymUser;
struct GymPackage; // because report functiond declaration define early then those struct thus need to mention it at here
//Function declaration
// GENERAL FUNCTION
int getMenuChoice(int low, int high);
void displayHeader(string title);
void clearInputBuffer();
void MainMenu();
// USER MODULE
void promptUserMenu();
void userMenu();
void addUser();
void updateUser();
void deleteUser();
void searchUser();
void displayUser();
void loadUserFromFile();
void saveUserToFile();
// PACKAGE MODULE
void packageMenu();
void addPackage();
void updatePackage();
void deletePackage();
void searchPackage();
void displayAllPackages();
void package();
void loadPackageFromFile();
void savePackageToFile();
// BOOKING MODULE
void createBooking();
void cancelBooking();
void modifyBooking();
void searchBooking();
void displayBooking();
void booking();
void saveBooking();
void loadBookingFromFile();
// REPORT MODULE 
void ReportMenu();
void ReportUser(GymUser users[], GymPackage packages[], int userCount, int packageCount);
void ReportSorting(GymUser users[], GymPackage packages[], int userCount, int packageCount);
void ReportRevenue(GymUser users[], GymPackage packages[], int userCount, int packageCount);
void ReportStatistics(GymUser users[], GymPackage packages[], int userCount, int packageCount);
void ReportAnalysis(GymUser users[], GymPackage packages[], int userCount, int packageCount);
void ReportPrintuser(GymUser users[], GymPackage packages[], int userCount, int packageCount);
// PAYMENT MODULE /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int findTransactionIndex(int transactionID);
void paymentProcess();
void displayReceipt();
void refundProcess();
void searchTransaction();
void displayPaymentHistory();
void payment();
void loadPaymentFromFile();
void savePaymentToFile();

//Enum
enum package_status {
	PackageActive,
	PackageInactive
};
enum booking_status {
	BookingActive,
	BookingInactive
};
string  status_to_string(booking_status status) {
	return (status == BookingActive) ? "Active" : "Inactive";
}
string status_to_string(booking_status status);
string statusToString(package_status status);
//Structure declaration
//GymUser module	
struct GymUser {
	string userID;
	string userName;
	string phoneNum;
	string userPackage;
};
//PackageData module
struct GymPackage {
	string packageID;
	string packageName;
	double price;
	int durationDays;
	package_status packageStatus;
};

//booking module
struct Gymbooking {
	int bookingID;
	string userName;
	string userID;
	string date;
	booking_status bookingStatus;

};

struct timeSlot {
	string slotID;
	string startTime;
	string endTime;
	bool isBooked;
};

//payment module
struct PaymentTransaction {
	int transactionID;
	string userID;
	string customerName;
	string packageName;
	double amount;
	string paymentMethod;
	string status;
};
//structure array declaration
const int maxUsers = 50;
const int maxPackages = 50;
const int maxBooking = 50;
const int MAX_TRANSACTIONS = 50;

GymUser users[maxUsers];
GymPackage packages[maxPackages];
Gymbooking bookings[maxBooking];
PaymentTransaction transactions[MAX_TRANSACTIONS];

int userCount = 0;
int packageCount = 0;
int bookingCount = 0;
int new_booking_id = 2001;
int transactionCount = 0;
int nextTransactionID = 1001;

//booking 
//set the time slot and array it
const int maxSlot = 10;
timeSlot timeSlots[maxSlot] = {
	{"1", "08:00", "09:00", false},
	{"2", "09:00", "10:00", false},
	{"3", "10:00", "11:00", false},
	{"4", "11:00", "12:00", false},
	{"5", "12:00", "13:00", false},
	{"6", "13:00", "14:00", false},
	{"7", "14:00", "15:00", false},
	{"8", "15:00", "16:00", false},
	{"9", "16:00", "17:00", false},
	{"10", "17:00", "18:00", false}

};
//Global variable 

int main() {
	loadUserFromFile();
	loadPackageFromFile();
	loadBookingFromFile();
	MainMenu();
}
//General Use function
void displayHeader(string title) {
	for (int i = 0; i < 120; i++) {
		cout << '=';
	}
	cout << "\n" << right << setw(60) << title << endl;
	for (int i = 0; i < 120; i++) {
		cout << '=';
	}
	cout << endl;
}
void clearInputBuffer() {
	cin.clear();
	cin.ignore(10000, '\n');
}
int getMenuChoice(int low, int high) {
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
// Main Menu 
void MainMenu() {
	int choice;
	system("cls");
	do {
		displayHeader("MAIN MENU");
		cout << "1. User Management Menu" << endl;
		cout << "2. Package Management Menu" << endl;
		cout << "3. Booking Menu" << endl;
		cout << "4. Report Menu" << endl;
		cout << "5. Payment Menu" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your choice (1-6): ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
		}
		switch (choice) {
		case 1:
			userMenu();
			break;
		case 2:
			package();
			break;
		case 3:
			booking();
			break;
		case 4:
			ReportMenu();
			break;
		case 5:
			payment();
			break;
		case 6:
			break;
		default:
			system("cls");
			cout << '\a' << "||Invalid choice. Please select between 1 and 5.||" << endl;
		}
	} while (choice != 6);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// USER MODULE
bool isDuplicateID(string id);
void loadUserFromFile() {
	ifstream inData("UserData.txt");

	if (!inData) {
		users[0] = { "0001", "Tan", "0193257193", "1001" },
			users[1] = { "0002", "Loh", "0138642947", "1001" },
			users[2] = { "0003", "Ooi", "0163841946", "1004" },

			userCount = 3;
		saveUserToFile();
		return;
	}

	userCount = 0;
	while (userCount < maxUsers && inData >> users[userCount].userID) {
		inData >> users[userCount].userName;
		inData >> users[userCount].phoneNum;
		inData >> users[userCount].userPackage;

		userCount++;
	}

	inData.close();
};

void saveUserToFile() {
	ofstream outData("UserData.txt");

	if (!outData) {
		cout << "[Error] Unable to open User data file" << endl;
		return;
	}
	for (int i = 0; i < userCount; i++) {
		outData << users[i].userID << endl;
		outData << users[i].userName << endl;
		outData << users[i].phoneNum << endl;
		outData << users[i].userPackage << endl;
	}

	outData.close();
}

void promptUserMenu() {
	cout << "| 1. Add User                            |" << endl;
	cout << "| 2. Update User                         |" << endl;
	cout << "| 3. Delete User                         |" << endl;
	cout << "| 4. Search Users                        |" << endl;
	cout << "| 5. Display Users                       |" << endl;
	cout << "| 6. Exit                                |" << endl;
}

//user valid ID exist
bool IsValidUserID(string userID) {
	for (int i = 0; i < userCount; i++) {
		if (users[i].userID == userID) {
			return true;
		};
	}
	return false;
};

//user valid PhoneNumber exist
bool IsValidPhoneNum(string phoneNum) {
	for (int i = 0; i < userCount; i++) {
		if (users[i].phoneNum == phoneNum) {
			return true;
		};
	}
	return false;
}

//just approve the number
bool isNumID(string userID) {
	if (userID.empty()) {
		return false;
	}
	for (int i = 0; i < userID.length(); i++) {
		if (!isdigit(userID[i])) {
			return false;
		}
	}
	return true;
}

//just approve the alphabet only username
bool isWordName(string userName) {
	if (userName.empty()) {
		return false;
	}
	for (int i = 0; i < userName.length(); i++) {
		if (!isalpha(userName[i])) {
			return false;
		}
	}
	return true;
}

//just approve the number only for phone Number
bool isNumPhone(string phoneNum) {
	if (phoneNum.empty()) {
		return false;
	}
	for (int i = 0; i < phoneNum.length(); i++) {
		if (!isdigit(phoneNum[i])) {
			return false;
		}
	}
	return true;
}
//valid first number = 0

void userMenu() {
	int userChoice;
	do {
		displayHeader("User Menu");
		promptUserMenu();
		userChoice = getMenuChoice(1, 6);
		switch (userChoice)
		{

		case 1:
			addUser();
			break;
		case 2:
			updateUser();
			break;
		case 3:
			deleteUser();
			break;
		case 4:
			searchUser();
			break;
		case 5:
			displayUser();
			break;
		case 6:
			cout << "Exiting User Menu" << endl;
			break;
		default:
			cout << "Please enter 1-6" << endl;
			// case 1-6

		}
	} while (userChoice != 6);
}

void addUser() {

	displayHeader("Add UserID");

	// > maxUsers
	if (userCount >= maxUsers) {
		cout << "Our User member are full" << endl;
		return;
	}

	// Add userID
	GymUser newUser;
	cout << "Enter UserID(first Num = 0): ";
	while (true) {
		cin >> newUser.userID;

		if (newUser.userID[0] != '0') {
			cout << "[ERROR] First Number start with (0):" << endl;
			cout << "Please try Again: ";
		}
		else if (!isNumID(newUser.userID)) {
			cout << "[ERROR] UserID must contain numbers only!" << endl;
			cout << "Please try Again: ";
		}
		else if (newUser.userID.length() != 4) {
			cout << "[ERROR] UserID number should 4 :" << endl;
			cout << "Please try Again: ";

		}
		else if (IsValidUserID(newUser.userID)) {
			cout << "[ERROR] UserID already exist. " << endl;
			cout << "Please try Again: ";
			clearInputBuffer();
		}
		else {
			break;
		}
	}

	//Add userName
	cout << "Enter Username (MAX 4 character): " << endl;
	while (true) {
		cin >> newUser.userName;
		if (!isWordName(newUser.userName)) {
			cout << "[ERROR] UserName must type (alphabet) " << endl;
			cout << "Please try Again: ";
		}
		else if (newUser.userName.length() > 4 || newUser.userName.empty()) {
			cout << "[ERROR] Username must below 5 charaters" << endl;
			cout << "Please try Again: ";
		}
		else {
			break;
		}
	};

	//Add PhoneNumber
	cout << "Enter PhoneNumber(MAX 11 character): " << endl;

	while (true) {
		cin >> newUser.phoneNum;


		if (newUser.phoneNum[0] != '0' || newUser.phoneNum[1] != '1') {
			cout << "[ERROR] Not a phone number format" << endl;
			cout << "Please try Again: ";
		}
		else if (!isNumPhone(newUser.phoneNum)) {
			cout << "[ERROR] UserID must contain numbers only!" << endl;
			cout << "Please try Again: ";
		}
		else if (newUser.phoneNum.length() > 11 || newUser.phoneNum.length() < 10) {
			cout << "[ERROR] PhoneNumber must 10 - 11 character" << endl;
			cout << "Please try Again: ";
		}
		else if (IsValidPhoneNum(newUser.phoneNum)) {
			cout << "[ERROR] Phone Number had been used. Please Try Again:" << endl;
			cout << "Please Try Again : ";
		}
		else {
			break;
		}
	}

	//Add packageID
	while (true) {
		cout << "Enter package ID : ";
		cin >> newUser.userPackage;
		if (isDuplicateID(newUser.userPackage)) {
			users[userCount] = newUser;
			userCount++;
			saveUserToFile();

			cout << "\n========================================\n";
			cout << "|        USER ADDED SUCCESSFULLY!      |\n";
			cout << "========================================\n";
			cout << " User ID       : " << newUser.userID << endl;
			cout << " Username      : " << newUser.userName << endl;
			cout << " Phone Number  : " << newUser.phoneNum << endl;
			cout << " Package ID    : " << newUser.userPackage << endl;
			cout << "========================================\n";
			return;
		}
		else {
			cout << "\n==========================================\n";
			cout << "| [ERROR] Unaccepted! Invalid Package ID.|\n";
			cout << "| User record was NOT saved.             |";
			cout << "\n==========================================\n";
			return;
		}
	}
}

void updateUser() {
	displayHeader("Update User");
	string userid;
	string username;
	string packageid;
	string phonenum;

	cout << "Enter your ID: ";
	cin >> userid;

	bool found = false;
	for (int i = 0; i < userCount; i++) {
		if (users[i].userID == userid) {
			found = true;
			cout << "\n Found The UserID! \n";

			//Key in Username
			cout << "Enter New Username: ";
			while (true) {
				cin >> username;
				if (!isWordName(username)) {
					cout << "[ERROR] UserName must type (alphabet) " << endl;
					cout << "Please try Again: ";
				}
				else if (username.length() > 4 || username.empty()) {
					cout << "[ERROR] Username must below 5 charaters" << endl;
					cout << "Please try Again: ";
				}
				else {
					break;
				}
			};
			//Key in Phone Number
			cout << "Enter New Phone Number:";
			while (true) {
				cin >> phonenum;

				if (phonenum[0] != '0' || phonenum[1] != '1' || !isNumPhone(phonenum) || phonenum.length() > 11 || phonenum.length() < 10) {
					cout << "[ERROR] Not a phone number format" << endl;
					cout << "Please try Again: ";
				}
				else if (phonenum != users[i].phoneNum && IsValidPhoneNum(phonenum)) {
					cout << "[ERROR] Phone Number have been exist!" << endl;
					cout << "Please try Again: ";
				}
				else {
					break;
				}
			}

			//Key in userPackage
			while (true) {
				cout << "Enter new packageID: ";
				cin >> packageid;
				if (isDuplicateID(packageid)) {
					users[i].userName = username;
					users[i].phoneNum = phonenum;
					users[i].userPackage = packageid;
					saveUserToFile();

					cout << "\n========================================\n";
					cout << "|        USER UPDATE SUCCESSFULLY!      |\n";
					cout << "========================================\n";
					cout << "New UserID: " << users[i].userID << endl;
					cout << "New Username: " << users[i].userName << endl;
					cout << "New phoneNum: " << users[i].phoneNum << endl;
					cout << "New package: " << users[i].userPackage << endl;
					cout << "========================================\n";
					return;
				}
				else {
					cout << "[ERROR] Invalid PacakageID";
					cout << "UPDATE Operator Be Cancel";
					return;
				}
			}
		}
	}
	if (!found) {
		cout << "User ID not found!" << endl;
	}
}

void deleteUser() {
	displayHeader("Delete User");

	string userid;
	string check;
	cout << "Enter Existing UserID ";
	cin >> userid;
	cout << "\nPlease Double confirm\n";
	cout << "Enter 'YES' OR 'NO' : ";
	cin >> check;

	if (check != "YES") {
		cout << "Cancel the delete statement";
		return;
	}

	bool found = false;
	for (int i = 0; i < userCount; i++) {
		if (users[i].userID == userid) {
			for (int j = i; j < userCount - 1; j++) {
				users[j] = users[j + 1];
			}
			userCount--;
			saveUserToFile();

			cout << "Delete [SUCCESS]!" << endl;
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "User ID not found!" << endl;
	}


}

void searchUser() {
	displayHeader("Search User");

	string userid;
	cout << "Enter UserID: ";
	cin >> userid;

	//loop for found UserID
	bool found = false;
	for (int i = 0; i < userCount; i++) {
		if (users[i].userID == userid) {
			cout << "[SUCCESS] Found UserID!" << endl;
			cout << "UserID: " << users[i].userID << endl;
			cout << "Username: " << users[i].userName << endl;
			cout << "Phone Number: " << users[i].phoneNum << endl;
			cout << "Package ID: " << users[i].userPackage << endl;
			found = true;
			break;
		}
	}
	if (!found) {
		cout << "[ERROR]User ID not be found!" << endl;
	}
}

void displayUser() {
	displayHeader("Display All User");

	cout << left
		<< setw(14) << "UserID"
		<< setw(16) << "UserName"
		<< setw(25) << "PhoneNumber"
		<< setw(32) << "Package ID" << endl;

	for (int i = 0; i < userCount; i++) {
		cout << left << setw(1)
			<< setw(14) << users[i].userID
			<< setw(16) << users[i].userName
			<< setw(25) << users[i].phoneNum
			<< setw(30) << users[i].userPackage << endl;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PACKAGE MODULE

// Helper function to render enum as text
string statusToString(package_status status) {
	return (status == PackageActive) ? "Active" : "Inactive";
}
void packageMenu() {
	cout << "1. Add Package" << endl;
	cout << "2. Update Package" << endl;
	cout << "3. Delete Package" << endl;
	cout << "4. Search Package" << endl;
	cout << "5. Display All Packages" << endl;
	cout << "6. Exit" << endl;
}
void loadPackageFromFile() {
	ifstream inData("PackageData.txt");

	if (!inData) {
		packages[0] = { "1001", "BasicPackage", 29.99, 30, PackageActive };
		packages[1] = { "1002", "StandardPackage", 49.99, 60, PackageActive };
		packages[2] = { "1003", "PremiumPackage", 69.99, 90, PackageActive };
		packages[3] = { "1004", "StudentPackage", 19.99, 30, PackageActive };
		packageCount = 4;

		savePackageToFile();
		return;
	}
	packageCount = 0;
	int statusInt;

	while (packageCount < maxPackages && inData >> packages[packageCount].packageID) {
		inData.ignore(10000, '\n');
		getline(inData, packages[packageCount].packageName);
		inData >> packages[packageCount].price;
		inData >> packages[packageCount].durationDays;
		inData >> statusInt;

		packages[packageCount].packageStatus = (statusInt == 0) ? PackageActive : PackageInactive;
		packageCount++;
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
		outData << static_cast<int>(packages[i].packageStatus) << endl;
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
	displayHeader("ADD NEW PACKAGE");
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
	cin >> newPackage.packageName;

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
	} while (true);

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
	} while (true);

	// New package default active
	newPackage.packageStatus = PackageActive;

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

	clearInputBuffer();
}

// Update package
void updatePackage() {
	displayHeader("UPDATE PACKAGE");
	string id;
	cout << "Enter Package ID to update : ";
	cin >> id;

	for (int i = 0; i < packageCount; i++) {
		if (packages[i].packageID == id) {
			cout << "\nFound Package [" << packages[i].packageName << "]" << endl;

			// Validation price cant be negative
			do {
				cout << "Enter package price (RM) : ";
				if (!(cin >> packages[i].price) || packages[i].price < 0) {
					cout << "[ERROR] Invalid price ! Must be a non-negative number." << endl;
					clearInputBuffer();
				}
				else {
					break;
				}
			} while (true);

			// Validation Duration Day
			do {
				cout << "Enter package duration (Days) : ";
				if (!(cin >> packages[i].durationDays) || packages[i].durationDays <= 0) {
					cout << "[ERROR] Invalid duration ! Must be a greater than 0." << endl;
					clearInputBuffer();
				}
				else {
					break;
				}
			} while (true);

			int statusInput;
			cout << "Set Status (0: Active, 1: Inactive) : ";
			cin >> statusInput;
			packages[i].packageStatus = (statusInput == 0) ? PackageActive : PackageInactive;

			savePackageToFile();

			cout << "[SUCCESS] Package Updated Successfully ! " << endl;
			return;
		}
	}
	cout << "[ERROR] Package ID" << id << "Not Found." << endl;
}
// Delete Package
void deletePackage() {
	displayHeader("DELETE PACKAGE");
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
	cout << "[ERROR] Package ID " << id << " Not Found. " << endl;
}
// Search Package
void searchPackage() {
	displayHeader("SEARCH PACKAGE");
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
	displayHeader("DISPLAY ALL PACKAGES");

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
			<< setw(14) << fixed << setprecision(2) << packages[i].price
			<< setw(18) << packages[i].durationDays
			<< setw(10) << statusToString(packages[i].packageStatus) << endl;
	}
}
// Main function
void package() {
	loadPackageFromFile();
	int packageChoice = 0;
	do {
		displayHeader("GYM MEMBERSHIP SYSTEM");
		cout << "--------------------------- Package Menu ----------------------------\n";
		packageMenu();
		packageChoice = getMenuChoice(1, 6);

		// Choice 1 until Choice 6
		switch (packageChoice) {
		case 1:
			addPackage();
			break;
		case 2:
			updatePackage();
			break;
		case 3:
			deletePackage();
			break;
		case 4:
			searchPackage();
			break;
		case 5:
			displayAllPackages();
			break;
		case 6:
			cout << "\nExiting the menu. ThankYou !\n";
			return;
			break;
		default:
			cout << "\nInvalid choice. Please select 1-6.\n";
		}
	} while (packageChoice != 6);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BOOKING MODULE

void saveBookingFromFile() {
	ofstream outFile;
	outFile.open("bookings.txt");

	if (!outFile) {
		cout << "Error opening file." << endl;
		return;
	}

	for (int i = 0; i < bookingCount; i++) {
		outFile << bookings[i].bookingID << " " << bookings[i].userName << " "
			<< bookings[i].date << " " << bookings[i].bookingStatus << "\n";
	}

	outFile.close();
}
void loadBookingFromFile() {
	ifstream inFile("bookings.txt");

	// no file, skipp
	if (!inFile) {
		return;
	}

	int id;
	string name, date;
	int status;
	int max_id_seen = 2000;

	inFile >> id;
	while (!inFile.eof()) {
		inFile >> name >> date >> status;

		Gymbooking b;
		b.bookingID = id;
		b.userName = name;
		b.date = date;
		b.bookingStatus = (booking_status)status;

		bookings[bookingCount] = b;
		bookingCount++;

		if (b.bookingID > max_id_seen) {
			max_id_seen = b.bookingID;
		}
		for (int i = 0; i < maxSlot; i++) {
			string range = timeSlots[i].startTime + " - " + timeSlots[i].endTime;
			if (range == b.date) {
				timeSlots[i].isBooked = true;
				break;
			}
		}
		inFile >> id;
	}

	new_booking_id = max_id_seen + 1;
	inFile.close();
}

void bookingMenu() {
	cout << "1. Create Booking" << endl;
	cout << "2. Cancel Booking" << endl;
	cout << "3. Modify Booking" << endl;
	cout << "4. Search Booking" << endl;
	cout << "5. Display Booking" << endl;
	cout << "6. Exit " << endl;
}
// create booking function
// verify user(id and name),show time slot （let user choice)
// display result(success booking/ not >> retry again)
void createBooking() {
	displayHeader("Add a booking.");


	//check booking count
	if (bookingCount >= maxBooking) {
		cout << "The booking is full." << endl;
		return;
	}

	string userName;
	cout << "----------------------------------" << endl;
	cout << "Please enter your username." << endl;
	cin >> userName;
	clearInputBuffer();

	cout << "Please select the time slot:\n";
	cout << "\n The avaible time slot : \n";
	for (int i = 0; i < maxSlot; i++) {
		cout << left << timeSlots[i].slotID << setw(6) << ": " << setw(5) << timeSlots[i].startTime << setw(6) << " - " <<
			setw(6) << timeSlots[i].endTime << setw(6) << (timeSlots[i].isBooked ? "Booked" : "Available") << endl;
	}

	int slot_ID = getMenuChoice(1, maxSlot);

	//check the time slot
	if (timeSlots[slot_ID - 1].isBooked) {
		cout << "Sorry, the time slot has already been booked. Please try agian."
			<< endl;
		return;
	}

	timeSlots[slot_ID - 1].isBooked = true;

	// acess the data 2 global
	bookings[bookingCount].bookingID = new_booking_id;
	bookings[bookingCount].userName = userName;
	bookings[bookingCount].date = timeSlots[slot_ID - 1].startTime + "-" + timeSlots[slot_ID - 1].endTime;
	bookings[bookingCount].bookingStatus = BookingActive;

	cout << "Your booking is confirmed! The booking ID is " << new_booking_id << "\nYou have booked: "
		<< timeSlots[slot_ID - 1].startTime << " - " << timeSlots[slot_ID - 1].endTime << endl;

	new_booking_id++;
	bookingCount++;

	saveBookingFromFile();
}
// cancel booking
void cancelBooking() {

	displayHeader("Cancel Booking");
	if (bookingCount == 0) {
		cout << "No bookings found.\n";
		return;
	}


	int searchID;
	cout << "Please enter your booking ID: ";
	cin >> searchID;
	clearInputBuffer();

	// check for booking
	int index = -1;
	for (int i = 0; i < bookingCount; i++) {
		if (bookings[i].bookingID == searchID) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		cout << "No booking found with the booking ID." << endl;
		return;
	}

	cout << "Found booking: " << bookings[index].userName << ", " << bookings[index].date << endl;
	cout << "1. Confirm cancellation\n2. Go back\n";

	int confirm = getMenuChoice(1, 2);

	if (confirm == 1) {
		for (int i = 0; i < maxSlot; i++) {
			string range = timeSlots[i].startTime + "-" + timeSlots[i].endTime;
			if (range == bookings[index].date) {
				timeSlots[i].isBooked = false;
				break;
			}
		}
		for (int i = index; i < bookingCount - 1; i++) {
			bookings[i] = bookings[i + 1];
		}
		bookingCount--;

		cout << "Booking cancelled successfully.\n";
	}
	else {
		cout << "Cancellation aborted." << endl;
	}
	saveBookingFromFile();
}
// modify booking
void modifyBooking() {

	displayHeader("Modify Booking");
	if (bookingCount == 0) {
		cout << "No bookings found." << endl;
		return;
	}


	int searchID;
	cout << "Please enter your booking ID: ";
	cin >> searchID;
	clearInputBuffer();

	int index = -1;
	for (int i = 0; i < bookingCount; i++) {
		// check
		if (bookings[i].bookingID == searchID) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		cout << "No booking found with that booking ID." << endl;
		return;
	}

	// show time
	cout << "Current booking: " << bookings[index].date << endl;
	cout << "\nAvailable time slots:\n";
	cout << left << setw(8) << "No" << setw(10) << "Start" << setw(10) << "End" << "Status" << endl;
	for (int i = 0; i < maxSlot; i++) {
		cout << left << setw(8) << timeSlots[i].slotID
			<< setw(10) << timeSlots[i].startTime
			<< setw(10) << timeSlots[i].endTime
			<< (timeSlots[i].isBooked ? "Booked" : "Available") << endl;
	}

	int newSlot = getMenuChoice(1, maxSlot);

	if (timeSlots[newSlot - 1].isBooked) {
		cout << "That slot is already booked. Modification cancelled." << endl;
		return;
	}
	// ensure the cencelled booking in status available
	for (int i = 0; i < maxSlot; i++) {
		string range = timeSlots[i].startTime + "-" + timeSlots[i].endTime;
		if (range == bookings[index].date) {
			timeSlots[i].isBooked = false;
			break;
		}
	}

	timeSlots[newSlot - 1].isBooked = true;
	bookings[index].date = timeSlots[newSlot - 1].startTime + "-" + timeSlots[newSlot - 1].endTime;

	cout << "Booking modified successfully. New time slot: " << bookings[index].date << endl;
	saveBookingFromFile();
}
//search booking
void searchBooking() {
	displayHeader("Search booking");

	int searchID;
	cout << "Please enter your booking ID:\n";
	cin >> searchID;
	clearInputBuffer();

	bool found = false;
	cout << left << setw(6) << "No." << setw(15) << "Username" << setw(15) <<
		"Time Slot" << "Status" << endl;

	// check booking and exit or not
	for (int i = 0; i < bookingCount; i++) {
		if (bookings[i].bookingID == searchID) {
			cout << left << setw(6) << (i + 1) << setw(15) << bookings[i].userName
				<< setw(15) << bookings[i].date << status_to_string(bookings[i].bookingStatus) << endl;
			found = true;
		}
	}
	if (!found) {
		cout << "No booking found under that user ID." << endl;
		return;
	}
}

//display booking
void displayBooking() {
	displayHeader("All Bookings");
	if (bookingCount == 0) {
		cout << "Your booking is not found." << endl;
		return;
	}
	cout << left << setw(6) << "No." << setw(15) << "Username" << setw(15)
		<< "Time Slot" << "Status" << endl;
	// display all booking
	int i = 0;
	while (i < bookingCount) {
		cout << left << setw(6) << (i + 1) << setw(15) << bookings[i].userName
			<< setw(15) << bookings[i].date
			<< status_to_string(bookings[i].bookingStatus) << endl;
		i++;
	}
}
// booking menu choice
void booking() {
	int bookingChoice = 0;
	do
	{
		displayHeader("Booking Menu");
		bookingMenu();
		bookingChoice = getMenuChoice(1, 6);

		switch (bookingChoice) {
		case 1:
			createBooking();
			break;
		case 2:
			cancelBooking();
			break;
		case 3:
			modifyBooking();
			break;
		case 4:
			searchBooking();
			break;
		case 5:
			displayBooking();
			break;
		case 6:
			cout << "Exiting booking menu." << endl;
			break;
		default:
			cout << "Invalid choice. Please try select number 1-6 again." << endl;
			break;

		}
	} while (bookingChoice != 6);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// REPORT MODULE
void ReportMenu() {
	ifstream userFile("UserData.txt");
	ifstream packageFile("PackageData.txt");
	if (!userFile || !packageFile) {
		cout << '\a' << "||Error opening files!||" << endl;
		exit(1);
	}
	GymPackage temppackage; // load all package data first to prepare	
	int tempholdint;
	for (packageCount = 0; packageCount < maxPackages; packageCount++) {
		packageFile >> temppackage.packageID >> temppackage.packageName >> temppackage.price >> temppackage.durationDays >> tempholdint;
		temppackage.packageStatus = static_cast<package_status>(tempholdint);
		if (packageFile.fail()) {
			break;
		}
		packages[packageCount] = temppackage;
	}
	GymUser tempuser;
	for (userCount = 0; userCount < maxUsers; userCount++) {
		userFile >> tempuser.userID >> tempuser.userName >> tempuser.phoneNum >> tempuser.userPackage;
		if (userFile.fail()) {
			break;
		}
		users[userCount] = tempuser;
	}
	packageFile.close();
	int choice;
	system("cls");
	do {
		displayHeader("REPORT MENU");
		cout << "1. User Report" << endl;
		cout << "2. User Report Sorting" << endl;
		cout << "3. Revenue Report" << endl;
		cout << "4. Statistics Report" << endl;
		cout << "5. Analysis Report" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your choice (1-6): ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
		}
		switch (choice) {
		case 1:
			ReportUser(users, packages, userCount, packageCount);
			break;
		case 2:
			ReportSorting(users, packages, userCount, packageCount);
			break;
		case 3:
			ReportRevenue(users, packages, userCount, packageCount);
			break;
		case 4:
			ReportStatistics(users, packages, userCount, packageCount);
			break;
		case 5:
			ReportAnalysis(users, packages, userCount, packageCount);
			break;
		case 6:
			break;
		default:
			system("cls");
			cout << '\a' << "||Invalid choice. Please select between 1 and 5.||" << endl;
		}
	} while (choice != 6);
}
void ReportUser(GymUser users[], GymPackage packages[], int userCount, int packageCount) {
	system("cls");
	ReportPrintuser(users, packages, userCount, packageCount);
	cout << "\nPress any key to return to the report menu" << endl;
	system("cls");
	system("pause");
}
void ReportSorting(GymUser users[], GymPackage packages[], int userCount, int packageCount) {
	system("cls");
	int sortingChoice;
	string repeatornot;
	do {
		displayHeader("USER REPORT SORTING OPTIONS");
		cout << "1. Sort by User ID" << endl;
		cout << "2. Sort by User Name" << endl;
		cout << "Enter your choice (1-2): ";
		cin >> sortingChoice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			system("cls");
			cout << '\a' << "||Invalid input. Please enter a number between 1 and 2.||" << endl;
		}
		switch (sortingChoice) {
		case 1:
			for (int j = 0; j < userCount - 1; j++) { // bubble sorting 
				for (int k = 0; k < userCount - j - 1; k++) {
					if (users[k].userID > users[k + 1].userID) {
						swap(users[k], users[k + 1]);
					}
				}
			}
			system("cls");
			ReportPrintuser(users, packages, userCount, packageCount);
			break;
		case 2:
			for (int j = 0; j < userCount - 1; j++) { // bubble sorting 
				for (int k = 0; k < userCount - j - 1; k++) {
					if (users[k].userName > users[k + 1].userName) {
						swap(users[k], users[k + 1]);
					}
				}
			}
			system("cls");
			ReportPrintuser(users, packages, userCount, packageCount);
			break;
		default:
			system("cls");
			cout << '\a' << "||Invalid choice. Please select between 1 and 2.||" << endl;
		}
	} while (sortingChoice != 1 && sortingChoice != 2);

	displayHeader("Enter 1 to Return Sorting Menu or Any Other Input to Return Report Menu : ");
	cout << "Enter your choices: ";
	cin >> repeatornot;
	if (repeatornot == "1") {
		system("cls");
		ReportSorting(users, packages, userCount, packageCount);
	}
	system("cls");
}
void ReportRevenue(GymUser users[], GymPackage packages[], int userCount, int packageCount) {
	system("cls");
	displayHeader("REVENUE REPORT");
	cout << left << setw(20) << "Package ID"
		<< setw(20) << "Package Name"
		<< setw(20) << "Price"
		<< setw(20) << "Number of Users"
		<< setw(20) << "Total Revenue (RM)" << endl;
	for (int i = 0; i < 120; i++) {
		cout << '-';
	}
	cout << endl;
	double accumulatedTotalRevenue = 0.00;
	for (int i = 0; i < packageCount; i++) {
		int numberOfUsers = 0;
		for (int j = 0; j < userCount; j++) {
			if (users[j].userPackage == packages[i].packageID) {
				numberOfUsers++;
			}
		}
		double totalRevenue = numberOfUsers * packages[i].price;
		cout << left << setw(20) << packages[i].packageID
			<< setw(20) << packages[i].packageName
			<< setw(20) << fixed << setprecision(2) << packages[i].price;
		if (package_status::PackageActive == packages[i].packageStatus) {
			cout << setw(20) << numberOfUsers
				<< setw(20) << fixed << setprecision(2) << totalRevenue << endl;
			accumulatedTotalRevenue += totalRevenue;
		}
		else {
			cout << setw(20) << "Package Is Inactive"
				<< setw(20) << "Package Is Inactive" << endl;
		}
	}
	cout << "\nTotal Revenue from all packages: RM" << fixed << setprecision(2) << accumulatedTotalRevenue << endl;
	cout << "\nPress any key to return to the report menu" << endl;
	system("pause");
	system("cls");
}
void ReportStatistics(GymUser users[], GymPackage packages[], int userCount, int packageCount) {
	system("cls");
	displayHeader("STATISTICS REPORT");
	cout << left << setw(40) << "Package Name"
		<< setw(20) << "Number of Users"
		<< setw(20) << "Percentage of Users" << endl;
	for (int i = 0; i < 120; i++) {
		cout << '-';
	}
	cout << endl;
	int tempcountusers = 0;
	int tempcountpackages = 0;
	for (int i = 0; i < packageCount; i++) {
		int numberofUsers = 0;
		for (int j = 0; j < userCount; j++) {
			if (users[j].userPackage == packages[i].packageID) {
				numberofUsers++;
			}
		}
		if (package_status::PackageActive == packages[i].packageStatus) {
			cout << left << setw(40) << packages[i].packageName
				<< setw(20) << numberofUsers
				<< setw(20) << fixed << setprecision(2) << numberofUsers * 100.0 / userCount << "%" << endl;
			tempcountpackages++;
		}
		else {
			tempcountusers += numberofUsers;
		}
	}
	cout << endl << left << setw(40) << "Unknown Packages"
		<< setw(20) << tempcountusers
		<< setw(20) << fixed << setprecision(2) << tempcountusers * 100.0 / userCount << "%" << endl;
	cout << "\nTotal Number of Packages: " << tempcountpackages << endl;
	cout << "Total Number of Users: " << userCount << endl;
	cout << "\nPress any key to return to the report menu" << endl;
	system("pause");
	system("cls");
}
void ReportAnalysis(GymUser users[], GymPackage packages[], int userCount, int packageCount) {
	system("cls");
	displayHeader("ANALYSIS REPORT");
	cout << left << setw(40) << "Most sales of Package"
		<< setw(20) << "Number of Users"
		<< setw(20) << "Revenue (RM)"
		<< setw(20) << "Percentage of Total Revenue" << endl;
	for (int i = 0; i < 120; i++) {
		cout << '-';
	}
	cout << endl;

	if (packageCount <= 0) {
		cout << "No packages available." << endl << endl;
		system("pause");
		system("cls");
		return;
	}
	// arrays for counts and revenue
	int sales[maxPackages] = { 0 };
	double revenue[maxPackages] = { 0.0 };
	double totalRevenue = 0.0;

	for (int i = 0; i < userCount; i++) {
		for (int j = 0; j < packageCount; j++) {
			if (users[i].userPackage == packages[j].packageID) {
				sales[j]++;
				revenue[j] += packages[j].price;
				totalRevenue += packages[j].price;
				break;
			}
		}
	}
	// find maximum sales value
	int maxSales = 0;
	for (int i = 0; i < packageCount; ++i) {
		if (sales[i] > maxSales)
			maxSales = sales[i];
	}

	if (maxSales == 0) {
		cout << "No package sales recorded." << endl << endl;
		system("pause");
		system("cls");
		return;
	}

	double percentage;
	// print	
	for (int i = 0; i < packageCount; ++i) {
		if (sales[i] == maxSales) {
			percentage = (totalRevenue > 0.0) ? (revenue[i] / totalRevenue * 100.0) : 0.0;
			cout << left << setw(40) << packages[i].packageName
				<< setw(20) << sales[i]
				<< setw(20) << fixed << setprecision(2) << revenue[i]
				<< setw(20) << fixed << setprecision(2) << percentage << "%" << endl;
		}
	}
	cout << endl;
	system("pause");
	system("cls");
}
void ReportPrintuser(GymUser users[], GymPackage packages[], int userCount, int packageCount) {
	displayHeader("USER REPORT");
	cout << left << setw(20) << "User ID"
		<< setw(20) << "User Name"
		<< setw(20) << "Phone Number"
		<< setw(20) << "Package ID"
		<< setw(20) << "Package Name"
		<< setw(20) << "Duration (Days)" << endl;
	for (int i = 0; i < 120; i++) {
		cout << '-';
	}
	cout << endl;
	for (int i = 0; i < userCount; i++) {
		bool packageFound = false;
		int matchedid = -1;
		for (int j = 0; j < packageCount; j++) { //to find the location of matched package id in array
			if (users[i].userPackage == packages[j].packageID) {
				packageFound = true;
				matchedid = j;
				break;
			}
		}
		cout << left << setw(20) << users[i].userID
			<< setw(20) << users[i].userName
			<< setw(20) << users[i].phoneNum
			<< setw(20) << users[i].userPackage;
		if (packageFound == false) {
			cout << setw(20) << "No Package Found"
				<< setw(20) << "No Package Found" << endl;
		}
		else {
			if (package_status::PackageActive == packages[matchedid].packageStatus) {
				cout << setw(20) << packages[matchedid].packageName
					<< setw(20) << packages[matchedid].durationDays << endl;
			}
			else {
				cout << setw(20) << "Inactive Package"
					<< setw(20) << "Inactive Package" << endl;
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PAYMENT MODULE
// Load payment records from PaymentData.txt
void paymentMenu() {
	cout << "1. Make Payment" << endl;
	cout << "2. Print Receipt" << endl;
	cout << "3. Refund Payment" << endl;
	cout << "4. Search Transaction" << endl;
	cout << "5. Payment History" << endl;
	cout << "6. Exit" << endl;
}
void loadPaymentFromFile() {
	ifstream inData("PaymentData.txt");
	if (!inData) {
		transactionCount = 0;
		nextTransactionID = 1001;
		return;
	}
	transactionCount = 0;
	nextTransactionID = 1001;
	while (transactionCount < MAX_TRANSACTIONS &&
		inData >> transactions[transactionCount].transactionID) {
		inData.ignore(10000, '\n');
		if (!getline(inData, transactions[transactionCount].customerName) ||
			!getline(inData, transactions[transactionCount].packageName) ||
			!(inData >> transactions[transactionCount].userID) ||
			!(inData >> transactions[transactionCount].amount)) {
			cout << "[ERROR] Payment data file is incomplete or corrupted.\n";
			transactionCount = 0;
			nextTransactionID = 1001;
			return;
		}
		inData.ignore(10000, '\n');
		getline(inData, transactions[transactionCount].paymentMethod);
		getline(inData, transactions[transactionCount].status);
		if (transactions[transactionCount].transactionID >= nextTransactionID) {
			nextTransactionID =
				transactions[transactionCount].transactionID + 1;
		}
		transactionCount++;
	}
	inData.close();
}
// Save payment records to PaymentData.txt
void savePaymentToFile() {
	ofstream outData("PaymentData.txt");
	if (!outData) {
		cout << "[ERROR] Unable to open payment data file.\n";
		return;
	}
	outData << fixed << setprecision(2);
	for (int i = 0; i < transactionCount; i++) {
		outData << transactions[i].transactionID << endl;
		outData << transactions[i].customerName << endl;
		outData << transactions[i].packageName << endl;
		outData << transactions[i].userID << endl;
		outData << transactions[i].amount << endl;
		outData << transactions[i].paymentMethod << endl;
		outData << transactions[i].status << endl;
	}
	outData.close();
}
// Find transaction index by transaction ID
int findTransactionIndex(int transactionID) {
	for (int i = 0; i < transactionCount; i++) {
		if (transactions[i].transactionID == transactionID) {
			return i;
		}
	}
	return -1;
}
// Make payment
void paymentProcess() {
	string userID;
	int userIndex = -1;
	cout << "\n========== MAKE PAYMENT ==========\n";
	// Always use the latest records from the User and Package modules.
	loadUserFromFile();
	loadPackageFromFile();
	loadPaymentFromFile();

	if (transactionCount >= MAX_TRANSACTIONS) {
		cout << "[ERROR] Transaction storage is full.\n";
		return;
	}

	// Keep asking until an existing User ID is entered
	while (userIndex == -1) {
		cout << "Enter customer User ID: ";
		cin >> userID;
		userIndex = -1;
		// Find the customer
		for (int i = 0; i < userCount; i++) {
			if (users[i].userID == userID) {
				userIndex = i;
				break;
			}
		}
		if (userIndex == -1) {
			cout << "[ERROR] Customer not found. Please enter again.\n";
		}
	}
	// Get the package ID selected by this customer
	string selectedPackageID = users[userIndex].userPackage;
	// Find the package
	int packageIndex = -1;
	for (int i = 0; i < packageCount; i++) {
		if (packages[i].packageID == selectedPackageID) {
			packageIndex = i;
			break;
		}
	}
	if (packageIndex == -1) {
		cout << "[ERROR] Package not found.\n";
		return;
	}
	if (packages[packageIndex].packageStatus == PackageInactive) {
		cout << "[ERROR] This package is inactive.\n";
		return;
	}
	// Get the package information
	string customerName = users[userIndex].userName;
	string packageName = packages[packageIndex].packageName;
	double packagePrice = packages[packageIndex].price;
	cout << fixed << setprecision(2);
	cout << "\nCustomer Name : " << customerName << endl;
	cout << "Package       : " << packageName << endl;
	cout << "Package ID    : " << packages[packageIndex].packageID << endl;
	cout << "Duration      : "
		<< packages[packageIndex].durationDays << " days" << endl;
	cout << "Total Price   : RM " << packagePrice << endl;
	// Confirm payment
	char confirmation;
	while (true) {
		cout << "\nConfirm payment? (Y/N): ";
		cin >> confirmation;
		if (confirmation == 'Y' || confirmation == 'y') {
			cout << "Payment confirmed.\n";
			break;
		}
		else if (confirmation == 'N' || confirmation == 'n') {
			cout << "[CANCELLED] Payment was not completed.\n";
			return;
		}
		else {
			cout << "[ERROR] Invalid input. Please enter Y or N.\n";
		}
	}
	// Select payment method
	int paymentMethod;
	string paymentMethodName;
	while (true) {
		cout << "\nSelect payment method:\n";
		cout << "1. Cash\n";
		cout << "2. Online Banking\n";
		cout << "3. Credit/Debit Card\n";
		cout << "Enter choice: ";
		cin >> paymentMethod;
		if (cin.fail()) {
			cout << "[ERROR] Please enter a number.\n";
			clearInputBuffer();
			continue;
		}
		switch (paymentMethod) {
		case 1:
			paymentMethodName = "Cash";
			break;
		case 2:
			paymentMethodName = "Online Banking";
			break;
		case 3:
			paymentMethodName = "Credit/Debit Card";
			break;
		default:
			cout << "[ERROR] Invalid payment method. Please try again.\n";
			continue;
		}
		break;
	}
	PaymentTransaction newTransaction;
	newTransaction.transactionID = nextTransactionID++;
	newTransaction.userID = userID;
	newTransaction.customerName = customerName;
	newTransaction.packageName = packageName;
	newTransaction.amount = packagePrice;
	newTransaction.paymentMethod = paymentMethodName;
	newTransaction.status = "Paid";
	transactions[transactionCount] = newTransaction;
	transactionCount++;
	// Save the new payment record
	savePaymentToFile();
	cout << "\n========== PAYMENT SUCCESSFUL ==========\n";
	cout << "Transaction ID : " << newTransaction.transactionID << endl;
	cout << "Customer       : " << customerName << endl;
	cout << "Package        : " << packageName << endl;
	cout << "Amount         : RM " << packagePrice << endl;
	cout << "Payment Method : " << paymentMethodName << endl;
	cout << "Status         : Paid\n";
}
// Display receipt
void displayReceipt() {
	int transactionID;
	int transactionIndex;
	cout << "\n========== DISPLAY RECEIPT ==========\n";

	loadPaymentFromFile();
	if (transactionCount == 0) {
		cout << "[ERROR] No payment records found.\n";
		return;
	}
	while (true) {
		cout << "Enter Transaction ID: ";
		cin >> transactionID;
		if (cin.fail()) {
			cout << "[ERROR] Invalid input. Please enter a number.\n";
			clearInputBuffer();
			continue;
		}
		transactionIndex = findTransactionIndex(transactionID);
		if (transactionIndex == -1) {
			cout << "[ERROR] Transaction not found. Please enter again.\n";
			continue;
		}
		break;
	}
	PaymentTransaction receipt = transactions[transactionIndex];
	cout << fixed << setprecision(2);
	cout << "\n=====================================\n";
	cout << "              PAYMENT RECEIPT        \n";
	cout << "=====================================\n";
	cout << "Transaction ID : " << receipt.transactionID << endl;
	cout << "User ID        : " << receipt.userID << endl;
	cout << "Customer       : " << receipt.customerName << endl;
	cout << "Package        : " << receipt.packageName << endl;
	cout << "Amount         : RM " << receipt.amount << endl;
	cout << "Payment Method : " << receipt.paymentMethod << endl;
	cout << "Status         : " << receipt.status << endl;
	cout << "=====================================\n";
}
// Refund payment
void refundProcess() {
	int transactionID;
	int transactionIndex;
	cout << "\n========== REFUND PAYMENT ==========\n";
	// Refresh transactions from PaymentData.txt before processing a refund.
	loadPaymentFromFile();
	if (transactionCount == 0) {
		cout << "[ERROR] No payment records found.\n";
		return;
	}
	while (true) {
		cout << "Enter Transaction ID to refund: ";
		cin >> transactionID;
		if (cin.fail()) {
			cout << "[ERROR] Invalid input. Please enter a number.\n";
			clearInputBuffer();
			continue;
		}
		transactionIndex = findTransactionIndex(transactionID);
		if (transactionIndex == -1) {
			cout << "[ERROR] Transaction not found. Please enter again.\n";
			continue;
		}
		break;
	}
	// Use the original payment record
	PaymentTransaction& payment = transactions[transactionIndex];
	if (payment.status == "Refunded") {
		cout << "[ERROR] This transaction has already been refunded.\n";
		return;
	}
	// Display payment information before refunding
	cout << fixed << setprecision(2);
	cout << "\nPayment information:\n";
	cout << "Transaction ID : " << payment.transactionID << endl;
	cout << "Customer       : " << payment.customerName << endl;
	cout << "Package        : " << payment.packageName << endl;
	cout << "Amount         : RM " << payment.amount << endl;
	cout << "Payment Method : " << payment.paymentMethod << endl;
	cout << "Status         : " << payment.status << endl;
	char confirmation;
	while (true) {
		cout << "\nConfirm refund? (Y/N): ";
		cin >> confirmation;
		if (confirmation == 'Y' || confirmation == 'y') {
			break;
		}
		else if (confirmation == 'N' || confirmation == 'n') {
			cout << "[CANCELLED] Refund was not processed.\n";
			return;
		}
		else {
			cout << "[ERROR] Please enter Y or N.\n";
		}
	}
	// Update and save the payment record
	payment.status = "Refunded";
	savePaymentToFile();
	cout << "\n========== REFUND SUCCESSFUL ==========\n";
	cout << "Transaction ID : " << payment.transactionID << endl;
	cout << "Customer       : " << payment.customerName << endl;
	cout << "Package        : " << payment.packageName << endl;
	cout << "Refund Amount  : RM " << payment.amount << endl;
	cout << "Status         : " << payment.status << endl;
}
// Search transaction
void searchTransaction() {
	int transactionID;
	cout << "\n========== SEARCH TRANSACTION ==========\n";
	// Refresh transactions from PaymentData.txt before searching.
	loadPaymentFromFile();
	if (transactionCount == 0) {
		cout << "[ERROR] No payment transactions found.\n";
		return;
	}
	cout << "Enter Transaction ID: ";
	cin >> transactionID;
	if (cin.fail()) {
		cout << "[ERROR] Invalid input. Please enter a number.\n";
		clearInputBuffer();
		return;
	}
	int transactionIndex = findTransactionIndex(transactionID);
	if (transactionIndex == -1) {
		cout << "[ERROR] Transaction not found.\n";
		return;
	}
	PaymentTransaction payment = transactions[transactionIndex];
	cout << fixed << setprecision(2);
	cout << "\n========== TRANSACTION FOUND ==========\n";
	cout << "Transaction ID : " << payment.transactionID << endl;
	cout << "User ID        : " << payment.userID << endl;
	cout << "Customer       : " << payment.customerName << endl;
	cout << "Package        : " << payment.packageName << endl;
	cout << "Amount         : RM " << payment.amount << endl;
	cout << "Payment Method : " << payment.paymentMethod << endl;
	cout << "Status         : " << payment.status << endl;
}
// Display payment history
void displayPaymentHistory() {
	cout << "\n========== PAYMENT HISTORY ==========\n";
	// Refresh transactions from PaymentData.txt before displaying history.
	loadPaymentFromFile();
	if (transactionCount == 0) {
		cout << "[ERROR] No payment transactions found.\n";
		return;
	}
	cout << fixed << setprecision(2);
	for (int i = 0; i < transactionCount; i++) {
		cout << "\n-------------------------------------\n";
		cout << "Transaction ID : " << transactions[i].transactionID << endl;
		cout << "User ID        : " << transactions[i].userID << endl;
		cout << "Customer       : " << transactions[i].customerName << endl;
		cout << "Package        : " << transactions[i].packageName << endl;
		cout << "Amount         : RM " << transactions[i].amount << endl;
		cout << "Payment Method : " << transactions[i].paymentMethod << endl;
		cout << "Status         : " << transactions[i].status << endl;
	}
	cout << "\n-------------------------------------\n";
	cout << "Total transactions: " << transactionCount << endl;
}
// Main payment menu
void payment() {
	loadUserFromFile();
	loadPackageFromFile();

	loadPaymentFromFile();
	int paymentChoice = 0;
	do {
		cout << "\n------------------------------------------------------------------\n";
		cout << "|                                                                |\n";
		cout << "|                          Payment Menu                          |\n";
		cout << "|                                                                |\n";
		cout << "------------------------------------------------------------------\n";
		paymentMenu();
		paymentChoice = getMenuChoice(1, 6);
		switch (paymentChoice) {
		case 1:
			paymentProcess();
			break;
		case 2:
			displayReceipt();
			break;
		case 3:
			refundProcess();
			break;
		case 4:
			searchTransaction();
			break;
		case 5:
			displayPaymentHistory();
			break;
		case 6:
			cout << "\nExiting payment menu...";
			break;
		default:
			cout << "\nInvalid choice. Please enter 1 - 6.\n";
		}
	} while (paymentChoice != 6);
}
