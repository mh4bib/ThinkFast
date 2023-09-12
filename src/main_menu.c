#include <stdio.h>
#include <clear_screen.h>
#include<login.h>
#include<register.h>
#include <playgame_submenu.h>
#include <client.h>
#include <leader_board.h>
#include<get_user_info.h>

char* Email = NULL;
int Level = NULL;

void main_menu()
{
    struct USER_INFO* user_info = NULL;
    user_info = get_users();
    if (user_info == NULL)
        return 1;
    int total_users = user_info->total_user;
    struct USER* user = user_info->user;

    int choice;
    do
    {
        printf("====================================\n");
        printf("|               Home               |\n");
        printf("====================================\n");
        printf("| 1. Play Game                     |\n");
        printf("| 2. Analytics                     |\n");
        printf("| 3. Login/Register                |\n");
        printf("| 4. Attend Online                 |\n");
        printf("| 5. Exit                          |\n");
        printf("====================================\n");
        printf("| Enter your choice (1-4):         |\n");
        printf("====================================\n");
        // fflush(stdout);  // make sure the prompt is displayed before input is read
        if (scanf("%d", &choice) != 1)
        {
            clear_screen();
            printf("\x1b[31mInvalid choice. Please enter a number between 1 and 4.\x1b[0m\n");
            // while (getchar() != '\n');  // clear input buffer
            // choice = -1;  // set invalid choice to continue loop
            fflush(stdin);
            continue;
        }
        switch (choice)
        {
        case 1:
            clear_screen();
            playgame_submenu(&Email, &Level);
            break;
        case 2:
            leader_board();
            break;
        case 3:
            clear_screen();
            login_prompt(&Email, &Level);
            break;
        case 4:
            clear_screen();
            // test(&Email, &Level);
            client(&Email, &Level);
            break;
        case 5:
            exit(0);
            // return 0;
            break;
        default:
            clear_screen();
            printf("\x1b[31mInvalid choice. Please enter a number between 1 and 4\x1b[0m\n");
            break;
        }
    } while (choice < 1 || choice > 4);

}
