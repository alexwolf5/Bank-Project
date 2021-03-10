#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

struct account{
    int acctnum;
    char name[80];
    char birthday[20];
    char address [100];
    double balance;
};
int input;
char output[];
int someput;

void main(){
    int input = 1;
    system("color 0A");
    printf("\n\n\t\t Project for self-learning completed by Alexander Peter in Code::Blocks.\n\n\t\t Press Enter to continue!\n\n\t\t");
    getchar();

    menu();

    return;
}

void menu(){ //Main menu, where user will decide from several options
    int someput;
    system("cls");

    printf("\n\n\t\t\t\xB0\xB0\xB0\xB0\xB0\xB0\xB1\xB1\xB1\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2      Welcome to the Bank      \xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB1\xB1\xB1\xB1\xB0\xB0\xB0\xB0\xB0\xB0");
    printf("\n\n\t\t\t   Please Pick An Option Below By Entering A Corresponding Number");
    printf("\n\n\t\t\t\t   1. Create a new account");
    printf("\n\t\t\t\t   2. View an existing account");
    printf("\n\t\t\t\t   3. Delete an account");
    printf("\n\t\t\t\t   4. Deposit or withdraw funds from an accounts");
    printf("\n\t\t\t\t   5. Exit \n\t\t\t\t\t");

    scanf(" %d", &someput);

    if(someput != 1 && someput != 2 && someput != 3 && someput != 4 && someput != 5)
    {
        menu();
    }
    else if(someput == 1)
    {
        newacct();
    }
    else if(someput == 2)
    {
        existingacct();
    }
    else if (someput == 3)
    {
        delete();
    }
    else if(someput == 4)
    {
        transact();
    }
    else if (someput == 5)
    {
        exit(0);
    }
}

void newacct(){
    system("cls");
    struct account person;
    char userfile[50];
    char buffer[20];
    char output;
    int input = 0;
    int exit = 0;

    printf("\n\n\t\t Please provide a series of numbers that will become the new account number.\n\t\t New account number: ");
    scanf(" %d", &person.acctnum);
    system("cls");

    sprintf(userfile, "%d.txt", person.acctnum);
    FILE * pf;
    if(pf = fopen(userfile, "r"))
    {                                    //To check if the account number is already in use
        while(input != 1 && input != 2)
        {
             printf("\n\n\t\tThis account number is already in use.\n\n\t\t Press 1 to try again.\n\t\t Press 2 to return to the main menu.\n\t\t");
             scanf(" %d", &input);
             fclose(pf);
        }
        if (input == 1)
        {                   //Allowing user to decide to try a new acct number, or return to main menu
            newacct();
        }
        else if(input == 2)
        {
            menu();
        }
    }

    printf("\n\n\t\t What is the name of the new account owner?\n\t\t Name: ");
    fgets(person.name, 80, stdin);
    scanf("%[^\n]%*c", person.name);  //Taking user input, including any spaces, into the string
    system("cls");

    printf("\n\n\t\t What is the birthday of the new account owner?\n\t\t Birthday (XX/XX/XXXX): ");
    scanf(" %s", person.birthday);
    system("cls");

    while (strlen(person.birthday) != 10)
    {
        printf("\n\n\t\t Invalid format.  Please enter birthday in the format 'XX/XX/XXXX'.\n\t\t Birthday: ");
        scanf(" %s", person.birthday);
        system("cls");
    }

    printf("\n\n\t\t What is the address of the new account owner?\n\t\t Address: ");
    fgets(person.address, 100, stdin);
    scanf("%[^\n]%*c", person.address);
    system("cls");

    printf("\n\n\t\t What is the initial deposit amount?\n\t\t Starting balance (do not include '$' sign): ");
    scanf(" %lf", &person.balance);
    person.balance = floor(person.balance * 100);
    person.balance = person.balance/100;
    system("cls");

    pf = fopen(userfile, "w");
    fprintf(pf, "%d %s %s %s %f", person.acctnum, person.name, person.birthday, person.address, person.balance);
    fclose(pf);

    printf("\n\n\t\tAccount Number: %d \n\t\tOwner: %s \n\t\tBirthday: %s \n\t\tAddress: %s \n\t\tBalance: %f", person.acctnum, person.name, person.birthday, person.address, person.balance);

    while (exit != 1)
    {
        printf("\n\n\t\t Press 1 to continue... \n\t\t");
        scanf(" %d", &exit);
    }
    menu();
}

void existingacct(){
    system("cls");
    struct account person;
    char userfile[50];
    int edit = 0;
    int exit = 0;

    printf("\n\n\t\t What is the account number?\n\t\t Account number: ");
    scanf("%d", &person.acctnum);
    system("cls");

    sprintf(userfile, "%d.txt", person.acctnum);
    FILE * pf;
    if(pf = fopen(userfile, "r"))
    {                             //To check if the account number is already in use
        pf = fopen(userfile, "r");
        fscanf(pf, "%d %s %s %s %lf", &person.acctnum, person.name, person.birthday, person.address, &person.balance);
        fclose(pf);
        printf("\n\n\t\t Account Number: %d \n\t\t Owner: %s \n\t\t Birthday: %s \n\t\t Address: %s \n\t\t Balance: %f", person.acctnum, person.name, person.birthday, person.address, person.balance);

        while(edit != 1 && edit != 2 && edit != 3 && edit != 4 && edit != 5)
        {
            printf("\n\n\t Would you like to edit a section of this account?  Enter the corresponding number. \n\n\t\t 1. Name \n\t\t 2. Birthday \n\t\t 3. Address \n\t\t 4. Everything \n\t\t 5. Return to Main Menu");
            scanf(" %d", &edit);
            fclose(pf);
        }

        if(edit == 5)
        {
            menu();
        }
        system("cls");

        if (edit == 1 || edit == 4)
        {
            printf("\n\n\t\t Please re-enter the name of the account owner.\n\t\t Name: ");
            fgets(person.name, 80, stdin);
            scanf("%[^\n]%*c", person.name);
            system("cls");
        }

        if (edit == 2 || edit == 4)
        {
            printf("\n\n\t\t Please re-enter the birthday of the account owner.\n\t\t Birthday (XX/XX/XXXX): ");
            scanf(" %s", person.birthday);
            system("cls");
            while (strlen(person.birthday) != 10)
            {
                printf("\n\n\t\t Invalid format.  Please enter the birthday as XX/XX/XXXX.\n\t\t Birthday (XX/XX/XXXX): ");
                scanf(" %s", person.birthday);
                system("cls");
            }
        }

        if (edit = 3 || edit == 4)
        {
            printf("\n\n\t\t Please re-enter the address of the account owner.\n\t\t Address: ");
            fgets(person.address, 100, stdin);
            scanf("%[^\n]%*c", person.address);
            system("cls");
        }

        pf = fopen(userfile, "w");
        fprintf(pf, "%d %s %s %s %f", person.acctnum, person.name, person.birthday, person.address, person.balance);
        fclose(pf);

        printf("\n\n\t\t Account Number: %d \n\t\t Owner: %s \n\t\t Birthday: %s \n\t\t Address: %s \n\t\t Balance: %f", person.acctnum, person.name, person.birthday, person.address, person.balance);

        while (exit != 1)
        {
                printf("\n\n\t\t Press 1 to continue... \n\t\t");
        scanf(" %d", &exit);
        }
        menu();
    }

    else
    {
        while(exit != 1 && exit != 2)
        {
             printf("\n\n\t\tThis account does not exist.\n\n\t\t Press 1 to try again.\n\t\t Press 2 to return to the main menu.\n\n\t\t");
             scanf(" %d", &input);
             fclose(pf);

        }
        if (exit == 1)
        {                   //Allowing user to decide to try a new acct number, or return to main menu
            existingacct();
        }
        else if(exit == 2)
        {
            menu();
        }
    }
}

void delete(){
    system("cls");
    struct account person;
    int edit = 0;
    int exit = 0;
    char userfile[50];

    printf("\n\n\t\t What is the account number you wish to delete?\n\t\t Account number: ");
    scanf("%d", &person.acctnum);
    system("cls");

    sprintf(userfile, "%d.txt", person.acctnum);
    FILE * pf;
    if(pf = fopen(userfile, "r"))
    {                                       //To check if the account number is already in use
        pf = fopen(userfile, "r");
        fscanf(pf, "%d %s %s %s %lf", &person.acctnum, person.name, person.birthday, person.address, &person.balance);
        fclose(pf);
        printf("\n\n\t\t Account Number: %d \n\t\t Owner: %s \n\t\t Birthday: %s \n\t\t Address: %s \n\t\t Balance: %f", person.acctnum, person.name, person.birthday, person.address, person.balance);

        while(edit != 1 && edit != 2)
        {
            printf("\n\n\t\t Are you sure you want to delete this account?\n\n\t\t Press 1 to delete.\n\t\t Press 2 to return to the main menu.\n");
            scanf(" %d", &edit);
        }
        if(edit == 2)
        {
            menu();
        }
        system("cls");

        remove(userfile);
        while (exit != 1)
        {
            printf("\n\n\t\t Account has been deleted.  Press 1 to return to the main menu.\n\t\t");
            scanf( " %d", &exit);
        }
        menu();
    }

    else{
        while(input != 1 && input != 2)
        {
             printf("\n\n\t\tThis account does not exist.\n\n\t\t Please press 1 to try again. \n\t\t Press 2 to return to the main menu.\n\n\t\t");
             scanf(" %d", &input);
             fclose(pf);

        }
        if (input == 1)
        {                   //Allowing user to decide to try a new acct number, or return to main menu
            delete();
        }
        else if(input == 2)
        {
            menu();
        }
    }
}

void transact(){
    system("cls");
    struct account person;
    int edit = 0;
    int exit = 0;
    int input = 0;
    double depdrawl = 0;
    char userfile[50];
    char output;

    printf("\n\n\t\t What is the account number you wish to deposit or withdrawal from?\n\t\t Account number: ");
    scanf(" %d", &person.acctnum);
    system("cls");

    sprintf(userfile, "%d.txt", person.acctnum);
    FILE * pf;
    if(pf = fopen(userfile, "r"))
    {                                       //To check if the account number is already in use
        pf = fopen(userfile, "r");
        fscanf(pf, "%d %s %s %s %lf", &person.acctnum, person.name, person.birthday, person.address, &person.balance);
        fclose(pf);
        printf("\n\n\t\t Account Number: %d \n\t\t Owner: %s \n\t\t Birthday: %s \n\t\t Address: %s \n\t\t Balance: %f", person.acctnum, person.name, person.birthday, person.address, person.balance);

        while(edit != 1 && edit != 2 && edit != 3)
        {
            printf("\n\n\t\t Press 1 to make a withdrawal.\n\t\t Press 2 to make a deposit.\n\t\t Press 3 to return to the main menu.\n\t\t");
            scanf(" %d", &edit);
        }
        if(edit == 3)
        {
            menu();
        }
        system("cls");

        if(edit == 1)  //Withdrawal
        {
            printf("\n\n\t\t What is the amount you wish to withdrawl?\n\t\t Amount (without '$' sign): ");
            scanf(" %lf", &depdrawl);
            depdrawl = floor(depdrawl * 100);
            depdrawl = depdrawl/100;
            if ((person.balance - depdrawl) < 0)
            {
                printf("\n\t\t This account does not have enough funds to withdraw that amount.  Returning to main menu...");
                sleep(3);
                menu();
            }
            person.balance = person.balance - depdrawl;
        }

        if(edit == 2)  //Deposit
        {
            printf("\n\n\t\t What is the amount you wish to deposit?\n\t\t Amount (without '$' sign): ");
            scanf(" %lf", &depdrawl);
            depdrawl = floor(depdrawl * 100);
            depdrawl = depdrawl/100;
            person.balance = person.balance + depdrawl;
        }

        system("cls");
        pf = fopen(userfile, "w");
        fprintf(pf, "%d %s %s %s %f", person.acctnum, person.name, person.birthday, person.address, person.balance);
        fclose(pf);

        printf("\n\n\t\t Account Number: %d \n\t\t Owner: %s \n\t\t Birthday: %s \n\t\t Address: %s \n\t\t Balance: %f", person.acctnum, person.name, person.birthday, person.address, person.balance);

        while (exit != 1)
        {
            printf("\n\n\t\t Press 1 to continue... \n\t\t");
            scanf(" %d", &exit);
        }
        menu();
    }
    else
    {
        while(input != 1 && input != 2)
        {
             printf("\n\n\t\tThis account does not exist.\n\n\t\t Press 1 to try again./n/t/t Press 2 to return to main menu.\n\t\t");
             scanf(" %d", &input);
             fclose(pf);

        }
        if (input == 1)
        {                   //Allowing user to decide to try a new acct number, or return to main menu
            transact();
        }
        else if(input == 2)
        {
            menu();
        }
    }
}
