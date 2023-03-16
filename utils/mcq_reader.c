#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <mcq_reader.h>
#include <random_number.h>
#include <clear_screen.h>

struct MCQ
{
    char text[100];
    char options[4][50];
    char correct_option;
};

struct MCQ_QUESTIONS
{
    int total_question;
    struct MCQ *mcq;
};

//read mcq from file
struct MCQ_QUESTIONS *read_file(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    struct MCQ_QUESTIONS *mcq_questions;
    mcq_questions = malloc(sizeof(struct MCQ_QUESTIONS));
    mcq_questions->total_question = 0;
    int count = 1;
    mcq_questions->mcq = (struct MCQ *)malloc(count * sizeof(struct MCQ));

    while (fgets(mcq_questions->mcq[mcq_questions->total_question].text, 100, fp))
    {
        count++;
        mcq_questions->mcq = realloc(mcq_questions->mcq, count * sizeof(struct MCQ));
        for (int i = 0; i < 4; i++)
        {
            fgets(mcq_questions->mcq[mcq_questions->total_question].options[i], 50, fp);
        }
        fscanf(fp, "%c\n", &mcq_questions->mcq[mcq_questions->total_question].correct_option);
        mcq_questions->total_question++;
    }
    fclose(fp);
    return mcq_questions;
}

//store mcq and display one by one
void display_mcq(char *filename)
{
    struct MCQ_QUESTIONS *mcq_questions = NULL;
    char user_answer;

    mcq_questions = read_file(filename);

    if (mcq_questions == NULL)
    {
        return 1;
    }

    int total_questions = mcq_questions->total_question;
    struct MCQ *mcq = mcq_questions->mcq;

    initialize_random();

    // Loop for displaying questions
    for (int i = 0; i < total_questions; i++)
    {
        // Generate a random number between 1 and total_questions
        int random_question = get_random_number(total_questions);

        //Progress Bar
        printf("%d/%d [", i+1, total_questions);
        for(int k=0; k<i+1; k++) printf("# ");
        for(int k=i+1; k<total_questions+1; k++) printf(". ");
        printf("]\n\n");

        // Displaying question and options
        printf("%d. %s", i + 1, mcq[random_question].text);
        for (int j = 0; j < 4; j++)
        {
            printf("%s", mcq[random_question].options[j]);
        }

        // Taking user's choice
        scanf("\n%c", &user_answer);
        user_answer = toupper(user_answer);

        // Checking user's answer
        if (user_answer == mcq[random_question].correct_option)
        {
            printf("Correct!\n\n");
        }
        else
        {
            printf("Incorrect. The correct answer is %c.\n\n", mcq[random_question].correct_option);
        }
        Sleep(500);
        clear_screen();
    }
}