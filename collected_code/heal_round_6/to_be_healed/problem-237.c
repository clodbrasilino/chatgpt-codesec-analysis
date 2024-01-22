#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TUPLES 100
#define MAX_NAME 31

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
    int upper_bound = n > MAX_TUPLES ? MAX_TUPLES : n;

    for (int i = 0; i < upper_bound; i++) {
        count[i]++;
        for (int j = i + 1; j < upper_bound; j++) {
            if (strcmp(tuples[i].name, tuples[j].name) == 0) {
                count[i]++;
                count[j] = count[i];
            }
        }
    }

    for (int i = 0; i < upper_bound; i++) {
        tuples[i].occurrence = count[i];
    }
}

int main() {
    Tuple tuples[MAX_TUPLES];
    int n = 0;

    printf("Enter the number of tuples: ");
    
    if(scanf("%d", &n) != 1)
        return 1;

    if(n > MAX_TUPLES)
        n = MAX_TUPLES;

    printf("Enter the tuples:\n");
    
    for (int i = 0; i < n; i++) {
        printf("Tuple #%d:\n", i + 1);
        printf("Name: ");

        /* Possible weaknesses found:
         *   It's unclear if the %s limit in the format string is small enough  (CWE-120). Check that the limit is sufficiently small, or use a different  input function.
         */
        if(scanf("%30s", tuples[i].name) != 1)
            return 1;
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