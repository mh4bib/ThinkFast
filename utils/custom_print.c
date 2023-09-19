int yCoord = 3;
void printCenter(const char ch[], int *y)
{
    gotoxy(20, *y);
    printf("%s", ch);
    (*y)++;
}

void printSemiCenter(const char ch[], int *y)
{
    gotoxy(2, *y);
    printf("%s", ch);
    (*y)++;
}