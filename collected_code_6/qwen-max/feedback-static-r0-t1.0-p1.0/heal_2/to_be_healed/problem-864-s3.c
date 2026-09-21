#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *str, size_t len) {
    for (size_t i = 0; i < len / 2; ++i) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

void find_palindromes(const char *strings[], size_t count, char **result, size_t *result_count) {
    *result_count = 0;
    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(strings[i]);
        if (is_palindrome(strings[i], len)) {
            result[*result_count] = strdup(strings[i]);
            (*result_count)++;
        }
    }
}

int main() {
    const char *strings[] = {"level", "world", "madam", "python", "racecar"};
    size_t count = sizeof(strings) / sizeof(strings[0]);

    char **palindromes = (char **)malloc(count * sizeof(char *));
    if (palindromes == NULL) {
        return 1;
    }

    size_t palindrome_count = 0;
    find_palindromes(strings, count, palindromes, &palindrome_count);

    for (size_t i = 0; i < palindrome_count; ++i) {
        printf("%s\n", palindromes[i]);
        free(palindromes[i]);
    }

    free(palindromes);
    return 0;
}