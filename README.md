

---

# **WalletWhiz (Smart Personal Expense Tracker)**

## Overview

The **Personal Expense Tracker** is a command-line application written in C that helps users manage their daily expenses and incomes efficiently. Unlike normal expense trackers, WalletWhiz provides advanced features such as monthly and yearly financial summaries, detailed reports, and recurring expense management. This simple yet effective tool is designed to assist individuals in maintaining their financial records securely.

---

## Features

| **Feature**                         | **Description**                                                                 |
|-------------------------------------|---------------------------------------------------------------------------------|
| **Add, View, Delete, Edit Expense** | Record new expenses with details (name, description, date, category, and amount). |
| **Add, View, Delete, Edit Income**  | Record new incomes with details (name, description, date, and amount).           |
| **Add Recurring Expense**           | Automatically add expenses periodically based on user-defined intervals.         |
| **Monthly & Yearly Reports**        | View income, expenses, maximum and minimum records, and total savings.           |
| **Log File**                        | Maintain a log of all user actions for transparency.                             |
| **Data Safety**                     | Ensures all data stays on the user's local machine with no external fetching.    |

---

## Installation

Follow these steps to install **WalletWhiz**:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Het2239/C-project.git
   ```
2. **Navigate to the Directory**:
   ```bash
   cd C-project
   ```
3. **Compile the Program**:
   ```bash
   make run
   ```
4. **Run the Program**:
   ```bash
   ./output
   ```
5. **Clean Object Files**:
   ```bash
   make clear
   ```

---

## Important Points

| **Point**                       | **Details**                                                                                      |
|----------------------------------|--------------------------------------------------------------------------------------------------|
| **Word Limit**                   | Username, password, and income/expense names: max 50 characters. Description: max 100 characters. |
| **New User Registration**        | Ensure first-time users register before adding data.                                             |
| **User Credentials**             | Credentials cannot be retrieved if lost; manual intervention required.                          |
| **System Compatibility**         | Only compatible with Linux, UNIX-based systems, or WSL.                                         |

---

## File Structure

| **File**                  | **Purpose**                                                             |
|---------------------------|-------------------------------------------------------------------------|
| **expense.c**             | Source code for managing expenses.                                     |
| **income.c**              | Source code for managing incomes.                                      |
| **report.c**              | Source code for generating reports.                                    |
| **savings.c**             | Source code for calculating savings.                                   |
| **main.c**                | Main implementation file.                                              |
| **expense.h**             | Header file for expense-related functions.                             |
| **income.h**              | Header file for income-related functions.                              |
| **savings.h**             | Header file for savings-related functions.                             |
| **report.h**              | Header file for report-related functions.                              |
| **credentials.txt**       | Stores user credentials.                                               |
| **Expense_details.txt**   | Stores expense data.                                                   |
| **Income_details.txt**    | Stores income data.                                                    |
| **log.txt**               | Stores logs of user actions.                                           |
| **Makefile**              | Automates compilation and execution tasks.                             |

---

## Contributing

Contributions are welcome! Follow these steps to contribute:

1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. Make your changes and commit:
   ```bash
   git commit -m "Add your feature"
   ```
4. Push to the branch:
   ```bash
   git push origin feature/your-feature-name
   ```
5. Open a pull request.

---

## Credits

| **S.No.** | **Name**              | **Roll No.** | **Email**                                  | **Tasks**                                  |
|-----------|-----------------------|--------------|--------------------------------------------|-------------------------------------------|
| 1         | Het Chavadia          | BT2024052    | [Het.Chavadia@iiitb.ac.in](mailto:Het.Chavadia@iiitb.ac.in)      | Functional logic and login structure      |
| 2         | Raghunandhan P        | BT2024029    | [Raghunandhan.P@iiitb.ac.in](mailto:Raghunandhan.P@iiitb.ac.in)  | Functional logic and log file implementation |
| 3         | Rohith Sai M          | BT2024144    | [Rohith.Sai@iiitb.ac.in](mailto:Rohith.Sai@iiitb.ac.in)          | Program structure and UI implementation   |
| 4         | Haneesh Reddy B       | BT2024126    | [Haneesh.Bandi@iiitb.ac.in](mailto:Haneesh.Bandi@iiitb.ac.in)    | Functional logic implementation           |
| 5         | Laksh V Chovatiya     | BT2024056    | [Laksh.Chovatiya@iiitb.ac.in](mailto:Laksh.Chovatiya@iiitb.ac.in)| Report function implementation            |
| 6         | Sai Sathvik K         | BT2024209    | [saisathvik.kadimisetty@iiitb.ac.in](mailto:saisathvik.kadimisetty@iiitb.ac.in)| Makefile and header files                 |

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE.txt) file for more details.

---

## Contact

For any questions or suggestions, please contact:  
[team.07.iiitb@gmail.com](mailto:team.07.iiitb@gmail.com)

---

