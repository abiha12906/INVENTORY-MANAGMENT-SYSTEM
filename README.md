# 📦 Inventory Management System (C++)

A console-based Inventory Management System built in C++ that allows Admin and User roles with basic product management capabilities using file handling. Admins can add, update, delete items, while users can only view and search.

---

## 🛠️ Features

### 👨‍💼 Admin:
- 🔐 Secure login (admin/admin123)
- ➕ Add item
- 📋 View all items
- 🔍 Search item by ID
- ✏️ Update item
- ❌ Delete item
- 🔁 Logout

### 👤 User:
- 🔐 Secure login (user/user123)
- 📋 View all items
- 🔍 Search item by ID
- 🔁 Logout

---

## 📁 File Structure

| File            | Description                      |
|-----------------|----------------------------------|
| `inventory.cpp` | Main source code                 |
| `inventory.txt` | Stores all inventory records     |
| `temp.txt`      | Temporary file used for updates  |

---

## 📌 Data Fields Stored

Each item in the inventory has:
- `ID` (int)
- `Name` (string)
- `Quantity` (int)
- `Price` (float)

Data is stored in this format:  
`id|name|quantity|price`

---

## 🔐 Login Credentials

| Role   | Username | Password   |
|--------|----------|------------|
| Admin  | `admin`  | `admin123` |
| User   | `user`   | `user123`  |

---

## 🚀 How to Run

### 🖥️ Compile (Windows/Linux):
System should have C++ installer (e.g Dev C++, Visual Studio)
