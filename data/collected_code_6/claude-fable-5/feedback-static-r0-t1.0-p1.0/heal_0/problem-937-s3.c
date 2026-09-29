#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int most_common_char(const char *str, char *result, size_t *count)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t i;
    size_t max_count = 0;
    int max_char = -1;

    if (str == NULL || result == NULL || count == NULL) {
        return -1;
    }

    if (str[0] == '\0') {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
            max_char = (int)c;
        }
    }

    if (max_char < 0) {
        return -1;
    }

    *result = (char)max_char;
    *count = max_count;
    return 0;
}

int main(void)
{
    const char *test_string = "programming in c is fun";
    char most_common = '\0';
    size_t occurrences = 0;

    if (most_common_char(test_string, &most_common, &occurrences) != 0) {
        fprintf(stderr, "Error: could not determine most common character\n");
        return EXIT_FAILURE;
    }

    if (printf("Most common character: '%c' (appears %zu times)\n",
               most_common, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}