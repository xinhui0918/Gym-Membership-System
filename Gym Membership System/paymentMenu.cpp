#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
using namespace std;

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
	int userID;
	string userName;
	string phoneNum;
	int packageID;
};

struct PaymentTransaction {
    int transactionID;
    int userID;
    string customerName;
    string packageName;
    double amount;
    string paymentMethod;
    string status;
};
//array maximum transaction
const int MAX_TRANSACTIONS = 50;

PaymentTransaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;
int nextTransactionID = 1001;

// These variables should be defined only once in another file
extern GymPackage packages[50];
extern int packageCount;

extern GymUser users[50];
extern int user_count;

//function protoypes
void displayHeader(string title);
void paymentMenu();
void clearInputBuffer();
int getMenuChoice(int low, int high);

//function members
int findTransactionIndex(int transactionID);
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
int findTransactionIndex(int transactionID) {
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].transactionID == transactionID) {
            return i;
        }
    }
    return -1;
}
void paymentProcess() {
    int userID;
    int userIndex = -1;

    cout << "\n========== MAKE PAYMENT ==========\n";

    // Keep asking until an existing User ID is entered
    while (userIndex == -1) {
        cout << "Enter customer User ID: ";
        cin >> userID;

        if (cin.fail()) {
            cout << "[ERROR] Invalid User ID. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        // Find the customer
        userIndex = -1;

        for (int i = 0; i < user_count; i++) {
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
    int selectedPackageID = users[userIndex].packageID;

    // Find the package
    int packageIndex = -1;

    for (int i = 0; i < packageCount; i++) {
        if (packages[i].packageID == to_string(selectedPackageID)) {
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
    cout << "Duration      : " << packages[packageIndex].durationDays << " days" << endl;
    cout << "Total Price   : RM " << packagePrice << endl;

    // Keep asking until the user enters Y or N
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

    // Keep asking until a valid payment method is entered
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
    if (transactionCount >= MAX_TRANSACTIONS) {
        cout << "[ERROR] Transaction storage is full.\n";
        return;
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

    cout << "\n========== PAYMENT SUCCESSFUL ==========\n";
    cout << "Transaction ID : " << newTransaction.transactionID << endl;
    cout << "Customer       : " << customerName << endl;
    cout << "Package        : " << packageName << endl;
    cout << "Amount         : RM " << packagePrice << endl;
    cout << "Payment Method : " << paymentMethodName << endl;
    cout << "Status         : Paid\n";
}
void displayReceipt() {
    int transactionID;
    int transactionIndex;

    cout << "\n========== DISPLAY RECEIPT ==========\n";

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

// Simulated refund process function
void refundProcess() {
    int transactionID;
    int transactionIndex;

    cout << "\n========== REFUND PAYMENT ==========\n";

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
    // Display the payment information before refunding
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

    // Update the original payment record
    payment.status = "Refunded";

    cout << "\n========== REFUND SUCCESSFUL ==========\n";
    cout << "Transaction ID : " << payment.transactionID << endl;
    cout << "Customer       : " << payment.customerName << endl;
    cout << "Package        : " << payment.packageName << endl;
    cout << "Refund Amount  : RM " << payment.amount << endl;
    cout << "Status         : " << payment.status << endl;
}

void searchTransaction() {
    int transactionID;

    cout << "\n========== SEARCH TRANSACTION ==========\n";

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

void displayPaymentHistory() {
    cout << "\n========== PAYMENT HISTORY ==========\n";

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

int main(){
	payment();
    return 0;
}
