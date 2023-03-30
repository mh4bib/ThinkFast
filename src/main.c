#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <clear_screen.h>
#include <main_menu.h>
#include<login.h>
#include<register.h>
#include<update_level.h>

int main()
{
  printf(" _________ __       _          __      ________            _    \n");
  printf("|  _   _  [  |     (_)        [  |  _ |_   __  |          / |_  \n");
  printf("|_/ | | \\_|| |--.  __  _ .--.  | | / ]  | |_ \\_,--.  .--.`| |-' \n");
  printf("    | |    | .-. |[  |[ `.-. | | '' <   |  _| `'_\\ :( (`\\]| |   \n");
  printf("   _| |_   | | | | | | | | | | | |`\\ \\ _| |_  // | |,`'.'.| |,  \n");
  printf("  |_____| [___]|__[___[___||__[__|  \\_|_____| \\\'-;__[\\__) \\__/  \n");

  Sleep(1000);
  clear_screen();
  main_menu();
  // login();
  //registr();

  //update_level("mymail@nomail.com");

  return 0;
}
