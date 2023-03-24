#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct USER
{
    char email[100];
    char name[100];
    char password[100];
    int highest_score;
    int level;
};

struct USER_INFO
{
    int total_user;
    struct USER* user;
};

//read file
struct USER_INFO* get_users()
{
    FILE* fp = fopen("D:\\C-C++\\Projects\\ThinkFast\\database\\user_info.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }

    struct USER_INFO* user_info;
    user_info = malloc(sizeof(struct USER_INFO));
    user_info->total_user = 0;
    int count = 1;
    user_info->user = (struct USER*)malloc(count * sizeof(struct USER));

    while (fgets(user_info->user[user_info->total_user].email, 100, fp))
    {
        count++;
        user_info->user = realloc(user_info->user, count * sizeof(struct USER));


        fgets(user_info->user[user_info->total_user].name, 100, fp);
        fgets(user_info->user[user_info->total_user].password, 100, fp);
        fscanf(fp, "%d\n", &user_info->user[user_info->total_user].highest_score);
        fscanf(fp, "%d\n", &user_info->user[user_info->total_user].level);
        user_info->total_user++;
    }
    fclose(fp);
    return user_info;
}
