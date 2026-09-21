#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_palindrome(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    size_t start = 0;
    size_t end = len - 1;

    while (start < end) {
        if (str[start] != str[end]) {
            return 0;
        }
        start++;
        end--;
    }

    return 1;
}

char **find_palindromes(const char **strings, size_t num_strings, size_t *out_count) {
    if (strings == NULL || out_count == NULL) {
        return NULL;
    }

    char **palindromes = malloc(num_strings * sizeof(char *));
    if (palindromes == NULL) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < num_strings; i++) {
        if (is_palindrome(strings[i])) {
            palindromes[count] = strdup(strings[i]);
            if (palindromes[count] == NULL) {
                for (size_t j = 0; j < count; j++) {
                    free(palindromes[j]);
                }
                free(palindromes);
                return NULL;
            }
            count++;
        }
    }

    *out_count = count;

    if (count < num_strings) {
        char **resized = realloc(palindromes, count * sizeof(char *));
        if (resized != NULL || count == 0) {
            palindromes = resized;
        }
    }

    return palindromes;
}

int main(void) {
    const char *strings[] = {
        "radar",
        "hello",
        "level",
        "world",
        "madam",
        "a",
        "",
        NULL
    };

    size_t num_strings = 7; 
    size_t out_count = 0;

    char **palindromes = find_palindromes(strings, num_strings, &out_count);

    if (palindromes != NULL) {
        for (size_t i = 0; i < out_count; i++) {
            printf("%s\n", palindromes[i]);
            free(palindromes[i]);
        }
        free(palindromes);
    } else if (out_count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}