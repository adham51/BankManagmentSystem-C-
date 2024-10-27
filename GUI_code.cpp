#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QString>
#include<QInputDialog>
#include<cfloat>
#include <algorithm>
using namespace std;

class Node
{
public:
    float val;
    float cash;
    float phn;
    QString email;
    QString name;
    QString lname;
    int id;

    Node* next;
};

class Bank
{
private:
    Node* head;

public:
    int length;

    Bank()
    {
        head = nullptr;
        length = 0;
    }

    void signUp(const QString& name, int id, float cash);
    void displayDetails();
    void currencyExchange();
    void deleteAccount();
    void deposit(int id, float amount);
    void withdrawal(int id, float amount);
    void update();
    void search(int id);
    void listing();
    void transfer(int senderId, int receiverId, float amount);
    void loanApplication();

private:
    Node* findAccount(int id);
};

void Bank::signUp(const QString& name, int id, float cash)
{
    Node* temp = nullptr;
    Node* p = nullptr;

    if (head == nullptr)
    {
        head = new Node;
        head->cash = cash;
        head->name = name;
        head->id = id;
        head->next = nullptr;
        p = head;
        length++;
    }
    else
    {
        temp = new Node;
        temp->cash = cash;
        temp->name = name;
        temp->id = id;
        temp->next = nullptr;
        p->next = temp;
        p = temp;
        length++;
    }
}

void Bank::currencyExchange()
{
    // Prompt the user to enter the amount in EGP
    bool ok;
    QString egpString = QInputDialog::getText(nullptr, "Currency Exchange", "Enter the amount in Egyptian pounds (EGP):", QLineEdit::Normal, "", &ok);

    if (ok)
    {
        float egp = egpString.toFloat();
        // Calculate the equivalent amounts in other currencies
        float usd = egp * 0.03236;
        float euros = egp * 0.03018;
        float aed = egp * 0.118854;
        // Display the conversion results
        QString result = QString("%1 EGP is approximately:\n%2 US dollars\n%3 euros\n%4 United Arab Emirates Dirham").arg(egpString).arg(usd).arg(euros).arg(aed);
        QMessageBox::information(nullptr, "Currency Exchange", result);
    }
}

void Bank::deleteAccount()
{
    bool ok;
    int id = QInputDialog::getInt(nullptr, "Delete Account", "Enter account id to be deleted:", 0, 0, INT_MAX, 1, &ok);

    if (ok)
    {
        Node* temp1 = nullptr;
        Node* p = nullptr;
        Node* q = nullptr;

        p = head;
        while (p != nullptr && p->id != id)
        {
            q = p;
            p = p->next;
        }

        if (p == nullptr)
        {
            QMessageBox::warning(nullptr, "Delete Account", QString("There is no Account Holder with id: %1").arg(id));
        }
        else if (q == nullptr)
        {
            head = p->next;
            delete p;
            length--;
            QMessageBox::information(nullptr, "Delete Account", "Account Deleted Successfully!");
        }
        else
        {
            q->next = p->next;
            delete p;
            length--;
            QMessageBox::information(nullptr, "Delete Account", "Account Deleted Successfully!");
        }
    }
}

void Bank::deposit(int id, float amount)
{
    Node* p = findAccount(id);

    if (p != nullptr)
    {
        p->cash += amount;
        QMessageBox::information(nullptr, "Deposit Money", "Deposit Successful!");
    }
    else
    {
        QMessageBox::warning(nullptr, "Deposit Money", "Account not found!");
    }
}

void Bank::withdrawal(int id, float amount)
{
    Node* p = findAccount(id);

    if (p != nullptr)
    {
        if (p->cash >= amount)
        {
            p->cash -= amount;
            QMessageBox::information(nullptr, "Withdraw Money", "Withdrawal Successful!");
        }
        else
        {
            QMessageBox::warning(nullptr, "Withdraw Money", "Insufficient funds in the account!");
        }
    }
    else
    {
        QMessageBox::warning(nullptr, "Withdraw Money", "Account not found!");
    }
}

void Bank::update()
{
    bool ok;
    int id = QInputDialog::getInt(nullptr, "Update Account", "Enter account id to be updated:", 0, 0, INT_MAX, 1, &ok);

    if (ok)
    {
        Node* p = findAccount(id);

        if (p != nullptr)
        {
            QString name = QInputDialog::getText(nullptr, "Update Account", "Enter new name:", QLineEdit::Normal, p->name);
            bool ok;
            float cash = QInputDialog::getDouble(nullptr, "Update Account", "Enter new cash (in EGP):", p->cash, 0, DBL_MAX, 2, &ok);

            if (ok)
            {
                p->name = name;
                p->cash = cash;
                QMessageBox::information(nullptr, "Update Account", "Update Successful!");
            }
        }
        else
        {
            QMessageBox::warning(nullptr, "Update Account", "Account not found!");
        }
    }
}

void Bank::search(int id)
{
    Node* p = findAccount(id);

    if (p != nullptr)
    {
        QString result = QString("Account Holder %1 -> Name: %2 -> Account id: %3 -> Cash in account: EGP. %4").arg(p->val).arg(p->name).arg(p->id).arg(p->cash);
        QMessageBox::information(nullptr, "Search Account", result);
    }
    else
    {
        QMessageBox::warning(nullptr, "Search Account", "Account not found!");
    }
}

void Bank::listing()
{
    Node* p = head;

    if (head == nullptr)
    {
        QMessageBox::information(nullptr, "List Accounts", "There is no data found!");
    }
    else
    {
        QString result = "Bank Account Management System\n\n";

        while (p != nullptr)
        {
            QString accountDetails = QString("Account Holder %1 -> Name: %2 -> Account id: %3 -> Cash in account: EGP. %4\n").arg(p->val).arg(p->name).arg(p->id).arg(p->cash);
            result += accountDetails;
            p = p->next;
        }

        result += QString("\nTotal Account Holders: %1").arg(length);
        QMessageBox::information(nullptr, "List Accounts", result);
    }
}

void Bank::transfer(int senderId, int receiverId, float amount)
{
    Node* sender = findAccount(senderId);
    Node* receiver = findAccount(receiverId);

    if (sender != nullptr && receiver != nullptr)
    {
        if (sender->cash >= amount)
        {
            sender->cash -= amount;
            receiver->cash += amount;
            QMessageBox::information(nullptr, "Transfer Money", "Transfer Successful!");
        }
        else
        {
            QMessageBox::warning(nullptr, "Transfer Money", "Insufficient funds in the sender's account!");
        }
    }
    else
    {
        QMessageBox::warning(nullptr, "Transfer Money", "One or both of the accounts not found!");
    }
}

void Bank::loanApplication()
{
    bool stableIncome = false, criminalRecord = false;
    int valueOfAssets, loanValue, salary;

    loanValue = QInputDialog::getInt(nullptr, "Loan Application", "How much money do you want to borrow?", 0, 0, INT_MAX, 1);
    valueOfAssets = QInputDialog::getInt(nullptr, "Loan Application", "What is the value of your assets?", 0, 0, INT_MAX, 1);
    salary = QInputDialog::getInt(nullptr, "Loan Application", "What is the value of your salary?", 0, 0, INT_MAX, 1);

    QString userInput = QInputDialog::getText(nullptr, "Loan Application", "Do you have a stable income? (Enter Yes or No)").toLower();

    if (userInput == "yes")
    {
        stableIncome = true;
    }

    userInput = QInputDialog::getText(nullptr, "Loan Application", "Do you have any criminal records? (Enter Yes or No)").toLower();

    if (userInput == "yes")
    {
        criminalRecord = true;
    }

    if (!stableIncome || criminalRecord || ((valueOfAssets <= 1.4 * loanValue) && (salary <= loanValue * 0.08)) ||
        ((valueOfAssets > 1.4 * loanValue) && (salary <= loanValue * 0.08)))
    {
        QMessageBox::information(nullptr, "Loan Application", "Sorry, you are not eligible for our loan service.");
        return;
    }

    if (valueOfAssets <= 1.4 * loanValue)
    {
        float monthlyPayment = loanValue * 0.0625;
        QMessageBox::information(nullptr, "Loan Application", QString("Congratulations, you are eligible for our loan service.\nYou will pay 25% interest.\nYou will pay %1 EGP every month.").arg(monthlyPayment));
    }
    else
    {
        float monthlyPayment = loanValue * 0.05;
        QMessageBox::information(nullptr, "Loan Application", QString("Congratulations, you are eligible for our loan service.\nYou will pay 20% interest.\nYou will pay %1 EGP every month.").arg(monthlyPayment));
    }
}

Node* Bank::findAccount(int id)
{
    Node* p = head;

    while (p != nullptr)
    {
        if (p->id == id)
        {
            return p;
        }
        p = p->next;
    }

    return nullptr;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Bank b;
    int choice, id, senderId, receiverId;
    float amount;

    do
    {
        QStringList choices;
        choices << "Sign Up" << "Currency Exchange" << "Delete an Account" << "Deposit Money" << "Withdraw Money"
                << "Update Account Details" << "Search for an Account" << "List All Accounts" << "TransferMoney" << "Loan Application" << "Exit";
        QString choiceString = QInputDialog::getItem(nullptr, "Bank Account Management System", "Choose an option:", choices, 0, false);

        choice = choices.indexOf(choiceString);

        switch (choice)
        {
        case 0: // Sign Up
        {
            QString name = QInputDialog::getText(nullptr, "Sign Up", "Enter your name:");
            bool ok;
            int id = QInputDialog::getInt(nullptr, "Sign Up", "Enter an account id:", 0, 0, INT_MAX, 1, &ok);
            float cash = QInputDialog::getDouble(nullptr, "Sign Up", "Enter the initial cash amount (in EGP):", 0, 0, DBL_MAX, 2, &ok);
            b.signUp(name, id, cash);
            break;
        }
        case 1: // Currency Exchange
        {
            b.currencyExchange();
            break;
        }
        case 2: // Delete an Account
        {
            b.deleteAccount();
            break;
        }
        case 3: // Deposit Money
        {
            bool ok;
            int id = QInputDialog::getInt(nullptr, "Deposit Money", "Enter account id:", 0, 0, INT_MAX, 1, &ok);
            float amount = QInputDialog::getDouble(nullptr, "Deposit Money", "Enter the amount to deposit (in EGP):", 0, 0, DBL_MAX, 2, &ok);
            b.deposit(id, amount);
            break;
        }
        case 4: // Withdraw Money
        {
            bool ok;
            int id = QInputDialog::getInt(nullptr, "Withdraw Money", "Enter account id:", 0, 0, INT_MAX, 1, &ok);
            float amount = QInputDialog::getDouble(nullptr, "Withdraw Money", "Enter the amount to withdraw (in EGP):", 0, 0, DBL_MAX, 2, &ok);
            b.withdrawal(id, amount);
            break;
        }
        case 5: // Update Account Details
        {
            b.update();
            break;
        }
        case 6: // Search for an Account
        {
            bool ok;
            int id = QInputDialog::getInt(nullptr, "Search for an Account", "Enter account id:", 0, 0, INT_MAX, 1, &ok);
            b.search(id);
            break;
        }
        case 7: // List All Accounts
        {
            b.listing();
            break;
        }
        case 8: // Transfer Money
        {
            bool ok;
            int senderId = QInputDialog::getInt(nullptr, "Transfer Money", "Enter sender's account id:", 0, 0, INT_MAX, 1, &ok);
            int receiverId = QInputDialog::getInt(nullptr, "Transfer Money", "Enter receiver's account id:", 0, 0, INT_MAX, 1, &ok);
            float amount = QInputDialog::getDouble(nullptr, "Transfer Money", "Enter the amount to transfer (in EGP):", 0, 0, DBL_MAX, 2, &ok);
            b.transfer(senderId, receiverId, amount);
            break;
        }
        case 9: // Loan Application
        {
            b.loanApplication();
            break;
        }
        case 10: // Exit
        {
            QMessageBox::information(nullptr, "Bank Account Management System", "Thank you for using the system!");
            break;
        }
        }
    } while (choice != 10);

    return a.exec();
}
