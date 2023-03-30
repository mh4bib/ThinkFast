#include<stdio.h>
#include<login.h>
#include<register.h>
#include<clear_screen.h>
#include<main_menu.h>
void login_prompt(char** email, int** level)
{
    int choice;
    do
    {
        printf("====================================\n");
        printf("|            Select One            |\n");
        printf("====================================\n");
        printf("| 1. Login                         |\n");
        printf("| 2. Register                      |\n");
        printf("| 3. Go back to Home               |\n");
        printf("====================================\n");
        printf("| Enter your choice (1-3):         |\n");
        printf("====================================\n");

        if (scanf("%d", &choice) != 1)
        {
            clear_screen();
            printf("\x1b[31mInvalid choice. Please enter a number between 1 and 4.\x1b[0m\n");
            while (getchar() != '\n');
            // choice = -1;  // set invalid choice to continue loop
            // fflush(stdin);
            continue;
        }
        switch (choice)
        {
        case 1:
            clear_screen();
            login(email, level);
            break;
        case 2:
            clear_screen();
            registr(email, level);
            break;
        case 3:
            clear_screen();
            main_menu();
        default:
            clear_screen();
            printf("\x1b[31mInvalid choice. Please enter a number between 1 and 4\x1b[0m\n");
            break;
        }

    } while (choice < 1 || choice > 3);
}