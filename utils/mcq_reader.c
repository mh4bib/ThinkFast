#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <mcq_reader.h>

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

struct MCQ_QUESTIONS *read_mcq(char *filename)
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
        mcq_questions->mcq = realloc(mcq_questions->mcq, count* sizeof(struct MCQ));
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