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
	cout << "| 3. Delete User   