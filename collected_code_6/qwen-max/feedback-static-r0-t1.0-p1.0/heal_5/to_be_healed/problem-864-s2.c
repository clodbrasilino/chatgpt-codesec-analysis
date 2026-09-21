#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *str, size_t len) {
    for (size_t i = 0; i < len / 2; ++i) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

void find_palindromes(char **strings, int count, char **result, int *result_count) {
    *result_count = 0;
    for (int i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(strings[i]);
        if (is_palindrome(strings[i], len)) {
            result[*result_count] = strings[i];
            (*result_count)++;
        }
    }
}

int main() {
    const char *strings[] = {"雷达", "level", "world", "madam", "deified", "hello"};
    int count = sizeof(strings) / sizeof(strings[0]);
    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        return 1;
    }
    int result_count;

    find_palindromes((char **)strings, count, result, &result_count);

    for (int i = 0; i < result_count; ++i) {
        printf("%s\n", result[i]);
    }

    free(result);
    return 0;
}