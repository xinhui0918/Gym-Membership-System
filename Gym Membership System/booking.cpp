#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;


enum booking_status {
	Active,
	Inactive
};

string  status_to_string(booking_status status) {
	return (status == Active) ? "Active" : "Inactive";
}



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

void saveBooking() {
	ofstream outFile;
	outFile.open("bookings.txt");

	if (!outFile) {
		cout << "Error opening file." << endl;
		return;
	}

	for (int i = 0; i < bookingCount; i++) {
		outFile << bookings[i].bookingID << " "<< bookings[i].userName << " "
			<< bookings[i].date << " "<< bookings[i].bookingStatus << "\n";
	}

	outFile.close();
}

void loadBookings() {
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


	// Task: put user name input
	// Task: change userid to bookingid and auto increment it

	cout << "Please select the time slot:\n";
	cout << "\n The avaible time slot : \n";
	for (int i = 0; i < maxSlot; i++) {
		cout << left << timeSlots[i].slotID << setw(6) << ": " << setw(5) << timeSlots[i].startTime << setw(6) << " - " <<
		setw(6) << timeSlots[i].endTime << setw(6) << (timeSlots[i].isBooked ? "Booked" : "Available")  << endl;
	}

	int slot_ID = getMenuChoice(1, maxSlot);

	//check the time slot
	if(timeSlots[slot_ID - 1].isBooked){
		cout << "Sorry, the time slot has already been booked. Please try agian."
			<< endl;
		return;
	}

	timeSlots[slot_ID - 1].isBooked = true;

	// acess the data 2 global
	bookings[bookingCount].bookingID = new_booking_id;
	bookings[bookingCount].userName = userName;
	bookings[bookingCount].date = timeSlots[slot_ID - 1].startTime + "-" + timeSlots[slot_ID - 1].endTime;
	bookings[bookingCount].bookingStatus = Active;
	
	cout << "Your booking is confirmed! The booking ID is " << new_booking_id << "\nYou have booked: " 
		<< timeSlots[slot_ID - 1].startTime<< " - " << timeSlots[slot_ID - 1].endTime << endl;
	
	new_booking_id++;
	bookingCount++;
		
	saveBooking();

		
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
	saveBooking();
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
saveBooking();

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
		while(i < bookingCount) {
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


int main() {
	loadBookings();
	booking();
	return 0;
}
