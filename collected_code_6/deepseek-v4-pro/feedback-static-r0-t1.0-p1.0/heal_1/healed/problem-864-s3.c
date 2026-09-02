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
    if (strings == NULL || result_count == NULL || count <= 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    char **results = (char **)malloc(count * sizeof(char *));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL && is_palindrome(strings[i])) {
            results[found] = (char *)malloc((strlen(strings[i]) + 1) * sizeof(char));
            if (results[found] == NULL) {
                for (int j = 0; j < found; j++) {
                    free(results[j]);
                }
                free(results);
                *result_count = 0;
                return NULL;
            }
            strcpy(results[found], strings[i]);
            found++;
        }
    }

    if (found == 0) {
        free(results);
        *result_count = 0;
        return NULL;
    }

    char **final_results = (char **)realloc(results, found * sizeof(char *));
    if (final_results == NULL) {
        for (int j = 0; j < found; j++) {
            free(results[j]);
        }
        free(results);
        *result_count = 0;
        return NULL;
    }

    *result_count = found;
    return final_results;
}

int main(void) {
    char *strings[] = {
        "racecar",
        "hello",
        "madam",
        "world",
        "level",
        "notapalindrome",
        "a",
        ""
    };
    int count = sizeof(strings) / sizeof(strings[0]);
    int palindrome_count = 0;

    char **palindromes = find_palindromes(strings, count, &palindrome_count);

    if (palindromes != NULL) {
        printf("Found %d palindromes:\n", palindrome_count);
        for (int i = 0; i < palindrome_count; i++) {
            printf("%s\n", palindromes[i]);
            free(palindromes[i]);
        }
        free(palindromes);
    } else {
        printf("No palindromes found or error occurred.\n");
    }

    return 0;
}