Qt User Management System





Overview

This project is a User Management System built with Qt & C++, integrating database connectivity with Oracle. It features:

User authentication & management

Role-based access control

Whitelist system for restricting signups

Activity logging & real-time updates

Data visualization (charts for user statistics)

PDF export functionality

Features

✅ User Authentication – Secure login with HWID binding✅ Whitelist System – Only approved users can register✅ Role Management – Assign roles with different permissions✅ User Activity Logs – Tracks sign-ins, edits, and status changes✅ Database Integration – Oracle backend with empl and whitelist_users tables✅ Admin Dashboard – Modify users, update permissions, view reports✅ Export to PDF – Save user data in PDF format✅ Modern UI – Developed with Qt Designer

Screenshots



Installation

Prerequisites

Qt 6.8.1 or later

MinGW 64-bit (for Windows users)

Oracle Database XE (or compatible DBMS)

CMake (if building manually)

Setup

Clone the Repository

git clone https://github.com/yourusername/your-repo.git
cd your-repo

Configure & Build

mkdir build && cd build
cmake ..
make -j$(nproc)

Run the Application

./UserManagementApp

Database Schema

empl Table (Users)

Column

Type

Description

user_id

VARCHAR

Unique user reference ID

hwid

VARCHAR

Hardware ID for binding

role

VARCHAR

User role (Admin/User)

status

VARCHAR

Online/Offline status

password_hash

VARCHAR

SHA-256 hashed password

whitelist_users Table

Column

Type

Description

hwid

VARCHAR

Whitelisted hardware ID

permission

INT

1 (User), 2 (Admin)

Usage

1. Adding a User

Enter role & password in the UI

Click ADD USER

User is saved to the empl table

2. Whitelist a User

Admin enters HWID in whitelist_table

Click Whitelist User

HWID is stored in whitelist_users

3. Editing a User

Double-click the row in the tableWidget

Modify role/status

Click Edit in the Actions column

Changes are applied to the database

4. Deleting a User

Click Delete in the Actions column

User is removed from the system

5. Export Data to PDF

Click Export PDF

Select a save path

Users list is saved as a PDF report

Troubleshooting

Database Connection Issues

Check home.cpp for correct Oracle DBQ, UID, PWD

Ensure Oracle service is running

UI Not Updating

Restart the application

Check if whitelist_table signals are correctly connected

Contributing

Fork the repo and submit PRs

Report issues under the Issues tab

Suggestions & improvements are welcome! 🚀

License

MIT License © 2025 DALI
