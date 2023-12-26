#include <stdio.h>
#include <string.h>

#define MAX_TUPLES 100

typedef struct {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char name[30];
    int occurrence;
} Tuple;

void countOccurrence(Tuple tuples[], int n) {
    int count[MAX_TUPLES];
    /* Possible weaknesses found:
     *  Cannot determine that 'count[0]' is initialized [premium-bughuntingUninit]
     */
    memset(count, 0, sizeof(count));

    for (int i = 0; i < n; i++) {
        count[i]++;

        for (int j = i + 1; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuples[i].name[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
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
    int n;

    printf("Enter the number of tuples: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);

    printf("Enter the tuples:\n");
    for (int i = 0; i < n; i++) {
        printf("Tuple #%d:\n", i + 1);
        printf("Name: ");
        /* Possible weaknesses found:
         *  Cannot determine that 'tuples[i] members' is initialized [premium-bughuntingUninit]
         *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
         */
        scanf("%s", tuples[i].name);
    }

    countOccurrence(tuples, n);

    printf("Occurrences of tuples:\n");
    for (int i = 0; i < n; i++) {
        printf("Tuple #%d:\n", i + 1);
        /* Possible weaknesses found:
         *  Cannot determine that 'tuples[i] members' is initialized [premium-bughuntingUninit]
         */
        printf("Name: %s\n", tuples[i].name);
        /* Possible weaknesses found:
         *  Cannot determine that 'tuples[i] members' is initialized [premium-bughuntingUninit]
         */
        printf("Occurrences: %d\n", tuples[i].occurrence);
        printf("\n");
    }

    return 0;
}