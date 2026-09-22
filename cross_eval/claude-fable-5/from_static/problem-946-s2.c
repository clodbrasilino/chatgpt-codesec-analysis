#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char element;
    size_t count;
} ElementCount;

int find_most_common(const char *text, ElementCount **results, size_t *result_count)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t num_max = 0;
    size_t i;
    size_t idx = 0;
    ElementCount *out = NULL;

    if (text == NULL || results == NULL || result_count == NULL) {
        return -1;
    }

    *results = NULL;
    *result_count = 0;

    for (i = 0; text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)text[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
        }
    }

    if (max_count == 0) {
        return 0;
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        if (counts[i] == max_count) {
            num_max++;
        }
    }

    out = malloc(num_max * sizeof(ElementCount));
    if (out == NULL) {
        return -1;
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        if (counts[i] == max_count) {
            out[idx].element = (char)i;
            out[idx].count = max_count;
            idx++;
        }
    }

    *results = out;
    *result_count = num_max;
    return 0;
}

int main(void)
{
    const char *text = "the quick brown fox jumps over the lazy dog";
    ElementCount *results = NULL;
    size_t result_count = 0;
    size_t i;

    if (find_most_common(text, &results, &result_count) != 0) {
        fprintf(stderr, "Failed to analyze text\n");
        return EXIT_FAILURE;
    }

    if (result_count == 0) {
        printf("Text is empty\n");
        return EXIT_SUCCESS;
    }

    printf("Most common elements in: \"%s\"\n", text);
    for (i = 0; i < result_count; i++) {
        if (results[i].element == ' ') {
            printf("'(space)' : %zu\n", results[i].count);
        } else {
            printf("'%c' : %zu\n", results[i].element, results[i].count);
        }
    }

    free(results);
    results = NULL;

    return EXIT_SUCCESS;
}