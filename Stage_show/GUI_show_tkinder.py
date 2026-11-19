import tkinter as tk
from tkinter import messagebox

# 存放所有演出的总列表（改用列表 []，才能不断存入 show1, show2...）
exist_show = []

def save_show():
    try:
        # 1. 从各个输入框用 .get() 获取数据
        show_id = entry_id.get()
        show_name = entry_name.get()
        
        day = entry_day.get()
        month = entry_month.get()
        year = entry_year.get()
        show_date = f"{day}/{month}/{year}"
        
        # 2. 时间计算（沿用你的逻辑，加上 :04d 保证 0000 不会变成单个 0）
        show_start = int(entry_start.get())
        show_process = int(entry_process.get())
        show_end = (show_start + (show_process * 100)) % 2400
        show_time = f"{show_start:04d}-{show_end:04d}"
        
        ticket_price = entry_price.get()
        ticket_quantity = entry_qty.get()

        # 3. 组合成当前演出的 list，并存进总列表 exist_show
        show1 = [show_id, show_name, show_date, show_time, ticket_price, ticket_quantity]
        exist_show.append(show1)

        with open("shows.txt", "a", encoding="utf-8") as file:
            file.write(f"{show_id},{show_name},{show_date},{show_time},{ticket_price},{ticket_quantity}\n")

        # 4. 终端打印核对 + 弹窗提示成功
        print("当前录入的演出：", show1)
        print("所有演出总表：", exist_show)
        messagebox.showinfo("Success", f"Show '{show_name}' saved!\nTime: {show_time}")

        # 5. 清空输入框，方便继续录入下一场演出
        for entry in [entry_id, entry_name, entry_day, entry_month, entry_year, 
                      entry_start, entry_process, entry_price, entry_qty]:
            entry.delete(0, tk.END)

    except ValueError:
        messagebox.showerror("Input Error", "Start time and Duration must be numbers!")

# --- 创建窗口界面 ---
root = tk.Tk()
root.title("Stage Show Management")
root.geometry("420x380")

# 第 0 行：Show ID
tk.Label(root, text="Show ID:").grid(row=0, column=0, padx=10, pady=8, sticky="e")
entry_id = tk.Entry(root, width=25)
entry_id.grid(row=0, column=1, sticky="w")

# 第 1 行：Show Name
tk.Label(root, text="Show Name:").grid(row=1, column=0, padx=10, pady=8, sticky="e")
entry_name = tk.Entry(root, width=25)
entry_name.grid(row=1, column=1, sticky="w")

# 第 2 行：Show Date (DD / MM / YYYY 排成一排)
tk.Label(root, text="Show Date (DD/MM/YYYY):").grid(row=2, column=0, padx=10, pady=8, sticky="e")
date_frame = tk.Frame(root)
date_frame.grid(row=2, column=1, sticky="w")
entry_day = tk.Entry(date_frame, width=4)
entry_day.pack(side="left")
tk.Label(date_frame, text="/").pack(side="left")
entry_month = tk.Entry(date_frame, width=4)
entry_month.pack(side="left")
tk.Label(date_frame, text="/").pack(side="left")
entry_year = tk.Entry(date_frame, width=6)
entry_year.pack(side="left")

# 第 3 行：Start Time
tk.Label(root, text="Start Time (0000):").grid(row=3, column=0, padx=10, pady=8, sticky="e")
entry_start = tk.Entry(root, width=25)
entry_start.grid(row=3, column=1, sticky="w")

# 第 4 行：Duration
tk.Label(root, text="Duration (Hours):").grid(row=4, column=0, padx=10, pady=8, sticky="e")
entry_process = tk.Entry(root, width=25)
entry_process.grid(row=4, column=1, sticky="w")

# 第 5 行：Ticket Price
tk.Label(root, text="Ticket Price:").grid(row=5, column=0, padx=10, pady=8, sticky="e")
entry_price = tk.Entry(root, width=25)
entry_price.grid(row=5, column=1, sticky="w")

# 第 6 行：Ticket Quantity
tk.Label(root, text="Audience Seats:").grid(row=6, column=0, padx=10, pady=8, sticky="e")
entry_qty = tk.Entry(root, width=25)
entry_qty.grid(row=6, column=1, sticky="w")

# 第 7 行：保存按钮（点击时触发 save_show 函数）
btn_save = tk.Button(root, text="Save Show", command=save_show, bg="#4CAF50", fg="white", width=18)
btn_save.grid(row=7, column=0, columnspan=2, pady=20)


root.mainloop()
