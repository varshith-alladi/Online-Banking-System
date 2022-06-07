#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

// structure with user details
typedef struct userDetails
{
    char phone[30];
    char accNum[30];
    char password[30];
    float balance;
} userD;

int main()
{

    userD user, user1;
    FILE *filePtr;
    char fileName[30], phone[30], pwd[30], pwd1[30], proceed = 'y';
    int choice, bankingChoice;
    float amount;

// using labels and goto to return to the login/register menu
label1:
    printf("\n------ Welcome to the Online Banking System ------");
    printf("\n\n(1) Register an account");
    printf("\n(2) Login to an account");
    printf("\n(3) Exit");

    printf("\n\nEnter your choice : ");
    scanf("%d", &choice);

    // Creating a new account for new user
    if (choice == 1)
    {
        system("cls"); /* used to pass the commands that can be executed in the terminal and returns the command after it has been completed */

        printf("Enter your account number : ");
        scanf("%s", user.accNum);

        printf("Enter your phone number : ");
        scanf("%s", user.phone);

        printf("Enter your password : ");
        scanf("%s", user.password);

        user.balance = 0;

        // Naming the file name as the phone number and writing the details of the new user
        strcpy(fileName, user.phone);
        filePtr = fopen(strcat(fileName, ".dat"), "w");
        fwrite(&user, sizeof(userD), 1, filePtr);

        if (fwrite != 0)
        {
            printf("\nCongratulations! Your account has been successfully created");
        }
        else
        {
            printf("\n\n---!Error!---\nPlease Try Again");
        }

        fclose(filePtr);
    }

    // Logging into already existing account
    if (choice == 2)
    {
        system("cls");

        printf("\nEnter your Phone Number : ");
        scanf("%s", phone);

        printf("Enter your password : ");
        scanf("%s", pwd);

        // reading the file and checking if the credentials match or not
        strcpy(fileName, phone);
        filePtr = fopen(strcat(fileName, ".dat"), "r");
        if (filePtr == NULL)
        {
            printf("\n---!Error!---\nNumber not regisered.Kindly register an account.");
        }
        else
        {
            fread(&user, sizeof(userD), 1, filePtr);
            fclose(filePtr);
            if (!strcmp(pwd, user.password))
            {
                // printf("\n-----Password Matched-----");
                while (proceed == 'y')
                {
                    system("cls");
                    printf("\n------ WELCOME %s ------", user.phone);
                    printf("\n\n1) Cash Deposit");
                    printf("\n2) Cash Withdrawl");
                    printf("\n3) Online Transfer");
                    printf("\n4) Balance Inquiry");
                    printf("\n5) Change Password");
                    printf("\n6) Logout");
                    printf("\n7) Exit");

                    printf("\n\nEnter your choice : ");
                    scanf("%d", &bankingChoice);

                    switch (bankingChoice)
                    {
                    case 1:
                        printf("\nEnter the Amount : ");
                        scanf("%f", &amount);
                        user.balance += amount;
                        filePtr = fopen(fileName, "w");
                        fwrite(&user, sizeof(userD), 1, filePtr);
                        if (fwrite != NULL)
                        {
                            printf("\nCash deposited successfully.");
                        }
                        else
                        {
                            printf("\n----!Error!----\nSomething went wrong. Please try again.");
                        }
                        fclose(filePtr);
                        break;
                    case 2:
                        printf("\nEnter the Amount : ");
                        scanf("%f", &amount);
                        if (amount > user.balance)
                        {
                            printf("\nInsufficient balance. Please check your balance.");
                        }
                        else
                        {
                            user.balance -= amount;
                            filePtr = fopen(fileName, "w");
                            fwrite(&user, sizeof(userD), 1, filePtr);
                            if (fwrite != NULL)
                            {
                                printf("\nWithdrawn amount : %.2f \n", amount);
                            }
                            else
                            {
                                printf("\n----!Error!----\nSomething went wrong. Please try again.");
                            }
                            fclose(filePtr);
                        }
                        break;
                    case 3:
                        printf("\nEnter the phone number of recepient : ");
                        scanf("%s", phone);
                        printf("Enter the amount to transfer : ");
                        scanf("%f", &amount);

                        strcpy(fileName, phone);
                        filePtr = fopen(strcat(fileName, ".dat"), "r");
                        if (filePtr == NULL)
                        {
                            printf("\nPhone number not registered");
                        }
                        else
                        {
                            fread(&user1, sizeof(userD), 1, filePtr);
                            fclose(filePtr);

                            if (amount > user.balance)
                            {
                                printf("\nInsufficient balance");
                            }
                            else
                            {
                                filePtr = fopen(fileName, "w");
                                user1.balance += amount;
                                fwrite(&user1, sizeof(userD), 1, filePtr);
                                fclose(filePtr);

                                if (fwrite != NULL)
                                {
                                    printf("\nTransaction Successful");
                                    strcpy(fileName, user.phone);
                                    filePtr = fopen(strcat(fileName, ".dat"), "w");
                                    user.balance -= amount;
                                    fwrite(&user, sizeof(userD), 1, filePtr);
                                    fclose(filePtr);
                                }
                            }
                        }
                        break;
                    case 4:
                        printf("\nYour current Balance is Rs.%.2f", user.balance);
                        break;
                    case 5:
                        printf("\nEnter a new password : ");
                        scanf("%s", pwd);
                        printf("\nConfirm the new password : ");
                        scanf("%s", pwd1);

                        if (!strcmp(pwd, pwd1))
                        {
                            filePtr = fopen(fileName, "w");
                            strcpy(user.password, pwd);
                            fwrite(&user, sizeof(userD), 1, filePtr);
                            if (fwrite != NULL)
                            {
                                printf("\nPassword change successful.");
                                printf("\nYou have been logged out as the password is changed.\nLogin again...!");
                                goto label1;
                            }
                            else
                            {
                                printf("\n----!Error!----\nSomething went wrong. Please try again.");
                            }
                        }
                        else
                        {
                            printf("\n----- The passwords do not match Please try again -----");
                        }
                        break;
                    case 6:
                        goto label1;
                    case 7:
                        return 0;
                    default:
                        printf("\nInvalid Banking Option");
                    }

                    printf("\n\nDo you want to continue the transaction? [y/n]");
                    scanf("%s", &proceed);
                }
            }
            else
            {
                printf("\n---!Error!---\nInvalid Password");
                goto label1;
            }
        }
    }

    if (choice == 3)
    {
        return 0;
    }

    return 0;
}