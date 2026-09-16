#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_palindrome(const char *str)
{
    size_t left;
    size_t right;
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = strlen(str);
    if (len == 0) {
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

size_t find_palindromes(const char *const *strings, size_t count, const char **results, size_t max_results)
{
    size_t found;

    if (strings == NULL || results == NULL || max_results == 0) {
        return 0;
    }

    found = 0;
    for (size_t i = 0; i < count && found < max_results; i++) {
        if (is_palindrome(strings[i])) {
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
        "level",
        "world",
        "Madam",
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