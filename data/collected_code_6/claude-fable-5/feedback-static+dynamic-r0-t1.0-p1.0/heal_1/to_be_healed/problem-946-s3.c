#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_TEXT_LEN 1024

typedef struct {
    unsigned char element;
    size_t count;
} ElementCount;

int find_most_common(const char *text, ElementCount *results, size_t max_results, size_t *num_results)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t i;
    size_t len;
    size_t found = 0;

    if (text == NULL || results == NULL || num_results == NULL || max_results == 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(text);
    if (len == 0) {
        *num_results = 0;
        return 0;
    }

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)text[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
        }
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        if (counts[i] == max_count) {
            if (found < max_results) {
                results[found].element = (unsigned char)i;
                results[found].count = counts[i];
                found++;
            } else {
                break;
            }
        }
    }

    *num_results = found;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char text[MAX_TEXT_LEN];
    ElementCount results[UCHAR_MAX + 1];
    size_t num_results = 0;
    size_t i;
    size_t len;

    printf("Enter text: ");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    if (find_most_common(text, results, UCHAR_MAX + 1, &num_results) != 0) {
        fprintf(stderr, "Error processing text\n");
        return EXIT_FAILURE;
    }

    if (num_results == 0) {
        printf("No elements found\n");
        return EXIT_SUCCESS;
    }

    printf("Most common element(s):\n");
    for (i = 0; i < num_results; i++) {
        printf("'%c' : %zu\n", results[i].element, results[i].count);
    }

    return EXIT_SUCCESS;
}