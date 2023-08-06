#include<stdio.h>
#include<get_user_info.h>

void update_score(char mail[], int new_score)
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
    (user + i)->highest_score = new_score;

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
    // Flush file buffer to write data immediately
    fflush(fp);
    fclose(fp);
}