#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_palindrome(const char *str, size_t len) {
    if (str == NULL) {
        return false;
    }
    for (size_t i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

static char *safe_strdup(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }
    char *copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    if (len > 0) {
        const char *src = str;
        char *dest = copy;
        size_t remaining = len;
        while (remaining > 0) {
            *dest++ = *src++;
            remaining--;
        }
    }
    copy[len] = '\0';
    return copy;
}

char **find_palindromes(char **strings, int count, int *result_count) {
    if (strings == NULL || result_count == NULL || count <= 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    char **results = (char **)malloc((size_t)count * sizeof(char *));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        size_t len = 0;
        const char *ptr = strings[i];
        while (*ptr != '\0' && len < SIZE_MAX) {
            ptr++;
            len++;
        }
        if (is_palindrome(strings[i], len)) {
            results[found] = safe_strdup(strings[i], len);
            if (results[found] == NULL) {
                for (int j = 0; j < found; j++) {
                    free(results[j]);
                }
                free(results);
                *result_count = 0;
                return NULL;
            }
            found++;
        }
    }

    if (found == 0) {
        free(results);
        *result_count = 0;
        return NULL;
    }

    if (found < count) {
        char **final_results = (char **)realloc(results, (size_t)found * sizeof(char *));
        if (final_results == NULL) {
            for (int j = 0; j < found; j++) {
                free(results[j]);
            }
            free(results);
            *result_count = 0;
            return NULL;
        }
        results = final_results;
    }

    *result_count = found;
    return results;
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
    int count = (int)(sizeof(strings) / sizeof(strings[0]));
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