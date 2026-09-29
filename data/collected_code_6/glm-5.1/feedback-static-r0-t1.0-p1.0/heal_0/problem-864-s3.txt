#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *s) {
    if (s == NULL) {
        return false;
    }
    size_t len = strlen(s);
    size_t i = 0;
    size_t j = len > 0 ? len - 1 : 0;
    while (i < j) {
        if (s[i] != s[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

char **find_palindromes(char **strings, size_t count, size_t *result_count) {
    if (strings == NULL || result_count == NULL) {
        return NULL;
    }
    *result_count = 0;
    char **results = (char **)malloc(count * sizeof(char *));
    if (results == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && is_palindrome(strings[i])) {
            results[*result_count] = strings[i];
            (*result_count)++;
        }
    }
    return results;
}

int main(void) {
    char *words[] = {"level", "world", "radar", "hello", "civic", NULL};
    size_t total_count = 0;
    while (words[total_count] != NULL) {
        total_count++;
    }
    size_t palindrome_count = 0;
    char **palindromes = find_palindromes(words, total_count, &palindrome_count);
    if (palindromes != NULL) {
        for (size_t i = 0; i < palindrome_count; i++) {
            printf("%s\n", palindromes[i]);
        }
        free(palindromes);
    }
    return 0;
}