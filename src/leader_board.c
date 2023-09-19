#include <stdio.h>
#include<get_user_info.h>
#include<main_menu.h>
#include<clear_screen.h>
#include<custom_print.h>
#include<gotoxy.h>

extern yCoord;

void sort(struct USER *user, int size) {
    for (int step = 0; step < size - 1; ++step) {

        int swapped = 0;

        for (int i = 0; i < size - step - 1; ++i) {

            if (user[i].highest_score < user[i + 1].highest_score) {

                struct USER temp = user[i];
                user[i] = user[i + 1];
                user[i + 1] = temp;

                swapped = 1;
            }
        }

        if (swapped == 0) {
            break;
        }

    }
}

int leader_board() {
    struct USER_INFO* user_info = NULL;

    user_info = get_users();
    if (user_info == NULL)
        return 1;

    int total_users = user_info->total_user;
    struct USER* user = user_info->user;

    sort(user, total_users);

    printCenter("+--------------------------------------+\n", &yCoord);
    printCenter("|             Leader Board             |\n", &yCoord);
    printCenter("+-----------+--------------+-----------|\n", &yCoord);
    printCenter("|    Rank   |  User Name   |   Score   |\n", &yCoord);
    printCenter("+-----------+--------------+-----------+\n", &yCoord);
    for (int i = 0; i < total_users; i++)
    {
        gotoxy(20, yCoord);
        printf("|%-10d |%-13s |%-11d|\n", i + 1, user[i].name, user[i].highest_score);
        yCoord++;
    }
    printCenter("+-----------+--------------+-----------+\n", &yCoord);

    gotoxy(20, yCoord+2);
    printf("Press any key to continue...\n");
    gotoxy(20+28, yCoord+2);
    getch();

    clear_screen(&yCoord);
    main_menu();
}
