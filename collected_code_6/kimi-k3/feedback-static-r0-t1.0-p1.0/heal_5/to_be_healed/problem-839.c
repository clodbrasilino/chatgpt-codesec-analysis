#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 50

typedef struct {
    char *first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    return strcmp(tuple_a->first, tuple_b->first);
}

void sort_tuples(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

void free_tuples(Tuple *tuples, size_t count) {
    size_t i;
    if (tuples == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(tuples[i].first);
    }
}

int main(void) {
    Tuple tuples[] = {
        {NULL, 2},
        {NULL, 1},
        {NULL, 3},
        {NULL, 4}
    };
    const char *strings[] = {"banana", "apple", "cherry", "date"};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;

    for (i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(strings[i]);
        tuples[i].first = (char *)malloc(len + 1);
        if (tuples[i].first == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_tuples(tuples, i);
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(tuples[i].first, strings[i]);
    }

    printf("Original tuples:\n");
    for (i = 0; i < count; i++) {
        printf("(%s, %d)\n", tuples[i].first, tuples[i].second);
    }

    sort_tuples(tuples, count);

    printf("\nSorted tuples:\n");
    for (i = 0; i < count; i++) {
        printf("(%s, %d)\n", tuples[i].first, tuples[i].second);
    }

    free_tuples(tuples, count);

    return EXIT_SUCCESS;
}