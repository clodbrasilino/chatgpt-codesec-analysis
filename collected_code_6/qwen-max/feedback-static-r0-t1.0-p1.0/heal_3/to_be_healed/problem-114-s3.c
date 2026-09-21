#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TUPLES 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char tuple[20];
    int frequency;
} Tuple;

int get_input(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin) == NULL) return 0;
    buffer[strcspn(buffer, "\n")] = 0;
    return 1;
}

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
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for number of tuples\n");
        return 1;
    }

    if (n <= 0 || n >= MAX_TUPLES) {
        fprintf(stderr, "Invalid number of tuples\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter tuple %d: ", i + 1);
        if (!get_input(tuples[i].tuple, sizeof(tuples[i].tuple))) {
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