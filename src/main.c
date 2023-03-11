#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int visited[101];
int is_duplicate(int num){
    if(!visited[num])
        return 0;
    else
        return 1;
}

struct Question {
    char text[100];
    char options[4][50];
    char correct_option;
};

int main() {
    struct Question questions[101];
    int total_questions = 0;
    char user_answer;

    // Opening file and read the questions and options
    FILE *fp = fopen("database\\question_bank\\primary\\question_bank.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    while (fgets(questions[total_questions].text, 100, fp)) {
        for (int i = 0; i < 4; i++) {
            fgets(questions[total_questions].options[i], 50, fp);
        }
        fscanf(fp, "%c\n", &questions[total_questions].correct_option);
        total_questions++;
    }
    fclose(fp);

    srand(time(NULL));

    // Loop for displaying questions
    for (int i = 0; i < total_questions; i++) {
        // Generate a random number between 1 and total_questions
        int random_question = rand() % total_questions + 1;

        //checking if the number is unique or not
        if(is_duplicate(random_question)){
            i--;
            continue;
        }
        else
            visited[random_question]=1;

        //making random_question 0 base
        random_question--;

        // Displaying question and options
        printf("%d. %s",i+1, questions[random_question].text);
        for (int j = 0; j < 4; j++) {
            printf("%s", questions[random_question].options[j]);
        }

        //Taking user's choice
        scanf("\n%c", &user_answer);
        user_answer=toupper(user_answer);

        // Checking user's answer
        if (user_answer == questions[random_question].correct_option) {
            printf("Correct!\n\n");
        } else {
            printf("Incorrect. The correct answer is %c.\n\n", questions[random_question].correct_option);
        }
    }

    return 0;
}
