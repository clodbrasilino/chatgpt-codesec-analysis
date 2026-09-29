#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

void find_palindromes(const char *strings[], size_t count, char **result, size_t *result_count) {
    *result_count = 0;
    for (size_t i = 0; i < count; ++i) {
        if (is_palindrome(strings[i])) {
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