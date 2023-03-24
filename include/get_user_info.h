#ifndef GET_USER_INFO
#define GET_USER_INFO

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

struct USER_INFO* get_users();

#endif // GET_USER_INFO
