#====================
# Register part
#====================
admin_id = 1234
exist_show = []
max_show = 50

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

def CUSTOMER():
    print("Welcome Customer! (Customer menu coming soon...)")

def CHECK_ADMIN():
    entry_admin = int(input("Enter The ID number: "))
    if entry_admin == admin_id:
        print("login success")
        CREATE_SHOW()
    else:
        print("[ERROR] Please try again.")




def CREATE_SHOW():
    #show1 = [show_id, show_name, show_date, show_time, ticket_price, ticket_quantity]


    show1 = []
    show_id = input('Enter your show ID number: ')
    show1 = [show_id]
    print (show1[0])

    show_name = str(input('Enter Show Name'))
    show1.append(show_name)
    print (show1[1])

    print("Enter your show date:")
    DAY = input("DAY (DD): ")
    MONTH = input("MONTH (MM): ")
    YEAR = input("YEAR (YYYY): ")
    show_date = f"{DAY}/{MONTH}/{YEAR}"
    show1.append(show_date)
    print (show1[2])

    show_start = int(input("Enter your time start (0000):"))
    show_process = int(input("How many hour your may perform: "))
    show_end = (show_start + (show_process*100)) % 2400
    show_time = str(show_start) + '-' + str(show_end)
    show1.append(show_time)
    print(show1[3])

    ticket_price = input("Enter your ticket price: ")
    show1.append(ticket_price)

    ticket_quantity = input("How many seat for audien: ")
    show1.append(ticket_quantity)

    print(show1[1])
    print(show1[2])
    print(show1[3])
    print(show1[4])
    print(show1[5])

Register()