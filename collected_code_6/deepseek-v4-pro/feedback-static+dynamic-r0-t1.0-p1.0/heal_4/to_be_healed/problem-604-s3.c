#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_range(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char *reverse_words(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, input, len + 1);

    reverse_range(result, result + len - 1);

    char *word_start = result;
    char *current = result;

    while (*current != '\0') {
        if (*current == ' ') {
            reverse_range(word_start, current - 1);
            word_start = current + 1;
        }
        current++;
    }

    if (word_start < current) {
        reverse_range(word_start, current - 1);
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "program python",
        "language java",
        "man indian",
        "Hello World",
        "The quick brown fox",
        "Single",
        "  Multiple   spaces  ",
        "",
        "C programming is fun"
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *reversed = reverse_words(test_cases[i]);
        if (reversed != NULL) {
            printf("Input: \"%s\"\nReversed words: \"%s\"\n\n", test_cases[i], reversed);
            free(reversed);
        } else {
            printf("Memory allocation failed for test case %zu\n", i);
        }
    }

    return 0;
}