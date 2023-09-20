#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <mcq_reader.h>
#include <random_number.h>
#include <get_current_time.h>
#include <update_level.h>
#include <update_score.h>
#include <clear_screen.h>
#include <custom_print.h>
#include <gotoxy.h>
#include <ansi_color_codes.h>

extern yCoord;

extern SOCKET client_socket;

struct MCQ
{
    char text[1024];
    char options[4][1024];
    char correct_option;
};

struct MCQ_QUESTIONS
{
    int total_question;
    struct MCQ* mcq;
};

// read mcq from file
struct MCQ_QUESTIONS* read_mcq(char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    struct MCQ_QUESTIONS* mcq_questions;
    mcq_questions = malloc(sizeof(struct MCQ_QUESTIONS));
    mcq_questions->total_question = 0;
    int count = 1;
    mcq_questions->mcq = (struct MCQ*)malloc(count * sizeof(struct MCQ));

    while (fgets(mcq_questions->mcq[mcq_questions->total_question].text, 1024, fp))
    {
        count++;
        mcq_questions->mcq = realloc(mcq_questions->mcq, count * sizeof(struct MCQ));
        for (int i = 0; i < 4; i++)
        {
            fgets(mcq_questions->mcq[mcq_questions->total_question].options[i], 1024, fp);
        }
        fscanf(fp, "%c\n", &mcq_questions->mcq[mcq_questions->total_question].correct_option);
        mcq_questions->total_question++;
    }
    fclose(fp);
    return mcq_questions;
}

// store mcq and display one by one
int display_mcq(char* filename, char* mail, int** Level, int isOnline, int time_limit)
{

    printCenter("+--------------------------------------+\n", &yCoord);
    printCenter("|                                      |\n", &yCoord);
    printCenter("|                                      |\n", &yCoord);
    gotoxy(20+5, yCoord-1);
    printf("You have %ds to finish the quiz", time_limit);
    printCenter("|       Time starts on key press       |\n", &yCoord);
    printCenter("|                                      |\n", &yCoord);
    printCenter("+--------------------------------------+\n", &yCoord);
    gotoxy(20, yCoord + 2);
    printf(HBLK"Press any key to start..."RESET);
    getch();
    clear_screen(&yCoord);

    char buffer[1024];
    double start_time = get_current_time();

    struct MCQ_QUESTIONS* mcq_questions = NULL;

    mcq_questions = read_mcq(filename);

    if (mcq_questions == NULL)
    {
        return 1;
    }

    int total_questions = mcq_questions->total_question;
    struct MCQ* mcq = mcq_questions->mcq;
    char user_answer[total_questions];
    int score = 0;

    for (int i = 0; i < total_questions; i++)
        user_answer[i] = NULL;


    initialize_random();

    // Loop for displaying questions
    for (int i = 0; i < total_questions; i++)
    {
        // Generate a random number between 1 and total_questions
        int random_question = get_random_number(total_questions);

        // Progress Bar
        gotoxy(2, 2);
        printf("%d/%d [", i + 1, total_questions);
        for (int k = 0; k < i + 1; k++)
            printf("# ");
        for (int k = i + 1; k < total_questions + 1; k++)
            printf(". ");
        printf("]                        ");

        printf("Remaining: %.0fs\n\n", time_limit - (get_current_time() - start_time));

        // Displaying question and options
        printSemiCenter("+------------------------------------------------------------------+", &yCoord);
        printSemiCenter("|                                                                  |", &yCoord);
        printSemiCenter("|                                                                  |", &yCoord);
        gotoxy(2 + 1, yCoord - 1);
        printf("%s", mcq[random_question].text);
        printSemiCenter("|                                                                  |", &yCoord);
        printSemiCenter("+------------------------------------------------------------------+\n", &yCoord);
        printSemiCenter("|                                                                  |", &yCoord);
        printSemiCenter("|                                                                  |", &yCoord);
        printSemiCenter("|                                                                  |", &yCoord);
        printSemiCenter("|                                                                  |", &yCoord);
        for (int j = 0; j < 4; j++)
        {
            gotoxy(2 + 1, yCoord - (4 - j));
            printf("%s", mcq[random_question].options[j]);
        }
        printSemiCenter("+------------------------------------------------------------------+", &yCoord);
        printSemiCenter("|Enter your choice (A-D):                                          |", &yCoord);
        printSemiCenter("+------------------------------------------------------------------+", &yCoord);
        gotoxy(2 + 26, yCoord - 2);
        // Taking user's choice
        scanf("\n%c", &user_answer[random_question]);

        //checking timer before accepting the answer
        if ((get_current_time() - start_time) > time_limit)
        {
            clear_screen(&yCoord);
            printCenter("+--------------------------------------+\n", &yCoord);
            printCenter("|                                      |\n", &yCoord);
            printCenter("|              "HRED"Time's up!"RESET"              |\n", &yCoord);
            printCenter("|                                      |\n", &yCoord);
            printCenter("+--------------------------------------+\n", &yCoord);
            if (!isOnline)
            {
                gotoxy(20, yCoord + 2);
                printf(HBLK"Press any key to continue..."RESET);
                getch();
                clear_screen(&yCoord);
                break;
            }
            else
            {
                // Send -1 to terminate receiving score
                sprintf(buffer, "%d", -1);
                if (send(client_socket, buffer, strlen(buffer), 0) == SOCKET_ERROR)
                {
                    perror("terminating code sending failed");
                    closesocket(client_socket);
                    return 1;
                }
                gotoxy(20, yCoord + 2);
                printf(HBLK"Press any key to continue..."RESET);
                getch();
                clear_screen(&yCoord);
                break;
            }
        }

        user_answer[random_question] = toupper(user_answer[random_question]);

        if (user_answer[random_question] == 'A' || user_answer[random_question] == 'B' || user_answer[random_question] == 'C' || user_answer[random_question] == 'D')
        {
            if (!isOnline)
            {
                // updating score
                if (user_answer[random_question] == mcq[random_question].correct_option)
                    score++;
            }
            else
            {
                // updating score
                if (user_answer[random_question] == mcq[random_question].correct_option)
                    score++;

                // Send updated score to the server
                sprintf(buffer, "%d", score);
                if (send(client_socket, buffer, strlen(buffer), 0) == SOCKET_ERROR)
                {
                    perror("uScore sending failed");
                    closesocket(client_socket);
                    return 1;
                }
            }
        }
        else
        {
            user_answer[random_question] = NULL;
        }

        //Sleep(300);
        clear_screen(&yCoord);
    }

    // displaying answer sheet
    printSemiCenter("+------------------------------------------------------------------+", &yCoord);
    printSemiCenter("|                                                                  |", &yCoord);
    printSemiCenter("|                                                                  |", &yCoord);
    gotoxy(2 + 22, yCoord - 1);
    printf("YOU SCORED %-2d OUT OF %-2d\n", score, total_questions);
    printSemiCenter("|                                                                  |", &yCoord);
    printSemiCenter("+------------------------------------------------------------------+", &yCoord);
    for (int i = 0; i < total_questions; i++)
    {

        printSemiCenter("|                                                                  |", &yCoord);
        printSemiCenter("|                                                                  |", &yCoord);
        // printSemiCenter("+------------------------------------------------------------------+", &yCoord);
        gotoxy(2 + 1, yCoord - 2);
        printf("Q%d. %s", i + 1, mcq[i].text);
        if (mcq[i].correct_option == user_answer[i])
        {
            printSemiCenter("|                                                                  |", &yCoord);
            gotoxy(2 + 1, yCoord - 1);
            char* option = strtok(mcq[i].options[user_answer[i] - 65], "\n");
            printf("Your answer:" HGRN"%s"RESET" (Correct)", option);
        }
        else
        {
            if (user_answer[i] == NULL)
            {
                printSemiCenter("|                                                                  |", &yCoord);
                gotoxy(2 + 1, yCoord - 1);
                printf(HRED "Not Attempted" RESET);
            }
            else
            {
                printSemiCenter("|                                                                  |", &yCoord);
                gotoxy(2 + 1, yCoord - 1);
                char* option = strtok(mcq[i].options[user_answer[i] - 65], "\n");
                printf("Your answer:" HRED "%s" RESET "(Incorrect)", option);
            }
            printSemiCenter("|                                                                  |", &yCoord);
            gotoxy(2 + 1, yCoord - 1);
            printf("Correct answer:" HCYN "%s" RESET, mcq[i].options[mcq[i].correct_option - 65]);

        }
        printSemiCenter("+------------------------------------------------------------------+", &yCoord);
    }

    if (score > 6)
        update_level(mail, Level);
    else
    {
        printSemiCenter("|                                                                  |", &yCoord);
        gotoxy(2 + 1, yCoord - 1);
        printf(HYEL "You have to play this round again as your score < 7" RESET);
        printSemiCenter("+------------------------------------------------------------------+", &yCoord);
    }

    gotoxy(2, yCoord + 2);
    printf(HBLK"Press any key to continue..."RESET);
    getch();
    clear_screen(&yCoord);

    if (!isOnline)
    {
        main_menu();
        // return 0;
    }
    else
    {
        update_score(mail, score);
        return score;
    }
}
