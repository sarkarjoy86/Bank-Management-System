/**
    Project Report Title: Bank Management System using CPP.
    =======================================================
    Group - G4
    --------------------------
    Joy Sarkar - 0822220105101086
**/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <cctype>
using namespace std;

class Bank_Account
{
    int account_number;
    char name[50];
    char type;
    int Money_Deposit;

public:
    // Default Constructor just for initializing values.
    Bank_Account()
    {
        account_number = 0;
        name[0] = '\0';
        type = '\0';
        Money_Deposit = 0;
    }

    void menu(); // Creating menu
    void create_account();
    void Display_account();

    int retacno() const // a simple getter()
    {
        return account_number;
    }

    void write_account(); // Function to write record in Binary File
    void display_balance(int n);
    void delete_account(int n);
    void display_all(); // Function to display all accounts
    void report();      // Function to show all account details
    void money_deposit_withdraw(int n, int option);
    void dep(int x);       // Founction to add money
    void withdrawn(int x); // Substract the money
    int return_deposit() const;
    void updation_bank_account(int n); // Main function to update an account
    void modify();                     // Function to modify prevoius account
};

void Bank_Account::menu()
{
    char ch;
    int num;
    do // Loop Until the user exit the menu
    {
        cout << "\t\t\t\t ------------------------------------- " << endl;
        cout << "\t\t\t\t | Welcome to Bank Management System |" << endl;
        cout << "\t\t\t\t ------------------------------------- " << endl;

        cout << endl;
        cout << "\t\t\t ---Main Menu---" << endl;
        cout << "\t\t\t 1. Create Account" << endl;
        cout << "\t\t\t 2. Deposit Money" << endl;
        cout << "\t\t\t 3. Withdraw Money" << endl;
        cout << "\t\t\t 4. Balance Inquiry" << endl;
        cout << "\t\t\t 5. All Account Holder List" << endl;
        cout << "\t\t\t 6. Close an Account" << endl;
        cout << "\t\t\t 7. Modify an Account" << endl;
        cout << "\t\t\t 8. Exit" << endl;

        cout << endl
             << endl;
        cout << "\t\t Enter Your Choice (1-8): ";
        cin >> ch;
        switch (ch)
        {
        case '1':
            write_account(); // Acount creation Function
            break;
        case '2':
            system("cls");
            cout << "\t Enter the Account Number: ";
            cin >> num;
            money_deposit_withdraw(num, 1); // Deposit function
            break;
        case '3':
            system("cls");
            cout << "\t Enter the Account Number: ";
            cin >> num;
            money_deposit_withdraw(num, 2); // Withdraw function
            break;
        case '4':
            system("cls");
            cout << "\t Enter the Account Number: ";
            cin >> num;
            display_balance(num); // Balance Enquiry Function
            break;
        case '5':
            system("cls");
            display_all();
            break;
        case '6':
            system("cls");
            cout << "\t Enter the Account Number: ";
            cin >> num;
            delete_account(num);
            break;
        case '7':
            system("cls");
            cout << "\t Enter the Account Number: ";
            cin >> num;
            updation_bank_account(num); // modify function
            break;
        case '8':
            system("cls");
            cout << endl
                 << endl;
            cout << "\t\t -------Thank you for using the Bank Management System-------" << endl;
            break;

        default:
            break;
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
}

void Bank_Account::create_account()
{
    system("cls");
    cout << "\t Enter the Account Number: ";
    cin >> account_number;
    cout << "\t Enter the Name of the Account Holder: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\t Enter the Type of the Account (C/S): ";
    cin >> type;
    type = toupper(type); // Autometically type cast to upper case
    cout << "\t Enter the Initial Amount (>= 500 for Saving and >= 100 for Current): ";
    cin >> Money_Deposit;
    cout << endl;
    cout << "\t\t Account Created ";
    cout << endl
         << endl;
}

void Bank_Account::Display_account()
{
    cout << "\t Bank Account Number: " << account_number << endl;
    cout << "\t Account Holder Name: " << name << endl;
    cout << "\t Type of Account: " << type << endl;
    cout << "\t Account Balance: " << Money_Deposit << endl;
}

void Bank_Account::write_account()
{
    Bank_Account ac;
    ofstream outfile; // Using ofstream file handling
    outfile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    // convert the object ac into a char pointer & passed to the write function.
    outfile.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));
    outfile.close();
}

void Bank_Account::delete_account(int n)
{
    Bank_Account ac;
    ifstream infile;  // Input file stream
    ofstream outfile; // Output file stream
    infile.open("account.dat", ios::binary);
    if (!infile)
    {
        cout << " File could not be open!! Press any key...";
        return;
    }
    outfile.open("temp.dat", ios::binary); // Open a temporary output file in binary mode
    infile.seekg(0, ios::beg);             // Move the read pointer to the beginning of the file

    while (infile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)))
    {
        if (ac.retacno() != n)
        {
            outfile.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)); // Write the record to the temp file
        }
    }
    infile.close();
    outfile.close();

    remove("account.dat");
    rename("temp.dat", "account.dat");

    cout << "Record Deleted" << endl;
}

void Bank_Account::display_balance(int n)
{
    Bank_Account ac;
    bool flag = false;
    ifstream infile;
    infile.open("account.dat", ios::binary);
    if (!infile)
    {
        cout << " File could not be open!! Press any key...";
        return;
    }
    cout << "\t Bank Account Details" << endl;
    while (infile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)))
    {
        if (ac.retacno() == n)
        {
            ac.Display_account();
            flag = true;
        }
    }
    infile.close();
    if (flag == false)
        cout << "\t Account Number does not exist" << endl;
}
void Bank_Account::report()
{
    cout << left << setw(10) << account_number
         << setw(20) << name
         << setw(10) << type
         << right << setw(10) << Money_Deposit <<" TK" << endl;
}
void Bank_Account::display_all()
{
    system("cls");
    Bank_Account ac;
    ifstream infile;
    infile.open("account.dat", ios::binary); // Opeining file as binary form
    if (!infile)
    {
        cout << " File could not be open!! Press any key...";
        return;
    }
    cout << "\t\t Bank Account Holder List" << endl;
    cout << "============================================================================" << endl;
    cout << left << setw(10) << "A/C No." << setw(20) << "Name"
         << setw(10) << "Type" << right << setw(12) << "Balance" << endl;
    cout << "============================================================================" << endl;
    while (infile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)))
    {
        ac.report();
    }
    infile.close();
}

void Bank_Account::dep(int x)
{
    if (x < 100)
    {
        throw "Deposit amount must be at least 100";
    }
    Money_Deposit += x; // Adding money
}

// Storing account money into this function
int Bank_Account::return_deposit() const
{
    return Money_Deposit; // return the availble money
}

void Bank_Account::withdrawn(int x)
{
    if (x < 100)
    {
        throw "Withdrawal amount must be at least 100";
    }
    if ((Money_Deposit - x) < 0)
    {
        throw "Insufficient funds for withdrawal";
    }
    Money_Deposit -= x; // Substracting money
}

void Bank_Account::money_deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    Bank_Account ac;
    fstream file;
    file.open("account.dat", ios::binary | ios::in | ios::out); // Opeing in both input and output stream
    if (!file)
    {
        cout << "File could not be opened! Press any key...";
        return;
    }

    while (!file.eof() && !found)
    {
        file.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)); // Reading and convert the record into char pointer
        if (ac.retacno() == n)
        {
            ac.Display_account();
            if (option == 1)
            {
                cout << "\nEnter the amount to be deposited: ";
                cin >> amt;
                try
                {
                    ac.dep(amt);
                    cout << "\nDeposit Successful";
                }
                catch (const char *msg) // Exception Handling
                {
                    cerr << msg << endl;
                }
            }
            else if (option == 2)
            {
                cout << "\nEnter the amount to be withdrawn: ";
                cin >> amt;
                try
                {
                    ac.withdrawn(amt);
                    cout << "\nWithdrawal Successful";
                }
                catch (const char *msg) // Exception Handling
                {
                    cerr << msg << endl;
                }
            }

            // calculating the position where the read/write pointer should be moved within a file.
            int pos = (-1) * static_cast<int>(sizeof(ac));
            file.seekp(pos, ios::cur);                                       // Move the pointer to the position of the file.
            file.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)); // Writing Record in the file
            cout << "\nRecord Updated";
            found = true;
        }
    }
    file.close();
    if (!found)
    {
        cout << "No such account exists";
    }
}

void Bank_Account::modify()
{
    cout << "\t Account Number: " << account_number << endl;
    cout << "\t Modify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\t Modify type of Account: ";
    cin >> type;
    type = toupper(type); // Coverting to uppercase
    cout << "\t Modify Balance Ammount: ";
    cin >> Money_Deposit;
}

void Bank_Account::updation_bank_account(int n)
{
    bool found = false;
    Bank_Account ac;
    fstream file;
    file.open("account.dat", ios::binary | ios::in | ios::out); // Openning the file in input and output stream
    if (!file)
    {
        cout << " File could not be open!! Press any key...";
        return;
    }
    while (!file.eof() && found == false)
    {
        file.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)); // Reading the record from the file
        if (ac.retacno() == n)
        {
            ac.Display_account();
            cout << endl
                 << endl;
            cout << "\t Enter the New Details of the Account" << endl;
            ac.modify();
            // calculating the position where the read/write pointer should be moved within a file.
            int pos = (-1) * static_cast<int>(sizeof(Bank_Account));
            file.seekp(pos, ios::cur);                                       // Move the pointer to the position of the file.
            file.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)); // Writing Record in the file
            cout << "\t Modification has been done." << endl;
            found = true; // Found updated
        }
    }
    file.close();
    if (found == false)
    {
        cout << "\t There is no Such Account" << endl;
    }
}

int main()
{
    // Login Page
    string userid;
    string pass;
    cout << endl
         << endl;
    cout << "\t\t\t ---------Login to the Bank Management System---------" << endl;
    cout << endl;
    cout << "\t\t\t Enter the Admin User ID: ";
    cin >> userid;
    cout << "\t\t\t Enter the Admin Password: ";
    for (int i = 0; i < 4; i++)
    {
        char ch = getch();
        pass = pass + ch;
        cout << "*";
    }
    cout << endl
         << endl;

    if (userid == "joy86" && pass == "2487")
    {
        system("cls");
        Bank_Account B;
        B.menu();
    }
    else
    {
        cout << "\t\t\t Username or password is wrong!!!!" << endl;
    }
    return 0;
}