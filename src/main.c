//build command: gcc -o main.exe src/*.c utils/*.c -I include/ -lws2_32
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <clear_screen.h>
#include <main_menu.h>
#include<login.h>
#include<register.h>
#include<update_level.h>
extern yCoord;

int main()
{
  printf(" _________ __       _          __      ________            _    \n");
  printf("|  _   _  [  |     (_)        [  |  _ |_   __  |          / |_  \n");
  printf("|_/ | | \\_|| |--.  __  _ .--.  | | / ]  | |_ \\_,--.  .--.`| |-' \n");
  printf("    | |    | .-. |[  |[ `.-. | | '' <   |  _| `'_\\ :( (`\\]| |   \n");
  printf("   _| |_   | | | | | | | | | | | |`\\ \\ _| |_  // | |,`'.'.| |,  \n");
  printf("  |_____| [___]|__[___[___||__[__|  \\_|_____| \\\'-;__[\\__) \\__/  \n");

  printf("\n\nPress any key to continue...\n");
  getch();
  clear_screen(&yCoord);
  main_menu();

  return 0;
}
