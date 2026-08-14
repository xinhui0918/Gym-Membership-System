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
void ReportMenu(); 
void ReportUser();
void ReportSorting(UserData users[], GymPackage packages[], int userCount, int &packageCount);
void ReportRevenue();
void ReportStatistics();
void ReportCalculation();
void displayHeader(string title);
//Structure declaration
//UserData module
struct UserData {
    int userID;
	string userName;
	string phoneNum;
	int packageID;
};
//PackageData module
struct GymPackage {
	int packageID;
    string packageName;
    double price;
    int durationDays;
};
//structure array declaration
const int maxUsers = 50;
const int maxPackages = 50;
UserData users[maxUsers];
GymPackage packages[maxPackages];
int UserCount = 0;
int PackageCount = 0;

//Global variable 

int main() {
	// remove later
	ReportMenu();
	return 0;
}
void ReportMenu() {
	int choice;
	system("cls");
	do {
		displayHeader("REPORT MENU");
		cout << "1. User Report" << endl;
		cout << "2. Revenue Report" << endl;
		cout << "3. Statistics Report" << endl;
		cout << "4. Calculation Report" << endl;
		cout << "5. Exit" << endl;
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
			ReportCalculation();
			break;
		case 5:
			cout << "Exiting to admin menu." << endl;
			// Back to admin menu 
			break;
		default:
			system("cls");
			cout << '\a'<< "||Invalid choice. Please select between 1 and 5.||" << endl;
		}
	} while (choice != 5);
}
void displayHeader(string title) {
    cout << "=================================================================\n";
    cout << "\t\t\t" << title << endl;
    cout << "=================================================================\n\n";
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
	for (PackageCount = 0; PackageCount < maxPackages; PackageCount++) {
		packageFile >> temppackage.packageID >> temppackage.packageName >> temppackage.price >> temppackage.durationDays;
		if (packageFile.fail()) {
			break;
		}
		packages[PackageCount] = temppackage;
	}
	packageFile.close();
	//Print the user report header
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
	UserData tempuser;
	for (UserCount = 0;UserCount < maxUsers;UserCount++) {
		userFile >> tempuser.userID >> tempuser.userName >> tempuser.phoneNum >> tempuser.packageID;
		if (userFile.fail()) {
			break;
		}
		bool packageFound = false;
		int matchedid = -1; // record the id of matched package
		// search through loaded packages (valid indices are 0..PackageCount-1)
		for (int i = 0; i < PackageCount; i++) {
			if (tempuser.packageID == packages[i].packageID) {
				packageFound = true;
				matchedid = i;
				break;
			}
		}
		cout << left << setw(20) << tempuser.userID
			<< setw(20) << tempuser.userName
			<< setw(20) << tempuser.phoneNum
			<< setw(20) << tempuser.packageID;

		users[UserCount] = tempuser; // store the user data in the array for storing
		if (packageFound) {
			cout << setw(20) << packages[matchedid].packageName
				<< setw(20) << packages[matchedid].durationDays << endl;
		}
		else {
			cout << setw(20) << "No Package Found"
				<< setw(20) << "No Package Found" << endl;
		}
	}
	userFile.close();
	char choicedirection;
	cout << "\nPress 1 to sort the report or any other key to return to the report menu: ";
	cin >> choicedirection;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		ReportMenu();
	}
	if (choicedirection == '1') {
		system("cls");
		ReportSorting(users, packages, UserCount, PackageCount);
	}
	else {
		ReportMenu();
	}
}
void ReportSorting(UserData users[maxUsers],GymPackage packages[maxPackages], int userCount, int &packageCount) {
	int sortingChoice;
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
			for (int j = 0; j < UserCount - 1; j++) { // bubble sorting 
				for (int k = 0; k < UserCount - j - 1; k++) {
					if (users[k].userID > users[k + 1].userID) {
						swap(users[k], users[k + 1]);
					}
				}
			}
			system("cls");
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
			for (int i = 0; i < UserCount; i++) {
				bool packageFound = false;
				int matchedid = -1;
				for (int j = 0; j < PackageCount; j++) {
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
				if (packageFound) {
					cout << setw(20) << packages[matchedid].packageName
						<< setw(20) << packages[matchedid].durationDays << endl;
				}
				else {
					cout << setw(20) << "No Package Found"
						<< setw(20) << "No Package Found" << endl;
				}
			}
			break;
		case 2:
			for (int j = 0; j < UserCount - 1; j++) { // bubble sorting 
				for (int k = 0; k < UserCount - j - 1; k++) {
					if (users[k].userName > users[k + 1].userName) {
						swap(users[k], users[k + 1]);
					}
				}
			}
			system("cls");
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
			for (int i = 0; i < UserCount; i++) {
				bool packageFound = false;
				int matchedid = -1;
				for (int j = 0; j < PackageCount; j++) {
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
				if (packageFound) {
					cout << setw(20) << packages[matchedid].packageName
						<< setw(20) << packages[matchedid].durationDays << endl;
				}
				else {
					cout << setw(20) << "No Package Found"
						<< setw(20) << "No Package Found" << endl;
				}
			}
			break;
		default:
			system("cls");
			cout << '\a' << "||Invalid choice. Please select between 1 and 2.||" << endl;
			ReportSorting(users, packages, UserCount, PackageCount);
		}
		system("pause");
		ReportMenu();
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
	for (PackageCount = 0; PackageCount < maxPackages; PackageCount++) {
		packageFile >> temppackage.packageID >> temppackage.packageName >> temppackage.price >> temppackage.durationDays;
		if (packageFile.fail()) {
			break;
		}
		packages[PackageCount] = temppackage;
	}
	packageFile.close();
	UserData tempuser; // load all user data first to prepare
	for (UserCount = 0; UserCount < maxUsers; UserCount++) {
		userFile >> tempuser.userID >> tempuser.userName >> tempuser.phoneNum >> tempuser.packageID;
		if (userFile.fail()) {
			break;
		}
		users[UserCount] = tempuser;
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
	for (int i = 0; i < PackageCount; i++) {
		int numberOfUsers = 0;
		for (int j = 0; j < UserCount; j++) {
			if (users[j].packageID == packages[i].packageID) {
				numberOfUsers++;
			}
		}
		double totalRevenue = numberOfUsers * packages[i].price;
		cout << left << setw(20) << packages[i].packageID
			<< setw(20) << packages[i].packageName
			<< setw(20) << fixed << setprecision(2) << packages[i].price
			<< setw(20) << numberOfUsers
			<< setw(20) << fixed << setprecision(2) << totalRevenue << endl;
		accumulatedTotalRevenue += totalRevenue;
	}
	cout << "\nTotal Revenue from all packages: " << fixed << setprecision(2) << accumulatedTotalRevenue << endl;
	cout << "\nPress any key to return to the report menu" << endl;
	system("pause");
	ReportMenu();
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
	for (PackageCount = 0; PackageCount < maxPackages; PackageCount++) {
		packageFile >> temppackage.packageID >> temppackage.packageName >> temppackage.price >> temppackage.durationDays;
		if (packageFile.fail()) {
			break;
		}
		packages[PackageCount] = temppackage;
	}
	packageFile.close();
	UserData tempuser; // load all user data first to prepare
	for (UserCount = 0; UserCount < maxUsers; UserCount++) {
		userFile >> tempuser.userID >> tempuser.userName >> tempuser.phoneNum >> tempuser.packageID;
		if (userFile.fail()) {
			break;
		}
		users[UserCount] = tempuser;
	}
	userFile.close();
	displayHeader("STATISTICS REPORT");
	cout << right << setw(40) << "Total Number of User"
		<< setw(20) << "Percentage of Users" << endl;
	for (int i = 0; i < 120; i++) {
		cout << '-';
	}
	cout << endl;
	for (int i = 0; i < PackageCount; i++) {
		int numberofUsers = 0;
		for (int j = 0; j < UserCount; j++) {
			if (users[j].packageID == packages[i].packageID) {
				numberofUsers++;
			}
		}
		cout << left << setw(40) << packages[i].packageName
			 << setw(20) << numberofUsers 
			<< setw(20) << fixed << setprecision(2) << numberofUsers * 100.0 / UserCount << "%" << endl;
	}
	cout << "\nPress any key to return to the report menu" << endl;
	system("pause");
	ReportMenu();
}
void ReportCalculation() {
}