#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char *str, size_t len) {
    if (str == NULL) {
        return false;
    }
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

char **find_palindromes(char **strings, const size_t *lengths, size_t count, size_t *result_count) {
    if (strings == NULL || lengths == NULL || result_count == NULL) {
        return NULL;
    }
    char **palindromes = malloc(count * sizeof(char *));
    if (palindromes == NULL) {
        return NULL;
    }
    size_t current_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && is_palindrome(strings[i], lengths[i])) {
            palindromes[current_count] = strings[i];
            current_count++;
        }
    }
    if (current_count == 0) {
        free(palindromes);
        *result_count = 0;
        return NULL;
    }
    char **trimmed = realloc(palindromes, current_count * sizeof(char *));
    if (trimmed != NULL) {
        palindromes = trimmed;
    }
    *result_count = current_count;
    return palindromes;
}

int main(void) {
    char *strings[] = {"radar", "hello", "level", "world", "madam", "c", "", "noon"};
    size_t count = sizeof(strings) / sizeof(strings[0]);
    /* Possible weaknesses found:
     *  Variable 'lengths' can be declared as const array [constVariable]
     */
    size_t lengths[] = {5, 5, 5, 5, 5, 1, 0, 4};
    size_t result_count = 0;
    char **palindromes = find_palindromes(strings, lengths, count, &result_count);
    if (palindromes != NULL) {
        for (size_t i = 0; i < result_count; i++) {
            printf("%s\n", palindromes[i]);
        }
        free(palindromes);
    }
    return 0;
}