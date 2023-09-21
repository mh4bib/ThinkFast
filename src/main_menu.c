#include <stdio.h>
#include <clear_screen.h>
#include<login.h>
#include<register.h>
#include <playgame_submenu.h>
#include <client.h>
#include <leader_board.h>
#include<get_user_info.h>
#include<gotoxy.h>
#include<ansi_color_codes.h>

char* Email = NULL;
int Level = NULL;
// int yCoord=3;
extern yCoord;

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
        printCenter("+----------------------------------+\n",&yCoord);
        printCenter("|               "UWHT"HOME"RESET"               |\n", &yCoord);
        printCenter("+----------------------------------+\n",&yCoord);
        printCenter("| 1. Play Game                     |\n",&yCoord);
        printCenter("| 2. Analytics                     |\n",&yCoord);
        if(Email==NULL)
            printCenter("| 3. Login/Register                |\n",&yCoord);
        else
            printCenter("| 3. Logout                        |\n",&yCoord);
        printCenter("| 4. Attend Online                 |\n",&yCoord);
        printCenter("| 5. Exit                          |\n",&yCoord);
        printCenter("+----------------------------------+\n",&yCoord);
        printCenter("| Enter your choice (1-5):         |\n",&yCoord);
        printCenter("+----------------------------------+\n",&yCoord);
        // fflush(stdout);  // make sure the prompt is displayed before input is read
        gotoxy(20+27, yCoord-2);
        if (scanf("%d", &choice) != 1)
        {
            clear_screen(&yCoord);
            gotoxy(20, 2);
            printf(BRED"Invalid choice"RESET);
            // while (getchar() != '\n');  // clear input buffer
            // choice = -1;  // set invalid choice to continue loop
            fflush(stdin);
            continue;
        }
        switch (choice)
        {
        case 1:
            clear_screen(&yCoord);
            playgame_submenu(&Email, &Level);
            break;
        case 2:
            clear_screen(&yCoord);
            leader_board();
            break;
        case 3:
        if(Email==NULL)
        {
            clear_screen(&yCoord);
            login_prompt(&Email, &Level);
            break;
        }
        else
        {
            Email=NULL;
            Level=NULL;
            clear_screen(&yCoord);
            main_menu();
            break;
        }
        case 4:
            clear_screen(&yCoord);
            // test(&Email, &Level);
            client(&Email, &Level);
            break;
        case 5:
            exit(0);
            // return 0;
            break;
        default:
            clear_screen(&yCoord);
            gotoxy(20, 2);
            printf(BRED"Invalid choice"RESET);
            break;
        }
    } while (choice < 1 || choice > 4);

}
