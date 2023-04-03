#ifndef RANDOM_NUMBER_H
#define RANDOM_NUMBER_H

int visited[101];
int is_duplicate(int num)
{
    if (!visited[num])
        return 0;
    else
        return 1;
}

void initialize_random();

int get_random_number(int max);

#endif // RANDOM_NUMBER_H
