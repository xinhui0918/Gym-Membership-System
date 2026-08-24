#include <iostream> 
#include <string> 
#include <cstdlib> 
#include <fstream> 
#include <iomanip> 

using namespace std;
// Forward declarations of structs so prototypes can use them
struct UserData;
struct GymPackage;
//Function declaration
// GENERAL FUNCTION
int getMenuChoice(int low, int high);
void displayHeader(string title);
void clearInputBuffer();
void MainMenu();
// USER MODULE


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
void ReportUser();
void ReportSorting(UserData users[], GymPackage packages[], int userCount, int packageCount);
void ReportRevenue();
void ReportStatistics();
void ReportPrintuser(UserData users[], GymPackage packages[], int userCount, int packageCount);
// PAYMENT MODULE
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
//UserData module	
struct UserData {
	string userID;
	string userName;
	string phoneNum;
	string packageID;
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
//structure array declaration
const int maxUsers = 50;
const int maxPackages = 50;
const int maxBooking = 50;
UserData users[maxUsers];
GymPackage packages[maxPackages];
Gymbooking bookings[maxBooking];
int userCount = 0;
int packageCount = 0;
int bookingCount = 0;
int new_booking_id = 2001;
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
			//TBA
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
			//TBA
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
		for (int i = index; i < bookingCount - 1;i++) {
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
	for (int i = 0; i < bookingCount;i++) {
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
	int choice;
	system("cls");
	do {
		displayHeader("REPORT MENU");
		cout << "1. User Report" << endl;
		cout << "2. Revenue Report" << endl;
		cout << "3. Statistics Report" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice (1-5): ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
		}
		switch (choice) {
		case 1:
			ReportUser();
			break;
		case 2:
			ReportRevenue();
			break;
		case 3:
			ReportStatistics();
			break;
		case 4:
			break;
		default:
			system("cls");
			cout << '\a' << "||Invalid choice. Please select between 1 and 5.||" << endl;
		}
	} while (choice != 4);
	system("cls");
}
void ReportUser() {
	system("cls");
	ifstream userFile("UserData.txt"); // CHANGE ACCORDING THE FILE NAME 
	ifstream packageFile("PackageData.txt"); // CHANGE ACCORDING THE FILE NAME
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
	UserData tempuser;
	for (userCount = 0; userCount < maxUsers; userCount++) {
		userFile >> tempuser.userID >> tempuser.userName >> tempuser.phoneNum >> tempuser.packageID;
		if (userFile.fail()) {
			break;
		}
		users[userCount] = tempuser;
	}
	packageFile.close();
	ReportPrintuser(users, packages, userCount, packageCount);
	string choicedirection;
	displayHeader("Press 1 to sort the report or any other key to return to the report menu ");
	cout << "\nEnter your choice: ";
	cin >> choicedirection;
	if (choicedirection == "1") {
		system("cls");
		ReportSorting(users, packages, userCount, packageCount);
	}
	else system("cls");
}
void ReportSorting(UserData users[], GymPackage packages[], int userCount, int packageCount) {
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
void ReportRevenue() {
	system("cls");
	ifstream userFile("UserData.txt"); // CHANGE ACCORDING THE FILE NAME 
	ifstream packageFile("PackageData.txt"); // CHANGE ACCORDING THE FILE NAME
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
	packageFile.close();
	UserData tempuser; // load all user data first to prepare
	for (userCount = 0; userCount < maxUsers; userCount++) {
		userFile >> tempuser.userID >> tempuser.userName >> tempuser.phoneNum >> tempuser.packageID;
		if (userFile.fail()) {
			break;
		}
		users[userCount] = tempuser;
	}
	userFile.close();
	displayHeader("REVENUE REPORT");
	cout << left << setw(20) << "Package ID"
		<< setw(20) << "Package Name"
		<< setw(20) << "Price"
		<< setw(20) << "Number of Users"
		<< setw(20) << "Total Revenue" << endl;
	for (int i = 0; i < 120; i++) {
		cout << '-';
	}
	cout << endl;
	double accumulatedTotalRevenue = 0.00;
	for (int i = 0; i < packageCount; i++) {
		int numberOfUsers = 0;
		for (int j = 0; j < userCount; j++) {
			if (users[j].packageID == packages[i].packageID) {
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
	cout << "\nTotal Revenue from all packages: " << fixed << setprecision(2) << accumulatedTotalRevenue << endl;
	cout << "\nPress any key to return to the report menu" << endl;
	system("pause");
	system("cls");
}
void ReportStatistics() {
	system("cls");
	ifstream userFile("UserData.txt"); // CHANGE ACCORDING THE FILE NAME 
	ifstream packageFile("PackageData.txt"); // CHANGE ACCORDING THE FILE NAME
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
	packageFile.close();
	UserData tempuser; // load all user data first to prepare
	for (userCount = 0; userCount < maxUsers; userCount++) {
		userFile >> tempuser.userID >> tempuser.userName >> tempuser.phoneNum >> tempuser.packageID;
		if (userFile.fail()) {
			break;
		}
		users[userCount] = tempuser;
	}
	userFile.close();
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
			if (users[j].packageID == packages[i].packageID) {
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
void ReportPrintuser(UserData users[], GymPackage packages[], int userCount, int packageCount) {
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
			if (users[i].packageID == packages[j].packageID) {
				packageFound = true;
				matchedid = j;
				break;
			}
		}
		cout << left << setw(20) << users[i].userID
			<< setw(20) << users[i].userName
			<< setw(20) << users[i].phoneNum
			<< setw(20) << users[i].packageID;
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
// PAYMENT MODULE