#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


struct Gymbooking {
	string userName;
	string date;
	string statusBooking;

};

struct timeSlot {
	string slotID;
	string startTime;
	string endTime;
	bool isBooked;
};

//set the time slot and array it
const int maxSlot = 8;
timeSlot timeSlots[maxSlot] = {
	{"1", "08:00", "09:00", false},
	{"2", "09:00", "10:00", false},
	{"3", "10:00", "11:00", false},
	{"4", "11:00", "12:00", false},
	{"5", "12:00", "13:00", false},
	{"6", "13:00", "14:00", false},
	{"7", "14:00", "15:00", false},
	{"8", "15:00", "16:00", false}
};

const int maxBooking = 50;
Gymbooking bookings[maxBooking];
int bookingCount = 0;


// Function prototypes
void displayHeader(string title);
void bookingMenu();
void clearInputBuffer();
int bookingChoice(int low, int high);

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

int getMenuChoice(int low, int high) {
	int choice;
	bool valid = false;
	while (!valid) {
		cout << "Please enter your choice (" << low << "-" << high << "): ";
		cin >> choice;

		if (choice >= low && choice <= high ) {
			valid = true;
		}

		else {
			cout << "Invalid input. Please try again." << endl;
			clearInputBuffer();
		}
	}
	return choice;
}






// create booking function
void createBooking() {
	displayHeader("Add a booking.");
	string userName;
	cout << "----------------------------------" << endl;
	cout << "Please enter your username." << endl;
	cin >> userName;
	clearInputBuffer();

	cout << "Please select the time slot:\n";

	


}

// cancel booking
void cancelBooking() {

}

// delete booking
void deleteBooking() {
}

// modify booking
void modifyBooking() {
}

//display booking
void displayBooking() {
	displayHeader("All Bookings");
	if (bookingCount == 0) {
		cout << "Your booking is not found." << endl;
	}
	cout << left << setw(6) << "No." << setw(15) << "Username" << setw(15)
		<< "Time Slot" << "Status" << endl;
	for (int i = 0; i < bookingCount;i++) {
		cout << left << setw(6) << (i + 1) << setw(15) << bookings[i].userName
			<< setw(15) << bookings[i].date << bookings[i].statusBooking << endl;
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


int main(){
	booking();
	return 0;
}