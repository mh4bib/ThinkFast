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

    initialize_random();

    // Loop for displaying questions
    for (int i = 0; i < total_questions; i++)
    {
        // Generate a random number between 1 and total_questions
        int random_question = get_random_number(total_questions);

        // Progress Bar
        printf("%d/%d [", i + 1, total_questions);
        for (int k = 0; k < i + 1; k++)
            printf("# ");
        for (int k = i + 1; k < total_questions + 1; k++)
            printf(". ");
        printf("]\t");

        printf("Remaining seconds: %.0f\n\n", time_limit - (get_current_time() - start_time));

        // Displaying question and options
        printf("%s", mcq[random_question].text);
        for (int j = 0; j < 4; j++)
        {
            printf("%s", mcq[random_question].options[j]);
        }


        // Taking user's choice
        scanf("\n%c", &user_answer[random_question]);

        //checking timer before accepting the answer
        if ((get_current_time() - start_time) > time_limit)
        {
            clear_screen();
            printf("Your time's up!\n");
            if (!isOnline)
            {
                printf("Press any key to continue...\n");
                getch();
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
                printf("Press any key to continue...\n");
                getch();
                break;
            }
        }

        user_answer[random_question] = toupper(user_answer[random_question]);

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



        //Sleep(300);
        clear_screen();
    }

    // displaying answer sheet
    printf("==============================================\n");
    printf("                     RESULT\n");
    printf("==============================================\n");
    printf("            You scored %d out of %d\n", score, total_questions);
    printf("==============================================\n");
    for (int i = 0; i < total_questions; i++)
    {
        printf("Q%d. %s", i + 1, mcq[i].text);
        if (mcq[i].correct_option == user_answer[i])
        {
            char* option = strtok(mcq[i].options[user_answer[i] - 65], "\n");
            printf("Your answer: \x1b[32m%s\x1b[0m (Correct)\n", option);
        }
        else
        {
            char* option = strtok(mcq[i].options[user_answer[i] - 65], "\n");
            printf("Your answer: \x1b[31m%s\x1b[0m (Incorrect)\n", option);
            printf("Correct answer: \x1b[33m%s\x1b[0m", mcq[i].options[mcq[i].correct_option - 65]);
        }
        printf("\n");
    }

    if (score > 6)
        update_level(mail, Level);
    else
        printf("\x1b[91mYou have to play this round again as you scored less than 7\x1b[0m\n");

    printf("Press any key to continue...\n");
    getch();
    clear_screen();

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
