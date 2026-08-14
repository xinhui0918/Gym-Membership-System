#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//User Information
struct GymUser
{
	int userID;
	string userName;
	string phoneNum;
	int packageID;
};

//array maximum number user
const int max_user = 50;

//UserData
GymUser users[max_user] = {

	{ 0001, "Tan", "0193257193", 1001},
	{ 0002, "Loh", "0138642947", 1002},
	{ 0003, "Ooi", "0163841946", 1004},

};
int user_count = 3;

// function prototypes
void displayHeader(string title);
void userMenu();
void clearInputBuffer();
int getMenuChoice(int low, int hight);

// function Member
void user();
void addUser();
void updateUser();
void deleteUser();
void searchUser();
void displayUser();


//Display User Menu Header
void displayHeader(string title)
{
	cout << "\n==========================================\n";
	cout << "|               " << title << "               |";
	cout << "\n==========================================\n";
}

// Display User menu
void userMenu() {
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
bool IsValidUserID(int userID) {
	for (int i = 0; i <= user_count; i++) {
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
bool IsValidPackageID(int packageID) {
	for (int i = 0; i < user_count; i++) {
		if (users[i].packageID == packageID) {
			return true;
		}
	}
	return false;
}
//valid first number = 0

void user() {
	int userChoice;
	do{
		cout << "\n==========================================\n";
		cout << "|                 User Menu              |";
		cout << "\n==========================================\n";
		userMenu();
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
			userMenu();
			break;
		default:
			cout << "Please enter 1-6" << endl;
			// case 1-6
			
		}
	} while (userChoice != 6);
}



void addUser() {

	displayHeader("Add UserID");
	int userID;
	string userName;
	string phoneNum;
	int packageID;

	// > max_user
	if ( user_count >= max_user) {
		cout << "Our User member are full" << endl;
		return user();
	}

	// Add userID
	GymUser users;
	while(true) {
		cout << "Enter UserID(first Num = 0): ";
		cin >> users.userID;
		if (IsValidUserID(users.userID)) {
			cout << "Please Enter Full Number New UserID" << endl;
			clearInputBuffer();
		}
		else {
			break;
		}

	}
	 
	//Add userName
	cout << "Enter Username (MAX 20 character): " << endl;
	cin >> users.userName;
	while (users.userName.length() > 20) {
		cout << "Username must below 20 charaters" << endl;
		cout << "Enter Username Again: ";
		cin >> users.userName;
	};

	//Add PhoneNumber
	cout << "Enter PhoneNumber(MAX 11 character): " << endl;

	while(true) {
		cin >> users.phoneNum;
		while (users.phoneNum.length() > 11 || users.phoneNum.length() < 10) {
			cout << "PhoneNumber must 10 - 11 character" << endl;
			cout << "Enter PhoneNumber Again: ";
			cin >> users.phoneNum;
		}
	
		if (IsValidPhoneNum(users.phoneNum)) {
			cout << "Phone Number had been used" << endl;
			cout << "Please Enter Again: ";
		}
		else {
			break;
		}
	}

	//Add packageID
	cout << "Enter PackageID: " << endl;
	cin >> users.packageID;
	if (IsValidPackageID(users.packageID)) {
		cout << "\n========================================\n";
		cout << "|        USER ADDED SUCCESSFULLY!      |\n";
		cout << "========================================\n";
		cout << "| User ID       : " << users.userID << "                    |" << endl;
		cout << "| Username      : " << users.userName << "                 |" << endl;
		cout << "| Phone Number  : " << users.phoneNum << "                 |" << endl;
		cout << "| Package ID    : " << users.packageID << "                 |" << endl;
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
	int userid;
	int packageid;
	string phonenum;
	
	cout << "Enter your ID: ";
	cin >> userid;
	for (int i = 0; i <= user_count; i++) {
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
					break;
				}
			}

			cout << "Enter NewPackageID: ";
			cin >> packageid;
			if (users[i].packageID == packageid) {
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
		}
	}
}

void deleteUser() {
	displayHeader("Delete User");

	int userid ;
	cout << "Enter Existing UserID ";
	cin >> userid;

	for (int i = 0; i <= user_count; i++) {
		if (users[i].userID == userid) {

			for (int j = i; j < user_count - 1; j++) {
				users[i] = users[j + 1];
			}
		user_count--;
		
		cout << "DELETE SUCCESSFULLY!" << endl;
		break;
		
		}
	}
	

}

void searchUser() {
	displayHeader("Search User");

	int userid;
	cout << "Enter UserID: ";
	cin >> userid;
	for (int i = 0; i < user_count; i++) {
		if (users[i].userID = userid) {
			cout << "UserID: " << users[i].userID << endl;
			cout << "Username: " << users[i].userName << endl;
			cout << "Phone Number: " << users[i].phoneNum << endl;
			cout << "Package ID: " << users[i].packageID << endl;
			return;
		}

	}
}

void displayUser() {
	displayHeader("Display All User");

	for (int i = 0; i <= user_count; i++) {
		cout << left
			<< setw(5) << users[i].userID 
			<< setw(7) << users[i].userName
			<< setw(13) << users[i].phoneNum
			<< setw(26) << users[i].packageID << endl;
	}

}

int main() {
	user();
	return 0;
}