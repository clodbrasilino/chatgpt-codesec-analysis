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
    int n;

    printf("Enter the number of tuples: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX_TUPLES) {
        fprintf(stderr, "Invalid number of tuples\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter tuple %d: ", i + 1);
        scanf("%s", tuples[i].tuple);
    }

    assign_frequency(tuples, n);

    for (int i = 0; i < n; i++) {
        if (tuples[i].frequency > 0) {
            printf("Tuple: %s, Frequency: %d\n", tuples[i].tuple, tuples[i].frequency);
        }
    }

    return 0;
}