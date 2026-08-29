#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
using namespace std;

//function members
int findTransactionIndex(int transactionID);
void paymentProcess();
void displayReceipt();
void refundProcess();
void searchTransaction();
void displayPaymentHistory();
void payment();
void loadPaymentFromFile();
void savePaymentToFile();

//data.txt Packagefile function (重复 package code）!!!
void loadPackageFromFile();
void savePackageToFile();

//data.txt Userfile function
void loadUserFromFile();
void saveUserToFile();

enum package_status {
	Active,
	Inactive
};

struct GymPackage {
	string packageID;
	string packageName;
	double price;
	int durationDays;
	package_status packageStatus;
};

struct GymUser {
	string userID;
	string userName;
	string phoneNum;
	string userPackage;
};

struct PaymentTransaction {
	int transactionID;
	string userID;
	string customerName;
	string packageName;
	double amount;
	string paymentMethod;
	string status;
};
//User Array
const int maxUsers = 50;//array maximum number user
GymUser users[maxUsers];
int userCount = 0;

//Package (重复 package code）!!!
const int maxPackages = 50; // Maximum array capacity
GymPackage packages[maxPackages]; // Array storing all gym packages
int packageCount = 0; // Count for total active packages

//array maximum transaction
const int MAX_TRANSACTIONS = 50;

PaymentTransaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;
int nextTransactionID = 1001;

//function protoypes
void displayHeader(string title);
void paymentMenu();
void clearInputBuffer();
int getMenuChoice(int low, int high);

//Display header
void displayHeader(string title) {
	cout << "\n--------------------------------------------------------------\n";
	cout << "|                                                              |";
	cout << "|                                                              |";
	cout << "|                         " << title << "                      |";
	cout << "|                                                              |";
	cout << "\n--------------------------------------------------------------\n";
}
// Display payment menu
void paymentMenu() {
	cout << "1. Make Payment" << endl;
	cout << "2. Print Receipt" << endl;
	cout << "3. Refund Payment" << endl;
	cout << "4. Search Transaction" << endl;
	cout << "5. Payment History" << endl;
	cout << "6. Exit" << endl;
}

void clearInputBuffer() {
	cin.clear();
	cin.ignore(10000, '\n');
}

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


// Load payment records from PaymentData.txt
void loadPaymentFromFile() {
	ifstream inData("PaymentData.txt");
	if (!inData) {
		transactionCount = 0;
		nextTransactionID = 3001;
		return;
	}
	transactionCount = 0;
	nextTransactionID = 3001;
	while (transactionCount < MAX_TRANSACTIONS &&
		inData >> transactions[transactionCount].transactionID) {
		inData.ignore(10000, '\n');
		if (!getline(inData, transactions[transactionCount].customerName) ||
			!getline(inData, transactions[transactionCount].packageName) ||
			!(inData >> transactions[transactionCount].userID) ||
			!(inData >> transactions[transactionCount].amount)) {
			cout << "[ERROR] Payment data file is incomplete or corrupted.\n";
			transactionCount = 0;
			nextTransactionID = 3001;
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
	if (packages[packageIndex].packageStatus == Inactive) {
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


int main() {
	loadUserFromFile();
	loadPackageFromFile();
	loadPaymentFromFile();
    payment();
    return 0;
}
