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

char *reverse_words(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    const char *ptr = str;
    while (*ptr != '\0') {
        len++;
        ptr++;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        result[i] = str[i];
    }
    result[len] = '\0';

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

    reverse_range(word_start, current - 1);

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "program python",
        "language java",
        "man indian"
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *reversed = reverse_words(test_cases[i]);
        if (reversed != NULL) {
            printf("%s\n", reversed);
            free(reversed);
        }
    }

    return 0;
}