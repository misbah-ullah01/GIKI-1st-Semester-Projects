# GIKI-1st-Semester-Projects


**Splitwise App Clone (Console-Based)**

This repository contains the source code for a simple console-based application that emulates some core functionalities of Splitwise, a popular expense-tracking and splitting platform.

**Features:**

- **User Accounts:** Create and manage user accounts with unique IDs and passwords.
- **Group Creation:** Create groups with names and add members to them.
- **Expense Tracking:** 
    - Add expenses to groups.
    - Specify the amount, payer, and members involved.
    - Support both equal and unequal expense splitting.
- **Settlement Calculation:** 
    - Determine how much each member owes to others based on the recorded expenses.
- **Expense Display:** 
    - View detailed expense information for each group.
- **Data Persistence:** 
    - User data, group information, and expense records are saved to files for future use.

**How to Use:**

1. **Compile:** Compile the C++ source code using a suitable compiler (e.g., g++).
2. **Run:** Execute the compiled program.
3. **Interact:** Follow the on-screen instructions to login/signup, create groups, add expenses, and settle up.

**File Structure:**

- `splitwise.cpp`: Contains the main program logic and all the functions.
- `groups.txt`: Stores group information (name, members, expenses).
- `users.txt`: Stores user account details (name, ID, password).
- `variables.txt`: Stores application-level variables (number of accounts, groups).

**Limitations:**

- Basic console interface with limited user experience.
- No graphical user interface (GUI).
- Limited error handling and input validation.
- Basic file handling for data persistence.

**Future Enhancements:**

- Implement a more user-friendly GUI.
- Add advanced features like recurring expenses, IOUs, and debt reminders.
- Improve error handling and input validation.
- Enhance data persistence and security.
- Consider using a database for more robust data management.

**Contributing:**

Contributions are welcome! Feel free to fork this repository, make improvements, and submit pull requests.

**Disclaimer:**

This is a simplified version of Splitwise and may not have all the features or functionalities of the actual application. It is intended for educational and learning purposes.

**Note:**

This README provides a basic overview. You may need to adapt it further based on the specific features and complexity of your implementation.

I hope this README is helpful!
