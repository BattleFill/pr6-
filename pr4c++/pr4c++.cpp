#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    string nickname; 
    double balance; 
    double interestRate; 

public:
    BankAccount(int accNumber, string nick, double initialBalance) {
        this->accountNumber = accNumber;
        this->nickname = nick;
        this->balance = initialBalance;
        this->interestRate = 0.0;
    }

    void deposit(double amount) {
        switch (amount > 0) {
        case true:
            this->balance += amount;
            cout << "Deposit of $" << amount << " successful.\n";
            break;
        case false:
            cout << "Invalid deposit amount. Please enter a positive value.\n";
            break;
        }
    }

    void withdraw(double amount) {
        switch (amount > 0 && amount <= this->balance) {
        case true:
            this->balance -= amount;
            cout << "Withdrawal of $" << amount << " successful.\n";
            break;
        case false:
            cout << "Invalid withdrawal amount or insufficient balance.\n";
            break;
        }
    }

    double getBalance() const {
        return this->balance;
    }

    double getInterest() const {
        return (this->balance * this->interestRate * (1.0 / 12.0));
    }

    void setInterestRate(double rate) {
        this->interestRate = rate;
    }

    int getAccountNumber() const {
        return this->accountNumber;
    }

    string getAccountNumberWithNickname() const {
        return "User " + to_string(this->accountNumber) + " (" + this->nickname + ")";
    }
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    switch (amount > 0 && amount <= from.getBalance() && &from != &to) {
    case true:
        from.withdraw(amount);
        to.deposit(amount);
        cout << "Transfer of $" << amount << " from account " << from.getAccountNumberWithNickname() << " to account " << to.getAccountNumberWithNickname() << " successful.\n";
        return true;
    case false:
        cout << "Invalid transfer amount, insufficient balance or transferring to the same account. Transfer failed.\n";
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    BankAccount account1(1, "Пользователь 1", 0);
    BankAccount account2(2, "Пользователь 2", 0);

    BankAccount* currentAccount = &account1;

    char choice;
    double rate;

    do {
        cout << "\nCurrent Account: " << currentAccount->getAccountNumberWithNickname() << endl;
        cout << "Select an action:\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Set Interest Rate\n";
        cout << "4. Get Interest\n";
        cout << "5. Transfer\n";
        cout << "6. Check Balance\n";
        cout << "7. Switch Account\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "Enter deposit amount: $";
            double amount;
            cin >> amount;
            currentAccount->deposit(amount);
            break;
        case '2':
            cout << "Enter withdrawal amount: $";
            cin >> amount;
            currentAccount->withdraw(amount);
            break;
        case '3':
            cout << "Enter new interest rate: ";
            cin >> rate;
            currentAccount->setInterestRate(rate);
            cout << "Interest rate set to " << rate << endl;
            break;
        case '4':
            cout << "Interest earned on " << currentAccount->getAccountNumberWithNickname() << ": $" << currentAccount->getInterest() << endl;
            break;
        case '5': {
            int recipientAccountNumber;
            cout << "Enter recipient account number: ";
            cin >> recipientAccountNumber;
            BankAccount* recipientAccount = (recipientAccountNumber == account1.getAccountNumber()) ? &account1 : ((recipientAccountNumber == account2.getAccountNumber()) ? &account2 : nullptr);
            if (recipientAccount != nullptr) {
                cout << "Enter transfer amount: $";
                cin >> amount;
                transfer(*currentAccount, *recipientAccount, amount);
            }
            else {
                cout << "Invalid recipient account number.\n";
            }
            break;
        }
        case '6':
            cout << "Current balance: $" << currentAccount->getBalance() << endl;
            break;
        case '7':
            currentAccount = (currentAccount == &account1) ? &account2 : &account1;
            cout << "Switched to account " << currentAccount->getAccountNumberWithNickname() << endl;
            break;
        case '8':
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != '8');

    return 0;
}
