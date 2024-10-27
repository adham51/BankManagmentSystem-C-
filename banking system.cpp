#include<iostream>
#include<string>
#include <algorithm>
using namespace std;

class node // This  class represents a node in a linked list, which stores information about a bank account for a single customer
{
public:
    float val;
    float cash;
    string name;
    int id;     // Account ID

    node* next;
};

class bank // The bank class manages the bank accounts, also known as nodes in this project because we utilize linked lists. It has a private member head, which is the head pointer of the linked list. The length member keeps track of the number of accounts in the bank.
{
private:
    node* head;          // The reason it's private is to ensure that no one from outside the bank class can mess with the linked list's important information, hence adding more security.



public:
    int length;          // Length of the linked list and it's an indicator of how many accounts are created since each node is one account

    bank()
    {
        head = NULL;
        length = 0;
    }

    // Declaration for all the functions used int he project
    void sign_up();
    void displayDetails();
    void currency_exchange();
    void deleteAccount();
    void deposite(int);
    void withdrawal(int);
    void update();      // Function to update account details
    void search();      // Function to search for an account by ID
    void listing();     // Function to list all accounts
    void transfer(int senderId, int receiverId, float amount);
    void loanApplication();

private:
    node* findAccount(int id); // It's private to make sure that not anyone can access customers' accounts. If someone wants to find an account, function goes through the linked list to locate the node that holds that account.

};


void bank::sign_up() // A function to create an account for a new bank customer

{
    // initialize pointers and other required variables that will be used inside the function
    node* temp = NULL;
    node* p = NULL;
    float ca;
    int ch1 = 1, ID;
    string na;
    while (ch1 == 1) // After the user creates one account, he's asked to press 1 if he needs to create another account, and so on
    { // take input from the user and his information
        cout << "Enter name: ";
        cin >> na;
        cout << "Enter account id: ";
        cin >> ID;
        cout << "Enter expected cash (in EGP): ";
        cin >> ca;
        if (head == NULL) // if the linked list is empty, or in other words head doesn't point to anything
        {
            head = new node; // create a new node
            head->cash = ca;
            head->name = na;
            head->id = ID;
            head->next = NULL; // have it's next pointer = none since it's the only and last node
            p = head;
            length++; // a counter so the system knows that an account has been created, hence knowing the total number of accounts in the bank
        }
        else // if linked list isn't empty
        {
            temp = new node;
            temp->cash = ca;
            temp->name = na;
            temp->id = ID;
            temp->next = NULL;
            // link new node to the end of the list and increment that a node has been added, or account has been created
            p->next = temp;
            p = temp;
            length++;
        }

        cout << "Press 1 to enter again: ";
        cin >> ch1; // take 1 as input if the user wants to create more than 1 account
    }
}
void bank::currency_exchange()
{
     // Prompt the user to enter the amount in EGP
    cout << "Enter the amount in Egyptian pounds (EGP): ";
    float egp;
    cin >> egp;
    // Calculate the equivalent amounts in other currencies
    float usd = egp * 0.03236;
    float euros = egp * 0.03018;
    float aed = egp * 0.118854;
    // Display the conversion results
    cout << egp << " EGP is approximately:\n";
    cout << usd << " US dollars\n";
    cout << euros << " euros\n";
    cout << aed << " United Arab Emirates Dirham\n";
}

void bank::deleteAccount()
{
    int id;
    node* temp1 = NULL;
    node* p = NULL;
    node* q = NULL;
    // you can think of p as a current node and q is a previous node or the behind it

    // Prompt the user to enter the account ID to be deleted
    cout << "\nEnter account id to be deleted: ";
    cin >> id;

    // Start the search from the head of the linked list
    p = head;
    while (p != NULL && p->id != id)
    {
        // Traverse through the linked list until the account with the specified ID is found
        q = p;
        p = p->next;
    }

    // Check if the account with the specified ID was found or not
    if (p == NULL)
    {
        // If p is NULL, it means no account with the specified ID was found
        cout << "There is no Account Holder with id: " << id << endl;
    }
    else if (q == NULL)
    {
        // If q is NULL, it means the account to be deleted is the first node of the linked list
        head = p->next; // make head point to the one after it
        delete p; // delete the node we dropped or passed
        length--; // a node has been removed from the system, hence decrease number of accounts
        cout << "Account Deleted Successfully!" << endl;
    }
    else
    {
        // If q is not NULL, it means the account to be deleted is not the head of the linked list
        q->next = p->next;    // Update the next pointer of the previous node (q) to skip the node to be deleted (p)
        delete p;
        length--;
        cout << "Account Deleted Successfully!" << endl;
    }
}


void bank::deposite(int id)
{
    float amount;
    node* p = findAccount(id);

    if (p != NULL)     // Check if the account with the specified ID exists, as long as p isn't null means something exists
    {
        // Prompt the user to enter the amount to be deposited
        cout << "Enter amount to deposit: ";
        cin >> amount;

        // Update the cash balance of the account by adding the deposited amount
        p->cash += amount;

        // Display a message indicating the successful deposit
        cout << "Deposit Successful!" << endl;
    }
    else         // If the account with the specified ID was not found, display a specific error message
    {
        cout << "Account not found!" << endl;
    }
}


void bank::withdrawal(int id)
{
    float amount;
    node* p = findAccount(id); // Find the bank account with the given ID

    if (p != NULL) // Check if the account exists
    {
        cout << "Enter amount to withdraw: ";
        cin >> amount;

        if (p->cash >= amount) // Check if the account has sufficient funds by checking if the cash in his account is more than or equal the amount he/she wants to withdraw
        {
            p->cash -= amount; // Subtract the withdrawal amount from the account balance
            cout << "Withdrawal Successful!" << endl;
        }
        else
        {
            cout << "Insufficient funds in the account!" << endl; // Print an error message if there are insufficient funds
        }
    }
    else
    {
        cout << "Account not found!" << endl; // Print an error message if the account doesn't exist
    }
}

void bank::update()
{
    int id;
    float ca;
    string na;
    node* p = NULL;
    cout << "\nEnter account id to be updated: ";
    cin >> id;

    p = findAccount(id);     // Find the account with the provided ID that you want to update
    if (p != NULL)
    {
        // Ask the user to enter new details for the account
        cout << "Enter new name: ";
        cin >> na;
        cout << "Enter new cash (in EGP): ";
        cin >> ca;
        // Update the name and cash of the account
        p->name = na;
        p->cash = ca;
        cout << "Update Successful!" << endl;
    }
    else
    {
        // Account not found
        cout << "Account not found!" << endl;
    }
}


void bank::search() // search for a specific account using a specific id
{
    int id;
    node* p = NULL;
    cout << "\nEnter account id to search: ";
    cin >> id;
    p = findAccount(id);  // Find the account with the provided ID

    if (p != NULL)
    {
        cout << "Account Holder " << p->val << " -> " << "Name: " << p->name << " -> " << "Account id: " << p->id << " -> " << "Cash in account: EGP. " << p->cash << endl;   // Print the details of the found account
    }
    else
    {
        cout << "Account not found!" << endl;
    }
}

void bank::listing() // list all the accounts in the bank
{
    node* p = head;   // Start from the head of the linked list
    if (head == NULL)     // Check if there are no accounts in the bank, or no nodes in the list
    {
        cout << "\nThere is no data found!" << endl;
    }
    else
    {
        cout << "\nBank Account Management System" << endl;
        while (p != NULL)       // Traverse the linked list and print the details of each account
        {
            cout << "Account Holder " << p->val << " -> " << " -> " << "Name: " << p->name << " -> " << " -> " << "Account id: " << p->id << " -> "<< "Cash in account: EGP. " << p->cash << endl;
            p = p->next;        // Move to the next node
        }
        cout << "\nTotal Account Holders: " << length << endl;        // Print the total number of account holders
    }
}

void bank::transfer(int senderId, int receiverId, float amount)
{
    // Find the sender and receiver accounts
    node* sender = findAccount(senderId);
    node* receiver = findAccount(receiverId);

    if (sender != NULL && receiver != NULL)   // Check if both accounts exist, if they aren't equal null which means they exist, proceed

    {
        if (sender->cash >= amount)      // Check if the sender has sufficient funds by checking if his cash is less than amount he's trying to transfer

        {
            // Perform the transfer
            sender->cash -= amount;
            receiver->cash += amount;
            cout << "Transfer Successful!" << endl;
        }
        else         // Insufficient funds in the sender's account
        {
            cout << "Insufficient funds in the sender's account!" << endl;
        }
    }
    else         // if one or both of the accounts not found

    {
        cout << "One or both of the accounts not found!" << endl;
    }
}

void bank::loanApplication() {
    bool stableIncome = false, criminalRecord = false;
    int valueOfAssets, loanValue, salary;

    // Get input from the user to verify wheather the user is eligible for loan or not
    cout << "How much money do you want to borrow? ";
    cin >> loanValue;

    cout << "What is the value of your assets? ";
    cin >> valueOfAssets;

    cout << "What is the value of your salary? ";
    cin >> salary;

    cout << "Do you have a stable income? (Enter Yes or No) ";
    string userInput;
    cin >> userInput;

    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);

    if (userInput == "yes") {
        stableIncome = true;
    }

    cout << "Do you have any criminal records? (Enter Yes or No) ";
    cin >> userInput;

    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);     // Convert user input to lowercase because if the user's keyboard has capslock on


    if (userInput == "yes") {     // Check if the user has any criminal records
        criminalRecord = true;
    }

    // Check eligibility for the loan by mathematical calculations to assure the user can pay for the loan if the loan is approved
    if (!stableIncome || criminalRecord || ((valueOfAssets <= 1.4 * loanValue) && (salary <= loanValue * 0.08)) ||
        ((valueOfAssets > 1.4 * loanValue) && (salary <= loanValue * 0.08))) {
        cout << "Sorry, you are not eligible for our loan service." << endl;
        return;
    }

    // Determine the loan terms based on the user's eligibility
    if (valueOfAssets <= 1.4 * loanValue) {
        cout << "Congratulations, you are eligible for our loan service. You will pay 25% interest." << endl;
        cout << "You will pay " << loanValue * 0.0625 << " EGP every month." << endl;
    } else {
        cout << "Congratulations, you are eligible for our loan service. You will pay 20% interest." << endl;
        cout << "You will pay " << loanValue * 0.05 << " EGP every month." << endl;
    }
}

node* bank::findAccount(int id)
{
    node* p = head; // create a node called p and make it equal to head

    while (p != NULL) // as long as p isn't null or there are nodes in the list or the end of the list isn't reached yet
    {
        if (p->id == id) // check if the id of the current node matches the id the user asked for
        {
            return p; // if it matches, return a pointer to the node representing the account that's been found
        }
        p = p->next; // traverse the linked list
    }

    return NULL; // in case the specific id wasn't found
}

int main()
{
    bank b;
    int choice, id, senderId, receiverId;
    float amount;

    do // create the main loop for the program to run
    {
        cout << "\n*** Bank Account Management System ***" << endl;
        cout << "1. sign_up" << endl;
        cout << "2. currency_exchange" << endl;
        cout << "3. Delete an Account" << endl;
        cout << "4. Deposit Money" << endl;
        cout << "5. Withdraw Money" << endl;
        cout << "6. Update Account Details" << endl;
        cout << "7. Search for an Account" << endl;
        cout << "8. List All Accounts" << endl;
        cout << "9. Transfer Money" << endl;
        cout << "10.loan" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) // depending on which number the user inputs, a function is called
        {
        case 1:
            b.sign_up();
            break;
        case 2:
            b.currency_exchange();
            break;
        case 3:
            b.deleteAccount();
            break;
        case 4:
            cout << "\nEnter account id to deposit money: ";
            cin >> id;
            b.deposite(id);
            break;
        case 5:
            cout << "\nEnter account id to withdraw money: ";
            cin >> id;
            b.withdrawal(id);
            break;
        case 6:
            b.update();
            break;
        case 7:
            b.search();
            break;
        case 8:
            b.listing();
            break;
        case 9:
            cout << "\nEnter sender's account id: ";
            cin >> senderId;
            cout << "Enter receiver's account id: ";
            cin >> receiverId;
            cout << "Enter amount to transfer: ";
            cin >> amount;
            b.transfer(senderId, receiverId, amount);
            break;
        case 10:
            b.loanApplication();
            break;
        case 0: // an option to exit the program
            cout << "\nThank you for using the Bank Account Management System!" << endl;
            break;
        default:
            cout << "\nInvalid choice! Please enter a valid option." << endl;
        }
    } while (choice != 0);

    return 0;
}
