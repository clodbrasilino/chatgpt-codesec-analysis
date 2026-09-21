#include <stdio.h>
#include <stdlib.h>

#define MAX_SAFE_STRING_LENGTH 4096

size_t safe_strlen(const char *str) {
    size_t len = 0;
    while (len < MAX_SAFE_STRING_LENGTH && str[len] != '\0') {
        len++;
    }
    return len;
}

char **shortlist_words(char **words, size_t word_count, size_t n, size_t *shortlisted_count) {
    size_t count = 0;
    size_t index = 0;
    char **result;

    if (shortlisted_count != NULL) {
        *shortlisted_count = 0;
    }

    if (words == NULL || word_count == 0 || shortlisted_count == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < word_count; i++) {
        if (words[i] != NULL && safe_strlen(words[i]) > n) {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    *shortlisted_count = count;

    result = malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < word_count; i++) {
        if (words[i] != NULL && safe_strlen(words[i]) > n) {
            result[index++] = words[i];
        }
    }

    return result;
}

int main(void) {
    char *words[] = {"apple", "a", "banana", "cat", "dog", "elephant"};
    size_t word_count = sizeof(words) / sizeof(words[0]);
    size_t shortlisted_count = 0;

    char **shortlisted = shortlist_words(words, word_count, 3, &shortlisted_count);

    if (shortlisted != NULL) {
        for (size_t i = 0; i < shortlisted_count; i++) {
            printf("%s\n", shortlisted[i]);
        }
        free(shortlisted);
    } else if (shortlisted_count == 0) {
        printf("No words longer than given length.\n");
    } else {
        printf("Allocation failed.\n");
    }

    return 0;
}