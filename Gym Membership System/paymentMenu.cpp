#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

//function protoypes
void displayHeader(string title);
void paymentMenu();
void clearInputBuffer();
int getMenuChoice(int low, int high);

//function members
void paymentProcess();
void displayReceipt();
void refundProcess();
void searchTransaction();
void displayPaymentHistory();

//Display header
void displayHeader(string title) {
	cout << "\n--------------------------------------------------------------\n";
	cout << "|                                                              |";
	cout << "|                                                              |";
	cout << "|                         " << title << "                      |";
	cout << "|                                                              |";
	cout << "\n--------------------------------------------------------------\n";
}

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

int getMenuChoice(int low, int high) {
	int choice = 0;
	bool valid = false;
	while (!valid) {
		cout << "\nPlease enter your choice (" << low << "-" << high << "): ";
		cin >> choice;

		if (choice >= low && choice <= high) {
			valid = true;
		}
		else {
			cout << " Invalid Input! Please Try again." << endl;
			clearInputBuffer();
		}
	}
}
void paymentProcess() {
	}

void displayReceipt() {
}

// Simulated refund process function
void refundProcess() {
     string customerName;
     double amount = 0.0;
     string reason;

// Get customer name
     cout << "Enter customer name: ";
     getline(cin, customerName);

// Validate refund amount
     cout << "Enter refund amount: ";
     while (!(cin >> amount) || amount <= 0) {
	       cout << "Invalid amount. Please enter a positive number: ";
	       clearInputBuffer();
     }
// Get refund reason
	 cout << "Enter refund reason: ";
     getline(cin, reason);

// Simulate refund processing
	 cout << "\nProcessing refund...\n";
	 cout << "----------------------------------\n";
	 cout << "Customer: " << customerName << "\n";
	 cout << "Amount:   $" << std::fixed << setprecision(2) << amount << "\n";
	 cout << "Reason:   " << reason << "\n";
	 cout << "Status:   Refund Approved and Processed\n";
	 cout << "----------------------------------\n";
}

void payment() {
	int paymentChoice = 0;
	do {
		cout << "\n------------------------------------------------------------------\n";
		cout << "|                                                                |";
		cout << "|                          Payment Menu                          |";
		cout << "|                                                                |";
		cout << "\n------------------------------------------------------------------\n";
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