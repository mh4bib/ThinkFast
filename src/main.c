#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <mcq_reader.h>

int visited[101];
int is_duplicate(int num)
{
    if (!visited[num])
        return 0;
    else
        return 1;
}

int main()
{
    struct MCQ_QUESTIONS *mcq_questions = NULL;
    char user_answer;

    mcq_questions = read_mcq("D:\\C-C++\\Projects\\ThinkFast\\database\\question_bank\\primary\\question_bank.txt");

    if (mcq_questions == NULL) {
        return 1;
    }

    int total_questions = mcq_questions->total_question;
    struct MCQ *mcq = mcq_questions->mcq;
    
    srand(time(NULL));

    // Loop for displaying questions
    for (int i = 0; i < total_questions; i++)
    {
        // Generate a random number between 1 and total_questions
        int random_question = rand() % total_questions + 1;

        // checking if the number is unique or not
        if (is_duplicate(random_question))
        {
            i--;
            continue;
        }
        else
            visited[random_question] = 1;

        // making random_question 0 base
        random_question--;

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
    }

    return 0;
}
