

* * *

WalletWhiz (Smart Personal Expense Tracker)
===========================================

Overview
--------

The **Personal Expense Tracker** is a command-line application written in C that helps users manage their daily expenses and incomes efficiently. Aside from normal expense trackers where users can add, view, and delete expenses and incomes while keeping track of the total expenditure, our software also provides additional feature of viewing monthly and yearly income statements , expenses and also detailed reports, WalletWhiz also has afeature to add recurring expenses. This simple yet effective tool is designed to assist individuals in maintaining their financial records.

Features
--------

*   **Add, View, Delete and Edit Expense**: Record a new expense with details such as name, description, date, category, and amount.Also you can view delete or edit a particular expense.
*   **Add, View, Delete and Edit Income**: Record a new income with details such as name, description, date, and amount.Also you can view delete or edit a particular income.
*   **Add Recurring Expense**: Add a recurring expense with no. of time to repeat that particular expense and the time duration after which it should add again.
*   **View Smart Monthly and Yearly Reports**: View total income and and expense along with maximum and minimum record and total savings.  
*   **Log File** : WalletWhiz provides with an additional feature of a log file which contains the logs of all the things a user does to have a record of everything.  
*   **Data Safety** : WalletWhiz provides full data protection as none of the personal data is fetches by our servers, Everything stays on your computer.

Installation
------------

To use the WalletWhiz (Smart Personal Expense Tracker) all the files are already present in the folder but if there is any issue with the current files or get the latest verion ot the application you can follow these steps:

1.  **Delete all the previous files and make a fresh installation of all the files**
    
2.  **Clone the Repository**:
    
        git clone https://github.com/Het2239/C-project.git
        
    
3.  **Navigate to the Directory**:
    
4.  **Compile the Program**:
    
        make run
        
    
5.  **Run the Program**:
    
        ./output
        
    
6.  **Clean all the object files after completion**:
    
        make clear
        
    

Important points
----------------

*   **Word Limit** : There are certain limitations in the program which you must adhere to in order to get the best experience. The username, password and Income or expense name has a maximum character limit of <50 characters and the description has a maximum character limit of <100 characters.
    
*   **New User Registration** : Wnen a user runs the program for the first time there won't be any user data so make sure to first register and add data.
    
*   **User Credentials** : Make sure you don't forget your credentials as you cannnot retrive it later you have to get it done manually in order to get acess to your data.  
*   **System configuration** : Make sure you are running the program on linux or wsl or unix based systems as it is not compatible with other operating systems.
    

File Structure
--------------

*   **expense.c**: Source code file containing the Expense functions.
*   **income.c**: Source code file containing the Income functions.
*   **report.c**: Source code file containing the Report functions.
*   **savings.c**: Source code file containing the Savings function.
*   **main.c**: Main source code file containing the implementation.
*   **expense.h**: File used to store and retrieve expense data.
*   **income.h**: File used to store and retrieve expense data.
*   **savings.h**: File used to store and retrieve expense data.
*   **report.h**: File used to store and retrieve expense data.
*   **credentials.txt**: File used to store and retrieve credentials.
*   **Expense\_details.txt**: File used to store and retrieve expense data.
*   **Income\_details.txt**: File used to store and retrieve income data.
*   **log.txt**: File used to store all the logs.
*   **Makefile**: Makefile to make procram compilation and execution easy.

Contributing
------------

Contributions are welcome! If you would like to improve this project, please follow these steps:

1.  Fork the repository.
2.  Create a new branch (`git checkout -b feature/your-feature-name`).
3.  Make your changes and commit them (`git commit -m 'Add your feature'`).
4.  Push to the branch (`git push origin feature/your-feature-name`).
5.  Open a pull request.

License
-------

This project is licensed under the MIT License. See the [LICENSE](LICENSE.txt) file for more details.

Credits
-------

S.No.

Name

Roll No.

Mail ID

Tasks

1

Het Chavadia

BT2024052

[Het.Chavadia@iiitb.ac.in](mailto:Het.Chavadia@iiitb.ac.in)

Functional logic and Login Structure implementation

2

Raghunandhan.P

BT2024029

[Raghunandhan.P@iiitb.ac.in](mailto:Raghunandhan.P@iiitb.ac.in)

Functional logic & log file implementation

3

Rohith Sai.M

BT2024144

[Rohith.Sai@iiitb.ac.in](mailto:Rohith.Sai@iiitb.ac.in)

Program Structure and UI implementation

4

Haneesh Reddy.B

BT2024126

[Haneesh.Bandi@iiitb.ac.in](mailto:Haneesh.Bandi@iiitb.ac.in)

Functional logic implementation

5

Laksh V Chovatiya

BT2024056

[Laksh.Chovatiya@iiitb.ac.in](mailto:Laksh.Chovatiya@iiitb.ac.in)

Report function implementation

6

Sai Sathvik.K

BT2024209

[saisathvik.kadimisetty@iiitb.ac.in](mailto:saisathvik.kadimisetty@iiitb.ac.in)

Makefile and header files

Contact
-------

For any questions or suggestions, please contact [team.07.iiitb@gmail.com](mailto:team.07.iiitb@gmail.com).

* * *