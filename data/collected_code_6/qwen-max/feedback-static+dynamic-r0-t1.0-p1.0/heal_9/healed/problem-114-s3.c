#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TUPLES 100
#define TUPLE_SIZE 20

typedef struct {
    char tuple[TUPLE_SIZE];
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
    int n;

    printf("Enter the number of tuples: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX_TUPLES) {
        fprintf(stderr, "Invalid number of tuples\n");
        return 1;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    for (int i = 0; i < n; i++) {
        printf("Enter tuple %d: ", i + 1);
        if (fgets(tuples[i].tuple, sizeof(tuples[i].tuple), stdin) != NULL) {
            size_t len = strcspn(tuples[i].tuple, "\n");
            if (len >= sizeof(tuples[i].tuple) - 1) {
                tuples[i].tuple[sizeof(tuples[i].tuple) - 1] = '\0';
                fprintf(stderr, "Tuple too long, try again:\n");
                while ((c = getchar()) != '\n' && c != EOF);
                i--;
            } else {
                tuples[i].tuple[len] = '\0';
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