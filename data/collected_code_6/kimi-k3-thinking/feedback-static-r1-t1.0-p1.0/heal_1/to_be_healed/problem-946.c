#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ELEMENT_RANGE 256

typedef struct {
    unsigned char element;
    size_t count;
} ElementCount;

int find_most_common(const char *text, ElementCount **results, size_t *result_count)
{
    size_t counts[ELEMENT_RANGE] = {0};
    size_t max_count = 0;
    size_t num_max = 0;
    size_t pos = 0;
    size_t i;

    if (text == NULL || results == NULL || result_count == NULL) {
        return -1;
    }

    *results = NULL;
    *result_count = 0;

    for (i = 0; text[i] != '\0'; i++) {
        counts[(unsigned char)text[i]]++;
    }

    for (i = 0; i < ELEMENT_RANGE; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
        }
    }

    if (max_count == 0) {
        return 0;
    }

    for (i = 0; i < ELEMENT_RANGE; i++) {
        if (counts[i] == max_count) {
            num_max++;
        }
    }

    *results = malloc(num_max * sizeof(**results));
    if (*results == NULL) {
        return -1;
    }

    for (i = 0; i < ELEMENT_RANGE; i++) {
        if (counts[i] == max_count) {
            (*results)[pos].element = (unsigned char)i;
            (*results)[pos].count = max_count;
            pos++;
        }
    }

    *result_count = num_max;
    return 0;
}

int main(int argc, char *argv[])
{
    const char *text = (argc > 1) ? argv[1] : "the quick brown fox jumps over the lazy dog";
    ElementCount *results = NULL;
    size_t result_count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (find_most_common(text, &results, &result_count) != 0) {
        fprintf(stderr, "Error: failed to process the text.\n");
        return EXIT_FAILURE;
    }

    if (result_count == 0) {
        printf("The text is empty.\n");
    } else {
        printf("Most common element(s) with count %zu:\n", results[0].count);
        for (i = 0; i < result_count; i++) {
            if (isprint((unsigned char)results[i].element)) {
                printf("  '%c' : %zu\n", results[i].element, results[i].count);
            } else {
                printf("  0x%02X : %zu\n", results[i].element, results[i].count);
            }
        }
    }

    free(results);
    results = NULL;

    return EXIT_SUCCESS;
}