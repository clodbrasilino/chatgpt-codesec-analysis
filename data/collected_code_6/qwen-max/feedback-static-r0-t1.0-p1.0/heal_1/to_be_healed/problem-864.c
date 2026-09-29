#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool is_palindrome(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

void find_palindromes(char *strings[], int count, char **result, int *result_count) {
    *result_count = 0;
    for (int i = 0; i < count; i++) {
        if (is_palindrome(strings[i])) {
            result[(*result_count)++] = strings[i];
        }
    }
}

int main() {
    char *strings[] = {"level", "world", "racecar", "hello"};
    int count = 4;
    char **result = (char **)malloc(count * sizeof(char *));
    if (!result) {
        return 1;
    }
    int result_count = 0;

    find_palindromes(strings, count, result, &result_count);

    for (int i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
    }

    free(result);
    return 0;
}