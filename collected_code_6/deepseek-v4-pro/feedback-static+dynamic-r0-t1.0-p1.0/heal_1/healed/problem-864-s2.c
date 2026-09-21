#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len == max_len) {
        return false;
    }
    
    for (size_t i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

char **find_palindromes(char **strings, size_t count, size_t *palindrome_count, size_t max_str_len) {
    if (strings == NULL || palindrome_count == NULL) {
        return NULL;
    }

    char **palindromes = malloc(count * sizeof(char *));
    if (palindromes == NULL) {
        return NULL;
    }

    size_t found = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && is_palindrome(strings[i], max_str_len)) {
            palindromes[found] = strings[i];
            found++;
        }
    }

    *palindrome_count = found;
    if (found == 0) {
        free(palindromes);
        return NULL;
    }

    char **result = realloc(palindromes, found * sizeof(char *));
    if (result == NULL) {
        free(palindromes);
        return NULL;
    }

    return result;
}

int main(void) {
    char *strings[] = {
        "radar",
        "hello",
        "level",
        "world",
        "deified",
        "c",
        "",
        "notapalindrome",
        "aabbaa"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t palindrome_count = 0;
    size_t max_str_len = 256;

    char **palindromes = find_palindromes(strings, count, &palindrome_count, max_str_len);

    if (palindromes != NULL) {
        printf("Found %zu palindromes:\n", palindrome_count);
        for (size_t i = 0; i < palindrome_count; i++) {
            printf("  %s\n", palindromes[i]);
        }
        free(palindromes);
    } else {
        printf("No palindromes found or allocation failed.\n");
    }

    return 0;
}