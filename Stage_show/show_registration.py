from datetime import datetime
#===================================================
# GLOBAL DATA
#===================================================
admin_id = 1234
exist_show = []
max_num_show = 50

def SAVE_SHOW():
    with open("shows.txt",'w') as file:
        for show in exist_show:
            line = str(show[0]) + "," + str(show[1]) + "," + str(show[2]) + "," + str(show[3]) + "," + str(show[4]) + "," + str(show[5]) + '\n'
            file.write(line)
    print("SAVE SUCCESS")

def LOAD_SHOW():
    with open("shows.txt", 'r') as file:
        for show in file:
            data = show.strip().split(',')

            data[0] = int(data[0])
            data[4] = int(data[4])
            data[5] = int(data[5])
        
            exist_show.append(data)
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
    print("Welcome Customer! (Customer menu coming soon...)")

#==================================================================


#==================================================================
#                         Check admin ID
#==================================================================
def CHECK_ADMIN():
    entry_admin = int(input("Enter The ID number: "))
    if entry_admin == admin_id:
        print("login success")
        ADMIN_MENU()
    else:
        print("[ERROR] Please try again.")

#==================================================================
#                         ADMIN MENU
#==================================================================
#主要在tkinder function
def ADMIN_MENU():
    print("1. Create Show")
    print("2. Modify Show")
    print("3. Delete Show")
    print("4. View Show")
    print("5. Exit ")
    choice = input("Enter your selection")
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
                show_time = str(show_start) + '-' + str(show_end)
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
            
    new_show =[int(show_id) ,show_name, show_date, show_time, ticket_price, ticket_quantity]
    exist_show.append(new_show)
    print(new_show[0:6])

    SAVE_SHOW()
    ADMIN_MENU()

#==================================================================
#                     MODIFY SHOW EVENT
#==================================================================
def MODIFY_SHOW():
    check_show = int(input("Enter the SHOW_ID: "))
    for show in exist_show:
        if show[0] == check_show:
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
    check_show_id = int(input("Enter the SHOW_ID: "))
    for show in exist_show:
        if show[0] == check_show_id:
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
    for show in exist_show:
        display_show = show[0], show[1], show[2], show[3], show[4], show[5]
        print(display_show)
    
    check = input("Click to return")

    ADMIN_MENU()
#==================================================================
#                     EXIT ADMIN MENU
#==================================================================
def EXIT():
    return

LOAD_SHOW()
Register()
