#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

struct account{  //Structure for all information accounts hold
    int acctnum;
    char lastname[80];
    char firstname[80];
    char birthday[20];
    char address [100];
    double balance;
};
int input;
char output[];
int someput;

void main(){  //Opening Page
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

void newacct(){  //Where a user can create a new account
    system("cls");
    struct account person;
    char userfile[50];
    char buffer[20];
    char output;
    int input = 0;
    int exit = 0;

    printf("\n\n\t\t Please provide a series of numbers that will become the new account number.\n\t\t New account number: ");
    if (scanf(" %d", &person.acctnum) != 1) //Takes in user input, which will become the file name all other information is stored in)
    {
        getchar();
        getchar();
        newacct();
    }
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

    printf("\n\n\t\t What is the last name of the new account owner?\n\t\t Last name: ");
    fgets(person.lastname, 80, stdin);
    scanf(" %s", person.lastname);  //Taking user input
    system("cls");

    printf("\n\n\t\t What is the first name of the new account owner?\n\t\t First name: ");
    fgets(person.firstname, 80, stdin);
    scanf(" %s", person.firstname);  //Taking user input
    system("cls");

    printf("\n\n\t\t What is the birthday of the new account owner?\n\t\t Birthday (XX/XX/XXXX): ");
    scanf(" %s", person.birthday);
    system("cls");

    while (strlen(person.birthday) != 10)  //Checks that the user inputted birthday is of appropriate length
    {
        printf("\n\n\t\t Invalid format.  Please enter birthday in the format 'XX/XX/XXXX'.\n\t\t Birthday: ");
        scanf(" %s", person.birthday);
        system("cls");
    }

    printf("\n\n\t\t What is the address of the new account owner?\n\t\t Address: ");
    fgets(person.address, 100, stdin);
    scanf("%[^\n]%*c", person.address);  //Takes in user input, including spaces
    system("cls");

    printf("\n\n\t\t What is the initial deposit amount?\n\t\t Starting balance (do not include '$' sign): ");
    while (scanf(" %lf", &person.balance) != 1)
    {
        getchar();
        getchar();
        printf("\n\t\t");
        continue;
    }
    person.balance = floor(person.balance * 100);
    person.balance = person.balance/100;  //Takes in double, but rounds deletes all values past hundredth decimal
    system("cls");

    pf = fopen(userfile, "w");  //Writes collected data onto file, and prints out for user to see
    fprintf(pf, "%d %s %s %s %f %s", person.acctnum, person.firstname, person.lastname, person.birthday, person.balance, person.address);
    fclose(pf);

    printf("\n\n\t\tAccount Number: %d \n\t\tOwner: %s %s \n\t\tBirthday: %s \n\t\tAddress: %s \n\t\tBalance: %f", person.acctnum, person.firstname, person.lastname, person.birthday, person.address, person.balance);

    while (exit != 1)  //To ensure proper input is received to exit program
    {
        printf("\n\n\t\t Press 1 to continue... \n\t\t");
        scanf(" %d", &exit);
    }
    menu();
}

void existingacct(){  //To allow users to view a previously created account, and choose to make edits to all sections except balance
    system("cls");
    struct account person;
    char userfile[50];
    int edit = 0;
    int input = 0;

    printf("\n\n\t\t What is the account number?\n\t\t Account number: ");
    scanf("%d", &person.acctnum);  //Takes in user input as account number
    system("cls");

    sprintf(userfile, "%d.txt", person.acctnum);
    FILE * pf;
    if(pf = fopen(userfile, "r"))
    {                                       //To check if the account number is already in use
        fscanf(pf, "%d %s %s %s %lf %[^\n]%*c %s", &person.acctnum, person.firstname, person.lastname, person.birthday, &person.balance, person.address);
        fclose(pf);
        printf("\n\n\t\t Account Number: %d \n\t\t Owner: %s %s \n\t\t Birthday: %s \n\t\t Address: %s \n\t\t Balance: %f", person.acctnum, person.firstname, person.lastname, person.birthday, person.address, person.balance);

        while(edit != 1 && edit != 2 && edit != 3 && edit != 4 && edit != 5)
        {
            printf("\n\n\t Would you like to edit a section of this account?  Enter the corresponding number. \n\n\t\t 1. Name \n\t\t 2. Birthday \n\t\t 3. Address \n\t\t 4. Everything \n\t\t 5. Return to Main Menu\n\t\t ");
            scanf(" %d", &edit);
            fclose(pf);
        }

        if(edit == 5)
        {
            menu();
        }
        system("cls");

        if (edit == 1 || edit == 4)  //Takes in user input for a new name
        {
            printf("\n\n\t\t Please re-enter the last name of the account owner.\n\t\t Last name: ");
            fgets(person.lastname, 80, stdin);
            scanf(" %s", person.lastname);
            system("cls");

            printf("\n\n\t\t Please re-enter the first name of the account owner.\n\t\t First name: ");
            fgets(person.firstname, 80, stdin);
            scanf(" %s", person.firstname);
            system("cls");
        }

        if (edit == 2 || edit == 4) //Takes in user input for a new birthday
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

        if (edit = 3 || edit == 4)  //Takes in user input for a new address
        {
            printf("\n\n\t\t Please re-enter the address of the account owner.\n\t\t Address: ");
            fgets(person.address, 100, stdin);
            scanf("%[^\n]%*c", person.address);
            system("cls");
        }

        pf = fopen(userfile, "w");  //Writes all information, including new information, back into file and prints out for user
        fprintf(pf, "%d %s %s %s %f %s", person.acctnum, person.firstname, person.lastname, person.birthday, person.balance, person.address);
        fclose(pf);

        printf("\n\n\t\t Account Number: %d \n\t\t Owner: %s %s \n\t\t Birthday: %s \n\t\t Address: %s \n\t\t Balance: %f", person.acctnum, person.firstname, person.lastname, person.birthday, person.address, person.balance);

        while (exit != 1)
        {
                printf("\n\n\t\t Press 1 to continue... \n\t\t");
        scanf(" %d", &exit);
        }
        menu();
    }

    else  //If account does not exist, give user option to try another number or return to menu
    {
        while(input != 1 && input != 2)
        {
             printf("\n\n\t\tThis account does not exist.\n\n\t\t Press 1 to try again.\n\t\t Press 2 to return to main menu.\n\t\t");
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

void delete(){
    system("cls");
    struct account person;
    int edit = 0;
    int exit = 0;
    int file = 0;
    int input = 0;
    char userfile[50];

    printf("\n\n\t\t What is the account number you wish to delete?\n\t\t Account number: ");
    scanf("%d", &person.acctnum); //Takes user input as account number
    system("cls");

    sprintf(userfile, "%d.txt", person.acctnum);
    FILE * pf;

    if(pf = fopen(userfile, "r"))
    {                                       //To check if the account number is already in use
        fscanf(pf, "%d %s %s %s %lf %[^\n]%*c %s", &person.acctnum, person.firstname, person.lastname, person.birthday, &person.balance, person.address);
        fclose(pf);
        printf("\n\n\t\t Account Number: %d \n\t\t Owner: %s %s \n\t\t Birthday: %s \n\t\t Address: %s \n\t\t Balance: %f", person.acctnum, person.firstname, person.lastname, person.birthday, person.address, person.balance);

        while(edit != 1 && edit != 2)  //Allows user to choose to delete the account
        {
            printf("\n\n\t\t Are you sure you want to delete this account?\n\n\t\t Press 1 to delete.\n\t\t Press 2 to return to the main menu.\n");
            scanf(" %d", &edit);
        }
        if(edit == 2)
        {
            menu();
        }

        system("cls");
        remove(userfile);  //Removes file (NOTE: A file created can not be deleted in the same instance of the program, program must be closed and opened again to work, gotta figure that out)

        while (exit != 1)
        {
            printf("\n\n\t\t Account has been deleted.  Press 1 to return to the main menu.\n\t\t");
            scanf( " %d", &exit);
        }
        menu();
    }

    else
    {
        while(input != 1 && input != 2)  //If account does not exist, gives user option to try again or return to menu
             printf("\n\n\t\tThis account does not exist.\n\n\t\t Please press 1 to try again. \n\t\t Press 2 to return to the main menu.\n\n\t\t");
             scanf(" %d", &input);
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
    scanf(" %d", &person.acctnum);  //Takes user input as account number
    system("cls");

    sprintf(userfile, "%d.txt", person.acctnum);
    FILE * pf;
    if(pf = fopen(userfile, "r"))
    {                                       //To check if the account number is already in use
        pf = fopen(userfile, "r");
        fscanf(pf, "%d %s %s %s %lf %[^\n]%*c %s", &person.acctnum, person.firstname, person.lastname, person.birthday, &person.balance, person.address);
        fclose(pf);
        printf("\n\n\t\t Account Number: %d \n\t\t Owner: %s %s \n\t\t Birthday: %s \n\t\t Address: %s \n\t\t Balance: %f", person.acctnum, person.firstname, person.lastname, person.birthday, person.address, person.balance);

        while(edit != 1 && edit != 2 && edit != 3)  //User chooses to withdraw, deposit or return to menu
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
            printf("\n\n\t\t What is the amount you wish to withdraw?\n\t\t Amount (without '$' sign): ");
            while (scanf(" %lf", &depdrawl) != 1)
            {
                getchar();
                getchar();
                printf("\n\t\t");
                continue;
            }
            depdrawl = floor(depdrawl * 100);  //Takes in withdraw amount and checks that the acct has the necessary funds
            depdrawl = depdrawl/100;
            if ((person.balance - depdrawl) < 0)
            {
                printf("\n\t\t This account does not have enough funds to withdraw that amount.  Returning to main menu...");
                sleep(3);
                menu();
            }
            person.balance = person.balance - depdrawl;
        }

        if(edit == 2)  //Deposits inputted value into account
        {
            printf("\n\n\t\t What is the amount you wish to deposit?\n\t\t Amount (without '$' sign): ");
            while (scanf(" %lf", &depdrawl) != 1)
            {
                getchar();
                getchar();
                printf("\n\t\t");
                continue;
            }
            depdrawl = floor(depdrawl * 100);
            depdrawl = depdrawl/100;
            person.balance = person.balance + depdrawl;
        }

        system("cls");
        pf = fopen(userfile, "w");  //Writes new balance info to file and prints details to user
        fprintf(pf, "%d %s %s %s %f %s", person.acctnum, person.firstname, person.lastname, person.birthday, person.balance, person.address);
        fclose(pf);

        printf("\n\n\t\t Account Number: %d \n\t\t Owner: %s %s \n\t\t Birthday: %s \n\t\t Address: %s \n\t\t Balance: %f", person.acctnum, person.firstname, person.lastname, person.birthday, person.address, person.balance);

        while (exit != 1)
        {
            printf("\n\n\t\t Press 1 to continue... \n\t\t");
            scanf(" %d", &exit);
        }
        menu();
    }
    else
    {
        while(input != 1 && input != 2)  //If account does not exist, user can try again or return to main menu
        {
             printf("\n\n\t\tThis account does not exist.\n\n\t\t Press 1 to try again.\n\t\t Press 2 to return to main menu.\n\t\t");
             scanf(" %d", &input);
             fclose(pf);

        }
        if (input == 1)
        {
            transact();
        }
        else if(input == 2)
        {
            menu();
        }
    }
}
