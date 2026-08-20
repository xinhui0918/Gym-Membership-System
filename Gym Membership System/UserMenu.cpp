#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

//User Information
struct GymUser
{
	string userID = "";
	string userName = "";
	string phoneNum = "";
	string packageID = "";
};

//Package Information
struct GymPackage
{
	string packageID = "";
};

//User
const int max_user = 50;//array maximum number user
GymUser users[max_user];
int user_count = 0;

//Package 
const int max_package = 50;//array maximum number user
GymPackage packages[max_package];
int package_count = 0;

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

//function integer number
void isNumber();

//data.txt file function
void LoadUserFromFile();
void SaveUserToFile();

void LoadUserFromFile() {
	ifstream inData("UserData.txt");
	
	if (!inData) {
		users[0] = { "0001", "Tan", "0193257193","1001"},
		users[1] = { "0002", "Loh", "0138642947","1001"},
		users[2] = { "0003", "Ooi", "0163841946","1004"},

		user_count = 3;
		SaveUserToFile();
		return;
	}

	while (user_count < max_user && inData >> users[user_count].userID) {
		inData >> users[user_count].userName;
		inData >> users[user_count].phoneNum;
		inData >> users[user_count].packageID;

		user_count++;
	}

	inData.close();
};

void SaveUserToFile() {
	ofstream outData("UserData.txt");

	if (!outData) {
		cout << "[Error] Unable to open data file" << endl;
		return;
	}
	for (int i = 0; i < max_user; i++) {
		outData << users[i].userID << endl;
		outData << users[i].userName << endl;
		outData << users[i].phoneNum << endl;
		outData << users[i].packageID << endl;
	}

	outData.close();
}

//Display User Menu Header
void displayHeader(string title)
{
	cout << "\n==========================================\n";
	cout << "|               " << title << "               |";
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

//package valid packageID exist
bool IsValidPackageID(string packageID) {
	for (int i = 0; i < user_count; i++) {
		if (users[i].packageID == packageID) {
			return true;
		}
	}
	return false;
}

//just approve the number
bool isNumber(string userID) {
	if (userID.empty()) {
		return false;
	}
	for (int i = 0; i < userID.length(); i++) {
		if (!isdigit(userID[i])) {
			return false;
		}
		else {
			return true;
		}
	}

}
//valid first number = 0

void userMenu() {
	int userChoice;
	do{
		cout << "\n==========================================\n";
		cout << "|                 User Menu              |";
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
			cout << "Exiting User Menu" << endl ;
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
	if ( user_count >= max_user) {
		cout << "Our User member are full" << endl;
		return;
	}

	// Add userID
	GymUser newUser;
	cout << "Enter UserID(first Num = 0): ";
	while(true) {
		cin >> newUser.userID;

		if (IsValidUserID(newUser.userID)) {
			cout << "UserID already exist. Please Try Again:" << endl;
			clearInputBuffer();
		}
		else if (newUser.userID[0] != '0') {
			cout << "First Number start with (0):";

		}
		else if (!isNumber(newUser.userID)) {
			cout << "UserID must contain numbers only!" << endl;
		}
		else {
			break;
		}

	}
	 
	//Add userName
	cout << "Enter Username (MAX 4 character): " << endl;
	cin >> newUser.userName;
	while (newUser.userName.length() > 4 || newUser.userName.empty()) {
		cout << "Username must below 5 charaters" << endl;
		cout << "Enter Username Again: ";
		cin >> newUser.userName;
	};

	//Add PhoneNumber
	cout << "Enter PhoneNumber(MAX 11 character): " << endl;

	while(true) {
		cin >> newUser.phoneNum;
		if (newUser.phoneNum.length() > 11 || newUser.phoneNum.length() < 10) {
			cout << "PhoneNumber must 10 - 11 character" << endl;
			cout << "Please try Again: ";
		}
		else if (IsValidPhoneNum(newUser.phoneNum)) {
			cout << "Phone Number had been used. Please Try Again:" << endl;
		}
		else {
			break;
		}
	}

	//Add packageID
	cout << "Enter PackageID: " << endl;
	cin >> newUser.packageID;
	if (IsValidPackageID(newUser.packageID)) {

		users[user_count] = newUser;
		user_count++;
		SaveUserToFile();

		cout << "\n========================================\n";
		cout << "|        USER ADDED SUCCESSFULLY!      |\n";
		cout << "========================================\n";
		cout << " User ID       : " << newUser.userID << endl;
		cout << " Username      : " << newUser.userName << endl;
		cout << " Phone Number  : " << newUser.phoneNum << endl;
		cout << " Package ID    : " << newUser.packageID << endl;
		cout << "========================================\n";
	}
	else {
		cout << "\n==========================================\n";
		cout << "| [ERROR] Unaccepted! Invalid Package ID.|\n";
		cout << "| User record was NOT saved.             |";
		cout << "\n==========================================\n";
		return;
	};
}

void updateUser() {
	displayHeader("Update User");
	string userid;
	string packageid;
	string phonenum;
	
	cout << "Enter your ID: ";
	cin >> userid;
	for (int i = 0; i < user_count; i++) {
		if (users[i].userID == userid) {
			cout << "\n Found The UserID! \n";

			cout << "Enter New Username: ";
			cin >> users[i].userName;

			cout << "Enter New Phone Number:";
			while (true) {
				cin >> phonenum;

				if (IsValidPhoneNum(phonenum)) {
					cout << "Phone Number have been exist" << endl;
					cout << "Please Enter New Phone Number : ";
				}
				else {
					users[i].phoneNum = phonenum;
					break;
				}
			}

			cout << "Enter current packageID: ";
			cin >> packageid;
			if (users[i].packageID == packageid) {
				SaveUserToFile();
				cout << "\n========================================\n";
				cout << "|        USER UPDATE SUCCESSFULLY!      |\n";
				cout << "========================================\n";
				cout << "New UserID: " << users[i].userID << endl;
				cout << "New Username: " << users[i].userName << endl;
				cout << "New phoneNum: " << users[i].phoneNum << endl;
				cout << "New package: " << users[i].packageID << endl;
				cout << "========================================\n";
			}
			else {
				cout << "Invalid PacakageID";
			}
			return;
		}
		else {
			cout << "User ID not found!" << endl;
			break;
		}
	}
}

void deleteUser() {
	displayHeader("Delete User");

	string userid ;
	cout << "Enter Existing UserID ";
	cin >> userid;

	for (int i = 0; i < user_count; i++) {
		if (users[i].userID == userid) {

			for (int j = i; j < user_count - 1; j++) {
				users[j] = users[j + 1];
			}
		user_count--;
		SaveUserToFile();
		
		cout << "DELETE SUCCESSFULLY!" << endl;
		return;
		
		}
		else {
			cout << "User ID not found!" << endl;
			break;
		}
	}
	

}

void searchUser() {
	displayHeader("Search User");

	string userid;
	cout << "Enter UserID: ";
	cin >> userid;
	for (int i = 0; i < user_count; i++) {
		if (users[i].userID == userid) {
			cout << "UserID: " << users[i].userID << endl;
			cout << "Username: " << users[i].userName << endl;
			cout << "Phone Number: " << users[i].phoneNum << endl;
			cout << "Package ID: " << users[i].packageID << endl;
			return;
		}
		else {
			cout << "User ID not found!" << endl;
			break;
		}
	}
}

void displayUser() {
	displayHeader("Display All User");

	for (int i = 0; i < user_count; i++) {
		cout << left
			<< setw(5) << users[i].userID 
			<< setw(7) << users[i].userName
			<< setw(13) << users[i].phoneNum
			<< setw(26) << users[i].packageID << endl;
	}

}

int main() {
	LoadUserFromFile();
	userMenu();
	return 0;
}
