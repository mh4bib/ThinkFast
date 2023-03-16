#include <stdio.h>
#include <clear_screen.h>
#include <main_menu.h>

void playgame_submenu()
{
    int choice;
    do
    {
    printf("====================================\n");
    printf("|           Select Level           |\n");
    printf("====================================\n");
    printf("| 1. Primary                       |\n");
    printf("| 2. Secondary                     |\n");
    printf("| 3. Higher Secondary              |\n");
    printf("| 4. go back to home               |\n");
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
        display_mcq("D:\\C-C++\\Projects\\ThinkFast\\database\\question_bank\\primary\\question_bank.txt");
        break;
    case 2:
        // code to add questions
        break;
    case 3:
        // code to display high scores
        break;
    case 4:
        clear_screen();
        main_menu();
        break;
    default:
        clear_screen();
        printf("Invalid choice. Please enter a number between 1 and 4.\n");
        break;
    }
    } while (choice < 1 || choice > 4);
}