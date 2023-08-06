#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to store email and total score
struct Entry {
    char email[100];
    int score;
};

// Custom function to compare two entries for sorting
int compare(const void* a, const void* b) {
    return ((struct Entry*)a)->score - ((struct Entry*)b)->score;
}

int leader_board() {
    // Assuming the file is named "data.txt"
    FILE* file = fopen("D:\\C-C++\\Projects\\ThinkFast\\database\\client_scores.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Assuming a maximum of 100 entries in the file
    struct Entry entries[100];
    int count = 0;

    // Read the file and store entries in the array
    char line[200]; // Assuming each line is less than 200 characters
    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse the email and score from each line
        char email[100];
        int score;
        sscanf(line, "Email: %99[^,], Total Score: %d", email, &score);

        // Store the email and score in the array
        strcpy(entries[count].email, email);
        entries[count].score = score;

        count++;
    }

    // Close the file after reading
    fclose(file);

    // Sort the entries in ascending order of score
    qsort(entries, count, sizeof(struct Entry), compare);

    // Display the sorted entries in the console
    printf("Sorted Entries (Ascending Order of Score):\n");
    for (int i = 0; i < count; i++) {
        printf("Email: %s, Total Score: %d\n", entries[i].email, entries[i].score);
    }

    return 0;
}
