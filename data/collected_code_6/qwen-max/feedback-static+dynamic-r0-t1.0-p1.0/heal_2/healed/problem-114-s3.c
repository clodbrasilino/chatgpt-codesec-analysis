#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TUPLES 100

typedef struct {
    char tuple[20];
    int frequency;
} Tuple;

void assign_frequency(Tuple *tuple_list, int n) {
    for (int i = 0; i < n; i++) {
        tuple_list[i].frequency = 1;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(tuple_list[i].tuple, tuple_list[j].tuple) == 0) {
                tuple_list[i].frequency++;
                tuple_list[j].frequency = -1;
            }
        }
    }
}

int main() {
    Tuple tuples[MAX_TUPLES] = {0};
    char input[20];
    int n;

    printf("Enter the number of tuples: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX_TUPLES) {
        fprintf(stderr, "Invalid number of tuples\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter tuple %d: ", i + 1);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = 0; // Remove newline character
            if (strlen(input) < sizeof(tuples[i].tuple)) {
                strcpy(tuples[i].tuple, input);
            } else {
                fprintf(stderr, "Tuple too long, try again: \n");
                i--;
            }
        } else {
            fprintf(stderr, "Invalid input for tuple\n");
            return 1;
        }
    }

    assign_frequency(tuples, n);

    for (int i = 0; i < n; i++) {
        if (tuples[i].frequency > 0) {
            printf("Tuple: %s, Frequency: %d\n", tuples[i].tuple, tuples[i].frequency);
        }
    }

    return 0;
}