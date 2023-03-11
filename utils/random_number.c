#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int visited[1001];

/* int is_duplicate(int num)
{
    if (!visited[num])
        return 0;
    else
        return 1;
} */


void initialize_random() {
    srand(time(NULL));
}


int get_random_number(int max) {
    // Generate a random number between 1 and total_questions
        int random_number = rand() % max + 1;

        // checking if the number is unique or not
        if (is_duplicate(random_number))
        {
            get_random_number(max);
        }
        else
        {
            visited[random_number] = 1;
            //return 0 based random_number
            return random_number-1;
        }
}
