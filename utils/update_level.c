#include<stdio.h>
#include<get_user_info.h>

void update_level(char mail[], int** Level)
{
    int i;
    struct USER_INFO* user_info = NULL;
    user_info = get_users();
    if (user_info == NULL)
        return 1;

    int total_users = user_info->total_user;
    struct USER* user = user_info->user;

    for (i = 0; i < total_users; i++)
    {
        //char* email = strtok(user[i].email, "\n");
        if (strcmp(user[i].email, mail) == 0)
            break;
    }
    (user + i)->level += 1;

    // update locally
    **Level += 1;

    FILE* fp = fopen("D:\\C-C++\\Projects\\ThinkFast\\database\\user_info.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    for (int i = 0; i < total_users; i++)
    {
        fprintf(fp, "%s\n%s\n%s\n%d\n%d\n",
            user[i].email,
            user[i].name,
            user[i].password,
            user[i].highest_score,
            user[i].level);
    }
    fclose(fp);
}