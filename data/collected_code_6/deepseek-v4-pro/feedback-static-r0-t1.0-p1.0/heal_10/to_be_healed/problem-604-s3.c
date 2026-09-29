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

    size_t len = strnlen(input, 4096);
    if (len >= 4096) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    size_t alloc_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<len' is always false
     */
    if (alloc_size < len) {
        return NULL;
    }

    char *result = (char *)malloc(alloc_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (result == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         *  Condition 'len<alloc_size' is always true [knownConditionTrueFalse]
         *  Condition 'len<alloc_size' is always true
         */
        if (len < alloc_size) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result, input, len);
        } else {
            free(result);
            return NULL;
        }
    }
    result[len] = '\0';

    if (len > 0) {
        reverse_range(result, result + len - 1);

        char *word_start = result;
        char *current = result;

        while (*current != '\0') {
            if (*current == ' ') {
                if (word_start < current) {
                    reverse_range(word_start, current - 1);
                }
                word_start = current + 1;
            }
            current++;
        }

        if (word_start < current) {
            reverse_range(word_start, current - 1);
        }
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
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