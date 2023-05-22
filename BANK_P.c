#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

struct Transaction {
    char type[20];                          //'Withdraw' for Withdraw and 'Deposit' for Deposit
    double amount;
    char DateTime[30];                      //Amount to deposit or withdraw
    struct Transaction *next;
};

struct BankAccount {
  char Name[50], Email[50];             //Full Name of the Account Holder
  long long int AccountNumber;                  //Account Number
  double AccountBalance;                    //Account Balance
  long long int PhoneNumber;             //Phone Number of the Account Holder
  struct Transaction *next;         //Pointer to the account's transactions
};

struct BANK{
    int size;                           //Number of accounts in the Bank
    struct BankAccount Accounts[1000];  //Array to store all the Banks
}Bank;

void setInitialSize(){
    Bank.size = 0;
}

int printMenu(){
    printf("\nBANK MANAGEMENT SYSTEM ");
    int ch = 1;
    return ch;
}

void openAccount(){
    char Name[50], Email[50];
    char ch[10];
    long long int PhoneNumber, AccNo;
    double initialAmount;
    struct BankAccount *Account = malloc(sizeof(struct BankAccount));
    gets(ch);
    printf("Enter your Full Name: ");
    gets(Name);
    printf("Enter your Email: ");
    gets(Email);
    printf("Enter your Phone Number: ");
    scanf("%lld",&PhoneNumber);
    printf("Enter the Initial Amount you want to deposit: ");
    scanf("%lf",&initialAmount);
    AccNo = 100000 + (rand()%900000);
    strcpy(Account->Name, Name);
    strcpy(Account->Email, Email);
    Account->PhoneNumber= PhoneNumber;
    Account->AccountBalance = initialAmount;
    Account->AccountNumber = AccNo;
    Account->next = NULL;
    Bank.Accounts[Bank.size] = *Account;
    printf("\nYour account is created successfully. Please take a note of your Account Number %lld for future reference.\n", Bank.Accounts[Bank.size].AccountNumber);
    Bank.size += 1;
    return;
}



void depositMoney(){
    int flag = 0;
    long long int AccNo;
    printf("Enter your Account Number: ");
    scanf("%lld", &AccNo);
    for(int i = 0; i < Bank.size; i++){
        if(Bank.Accounts[i].AccountNumber == AccNo){
            struct Transaction *transaction = malloc(sizeof(struct Transaction));
            double amount;
            printf("Enter the amount of money you want to deposit: ");
            scanf("%lf", &amount);
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char curr_date[64];
            assert(strftime(curr_date, sizeof(curr_date), "%c", tm));
            strcpy(transaction->type, "Deposit ");
            transaction->amount = amount;
            strcpy(transaction->DateTime, curr_date);
            transaction->next = Bank.Accounts[i].next;
            Bank.Accounts[i].next = transaction;
            Bank.Accounts[i].AccountBalance = Bank.Accounts[i].AccountBalance + amount;
            printf("\nYour Money of INR. %.2lf has been deposited successfully.\nYour current Account Balance is INR. %.2lf.\n", amount, Bank.Accounts[i].AccountBalance);
            flag = 1;
            break;
        }
    }
    if(flag != 1){
     printf("\nBank Account not found for the Account Number %lld\n", AccNo);
    }
    return;
}

void withdrawMoney(){
    int flag = 0;
    long long int AccNo;
    printf("Enter your Account Number: ");
    scanf("%lld", &AccNo);
    for(int i = 0; i < Bank.size; i++){
        if(Bank.Accounts[i].AccountNumber == AccNo){
            struct Transaction *transaction = malloc(sizeof(struct Transaction));
            double amount;
            printf("Enter the amount of money you want to withdraw: ");
            scanf("%lf", &amount);
            if(Bank.Accounts[i].AccountBalance - amount < 0){
                printf("\nYour current Account Balance is INR. %.2lf. INR. %.2lf can not be withdrawn due to insufficient balance.\n", Bank.Accounts[i].AccountBalance, amount);
                break;
            }
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char curr_date[64];
            assert(strftime(curr_date, sizeof(curr_date), "%c", tm));
            strcpy(transaction->type, "Withdraw");
            transaction->amount = amount;
            strcpy(transaction->DateTime, curr_date);
            transaction->next = Bank.Accounts[i].next;
            Bank.Accounts[i].next = transaction;
            Bank.Accounts[i].AccountBalance = Bank.Accounts[i].AccountBalance - amount;
            printf("\nYour Money of INR. %.2lf has been withdrawn successfully.\nYour current Account Balance is INR. %.2lf.\n", amount, Bank.Accounts[i].AccountBalance);
            flag = 1;
            break;
        }
    }
    if(flag != 1){
     printf("\nBank Account not found for the Account Number %lld\n", AccNo);
    }
    return;
}

void generateMiniStatement(){
    int flag = 0;
    long long int AccNo;
    printf("Enter your Account Number: ");
    scanf("%lld", &AccNo);
    for(int i = 0; i < Bank.size; i++){
        if(Bank.Accounts[i].AccountNumber == AccNo){
            printf("\n-------------------------------------------------------------------------------\n");
            printf("Account Holder Name: %s\n", Bank.Accounts[i].Name);
            printf("Account Number: %lld \n", Bank.Accounts[i].AccountNumber);
            printf("Account Holder Email: %s \n", Bank.Accounts[i].Email);
            printf("Account Holder Phone Number: %lld \n", Bank.Accounts[i].PhoneNumber);
            printf("Account Balance: INR. %.2lf \n", Bank.Accounts[i].AccountBalance);
            printf("\n                  Last 3 Transactions               \n");
            printf("\nSNo.   Transaction Type     Date and Time        Amount\n");
            struct Transaction *temp = Bank.Accounts[i].next;
            for(int j = 0; j < 3; j++){
                    if(temp == NULL){
                        break;
                    }
                    printf("%d      %s             %s    INR. %.2lf\n", j + 1, temp->type, temp->DateTime, temp->amount);
                    temp = temp->next;
            }
            printf("--------------------------------------------------------------------------------\n");
            flag = 1;
            break;
        }
    }
    if(flag != 1){
     printf("\nBank Account not found for the Account Number %lld\n", AccNo);
    }
    return;
}

void displayAccountDetails(){
    int flag = 0;
    long long int AccNo;
    printf("Enter your Account Number: ");
    scanf("%lld", &AccNo);
    for(int i = 0; i < Bank.size; i++){
        if(Bank.Accounts[i].AccountNumber == AccNo){
            printf("\n------------------------------------------------\n");
            printf("Account Holder Name: %s\n", Bank.Accounts[i].Name);
            printf("Account Number: %lld \n", Bank.Accounts[i].AccountNumber);
            printf("Account Holder Email: %s \n", Bank.Accounts[i].Email);
            printf("Account Holder Phone Number: %lld \n", Bank.Accounts[i].PhoneNumber);
            printf("Account Balance: INR. %.2lf \n", Bank.Accounts[i].AccountBalance);
            printf("------------------------------------------------\n");
            flag = 1;
            break;
        }
    }
    if(flag != 1){
     printf("\nBank Account not found for the Account Number %lld\n", AccNo);
    }
    return;
}

void removeAccount(){
    int flag = 0;
    long long int AccNo;
    printf("Enter your Account Number: ");
    scanf("%lld", &AccNo);
    for(int i = 0; i < Bank.size; i++){
        if(Bank.Accounts[i].AccountNumber == AccNo){
            for (int j = i ; j < Bank.size - 1 ; j++ ){
                Bank.Accounts[j] = Bank.Accounts[j + 1];
            }
            Bank.size = Bank.size - 1;
            printf("\nBank Account with Account Number %lld has been removed succesfully.", AccNo);
            break;
        }
        flag = 1;
        break;
    }
    if(flag != 1){
     printf("\nBank Account not found for the Account Number %lld\n", AccNo);
    }
    return;
}

int main () {
    setInitialSize();
    srand(time(0));
    int initialChoice = printMenu();
    char userChoice;
    while(initialChoice == 1){
        printf("\nMENU\n1.Open Account\n2.Deposit Money\n3.Withdraw Money\n4.Generate Mini Statement\n5.Display Account Details\n6.Remove Account\n7.Exit System\n\n");
        printf("Enter your choice: ");
        scanf("%c", &userChoice);
            switch(userChoice){
                case '1':
                    openAccount();
                    break;
                case '2':
                    depositMoney();
                    break;
                case '3':
                    withdrawMoney();
                    break;
                case '4':
                    generateMiniStatement();
                    break;
                case '5':
                    displayAccountDetails();
                    break;
                case '6':
                    removeAccount();
                    break;
                case '7':
                    printf("Thank you for visiting our bank. Please Visit Again!!");
                    exit(0);
                default:
                    printf("You have entered a wrong option. Lets Begin Again.\n");
                    break;
        }
        fflush(stdin);
    }
    return 0;
}