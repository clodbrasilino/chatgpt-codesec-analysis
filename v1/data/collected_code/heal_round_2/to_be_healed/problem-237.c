#include <stdio.h>
#include <string.h>

#define MAX_TUPLES 100
#define MAX_NAME 30

typedef struct {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char name[MAX_NAME];
    int occurrence;
} Tuple;

void countOccurrence(Tuple tuples[], int n) {
    int count[MAX_TUPLES];
    memset(count, 0, sizeof(count));

    for (int i = 0; i < n; i++) {
        count[i]++;

        for (int j = i + 1; j < n; j++) {
            if (strcmp(tuples[i].name, tuples[j].name) == 0) {
                count[i]++;
                count[j]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        tuples[i].occurrence = count[i];
    }
}

int main() {
    Tuple tuples[MAX_TUPLES];
    int n = 0;

    printf("Enter the number of tuples: ");
    scanf("%d", &n);

    printf("Enter the tuples:\n");
    for (int i = 0; i < n; i++) {
        printf("Tuple #%d:\n", i + 1);
        printf("Name: ");
        /* Possible weaknesses found:
         *   It's unclear if the %s limit in the format string is small enough  (CWE-120). Check that the limit is sufficiently small, or use a different  input function.
         */
        scanf("%29s", tuples[i].name);
    }

    countOccurrence(tuples, n);

    printf("Occurrences of tuples:\n");
    for (int i = 0; i < n; i++) {
        printf("Tuple #%d:\n", i + 1);
        printf("Name: %s\n", tuples[i].name);
        printf("Occurrences: %d\n", tuples[i].occurrence);
        printf("\n");
    }

    return 0;
}
