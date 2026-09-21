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

void find_palindromes(const char *strings[], size_t count, const size_t string_sizes[], char **result, size_t *result_count) {
    *result_count = 0;
    for (size_t i = 0; i < count; ++i) {
        size_t len = string_sizes[i];
        if (is_palindrome(strings[i], len)) {
            result[*result_count] = (char *)malloc(len + 1);
            if (result[*result_count]) {
                strncpy(result[*result_count], strings[i], len);
                result[*result_count][len] = '\0';
                (*result_count)++;
            } else {
                for (size_t j = 0; j < *result_count; ++j) {
                    free(result[j]);
                }
                *result_count = 0;
                return;
            }
        }
    }
}

int main() {
    const char *strings[] = {"level", "world", "madam", "python", "racecar"};
    size_t count = sizeof(strings) / sizeof(strings[0]);

    const size_t string_sizes[] = {strlen(strings[0]), strlen(strings[1]), strlen(strings[2]), strlen(strings[3]), strlen(strings[4])};

    char **palindromes = (char **)malloc(count * sizeof(char *));
    if (palindromes == NULL) {
        return 1;
    }

    size_t palindrome_count = 0;
    find_palindromes(strings, count, string_sizes, palindromes, &palindrome_count);

    for (size_t i = 0; i < palindrome_count; ++i) {
        printf("%s\n", palindromes[i]);
        free(palindromes[i]);
    }

    free(palindromes);
    return 0;
}