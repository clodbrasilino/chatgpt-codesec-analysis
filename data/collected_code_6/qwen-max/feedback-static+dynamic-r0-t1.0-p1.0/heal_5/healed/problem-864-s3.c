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

void find_palindromes(const char *strings[], size_t count, const size_t *lengths, char **result, size_t *result_count) {
    *result_count = 0;
    for (size_t i = 0; i < count; ++i) {
        size_t len = lengths[i];
        if (is_palindrome(strings[i], len)) {
            result[*result_count] = strdup(strings[i]);
            (*result_count)++;
        }
    }
}

int main() {
    const char *strings[] = {"level", "world", "madam", "python", "racecar"};
    const size_t lengths[] = {5, 5, 5, 6, 7};
    size_t count = sizeof(strings) / sizeof(strings[0]);

    char **palindromes = (char **)malloc(count * sizeof(char *));
    if (palindromes == NULL) {
        return 1;
    }

    size_t palindrome_count = 0;
    find_palindromes(strings, count, lengths, palindromes, &palindrome_count);

    for (size_t i = 0; i < palindrome_count; ++i) {
        printf("%s\n", palindromes[i]);
        free(palindromes[i]);
    }

    free(palindromes);
    return 0;
}