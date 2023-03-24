#include<stdio.h>
#include<get_user_info.h>

int login() {
  struct USER_INFO* user_info = NULL;
  char mail[100], pass[100];
  int is_valid = 0, i;

  user_info = get_users();
  if (user_info == NULL)
    return 1;

  int total_users = user_info->total_user;
  struct USER* user = user_info->user;

  printf("Enter Email: ");
  scanf("%s", &mail);

  for (i = 0; i < total_users; i++)
  {
    char* email = strtok(user[i].email, "\n");
    if (strcmp(email, mail) == 0)
    {
      is_valid = 1;
      break;
    }
  }

  if (!is_valid)
  {
    printf("You are not registered!\n");
    return 1;
  }

  printf("Enter Password: ");
  scanf("%s", &pass);
  char* password = strtok(user[i].password, "\n");
  if (strcmp(password, pass) != 0)
  {
    printf("Incorrect password\n");
    return 1;
  }
  printf("YOU ARE LOGGED IN\n");

  return 0;
}