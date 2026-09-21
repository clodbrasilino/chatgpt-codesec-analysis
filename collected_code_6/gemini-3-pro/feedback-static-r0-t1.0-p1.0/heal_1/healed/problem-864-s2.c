#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 4096

bool is_palindrome(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strnlen(str, MAX_STRING_LENGTH);
    if (len == 0 || len == MAX_STRING_LENGTH) {
        return false;
    }
    
    for (size_t i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

char **find_palindromes(const char **strings, size_t count, size_t *out_count) {
    if (strings == NULL || out_count == NULL) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    char **palindromes = malloc(count * sizeof(char *));
    if (palindromes == NULL) {
        *out_count = 0;
        return NULL;
    }

    size_t found_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (is_palindrome(strings[i])) {
            char *copy = strdup(strings[i]);
            if (copy == NULL) {
                for (size_t j = 0; j < found_count; j++) {
                    free(palindromes[j]);
                }
                free(palindromes);
                *out_count = 0;
                return NULL;
            }
            palindromes[found_count++] = copy;
        }
    }

    *out_count = found_count;
    char **shrunk = realloc(palindromes, found_count * sizeof(char *));
    if (shrunk != NULL || found_count == 0) {
        palindromes = shrunk;
    }

    return palindromes;
}

int main(void) {
    const char *test_strings[] = {
        "radar",
        "hello",
        "level",
        "world",
        "racecar",
        "",
        "a"
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t palindrome_count = 0;

    char **palindromes = find_palindromes(test_strings, count, &palindrome_count);
    
    if (palindromes != NULL) {
        for (size_t i = 0; i < palindrome_count; i++) {
            printf("%s\n", palindromes[i]);
            free(palindromes[i]);
        }
        free(palindromes);
    }

    return 0;
}