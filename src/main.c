//build command: gcc -o main.exe src/*.c utils/*.c -I include/ -lws2_32
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <clear_screen.h>
#include <main_menu.h>
#include<login.h>
#include<register.h>
#include<update_level.h>
#include<custom_print.h>
#include<gotoxy.h>

extern yCoord;

int main()
{
  printCenter("$$$$$$$$\\ $$\\       $$\\           $$\\             $$$$$$$$\\                   $$\\     \n", &yCoord);
  printCenter("\\__$$  __|$$ |      \\__|          $$ |            $$  _____|                  $$ |    \n", &yCoord);
  printCenter("   $$ |   $$$$$$$\\  $$\\ $$$$$$$\\  $$ |  $$\\       $$ |   $$$$$$\\   $$$$$$$\\ $$$$$$\\   \n", &yCoord);
  printCenter("   $$ |   $$  __$$\\ $$ |$$  __$$\\ $$ | $$  |      $$$$$\\ \\____$$\\ $$  _____|\\_$$  _|  \n", &yCoord);
  printCenter("   $$ |   $$ |  $$ |$$ |$$ |  $$ |$$$$$$  /       $$  __|$$$$$$$ |\\$$$$$$\\    $$ |    \n", &yCoord);
  printCenter("   $$ |   $$ |  $$ |$$ |$$ |  $$ |$$  _$$<        $$ |  $$  __$$ | \\____$$\\   $$ |$$\\ \n", &yCoord);
  printCenter("   $$ |   $$ |  $$ |$$ |$$ |  $$ |$$ | \\$$\\       $$ |  \\$$$$$$$ |$$$$$$$  |  \\$$$$  |\n", &yCoord);
  printCenter("   \\__|   \\__|  \\__|\\__|\\__|  \\__|\\__|  \\__|      \\__|   \\_______|\\_______/    \\____/ \n", &yCoord);

  gotoxy(20, yCoord + 2);
  printf("Press any key to continue...");
  getch();
  clear_screen(&yCoord);
  main_menu();
  return 0;
}
