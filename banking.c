#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void printing_reciept(FILE *ptr, float total_amount, char *account_number, char *name)
{
    fprintf(ptr, "\t\t\t\t\t\t\t\t\t\tBharat Bank Private Limited\n");
    fprintf(ptr, "\t\t\t\t\t\t\t\t\t Alampur,New Kolorah,Howrah-711302\n\n\n\n");
    fprintf(ptr, "Date  :-   %s\n\n", __DATE__);
    fprintf(ptr, "Time   :-    %s\n\n", __TIME__);
    fprintf(ptr, "Account Number :---    %s\n\n", account_number);
    fprintf(ptr, "Account Holder's Name :---    %s\n\n\n\n", name);
    fprintf(ptr, "The total amount in your account is Rs %f .\nThank You for using our services and giving us a chance to serve you.\n\n\nFor any other query call +9145624636 or\nEmail :- bharatbankalampur@gmail.com .\nOur central bank :-  Bharat Bank Private Limited,Kolkata,Salt Lake.", total_amount);
}
float total_amount(FILE *ptr)
{
    char *arr = (char *)malloc(300 * sizeof(char));
    for (int i = 0; i < 15; i++)
    {
        fgets(arr, 300, ptr);
    }
    for (int i = 0; i < 9; i++)
    {
        fscanf(ptr, "%s", arr);
    }
    return atof(arr);
}
void print_passbook(FILE *ptr, char *account_number, char *name)
{
    fprintf(ptr, "\t\t\t\t\t\t\t\t\t\tBharat Bank Private Limited\n");
    fprintf(ptr, "\t\t\t\t\t\t\t\t\t Alampur,New Kolorah,Howrah-711302\n\n\n\n");
    fprintf(ptr, "Account Holder's Name  :--      %s\n\n", account_number);
    fprintf(ptr, "Account Number:--    %s\n\n\n", name);
    fprintf(ptr, "|    Date        |    Time    |     Amount  |       Activity   |   Amount Left  |\n");
    for (int i = 0; i < 82; i++)
    {
        fprintf(ptr, "~");
    }
    fprintf(ptr, "\n");
}
void withdraw_pass(FILE *ptr,float amount_withdrawn,float final_amount)
{
    fprintf(ptr,"|   %s  |",__DATE__);
    fprintf(ptr,"|   %s  |",__TIME__);
    fprintf(ptr,"|   %f  |",amount_withdrawn);
    fprintf(ptr,"|   withdrawl  |");
    fprintf(ptr,"|   %f  |\n",final_amount);
    for (int i = 0; i < 82; i++)
    {
        fprintf(ptr, "~");
    }
    fprintf(ptr, "\n");
}
void deposit_pass(FILE *ptr,float final_amount,float amount_deposited)
{
    fprintf(ptr,"|   %s  |",__DATE__);
    fprintf(ptr,"|   %s  |",__TIME__);
    fprintf(ptr,"|   %f  |",amount_deposited);
    fprintf(ptr,"|   deposition  |");
    fprintf(ptr,"|   %f  |\n",final_amount);
    for (int i = 0; i < 82; i++)
    {
        fprintf(ptr, "~");
    }
    fprintf(ptr, "\n");
}

int main()
{
    char *reciept = (char *)malloc(200);
    char *passbook = (char *)malloc(200);
    printf("Enter the account number of the customer:---  ");
    gets(passbook);
    printf("Enter Name of the account holder:-->   ");
    gets(reciept);
    char *account_number = (char *)malloc(200);
    char *account_name = (char *)malloc(200);
    strcpy(account_number, passbook);
    strcpy(account_name, reciept);
    int l = strlen(reciept);
    for (int i = 0; i < 2; i++)
    {
        reciept[l + i] = passbook[i];
    }
    char txt[] = ".txt";
    strcpy(&reciept[l + 2], txt);
    strcpy(&passbook[strlen(passbook)], txt);
    FILE *pointer_reciept = fopen(reciept, "a+");
    FILE *pointer_passbook = fopen(passbook, "a+");
    fclose(pointer_passbook);
    fclose(pointer_reciept);
    pointer_reciept = fopen(reciept, "r+");
    pointer_passbook = fopen(passbook, "r+");
    print_passbook(pointer_passbook, account_number, account_name);
    fclose(pointer_passbook);
    pointer_passbook = fopen(passbook, "a+");

    printf("\t\t\t\t\t\t\tWelcome to Bharat Bank Online transanctions.\n\n\n\n\n");
    printf("Enter 1 to do balance enquiry.\n");
    printf("Enter 2 to Withdraw Cash.\n");
    printf("Enter 3 to Deposit Money.\n");
    printf("Enter any other key to Exit.\n");
    printf("\n\nEnter your choice HERE:-->   ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        float amount = total_amount(pointer_reciept);
        printf("%f", amount);
        printing_reciept(pointer_reciept, amount, account_number, account_name);
    }
    else if (choice == 2)
    {
        printf("\nEnter the amount to be withdrawn :--   ");
        float amount_withdrawn;
        scanf("%f",&amount_withdrawn);
        float amount = total_amount(pointer_reciept);
        if(amount_withdrawn>amount)
        {
            printf("The amount Entered to be withdrawn is greater than the amount in account.\nTransanction denied..................\n\n");
        }
        else
        {
            amount = amount-amount_withdrawn;
            withdraw_pass(pointer_passbook,amount_withdrawn,amount);
            fclose(pointer_reciept);
            pointer_reciept = fopen(reciept,"w");
            printing_reciept(pointer_reciept, amount, account_number, account_name);
            printf("\n\nTransanction completed..........\nWithdrawl of %f is complete.\n\n",amount_withdrawn);
        }
    }
    else if (choice == 3)
    {
        printf("Enter the amount to be deposited  :--  ");
        float amount_deosit;
        scanf("%f",&amount_deosit);
        float amount = total_amount(pointer_reciept);
        amount = amount + amount_deosit;
        deposit_pass(pointer_passbook,amount,amount_deosit);
        fclose(pointer_reciept);
        pointer_reciept = fopen(reciept,"w");
        printing_reciept(pointer_reciept, amount, account_number, account_name);
        printf("\n\nTransanction completed..........\nDeposition of %f is complete.\n\n",amount_deosit);

    }
    else
    {
        printf("\n\nThank you choosing us to serve you");
    }

    fclose(pointer_passbook);
    fclose(pointer_reciept);
    return 0;
}