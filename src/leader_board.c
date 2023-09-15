#include <stdio.h>
#include<get_user_info.h>
#include<main_menu.h>
#include<clear_screen.h>

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

    printf("Rank        User Name      Score       \n");
    printf("----        ---------      -----       \n");
    for (int i = 0; i < total_users; i++)
    {
        printf("%-10d  %-13s  %-8d\n", i + 1, user[i].name, user[i].highest_score);
    }

    printf("\n\nPress any key to continue...\n");
    getch();

    clear_screen();
    main_menu();
}
