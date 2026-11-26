#====================================================
# GLOBAL DATA
#====================================================

BOOKING_FILE = "bookings.txt"
SHOW_FILE = "shows.txt"

#====================================================
# LOAD BOOKING DATA
#====================================================

def LOAD_BOOKINGS():

    booking_list = []

    try:
        with open(BOOKING_FILE, "r") as file:

            for line in file:

                if line.strip():
                    data = line.strip().split(",")

                    # Convert to integer
                    data[0] = int(data[0])
                    data[4] = int(data[4])
                    data[5] = int(data[5])
                    data[6] = int(data[6])

                    # Old booking records have no status
                    if len(data) == 7:
                        data.append("CONFIRMED")

                    booking_list.append(data)

    except FileNotFoundError:
        print("[ERROR] bookings.txt not found.")

    except ValueError:
        print("[ERROR] Invalid booking data.")

    return booking_list


#====================================================
# LOAD SHOW DATA
#====================================================

def LOAD_SHOWS():

    show_list = []

    try:
        with open(SHOW_FILE, "r") as file:

            for line in file:

                if line.strip():
                    data = line.strip().split(",")

                    data[0] = int(data[0])
                    data[4] = int(data[4])
                    data[5] = int(data[5])

                    show_list.append(data)

    except FileNotFoundError:
        print("[ERROR] shows.txt not found.")

    except ValueError:
        print("[ERROR] Invalid show data.")

    return show_list


#====================================================
# SAVE SHOW DATA
#====================================================

def SAVE_SHOWS(show_list):

    with open(SHOW_FILE, "w") as file:

        for show in show_list:

            line = (
                str(show[0]) + "," +
                str(show[1]) + "," +
                str(show[2]) + "," +
                str(show[3]) + "," +
                str(show[4]) + "," +
                str(show[5]) + "\n"
            )

            file.write(line)


#====================================================
# SAVE BOOKING DATA
#====================================================

def SAVE_BOOKINGS(booking_list):

    with open(BOOKING_FILE, "w") as file:

        for booking in booking_list:

            line = (
                str(booking[0]) + "," +
                str(booking[1]) + "," +
                str(booking[2]) + "," +
                str(booking[3]) + "," +
                str(booking[4]) + "," +
                str(booking[5]) + "," +
                str(booking[6]) + "," +
                str(booking[7]) + "\n"
            )

            file.write(line)


#====================================================
# FIND BOOKING
#====================================================

def FIND_BOOKING(booking_dict, target_id):

    return booking_dict.get(target_id)


#====================================================
# FIND SHOW
#====================================================

def FIND_SHOW(show_dict, booking):

    # Tuple: match show name, date and time
    
    show_key = (
        booking[1],
        booking[2],
        booking[3],
    )

    return show_dict.get(show_key)


#====================================================
# BOOKING CANCELLATION MODULE
#====================================================

def CANCEL_BOOKING():

    print("\n===================================")
    print("\tBOOKING CANCELLATION")
    print("===================================")

    # Load existing records
    booking_list = LOAD_BOOKINGS()
    show_list = LOAD_SHOWS()

    # Dictionary: Booking ID as key, booking record as value
    booking_dict = {
    booking[0]: booking
    for booking in booking_list
    }

    # Set: store unique Booking IDs
    booking_ids = set(booking_dict.keys())

    # Dictionary: show name, date and time as tuple key
    show_dict = {
    (show[1], show[2], show[3]): show
    for show in show_list
    }

    if not booking_list or not show_list:
        print("[ERROR] Booking or show data is unavailable.")
        return

    # Get booking ID
    print("Please enter your Booking ID.")
    print("Example: 1001")

    while True:

        try:
            target_id = int(input("\nEnter Booking ID (0 to return): "))

            if target_id == 0:
                print("[INFO] Returning to Cancellation Menu.")
                return

            if target_id < 1000:
                print("[ERROR] Booking ID must be at least 1000.")
                print("Please enter your Booking ID again.")
                continue

            # Set: check whether Booking ID exists
            if target_id not in booking_ids:

                print("[ERROR] Booking ID not found.")
                print("Please enter your Booking ID again.")
                continue

            # Dictionary: find booking record
            booking = FIND_BOOKING (booking_dict, target_id)

            break

        except ValueError:
            print("[ERROR] Please enter a valid Booking ID.")

    # Check booking status
    if booking[7].upper() == "CANCELLED":

        print("[ERROR] This booking has already been cancelled.")
        return

    # Find the corresponding show
    show = FIND_SHOW(show_dict, booking)

    if show is None:

        print("[ERROR] Corresponding show not found.")
        print("[ERROR] Cancellation cannot be completed.")
        return

    # Display booking information
    print("\n\tBooking Details")
    print("-----------------------------------")
    print("Booking ID :", booking[0])
    print("Show Name :", booking[1])
    print("Show Date :", booking[2])
    print("Show Time :", booking[3])
    print("Ticket Quantity :", booking[5])
    print("Total Amount :", booking[6])
    print("Status :", booking[7])

    # Confirmation
    while True:

        confirm = input(
            "\nAre you sure you want to cancel? (Yes/No): "
        ).strip().upper()

        if confirm == "YES":
            break

        elif confirm == "NO":
            print("[INFO] Cancellation process stopped.")
            return

        else:
            print("[ERROR] Please enter Yes or No.")

    #========================================
    # Update booking status
    #========================================

    booking[7] = "CANCELLED"

    #========================================
    # Restore ticket quantity
    #========================================

    show[5] += booking[5]

    #========================================
    # Save updated records
    #========================================

    try:

        SAVE_BOOKINGS(booking_list)
        SAVE_SHOWS(show_list)

        print("\n[SUCCESS] Booking cancelled successfully.")
        print("Booking Status :", booking[7])
        print("Tickets Restored :", booking[5])
        print("Available Tickets :", show[5])

    except OSError:

        print("[ERROR] Unable to save the updated files.")


#====================================================
# CANCELLATION MENU
#====================================================

def CANCELLATION_MENU():

    while True:

        print("\n===================================")
        print("\tCANCELLATION MENU")
        print("===================================")
        print("1. Cancel Booking")
        print("2. Return to Main Menu")

        choice = input("Enter your choice: ")

        if choice == "1":

            CANCEL_BOOKING()

        elif choice == "2":

            print("[INFO] Returning to Main Menu.")
            break

        else:

            print("[ERROR] Please enter 1 or 2.")


#====================================================
# MAIN PROGRAM
#====================================================

if __name__ == "__main__":

    CANCELLATION_MENU()