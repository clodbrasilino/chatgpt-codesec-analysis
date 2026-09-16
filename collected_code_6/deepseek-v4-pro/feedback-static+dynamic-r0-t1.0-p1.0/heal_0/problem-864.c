#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

char **find_palindromes(char **strings, int count, int *result_count) {
    if (strings == NULL || count <= 0 || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    char **palindromes = malloc((size_t)count * sizeof(char *));
    if (palindromes == NULL) {
        *result_count = 0;
        return NULL;
    }

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL && is_palindrome(strings[i])) {
            palindromes[found] = strings[i];
            found++;
        }
    }

    if (found == 0) {
        free(palindromes);
        *result_count = 0;
        return NULL;
    }

    char **result = realloc(palindromes, (size_t)found * sizeof(char *));
    if (result == NULL) {
        free(palindromes);
        *result_count = 0;
        return NULL;
    }

    *result_count = found;
    return result;
}

int main(void) {
    char *strings[] = {"racecar", "hello", "level", "world", "madam", "test"};
    int count = sizeof(strings) / sizeof(strings[0]);
    int result_count = 0;

    char **palindromes = find_palindromes(strings, count, &result_count);

    if (palindromes != NULL) {
        printf("Palindromes found:\n");
        for (int i = 0; i < result_count; i++) {
            printf("%s\n", palindromes[i]);
        }
        free(palindromes);
    } else {
        printf("No palindromes found or error occurred.\n");
    }

    return 0;
}