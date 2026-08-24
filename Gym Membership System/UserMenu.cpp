#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

// Package status enum(重复 package code）
enum package_status {
	Active,
	Inactive
};

//User Information
struct GymUser
{
	string userID = "";
	string userName = "";
	string phoneNum = "";
	string userPackage = "";
};

//Package Information (重复 package code）
struct GymPackage {
	string packageID;
	string packageName;
	double price;
	int durationDays;
	package_status packageStatus;
};

//User
const int max_user = 50;//array maximum number user
GymUser users[max_user];
int user_count = 0;

//Package (重复 package code）!!!
const int maxPackages = 50; // Maximum array capacity
GymPackage packages[maxPackages]; // Array storing all gym packages
int packageCount = 0; // Count for total active packages

// function prototypes
void displayHeader(string title);
void userMenu();
void clearInputBuffer();
int getMenuChoice(int low, int hight);

// function User Membership
void addUser();
void updateUser();
void deleteUser();
void searchUser();
void displayUser();
void promptUser();

//data.txt Packagefile function (重复 package code）!!!
void loadPackageFromFile();
void savePackageToFile();

//data.txt Userfile function
void LoadUserFromFile();
void SaveUserToFile();

//(重复 package code）
void loadPackageFromFile() {
	ifstream inData("PackageData.txt");

	if (!inData) {
		packages[0] = { "1001", "BasicPackage", 29.99, 30, Active };
		packages[1] = { "1002", "StandardPackage", 49.99, 60, Active };
		packages[2] = { "1003", "PremiumPackage", 69.99, 90, Active };
		packages[3] = { "1004", "StudentPackage", 19.99, 30, Active };
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

		packages[packageCount].packageStatus = (statusInt == 0) ? Active : Inactive;
		packageCount++;
	}

	inData.close();
}

//(重复 package code）!!!
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


void LoadUserFromFile() {
	ifstream inData("UserData.txt");

	if (!inData) {
		users[0] = { "0001", "Tan", "0193257193", "1001" },
			users[1] = { "0002", "Loh", "0138642947", "1001" },
			users[2] = { "0003", "Ooi", "0163841946", "1004" },

			user_count = 3;
		SaveUserToFile();
		return;
	}

	user_count = 0;
	while (user_count < max_user && inData >> users[user_count].userID) {
		inData >> users[user_count].userName;
		inData >> users[user_count].phoneNum;
		inData >> users[user_count].userPackage;

		user_count++;
	}

	inData.close();
};

void SaveUserToFile() {
	ofstream outData("UserData.txt");

	if (!outData) {
		cout << "[Error] Unable to open User data file" << endl;
		return;
	}
	for (int i = 0; i < user_count; i++) {
		outData << users[i].userID << endl;
		outData << users[i].userName << endl;
		outData << users[i].phoneNum << endl;
		outData << users[i].userPackage << endl;
	}

	outData.close();
}

//Display User Menu Header
void displayHeader(string title)
{
	cout << "\n==========================================\n";
	cout << "                " << title << "               ";
	cout << "\n==========================================\n";
}

// Display User menu
void promptUser() {
	cout << "| 1. Add User                            |" << endl;
	cout << "| 2. Update User                         |" << endl;
	cout << "| 3. Delete User                         |" << endl;
	cout << "| 4. Search Users                        |" << endl;
	cout << "| 5. Display Users                       |" << endl;
	cout << "| 6. Exit                                |" << endl;
}

// clear input buffer
void clearInputBuffer() {
	cin.clear();
	cin.ignore(10000, '\n');
}

//
int getMenuChoice(int low, int high)
{
	int choice = 0;
	bool valid = false;
	while (!valid)
	{
		cout << "| Please enter your choice (" << low << "-" << high << "):        |";
		cout << "\n==========================================\n";
		cin >> choice;

		if (choice >= low && choice <= high) {
			valid = true;
			cout << "Success";
			clearInputBuffer();
		}
		else {
			valid = false;
			cout << "Please Enter Again" << endl;
			clearInputBuffer();
		}
	}
	return choice;
}



//user valid ID exist
bool IsValidUserID(string userID) {
	for (int i = 0; i < user_count; i++) {
		if (users[i].userID == userID) {
			return true;
		};
	}
	return false;
};

//user valid PhoneNumber exist
bool IsValidPhoneNum(string phoneNum) {
	for (int i = 0; i < user_count; i++) {
		if (users[i].phoneNum == phoneNum) {
			return true;
		};
	}
	return false;
}

//(重复 package code）!!!
bool isDuplicateID(string id) {
	for (int i = 0; i < packageCount; i++) {
		if (packages[i].packageID == id) {
			return true;
		}
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
		cout << "\n==========================================\n";
		cout << "                   User Menu              ";
		cout << "\n==========================================\n";

		promptUser();
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

	// > max_user
	if (user_count >= max_user) {
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


		if (newUser.phoneNum[0] != '0') {
			cout << "[ERROR] First Number start with (0)" << endl;
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
			users[user_count] = newUser;
			user_count++;
			SaveUserToFile();

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
	for (int i = 0; i < user_count; i++) {
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

				if (phonenum[0] != '0' || !isNumPhone(phonenum) || phonenum.length() > 11 || phonenum.length() < 10) {
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
					SaveUserToFile();

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
					cout << "Invalid PacakageID";
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
	for (int i = 0; i < user_count; i++) {
		if (users[i].userID == userid) {
			for (int j = i; j < user_count - 1; j++) {
				users[j] = users[j + 1];
			}
			user_count--;
			SaveUserToFile();

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
	for (int i = 0; i < user_count; i++) {
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
		cout << "User ID not found!" << endl;
	}
}

void displayUser() {
	displayHeader("Display All User");

	cout << left
		<< setw(9) << "UserID"
		<< setw(12) << "UserName"
		<< setw(15) << "PhoneNumber"
		<< setw(20) << "Package ID" << endl;

	for (int i = 0; i < user_count; i++) {
		cout << left << setw(1)
			<< setw(11) << users[i].userID
			<< setw(10) << users[i].userName
			<< setw(16) << users[i].phoneNum
			<< setw(21) << users[i].userPackage << endl;
	}

}

int main() {
	LoadUserFromFile();
	loadPackageFromFile();//(重复 package code）
	userMenu();
	return 0;
}
