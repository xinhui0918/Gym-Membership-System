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


def REGISTER():
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
        CREATE_SHOW(max_num_show)
    else:
        print("[ERROR] Please try again.")

#==================================================================
#                         ADMIN MENU
#==================================================================
#主要在tkinder function

#==================================================================

#==================================================================
#                     Create NEW SHOW EVENT
#==================================================================
def CREATE_SHOW(max_num_show):
    #show1 = [show_id, show_name, show_date, show_time, ticket_price, ticket_quantity]

    if len(exist_show) > max_num_show: #(可以通过)
        print("[ERROR]. The Stage Show is FULL.")
    
    if len(exist_show) == 0:
        show_id = 1001
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
        for show in exist_show:
            if show[2] == show_date:
                print("The date had been exist.Please Change Date.")#########zh
                data_exist = True
    
        if not data_exist:
            print("SUCCESS")
            break

#===============GET TIME===================
    while True:
        show_start = int(input("Enter your time start (0000):"))
        if show_start > 2400:
            print("[ERROR] Put a time set (0000-2400)\n")
            continue
            
        else:    
            show_process = int(input("How many hour your may perform(max = 6): "))
            if show_process > 6 | show_process <= 0:
                print('[ERROR]Maximum perform time is 6 hours.')
                continue

            else:
                show_end = (show_start + (show_process*100)) % 2400
                show_time = str(show_start) + '-' + str(show_end)
                print("SUCCESS")
                break

        #GET PRICE
        
    while True:
        ticket_price = input("Enter your ticket price: ")
        if ticket_price.isalpha():
            print("[ERROR]Please enter the number.")
        else:
            print("SUCCESS")
            break

    #GET QUANTITY
    while True:
        ticket_quantity = input("How many seat for audien: ")
        if ticket_price.isalpha():
            print("[ERROR]Please enter the number.")
        else:
            print("SUCCESS")
            break
            
    new_show =[show_id ,show_name, show_date, show_time, ticket_price, ticket_quantity]
    exist_show.append(new_show)

    SAVE_SHOW()
        
LOAD_SHOW()
Register()
