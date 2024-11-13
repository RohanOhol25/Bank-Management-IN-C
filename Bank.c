#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define NAME_LENGTH 50
#define DATA_FILE "accounts.dat"

typedef struct {
    int accountNumber;
    char name[NAME_LENGTH];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Function prototypes
void createAccount();
void viewAccount(int accountNumber);
void depositMoney(int accountNumber, float amount);
void withdrawMoney(int accountNumber, float amount);
void saveAccountsToFile();
void loadAccountsFromFile();

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum account limit reached.\n");
        return;
    }
    
    Account newAccount;
    printf("Enter account number: ");
    scanf("%d", &newAccount.accountNumber);
    
    // Check if account number already exists
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == newAccount.accountNumber) {
            printf("Account number already exists. Try again.\n");
            return;
        }
    }

    printf("Enter account holder name: ");
    scanf(" %[^\n]", newAccount.name);
    
    newAccount.balance = 0.0; // Initial balance set to 0
    accounts[accountCount++] = newAccount;

    // Save updated account list to file
    saveAccountsToFile();
    
    printf("Account created successfully!\n");
}

void viewAccount(int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Account Number: %d\n", accounts[i].accountNumber);
            printf("Account Holder Name: %s\n", accounts[i].name);
            printf("Balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

void depositMoney(int accountNumber, float amount) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            accounts[i].balance += amount;
            printf("Deposited %.2f. New balance: %.2f\n", amount, accounts[i].balance);
            
            // Save updated account list to file
            saveAccountsToFile();
            return;
        }
    }
    printf("Account not found.\n");
}

void withdrawMoney(int accountNumber, float amount) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                printf("Withdrawn %.2f. New balance: %.2f\n", amount, accounts[i].balance);
                
                // Save updated account list to file
                saveAccountsToFile();
            } else {
                printf("Insufficient balance.\n");
            }
            return;
        }
    }
    printf("Account not found.\n");
}

void saveAccountsToFile() {
    FILE *file = fopen(DATA_FILE, "wb");
    if (file == NULL) {
        printf("Error saving accounts to file.\n");
        return;
    }
    fwrite(accounts, sizeof(Account), accountCount, file);
    fclose(file);
}

void loadAccountsFromFile() {
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL) {
        printf("No existing account data found. Starting fresh.\n");
        return;
    }
    accountCount = fread(accounts, sizeof(Account), MAX_ACCOUNTS, file);
    fclose(file);
}

int main() {
    loadAccountsFromFile(); // Load accounts from file at the start

    int choice;
    
    do {
        printf("\nBank Management System\n");
        printf("1. Create Account\n");
        printf("2. View Account\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        int accountNumber;
        float amount;
        
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                viewAccount(accountNumber);
                break;
            case 3:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                depositMoney(accountNumber, amount);
                break;
            case 4:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                withdrawMoney(accountNumber, amount);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    
    return 0;
}
