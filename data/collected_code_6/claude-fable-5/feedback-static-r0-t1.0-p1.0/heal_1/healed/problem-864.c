#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 4096

bool is_palindrome(const char *str)
{
    size_t left;
    size_t right;
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = strnlen(str, MAX_STRING_LENGTH);
    if (len == 0 || len >= MAX_STRING_LENGTH) {
        return false;
    }

    left = 0;
    right = len - 1;

    while (left < right) {
        if (tolower((unsigned char)str[left]) != tolower((unsigned char)str[right])) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

size_t find_palindromes(const char *strings[], size_t count, const char *results[], size_t max_results)
{
    size_t found = 0;
    size_t i;

    if (strings == NULL || results == NULL || max_results == 0) {
        return 0;
    }

    for (i = 0; i < count && found < max_results; i++) {
        if (strings[i] != NULL && is_palindrome(strings[i])) {
            results[found] = strings[i];
            found++;
        }
    }

    return found;
}

int main(void)
{
    const char *words[] = {
        "racecar",
        "hello",
        "Level",
        "world",
        "madam",
        "noon",
        "example"
    };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    const char **palindromes;
    size_t palindrome_count;

    palindromes = malloc(word_count * sizeof(*palindromes));
    if (palindromes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    palindrome_count = find_palindromes(words, word_count, palindromes, word_count);

    if (palindrome_count == 0) {
        printf("No palindromes found.\n");
    } else {
        printf("Palindromes found:\n");
        for (size_t i = 0; i < palindrome_count; i++) {
            printf("%s\n", palindromes[i]);
        }
    }

    free(palindromes);
    return EXIT_SUCCESS;
}