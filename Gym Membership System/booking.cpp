#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <fstream>

using namespace std;


enum booking_status {
	BookingActive,
	BookingInactive
};

string status_to_string(booking_status status) {
	return (status == BookingActive) ? "Booked" : "Available";
}
struct Gymbooking {
	int bookingID;
	string userName;
	string date;
	booking_status bookingStatus;

};

//set the time slot and array it
const int maxSlot = 10;
string timeSlots[maxSlot][2] = {
	{"08:00","09:00" },
	{"09:00","10:00" },
	{"10:00","11:00" },
	{"11:00","12:00" },
	{"12:00","13:00" },
	{"13:00","14:00" },
	{"14:00","15:00" },
	{"15:00","16:00" },
	{"16:00","17:00" },
	{"17:00","18:00" },

};

bool isBooked[maxSlot] = { false,false, false, false, false, false, false, false, false, false };

//set the max of the booking
const int maxBooking = 50;
Gymbooking bookings[maxBooking];
int bookingCount = 0;
int new_booking_id = 2001;

// Function prototypes
void displayHeader(string title);
void bookingMenu();
void clearInputBuffer();
int bookingChoice(int low, int high);
string status_to_string(booking_status status);

// save n load file
void saveBooking();
void loadBooking();

// student C (booking module)
void createBooking();
void cancelBooking();
void modifyBooking();
void searchBooking();
void displayBooking();
void booking();


// Display header
void displayHeader(string title) {
	cout << "\n=====================================================================\n";
	cout << "\n" << title << endl;
	cout << "\n=====================================================================\n";
}

//display booking menu
void bookingMenu() {
	cout << "1. Create Booking" << endl;
	cout << "2. Cancel Booking" << endl;
	cout << "3. Modify Booking" << endl;
	cout << "4. Search Booking" << endl;
	cout << "5. Display Booking" << endl;
	cout << "6. Exit " << endl;
}

// clear input buffer
void clearInputBuffer() {
	cin.clear();
	cin.ignore(10000, '\n');
}

// like template
int getMenuChoice(int low, int high) {
	int choice;
	bool valid = false;
	while (!valid) {
		cout << "Please enter your choice (" << low << "-" << high << "): ";
		cin >> choice;

		if (choice >= low && choice <= high) {
			valid = true;
		}

		else {
			cout << "Invalid input. Please try again." << endl;
			clearInputBuffer();
		}
	}
	return choice;
}

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
			string range = timeSlots[i][0] + "-" + timeSlots[i][1];
			if (range == b.date) {
				isBooked[i] = true;
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
void createBooking() {
	displayHeader("Add a booking.");


	//check booking count
	if (bookingCount >= maxBooking) {
		cout << "The booking is full." << endl;
		return;
	}

	string userName;
	bool isValid = false;
	cout << "----------------------------------" << endl;
	do
	{

		cout << "Please enter your username." << endl;
		cin >> userName;
		clearInputBuffer();

		isValid = true;
		if (userName.empty())
		{
			isValid = false;
		}
		for (int i = 0; i < userName.length(); i++) {
			if (!isalpha(userName[i])) {
				isValid = false;
			}
		}

		if (!isValid) {
			cout << "Username must contain letters only." << endl;
		}

	} while (!isValid);



	cout << "Please select the time slot:\n";
	cout << "\n The available time slot : \n";
	cout << left << setw(4) << "No." << setw(8) << "Start" << setw(4) << "" << setw(8) << "End" << setw(10) << "Status" << endl;
	for (int i = 0; i < maxSlot; i++) {
		cout << left << setw(4) << (i + 1) << setw(8) << timeSlots[i][0] << setw(4) << " - " << setw(8) << timeSlots[i][1] << setw(10) << (isBooked[i] ? "Booked" : "Available") << endl;
	}

	int slot_ID = getMenuChoice(1, maxSlot);

	//check the time slot
	if (isBooked[slot_ID - 1]) {
		cout << "Sorry, the time slot has already been booked. Please try again."
			<< endl;
		return;
	}

	isBooked[slot_ID - 1] = true;

	// acess the data 2 global
	bookings[bookingCount].bookingID = new_booking_id;
	bookings[bookingCount].userName = userName;
	bookings[bookingCount].date = timeSlots[slot_ID - 1][0] + "-" + timeSlots[slot_ID - 1][1];
	bookings[bookingCount].bookingStatus = BookingActive;

	cout << "Your booking is confirmed! The booking ID is " << new_booking_id << "\nYou have booked: "
		<< timeSlots[slot_ID - 1][0] << " - " << timeSlots[slot_ID - 1][1] << endl;

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
			string range = timeSlots[i][0] + "-" + timeSlots[i][1];
			if (range == bookings[index].date) {
				isBooked[i] = false;
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
		cout << left << setw(8) << (i + 1)
			<< setw(10) << timeSlots[i][0]
			<< setw(10) << timeSlots[i][1]
			<< (isBooked[i] ? "Booked" : "Available") << endl;
	}

	int newSlot = getMenuChoice(1, maxSlot);

	if (isBooked[newSlot - 1]) {
		cout << "That slot is already booked. Modification cancelled." << endl;
		return;
	}
	// ensure the cancelled booking status is available
	for (int i = 0; i < maxSlot; i++) {
		string range = timeSlots[i][0] + "-" + timeSlots[i][1];
		if (range == bookings[index].date) {
			isBooked[i] = false;
			break;
		}
	}

	isBooked[newSlot - 1] = true;
	bookings[index].date = timeSlots[newSlot - 1][0] + "-" + timeSlots[newSlot - 1][1];

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
	cout << endl << left << setw(15) << "Booking ID" << setw(15) << "Username" << setw(15) <<
		"Time Slot" << "Status" << endl;

	// check booking and exit or not
	for (int i = 0; i < bookingCount;i++) {
		if (bookings[i].bookingID == searchID) {
			cout << left << setw(15) << bookings[i].bookingID << setw
			(15) << bookings[i].userName
				<< setw(15) << bookings[i].date << status_to_string(bookings[i].bookingStatus) << endl;
			found = true;
		}
	}
	if (!found) {
		cout << "No booking found under that booking ID." << endl;
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

	cout << left << setw(6) << "No." << setw(15) << "Booking ID" << setw(10) << "Username" << setw(15)
		<< "Time Slot" << setw(15) << "Status" << endl;
	// display all booking
	int i = 0;
	while (i < bookingCount) {
		cout << left << setw(6) << (i + 1) << setw(15) << bookings[i].bookingID << setw(10) << bookings[i].userName
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

int main() {
	loadBookingFromFile();
	booking();
	return 0;
}
