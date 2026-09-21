#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *s, size_t max_len) {
    if (s == NULL) {
        return false;
    }
    size_t len = strnlen(s, max_len);
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

char **find_palindromes(char **strings, size_t count, size_t max_len, size_t *result_count) {
    if (strings == NULL || result_count == NULL) {
        return NULL;
    }
    *result_count = 0;
    char **results = malloc(count * sizeof(char *));
    if (results == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && is_palindrome(strings[i], max_len)) {
            results[*result_count] = strings[i];
            (*result_count)++;
        }
    }
    return results;
}

int main(void) {
    char *words[] = {"level", "world", "radar", "hello", "civic", NULL};
    size_t total_count = 0;
    size_t max_len = 0;
    while (words[total_count] != NULL) {
        size_t current_len = strnlen(words[total_count], SIZE_MAX);
        if (current_len > max_len) {
            max_len = current_len;
        }
        total_count++;
    }
    size_t palindrome_count = 0;
    char **palindromes = find_palindromes(words, total_count, max_len, &palindrome_count);
    if (palindromes != NULL) {
        for (size_t i = 0; i < palindrome_count; i++) {
            printf("%s\n", palindromes[i]);
        }
        free(palindromes);
    }
    return 0;
}