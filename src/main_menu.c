#include <stdio.h>
#include <clear_screen.h>
#include <playgame_submenu.h>

void main_menu()
{
    int choice;
    do
    {
        printf("====================================\n");
        printf("|               Home               |\n");
        printf("====================================\n");
        printf("| 1. Play Game                     |\n");
        printf("| 2. Analytics                     |\n");
        printf("| 3. Login/Register                |\n");
        printf("| 4. Exit                          |\n");
        printf("====================================\n");
        printf("| Enter your choice (1-4):         |\n");
        printf("====================================\n");
        // fflush(stdout);  // make sure the prompt is displayed before input is read
        if(scanf("%d", &choice)!=1)
        {
            clear_screen();
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
            // while (getchar() != '\n');  // clear input buffer
            // choice = -1;  // set invalid choice to continue loop
            fflush(stdin);
            continue;
        }
        switch (choice)
        {
        case 1:
            clear_screen();
            playgame_submenu();
            break;
        case 2:
            // code to add questions
            break;
        case 3:
            // code to display high scores
            break;
        case 4:
            // code to exit program
            break;
        default:
            clear_screen();
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
            break;
        }
    } while (choice < 1 || choice > 4);
}
