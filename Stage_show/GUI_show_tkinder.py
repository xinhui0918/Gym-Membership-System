import tkinter as tk
from tkinter import messagebox
from datetime import datetime
import os

# 锁定当前脚本所在目录，确保读写的是同一个 shows.txt
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
FILE_PATH = os.path.join(BASE_DIR, "shows.txt")

# ===================================================
# GLOBAL DATA
# ===================================================
admin_id = 1234
exist_show = []
max_num_show = 50


def SAVE_SHOW():
    with open(FILE_PATH, 'w') as file:
        for show in exist_show:
            line = (
                f"{show[0]},{show[1]},{show[2]},{show[3]},{show[4]},{show[5]}\n"
            )
            file.write(line)


def LOAD_SHOW():
    exist_show.clear()
    try:
        with open(FILE_PATH, 'r') as file:
            for show in file:
                if show.strip() == "":
                    continue
                data = show.strip().split(',')
                data[0] = int(data[0])
                data[4] = int(data[4])
                data[5] = int(data[5])
                exist_show.append(data)
    except FileNotFoundError:
        pass
    return exist_show


# ===================================================
# 主窗口初始化 & 清屏工具
# ===================================================
root = tk.Tk()
root.title("Stage Show Management System")
root.geometry("620x560")


def clear_screen():
    for widget in root.winfo_children():
        widget.destroy()


# ===================================================
# 1. Register 主入口
# ===================================================
def Register():
    clear_screen()
    tk.Label(root, text="Stage Show Management System", font=("Arial", 20, "bold")).pack(pady=45)
    tk.Label(root, text="Select your role:", font=("Arial", 12)).pack(pady=10)

    tk.Button(root, text="1. Customer", width=22, height=2, font=("Arial", 12),
              command=CUSTOMER).pack(pady=10)
    tk.Button(root, text="2. Admin", width=22, height=2, font=("Arial", 12),
              command=CHECK_ADMIN).pack(pady=10)


# ===================================================
# 2. Customer MENU
# ===================================================
def CUSTOMER():
    clear_screen()
    tk.Label(root, text="Welcome Customer!", font=("Arial", 18, "bold")).pack(pady=40)
    tk.Label(root, text="(Customer booking module coming soon...)", font=("Arial", 12)).pack(pady=10)
    tk.Button(root, text="Back to Menu", width=16, command=Register).pack(pady=30)


# ===================================================
# 3. Check Admin ID
# ===================================================
def CHECK_ADMIN():
    clear_screen()
    tk.Label(root, text="Admin Login", font=("Arial", 18, "bold")).pack(pady=35)
    tk.Label(root, text="Enter Admin ID Number:", font=("Arial", 12)).pack(pady=5)

    id_entry = tk.Entry(root, font=("Arial", 14), show="*")
    id_entry.pack(pady=10)
    id_entry.focus()

    def verify_login():
        try:
            entry_admin = int(id_entry.get())
        except ValueError:
            messagebox.showerror("Error", "Admin ID must be numbers.")
            return

        if entry_admin == admin_id:
            ADMIN_MENU()
        else:
            messagebox.showerror("Error", "Wrong Admin ID! Please try again.")

    tk.Button(root, text="Login", width=16, bg="#4CAF50", fg="white",
              font=("Arial", 11, "bold"), command=verify_login).pack(pady=12)
    tk.Button(root, text="Back", width=16, command=Register).pack(pady=5)


# ===================================================
# 4. ADMIN MENU (集成 View / Create / Modify / Delete)
# ===================================================
def ADMIN_MENU():
    clear_screen()
    tk.Label(root, text="Admin Control Panel", font=("Arial", 18, "bold")).pack(pady=(15, 5))

    # --- 顶部列表展示区 (View Show) ---
    tk.Label(root, text="All Registered Shows (Click a row to select ID):", font=("Arial", 10)).pack()

    list_frame = tk.Frame(root)
    list_frame.pack(pady=5)

    scrollbar = tk.Scrollbar(list_frame)
    scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

    listbox = tk.Listbox(list_frame, width=76, height=11, font=("Consolas", 9),
                         yscrollcommand=scrollbar.set)
    listbox.pack(side=tk.LEFT)
    scrollbar.config(command=listbox.yview)

    for show in exist_show:
        row_text = f"ID:{show[0]} | {show[1]:<15} | {show[2]:<10} | {show[3]} | RM{show[4]:<4} | Seats:{show[5]}"
        listbox.insert(tk.END, row_text)

    # --- 中间 ID 选择框（支持手动输入或点击列表自动填入） ---
    select_frame = tk.Frame(root)
    select_frame.pack(pady=10)

    tk.Label(select_frame, text="Target Show ID:", font=("Arial", 11, "bold")).pack(side=tk.LEFT, padx=5)
    target_id_entry = tk.Entry(select_frame, width=12, font=("Arial", 11))
    target_id_entry.pack(side=tk.LEFT, padx=5)

    def on_select_row(event):
        selection = listbox.curselection()
        if selection:
            index = selection[0]
            selected_id = exist_show[index][0]
            target_id_entry.delete(0, tk.END)
            target_id_entry.insert(0, str(selected_id))

    listbox.bind("<<ListboxSelect>>", on_select_row)

    # --- 操作按钮区 ---
    btn_frame = tk.Frame(root)
    btn_frame.pack(pady=10)

    def handle_modify():
        raw_id = target_id_entry.get().strip()
        if not raw_id.isdigit():
            messagebox.showerror("Error", "Please select a show from the list or enter a valid Show ID.")
            return
        check_id = int(raw_id)
        for show in exist_show:
            if show[0] == check_id:
                MODIFY_SHOW(show)
                return
        messagebox.showerror("Error", "SHOW ID NOT FOUND.")

    def handle_delete():
        raw_id = target_id_entry.get().strip()
        if not raw_id.isdigit():
            messagebox.showerror("Error", "Please select a show from the list or enter a valid Show ID.")
            return
        check_id = int(raw_id)
        for show in exist_show:
            if show[0] == check_id:
                DELETE_SHOW(show)
                return
        messagebox.showerror("Error", "Show ID not Found.")

    tk.Button(btn_frame, text="1. Create Show", width=15, height=2, bg="#2196F3", fg="white",
              font=("Arial", 10, "bold"), command=CREATE_SHOW).grid(row=0, column=0, padx=6, pady=5)
    tk.Button(btn_frame, text="2. Modify Show", width=15, height=2, bg="#FF9800", fg="white",
              font=("Arial", 10, "bold"), command=handle_modify).grid(row=0, column=1, padx=6, pady=5)
    tk.Button(btn_frame, text="3. Delete Show", width=15, height=2, bg="#F44336", fg="white",
              font=("Arial", 10, "bold"), command=handle_delete).grid(row=0, column=2, padx=6, pady=5)
    tk.Button(btn_frame, text="4. View Details", width=15, height=2, bg="#607D8B", fg="white",
              font=("Arial", 10, "bold"), command=VIEW_SHOW).grid(row=1, column=0, padx=6, pady=5)
    tk.Button(btn_frame, text="5. Exit / Logout", width=15, height=2,
              font=("Arial", 10), command=Register).grid(row=1, column=1, padx=6, pady=5)


# ===================================================
# 5. CREATE SHOW EVENT
# ===================================================
def CREATE_SHOW():
    if len(exist_show) >= max_num_show:
        messagebox.showerror("Error", "The Stage Show is FULL.")
        return

    clear_screen()
    next_id = 1001 if len(exist_show) == 0 else exist_show[-1][0] + 1

    tk.Label(root, text="Create New Show Event", font=("Arial", 16, "bold")).pack(pady=15)

    form = tk.Frame(root)
    form.pack(pady=5)

    # Show ID (自动生成并展示)
    tk.Label(form, text="Show ID (Auto):", font=("Arial", 11)).grid(row=0, column=0, sticky="e", padx=6, pady=7)
    tk.Label(form, text=str(next_id), font=("Arial", 11, "bold"), fg="#2196F3").grid(row=0, column=1, columnspan=3, sticky="w")

    # Name
    tk.Label(form, text="Show Name:", font=("Arial", 11)).grid(row=1, column=0, sticky="e", padx=6, pady=7)
    name_entry = tk.Entry(form, width=26, font=("Arial", 11))
    name_entry.grid(row=1, column=1, columnspan=3, sticky="w")

    # Date
    tk.Label(form, text="Date (DD/MM/YYYY):", font=("Arial", 11)).grid(row=2, column=0, sticky="e", padx=6, pady=7)
    day_entry = tk.Entry(form, width=5, font=("Arial", 11))
    day_entry.grid(row=2, column=1, sticky="w")
    month_entry = tk.Entry(form, width=5, font=("Arial", 11))
    month_entry.grid(row=2, column=2, sticky="w")
    year_entry = tk.Entry(form, width=8, font=("Arial", 11))
    year_entry.grid(row=2, column=3, sticky="w")

    # Start Time
    tk.Label(form, text="Start Time (0000):", font=("Arial", 11)).grid(row=3, column=0, sticky="e", padx=6, pady=7)
    start_entry = tk.Entry(form, width=26, font=("Arial", 11))
    start_entry.grid(row=3, column=1, columnspan=3, sticky="w")

    # Duration
    tk.Label(form, text="Duration (1-6 hrs):", font=("Arial", 11)).grid(row=4, column=0, sticky="e", padx=6, pady=7)
    process_entry = tk.Entry(form, width=26, font=("Arial", 11))
    process_entry.grid(row=4, column=1, columnspan=3, sticky="w")

    # Price
    tk.Label(form, text="Ticket Price (RM):", font=("Arial", 11)).grid(row=5, column=0, sticky="e", padx=6, pady=7)
    price_entry = tk.Entry(form, width=26, font=("Arial", 11))
    price_entry.grid(row=5, column=1, columnspan=3, sticky="w")

    # Quantity
    tk.Label(form, text="Seat Quantity:", font=("Arial", 11)).grid(row=6, column=0, sticky="e", padx=6, pady=7)
    qty_entry = tk.Entry(form, width=26, font=("Arial", 11))
    qty_entry.grid(row=6, column=1, columnspan=3, sticky="w")

    def submit_create():
        show_name = name_entry.get()
        if show_name.strip() == "" or show_name.isdigit():
            messagebox.showerror("Error", "Please enter a valid show name (cannot be empty or pure numbers).")
            return

        try:
            DAY = int(day_entry.get())
            MONTH = int(month_entry.get())
            YEAR = int(year_entry.get())
            input_date = datetime(YEAR, MONTH, DAY).date()
            today = datetime.now().date()
        except ValueError:
            messagebox.showerror("Error", "Invalid date! Please check DD / MM / YYYY.")
            return

        if input_date < today:
            messagebox.showerror("Error", "Please put a date today or after today.")
            return

        show_date = f"{DAY}/{MONTH}/{YEAR}"
        for show in exist_show:
            if show[2] == show_date:
                messagebox.showerror("Error", "The date already exists. Please change date.")
                return

        start_str = start_entry.get().strip()
        if len(start_str) != 4 or not start_str.isdigit():
            messagebox.showerror("Error", "Please enter 4 digits for Start Time (Exp: 0930).")
            return
        if int(start_str) >= 2400 or int(start_str) % 100 >= 60:
            messagebox.showerror("Error", "Invalid Time Set (0000-2359, minutes < 60).")
            return

        try:
            show_process = int(process_entry.get())
        except ValueError:
            messagebox.showerror("Error", "Duration must be a number.")
            return

        if show_process > 6 or show_process <= 0:
            messagebox.showerror("Error", "Maximum perform time is 1 to 6 hours.")
            return

        show_end = (int(start_str) + (show_process * 100)) % 2400
        show_time = f"{start_str}-{show_end:04d}"

        price_str = price_entry.get().strip()
        qty_str = qty_entry.get().strip()
        if not price_str.isdigit() or not qty_str.isdigit():
            messagebox.showerror("Error", "Ticket price and seat quantity must be valid numbers.")
            return

        new_show = [int(next_id), show_name, show_date, show_time, int(price_str), int(qty_str)]
        exist_show.append(new_show)
        SAVE_SHOW()
        messagebox.showinfo("Success", f"Show ID {next_id} Created & Saved!")
        ADMIN_MENU()

    tk.Button(root, text="Save Show", width=18, height=2, bg="#4CAF50", fg="white",
              font=("Arial", 11, "bold"), command=submit_create).pack(pady=15)
    tk.Button(root, text="Cancel", width=18, command=ADMIN_MENU).pack()


# ===================================================
# 6. MODIFY SHOW EVENT (自动预填原有数据，可直接修改任意项)
# ===================================================
def MODIFY_SHOW(target_show):
    clear_screen()
    tk.Label(root, text=f"Modify Show (ID: {target_show[0]})", font=("Arial", 16, "bold")).pack(pady=15)

    form = tk.Frame(root)
    form.pack(pady=5)

    # 拆解原有的日期和时间用于预填输入框
    old_d, old_m, old_y = target_show[2].split("/")
    old_start, old_end = target_show[3].split("-")
    old_duration = (int(old_end[:2]) - int(old_start[:2])) % 24
    if old_duration == 0:
        old_duration = 1

    # Name
    tk.Label(form, text="Show Name:", font=("Arial", 11)).grid(row=0, column=0, sticky="e", padx=6, pady=7)
    name_entry = tk.Entry(form, width=26, font=("Arial", 11))
    name_entry.insert(0, target_show[1])
    name_entry.grid(row=0, column=1, columnspan=3, sticky="w")

    # Date
    tk.Label(form, text="Date (DD/MM/YYYY):", font=("Arial", 11)).grid(row=1, column=0, sticky="e", padx=6, pady=7)
    day_entry = tk.Entry(form, width=5, font=("Arial", 11))
    day_entry.insert(0, old_d)
    day_entry.grid(row=1, column=1, sticky="w")
    month_entry = tk.Entry(form, width=5, font=("Arial", 11))
    month_entry.insert(0, old_m)
    month_entry.grid(row=1, column=2, sticky="w")
    year_entry = tk.Entry(form, width=8, font=("Arial", 11))
    year_entry.insert(0, old_y)
    year_entry.grid(row=1, column=3, sticky="w")

    # Start Time
    tk.Label(form, text="Start Time (0000):", font=("Arial", 11)).grid(row=2, column=0, sticky="e", padx=6, pady=7)
    start_entry = tk.Entry(form, width=26, font=("Arial", 11))
    start_entry.insert(0, old_start)
    start_entry.grid(row=2, column=1, columnspan=3, sticky="w")

    # Duration
    tk.Label(form, text="Duration (1-6 hrs):", font=("Arial", 11)).grid(row=3, column=0, sticky="e", padx=6, pady=7)
    process_entry = tk.Entry(form, width=26, font=("Arial", 11))
    process_entry.insert(0, str(old_duration))
    process_entry.grid(row=3, column=1, columnspan=3, sticky="w")

    # Price
    tk.Label(form, text="Ticket Price (RM):", font=("Arial", 11)).grid(row=4, column=0, sticky="e", padx=6, pady=7)
    price_entry = tk.Entry(form, width=26, font=("Arial", 11))
    price_entry.insert(0, str(target_show[4]))
    price_entry.grid(row=4, column=1, columnspan=3, sticky="w")

    # Quantity
    tk.Label(form, text="Seat Quantity:", font=("Arial", 11)).grid(row=5, column=0, sticky="e", padx=6, pady=7)
    qty_entry = tk.Entry(form, width=26, font=("Arial", 11))
    qty_entry.insert(0, str(target_show[5]))
    qty_entry.grid(row=5, column=1, columnspan=3, sticky="w")

    def submit_modify():
        show_name = name_entry.get()
        if show_name.strip() == "" or show_name.isdigit():
            messagebox.showerror("Error", "Please enter a valid show name.")
            return

        try:
            DAY = int(day_entry.get())
            MONTH = int(month_entry.get())
            YEAR = int(year_entry.get())
            input_date = datetime(YEAR, MONTH, DAY).date()
            today = datetime.now().date()
        except ValueError:
            messagebox.showerror("Error", "Invalid date!")
            return

        if input_date < today:
            messagebox.showerror("Error", "Please put a date today or after today.")
            return

        show_date = f"{DAY}/{MONTH}/{YEAR}"
        for item in exist_show:
            if item[2] == show_date and item[0] != target_show[0]:
                messagebox.showerror("Error", "The date already exists. Please change date.")
                return

        start_str = start_entry.get().strip()
        if len(start_str) != 4 or not start_str.isdigit():
            messagebox.showerror("Error", "Please enter 4 digits (Exp: 0930).")
            return
        if int(start_str) >= 2400 or int(start_str) % 100 >= 60:
            messagebox.showerror("Error", "Invalid Time Set.")
            return

        try:
            show_process = int(process_entry.get())
        except ValueError:
            messagebox.showerror("Error", "Duration must be a number.")
            return

        if show_process > 6 or show_process <= 0:
            messagebox.showerror("Error", "Maximum perform time is 6 hours.")
            return

        show_end = (int(start_str) + (show_process * 100)) % 2400
        show_time = f"{start_str}-{show_end:04d}"

        price_str = price_entry.get().strip()
        qty_str = qty_entry.get().strip()
        if not price_str.isdigit() or not qty_str.isdigit():
            messagebox.showerror("Error", "Price and Quantity must be numbers.")
            return

        # 覆盖更新原记录并保存
        target_show[1] = show_name
        target_show[2] = show_date
        target_show[3] = show_time
        target_show[4] = int(price_str)
        target_show[5] = int(qty_str)

        SAVE_SHOW()
        messagebox.showinfo("Success", "UPDATE SUCCESS!")
        ADMIN_MENU()

    tk.Button(root, text="Update & Save", width=18, height=2, bg="#FF9800", fg="white",
              font=("Arial", 11, "bold"), command=submit_modify).pack(pady=15)
    tk.Button(root, text="Cancel", width=18, command=ADMIN_MENU).pack()


# ===================================================
# 7. DELETE SHOW EVENT (保留双层确认逻辑)
# ===================================================
def DELETE_SHOW(target_show):
    first_confirm = messagebox.askyesno(
        "Confirm Delete",
        f"Are you sure you want to delete this show?\n\n"
        f"ID: {target_show[0]} | {target_show[1]} ({target_show[2]})"
    )
    if not first_confirm:
        messagebox.showinfo("Cancelled", "Cancel The Delete Process.")
        return

    double_confirm = messagebox.askyesno(
        "Double Confirm",
        f"Please double confirm!\nThis action cannot be undone.\n\nDelete '{target_show[1]}'?"
    )
    if double_confirm:
        exist_show.remove(target_show)
        SAVE_SHOW()
        messagebox.showinfo("Success", "Show Deleted Successfully!")
        ADMIN_MENU()
    else:
        messagebox.showinfo("Cancelled", "Cancel The Process.")


# ===================================================
# 8. VIEW SHOW EVENT (独立查看窗口)
# ===================================================
def VIEW_SHOW():
    clear_screen()
    tk.Label(root, text="Registered Stage Shows", font=("Arial", 16, "bold")).pack(pady=15)

    text_box = tk.Text(root, width=72, height=18, font=("Consolas", 10))
    text_box.pack(pady=10)

    header = f"{'ID':<6} | {'Title':<18} | {'Date':<11} | {'Time':<10} | {'Price':<7} | {'Seats'}\n"
    text_box.insert(tk.END, header)
    text_box.insert(tk.END, "-" * 70 + "\n")

    for show in exist_show:
        line = f"{show[0]:<6} | {show[1]:<18} | {show[2]:<11} | {show[3]:<10} | RM{show[4]:<5} | {show[5]}\n"
        text_box.insert(tk.END, line)

    text_box.config(state=tk.DISABLED)  # 设为只读，防止误改

    tk.Button(root, text="Back to Admin Menu", width=20, height=2, command=ADMIN_MENU).pack(pady=15)


# ===================================================
# 启动程序
# ===================================================
LOAD_SHOW()
Register()
root.mainloop()
