#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return true;
    }

    size_t left = 0;
    size_t right = len - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

char **find_palindromes(char **strings, size_t count, size_t *result_count) {
    if (strings == NULL || result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    char **palindromes = malloc(count * sizeof(char *));
    if (palindromes == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && is_palindrome(strings[i])) {
            palindromes[*result_count] = strings[i];
            (*result_count)++;
        }
    }

    if (*result_count == 0) {
        free(palindromes);
        return NULL;
    }

    char **shrunk_palindromes = realloc(palindromes, *result_count * sizeof(char *));
    if (shrunk_palindromes != NULL) {
        palindromes = shrunk_palindromes;
    }

    return palindromes;
}

int main(void) {
    char *strings[] = {
        "racecar",
        "hello",
        "level",
        "world",
        "madam",
        "",
        "c",
        NULL
    };

    size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t result_count = 0;

    char **palindromes = find_palindromes(strings, count, &result_count);

    if (palindromes != NULL) {
        for (size_t i = 0; i < result_count; i++) {
            printf("%s\n", palindromes[i]);
        }
        free(palindromes);
    } else {
        printf("No palindromes found.\n");
    }

    return 0;
}