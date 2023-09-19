#include <stdio.h>
#include <stdlib.h>
#include<get_user_info.h>
#include<main_menu.h>
#include<clear_screen.h>
extern yCoord;

void registr(char** Email, int** Level) {
    int choice, i;
    char mail[100];
    char name[100];
    char password[100];
    int highest_score = 0;
    int level;
    struct USER_INFO* user_info = NULL;
    user_info = get_users();
    if (user_info == NULL)
        return 1;

    int total_users = user_info->total_user;
    struct USER* user = user_info->user;

    printf("Enter email: ");
    scanf("%s", &mail);

    for (i = 0; i < total_users; i++)
    {
        // char* email = strtok(user[i].email, "\n");
        if (strcmp(user[i].email, mail) == 0)
        {
            printf("You are already registered! Please login");
            return 1;
        }
    }

    while (getchar() != '\n');
    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);

    do
    {
        //printf("====================================\n");
        printf("\nSelect Level\n");
        //printf("====================================\n");
        printf(" 1. Primary\n");
        printf(" 2. Secondary\n");
        printf(" 3. Higher Secondary\n\n");
        //printf("====================================\n");
        printf(" Enter your choice (1-3): ");
        //printf("====================================\n");
        // fflush(stdout);  // make sure the prompt is displayed before input is read
        if (scanf("%d", &choice) != 1)
        {
            clear_screen(&yCoord);
            printf("\x1b[31mInvalid choice. Please enter a number between 1 and 3\x1b[0m\n");
            // while (getchar() != '\n');  // clear input buffer
            // choice = -1;  // set invalid choice to continue loop
            fflush(stdin);
            continue;
        }
        switch (choice)
        {
        case 1:
            level = 1;
            break;
        case 2:
            level = 11;
            break;
        case 3:
            level = 21;
            break;
        default:
            clear_screen(&yCoord);
            printf("\x1b[31mInvalid choice. Please enter a number between 1 and 3\x1b[0m\n");
            break;
        }
    } while (choice < 1 || choice > 3);


    FILE* fp = fopen("D:\\C-C++\\Projects\\ThinkFast\\database\\user_info.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }
    fprintf(fp, "%s\n%s%s%d\n%d\n", mail, name, password, highest_score, level);
    // Flush file buffer to write data immediately
    fflush(fp);
    *Email = &mail;
    *Level = &level;
    clear_screen(&yCoord);
    main_menu();
}
