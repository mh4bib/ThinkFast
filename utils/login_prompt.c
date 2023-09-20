#include<stdio.h>
#include<login.h>
#include<register.h>
#include<clear_screen.h>
#include<main_menu.h>
#include<custom_print.h>
#include<gotoxy.h>
#include<ansi_color_codes.h>
extern yCoord;

void login_prompt(char** email, int** level)
{
    int choice;
    do
    {
        printCenter("+----------------------------------+\n", &yCoord);
        printCenter("|            "UWHT"SELECT ONE"RESET"            |\n", &yCoord);
        printCenter("+----------------------------------+\n", &yCoord);
        printCenter("| 1. Login                         |\n", &yCoord);
        printCenter("| 2. Register                      |\n", &yCoord);
        printCenter("| 3. Go back to Home               |\n", &yCoord);
        printCenter("+----------------------------------+\n", &yCoord);
        printCenter("| Enter your choice (1-3):         |\n", &yCoord);
        printCenter("+----------------------------------+\n", &yCoord);

        gotoxy(20 + 27, yCoord - 2);
        if (scanf("%d", &choice) != 1)
        {
            clear_screen(&yCoord);
            gotoxy(12, 2);
            printf("\x1b[31mInvalid choice. Please enter a number between 1 and 4.\x1b[0m\n");
            while (getchar() != '\n');
            // choice = -1;  // set invalid choice to continue loop
            // fflush(stdin);
            continue;
        }
        switch (choice)
        {
        case 1:
            clear_screen(&yCoord);
            login(email, level);
            break;
        case 2:
            clear_screen(&yCoord);
            registr(email, level);
            break;
        case 3:
            clear_screen(&yCoord);
            main_menu();
        default:
            clear_screen(&yCoord);
            gotoxy(12, 2);
            printf("\x1b[31mInvalid choice. Please enter a number between 1 and 4\x1b[0m\n");
            break;
        }

    } while (choice < 1 || choice > 3);
}