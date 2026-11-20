import tkinter as tk
from tkinter import messagebox

#Global variables
admin_id = 1234
exist_show = []
max_num_show = 50

existed_payment = []  # List to store payment details

#=========DEGUGGING PURPOSES========
#Show_id should be retrieved from the selection menu, for now it is hardcoded for debug
show_id = 1001
# show_name = "Show Name"
# show_date = "DD/MM/YYYY"
# show_time = "HHMM-HHMM"
# ticket_price = 10.0
# ticket_quantity = 100   
#=================================
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

def rewrite_bookings_file(existed_payment):
    with open("bookings.txt", "a") as file:
        for detail in existed_payment:
            # detail[6] is now total_price directly
            line = str(detail[0]) + "," + str(detail[1]) + "," + str(detail[2]) + "," + str(detail[3]) + "," + str(detail[4]) + "," + str(detail[5]) + "," + str(detail[6]) + '\n'
            file.write(line)

def add_booking(existed_payment,unique_id,show_name,show_date,show_time,ticket_price,get_amount,total_price): # booking file format: unique_id, show_name, show_date, show_time, ticket_price, get_amount, total

    existed_payment.append((unique_id,show_name,show_date,show_time,ticket_price,get_amount,total_price))

    rewrite_bookings_file(existed_payment)

def delete_booking(existed_payment, target_id):
    # keep only bookings that do not match the target_id
    existed_payment[:] = [detail for detail in existed_payment if detail[0] != target_id]
    rewrite_bookings_file(existed_payment)

def book_ticket(show_id):
    # matching with the show_id that should be retrieve from selection menu
    exist_show = LOAD_SHOW()
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


    
book_ticket(show_id) #debugging purposes, should be called from selection menu