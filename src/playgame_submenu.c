#include <stdio.h>
#include <clear_screen.h>
#include <main_menu.h>
#include <mcq_reader.h>

extern yCoord;

void playgame_submenu(char** mail, int** level)
{
    if (*mail == NULL)
    {
        // clear_screen(&yCoord);
        gotoxy(20, 2);
        printf("\x1b[31mLogin first to play...\x1b[0m\n");
        login_prompt(mail, level);
    }

    char filename[100];
    if (**level > 20)
        sprintf(filename, "database\\question_bank\\higher_secondary\\higher_secondary_level_%d.txt", **level);
    else if (**level > 10)
        sprintf(filename, "database\\question_bank\\secondary\\secondary_level_%d.txt", **level);
    else
        sprintf(filename, "database\\question_bank\\primary\\primary_level_%d.txt", **level);

    display_mcq(filename, *mail, level, 0, 20);

}