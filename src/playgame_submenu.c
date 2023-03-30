#include <stdio.h>
#include <clear_screen.h>
#include <main_menu.h>

void playgame_submenu(char** mail, int** level)
{
    if (*mail == NULL)
    {
        printf("You're not logged in.Please login/register first\n");
        login_prompt(mail, level);
    }

    switch (**level)
    {
    case 1:
        clear_screen();
        display_mcq("D:\\C-C++\\Projects\\ThinkFast\\database\\question_bank\\primary\\primary_easy_10.txt", *mail);
        break;

    default:
        clear_screen();
        main_menu();
        break;
    }
}