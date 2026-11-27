import os
from datetime import datetime

# 自动将工作目录切换到当前 .py 文件所在的文件夹（Stage_show）
os.chdir(os.path.dirname(os.path.abspath(__file__)))
#===================================================
# GLOBAL DATA
#===================================================
admin_id = 1234
exist_show = []
max_num_show = 50

existed_payment = []


#===================================================
# DATABASE
#===================================================

##============XIN HUI PART==========
def LOAD_BOOKINGS():

##################有global list，所以用那个exist_payment删掉了booking_list
    try:
        with open('bookings.txt', "r") as file:

            for line in file:

                if line.strip():
                    data = line.strip().split(",")

                    # Convert to integer
                    data[0] = int(data[0])
                    data[4] = float(data[4])###price 改成float
                    data[5] = int(data[5])
                    data[6] = float(data[6])###price 改成float

                    # Old booking records have no status
                    if len(data) == 7:
                        data.append("CONFIRMED")

                    existed_payment.append(data)

    except FileNotFoundError:
        print("[ERROR] bookings.txt not found.")

    except ValueError:
        print("[ERROR] Invalid booking data.")

    return existed_payment


def SAVE_BOOKINGS(existed_payment):

    with open('bookings.txt', "w") as file:

        for booking in existed_payment:

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



def SAVE_SHOW():
    with open("shows.txt",'w') as file:
        for show in exist_show:
            line = str(show[0]) + "," + str(show[1]) + "," + str(show[2]) + "," + str(show[3]) + "," + str(show[4]) + "," + str(show[5]) + '\n'
            file.write(line)
    print("SAVE SUCCESS")

def LOAD_SHOWS():
    
##################有global list，所以用那个exist_show删掉了shows_list
    try:
        with open('shows.txt', "r") as file:

            for line in file:

                if line.strip():
                    data = line.strip().split(",")

                    data[0] = int(data[0])
                    data[4] = int(data[4])
                    data[5] = int(data[5])

                    exist_show.append(data)

    except FileNotFoundError:
        print("[ERROR] shows.txt not found.")

    except ValueError:
        print("[ERROR] Invalid show data.")

    return exist_show


def Register():
    while True:
        print("1. cumtomer")
        print("2. admin")
        num = int(input("Select your option:"))
        match num:
            case 1:
                CUSTOMER()
            case 2:
                CHECK_ADMIN()
            case _:
                print("[Error] Please enter 1/2")
                Register()
#都是主要做在tkinfder
#=====================================================

#=================================================================
#                         Customer MENU
#=================================================================
def CUSTOMER():
    if not exist_show:  # 等同于 if len(exist_show) == 0:
        print("[ERROR] Now don't have any show to select.")
        return
    
    for show in exist_show:
            print(show)

    print("Select The Show To Booking")

    show_id = int(input("Enter The show ID:"))
    for show in exist_show:
        if show_id == show[0]:
            book_ticket(show_id)
            return
    print("[ERROR]Show ID Not Found")
#==================================================================

def generate_unique_id():
    existing_ids = set()

    with open("bookings.txt", "r") as file:
        for line in file:
            if line.strip(): 
                parts = line.strip().split(",")
                booking_id = int(parts[0])
                existing_ids.add(booking_id)

    for unique_id in range(1000, 100000):
        if unique_id not in existing_ids:
            return unique_id

    raise ValueError("No unique ID available.")

###REWRITE FUNCTION 我删掉了因为我们已经有SAVE_BOOKING了，她的file funtion也是用‘W'，所以选她的

def add_booking(existed_payment,unique_id,show_name,show_date,show_time,ticket_price,get_amount,total_price): 
    # booking file format: unique_id, show_name, show_date, show_time, ticket_price, get_amount, total
    existed_payment.append([unique_id,show_name,show_date,show_time,float(ticket_price),get_amount,float(total_price),"CONFIRMED"]) ###########加了status booking所以多了confirmed ,price的全部改成float
    SAVE_BOOKINGS(existed_payment) ###改了function名

def delete_booking(existed_payment, target_id):
    # keep only bookings that do not match the target_id
    existed_payment[:] = [detail for detail in existed_payment if detail[0] != target_id]
    SAVE_BOOKINGS(existed_payment) ###改了function名

def book_ticket(show_id):
    # matching with the show_id that should be retrieve from selection menu

    for show in exist_show:
        if show[0] == show_id:
            show_name = show[1]
            show_date = show[2]
            show_time = show[3]
            ticket_price = show[4]
            ticket_quantity = show[5]

            print(f"Booking ticket for {show_name} on {show_date} at {show_time}.")
            print(f"Ticket price: ${ticket_price}, Tickets available: {ticket_quantity}")
            while True:
                try:
                    get_amount = int(input("Enter the number of tickets to book: "))
                    if get_amount > ticket_quantity:
                        print(f"Error: Only {ticket_quantity} tickets are available.")
                        raise ValueError
                    elif get_amount <= 0:
                        print("Error: Please enter a positive number.")
                        raise ValueError
                    else: 
                        break
                except ValueError:
                   print("Please enter a valid number.")

            ticket_quantity -= get_amount
            show[5] = ticket_quantity  
            print(f"Successfully booked {get_amount} tickets for {show_name}.")
            print(f"Remaining tickets: {ticket_quantity}")
            payment_ticket(show_id, show_name, show_date, show_time, ticket_price, get_amount)
            break

    else:
        print("Error: Show not found.")
        return ### suppose to return to selection menu , to be added
    return  # suppose to return to selection menu , to be added

def payment_ticket(show_id, show_name, show_date, show_time, ticket_price, get_amount):
    total_price = ticket_price * get_amount
    print(f"Ticket Receipt")
    print(f"Show: {show_name}")
    print(f"Date: {show_date}")
    print(f"Time: {show_time}")
    print(f"Number of tickets: {get_amount}")
    print(f"Total price: ${total_price:.2f}")
    print(f"Confirm your payment of ${total_price:.2f} to complete the booking.")

    ########### roleplay banking payment process
    while True:
        try:
            payment = float(input("Enter payment amount: "))
            if payment < total_price:
                print(f"Error: Payment is less than total price. Please pay at least ${total_price}.")
                raise ValueError
            else:
                change = payment - total_price
                print(f"Payment successful. Change: ${change:.2f}")
                SAVE_SHOW()  # Save the updated ticket quantity
                add_booking(existed_payment, generate_unique_id(), show_name, show_date, show_time, ticket_price, get_amount, total_price)  # Save the booking details
                print("Booking details saved successfully.")
                break
        except ValueError:
            print("Please enter a valid payment amount.")
    return # return to booking menu, and then return to selection menu


#==================================================================
#                         Check admin ID
#==================================================================
def CHECK_ADMIN():
    entry_admin = int(input("Enter The ADMIN WORKER ID number: "))
    if entry_admin == admin_id:
        print("login success")
        ADMIN_MENU()
    else:
        print("[ERROR] Please try again.")

#==================================================================
#                         ADMIN SHOW MENU
#==================================================================
def ADMIN_MENU():
    print("1. ADMIN SHOW MENU")
    print("2. Cancel Customer Ticket")
    print("3. Exit ")
    choice = input("Enter Your Selection: ")
    match choice:
        case '1':
            ADMIN_SHOW_MENU()
        case '2':
            CANCELLATION_MENU()
            return
        case '3':
            EXIT()
#==================================================================
#                         ADMIN SHOW MENU
#==================================================================
#主要在tkinder function
def ADMIN_SHOW_MENU():
    print("1. Create Show")
    print("2. Modify Show")
    print("3. Delete Show")
    print("4. View Show")
    print("5. Exit ")
    choice = input("Enter your selection: ")
    match choice:
        case '1':
            CREATE_SHOW(max_num_show)
        case '2':
            MODIFY_SHOW()
        case '3':
            DELETE_SHOW()
        case '4':
            VIEW_SHOW()
        case '5':
            EXIT()
#==================================================================


#==================================================================
#                     Create NEW SHOW EVENT
#==================================================================
def CREATE_SHOW(max_num_show):
    #show1 = [show_id, show_name, show_date, show_time, ticket_price, ticket_quantity]

    if len(exist_show) > max_num_show: #(可以通过)
        print("[ERROR]. The Stage Show is FULL.")
    
    if len(exist_show) == 0:
        show_id = int(1001)
    else:
        show_id = exist_show[-1][0] + 1

        #GET NAME

#GET DATE
    while True:
        show_name = str(input('Enter Show Name:'))#tkinder
        print("Enter your show date:")
        DAY = int(input("DAY (DD): "))
        MONTH = int(input("MONTH (MM): "))
        YEAR = int(input("YEAR (YYYY): "))

        input_date = datetime(YEAR, MONTH, DAY).date()
        today = datetime.now().date()

        if input_date < today:
            print("[ERROR] Please put a date after today.")
            continue
        else:
            show_date = str(DAY) + "/" + str(MONTH) + '/' + str(YEAR)
#******
        data_exist = False
        for show in exist_show:
            if show[2] == show_date:
                print("The date had been exist.Please Change Date.")#########zh
                data_exist = True
    
        if not data_exist:
            print("SUCCESS")
            break

#===============GET TIME===================
    while True:
        show_start = input("Enter your time start (0000):")

        if len(show_start) != 4:
            print("[ERROR]", "Please enter 4 digit(Exp:0930).")
            continue
        elif int(show_start) > 2400 or int(show_start) % 100 >= 60:
            print("[ERROR], Invalid Time Set.\n")
            continue

        else:    
            show_process = int(input("How many hour your may perform(max = 6): "))
            if show_process > 6 or show_process <= 0:
                print('[ERROR]Maximum perform time is 6 hours.')
                continue

            else:
                show_end = (int(show_start) + (show_process*100)) % 2400
                show_time = str(show_start) + '-' + f"{show_end:04d}"
                print("SUCCESS")
                break

    #GET PRICE
    while True:
        ticket_price = input("Enter your ticket price: ")
        if not ticket_price.isdigit():
            print("[ERROR]Please enter the number.")
        else:
            print("SUCCESS")
            break

    #GET QUANTITY
    while True:
        ticket_quantity = input("How many seat for audien: ")
        if not ticket_price.isdigit():
            print("[ERROR]Please enter the number.")
        else:
            print("SUCCESS")
            break
            
    new_show =[int(show_id) ,show_name, show_date, show_time, int(ticket_price), int(ticket_quantity)]
    exist_show.append(new_show)
    print(new_show[0:6])

    SAVE_SHOW()
    ADMIN_SHOW_MENU()

#==================================================================
#                     MODIFY SHOW EVENT
#==================================================================
def MODIFY_SHOW():
    #Check 目前有没有show存在
    if not exist_show:  # 等同于 if len(exist_show) == 0:
        print("[ERROR] Now don't have any show to modify.")
        print("Please Create A New Show")
        return

    check_show = int(input("Enter the SHOW_ID: "))
    for show in exist_show:
        if show[0] == check_show:
            for booking in existed_payment:
                if (booking[1] == show[1]) and (booking[2] == show[2]) and (booking[3] == show[3]):
                    print("[RECJECTED] The customer have book this show already")
                    return
            
            print("Found The Show ID. SUCCESS.\n")

            while True:
                print(show)
                print("1. Name")
                print("2. Date")
                print("3. Time")
                print("4. Ticket Price")
                print("5. Ticket Quantity")
                print("6. Exit")
                choice = input("Which information you want to modify?\n")
                match choice:
                    case '1':# GET NAME
                        show_name = str(input('Enter Show Name:'))#tkinder
                        show[1] = show_name
                        SAVE_SHOW()
                        print("UPDATE SUCCESS")

                    case '2':# GET DATE
                        while True:
                            print("Enter your show date:")
                            DAY = int(input("DAY (DD): "))
                            MONTH = int(input("MONTH (MM): "))
                            YEAR = int(input("YEAR (YYYY): "))

                            input_date = datetime(YEAR, MONTH, DAY).date()
                            today = datetime.now().date()

                            if input_date < today:
                                print("[ERROR] Please put a date after today.")
                                continue
                            else:
                                show_date = str(DAY) + "/" + str(MONTH) + '/' + str(YEAR)
                            
                            data_exist = False
                            for item in exist_show:
                                if item[2] == show_date and item[2] != show[2]:
                                    print("The date had been exist.Please Change Date.")#########zh
                                    data_exist = True
                                    break
                            
                            if not data_exist:
                                show[2] = show_date
                                SAVE_SHOW()
                                print("UPDATE SUCCESS")
                                break

                    case '3':# GET TIME
                            while True:
                                show_start = input("Enter your time start (0000):")
                                if len(show_start) != 4:
                                    print("[ERROR]", "Please enter 4 digit(Exp:0930).")
                                    continue
                                
                                elif not show_start.isdigit():
                                    print("[ERROR]", "Please Enter the number.")
                                    continue
                                
                                elif int(show_start) >= 2400 or int(show_start) % 100 >= 60:
                                    print("[ERROR], Invalid Time Set.\n")
                                    continue
                                
                                else:    
                                    show_process = int(input("How many hour your may perform(max = 6): "))
                                    if show_process > 6 or show_process <= 0:
                                        print('[ERROR]Maximum perform time is 6 hours.')
                                        continue

                                    else:
                                        show_end = (int(show_start) + (show_process*100)) % 2400
                                        show_time = str(show_start) + '-' + f"{show_end:04d}"
                                        show[3] = show_time
                                        SAVE_SHOW()
                                        print("UPDATE SUCCESS")
                                        break

                    case '4':#GET PRICE
                        while True:
                            ticket_price = input("Enter your ticket price: ")
                            if not ticket_price.isdigit():
                                print("[ERROR]Please enter the number.")
                            else:
                                show[4] = int(ticket_price)
                                SAVE_SHOW()
                                print("UPDATE SUCCESS")
                                break
                            

                    case '5':#GET QUANTITY
                        while True:
                            ticket_quantity = input("How many seat for audien: ")
                            if not ticket_quantity.isdigit():
                                print("[ERROR]Please enter the number.")
                            else:
                                show[5] = int(ticket_quantity)
                                SAVE_SHOW()
                                print("UPDATE SUCCESS")
                                break
                    case '6':
                        print('[SUCCESS]Exit to Admin Menu')
                        SAVE_SHOW()
                        return

                    case _:
                        print("[ERROR] Please Enter 1-6.")

    print("[ERROR] SHOW ID NOT FOUND.")


#==================================================================
#                     DELETE SHOW EVENT
#==================================================================
def DELETE_SHOW():
#Check 目前有没有show存在
    if not exist_show:  # 等同于 if len(exist_show) == 0:
        print("[ERROR] Now don't have any show to Delete.")
        print("Please Create A New Show")
        return
    check_show_id = int(input("Enter the SHOW_ID: "))
    for show in exist_show:
        if show[0] == check_show_id:
            for booking in existed_payment:
                if (booking[1] == show[1]) and (booking[2] == show[2]) and (booking[3] == show[3]):
                    print("[RECJECTED] The customer have book this show already")
                    return

            print("[SUCCESS] Show ID Found")
            while True:
                choice = str(input("Enter 'Yes'/'No': "))
                if choice == 'Yes' or choice == 'yes':
                    double_check = input("Please double confirm.[Yes]")
                    if double_check == 'Yes' or double_check == 'yes':
                        exist_show.remove(show)
                        SAVE_SHOW()
                        print("[SUCCESS] Show Deleted")
                        return
                    else:
                        print("Cancel The Process")
                        return
                elif choice == 'No' or choice == 'no':
                    print("Cancal The Delete Process")
                    return
                else:
                    print("[Error]. Please Enter (Yes/No)")
                    continue

    print("[ERROR]Show ID not Found.")
#==================================================================
#                     SEARCH SHOW EVENT
#==================================================================
def VIEW_SHOW():
    #Check 目前有没有show存在
    if not exist_show:  # 等同于 if len(exist_show) == 0:
        print("[ERROR] Now don't have any show to View.")
        print("Please Create A New Show")
        return

    for show in exist_show:
        display_show = show[0], show[1], show[2], show[3], show[4], show[5]
        print(display_show)
    
    check = input("Click to return")

    ADMIN_SHOW_MENU()


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
    #///////////////////////////////我删了，有load进list了所以不用了

    # Dictionary: Booking ID as key, booking record as value
    booking_dict = {
    booking[0]: booking
    for booking in existed_payment
    }

    # Set: store unique Booking IDs
    booking_ids = set(booking_dict.keys())

    # Dictionary: show name, date and time as tuple key
    show_dict = {
    (show[1], show[2], show[3]): show
    for show in exist_show
    }

    if not existed_payment or not exist_show:
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

        SAVE_BOOKINGS(existed_payment)
        SAVE_SHOW()

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

#==================================================================
#                     EXIT ADMIN MENU
#==================================================================
def EXIT():
    return

#====================================================
# MAIN PROGRAM
#====================================================
if __name__ == "__main__":
    LOAD_SHOWS()
    LOAD_BOOKINGS()
    Register()