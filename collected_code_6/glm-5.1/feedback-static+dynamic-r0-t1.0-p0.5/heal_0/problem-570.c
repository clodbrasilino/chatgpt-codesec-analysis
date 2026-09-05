#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_match(const char *word, const char *substr, char ch) {
    if (substr != NULL && *substr != '\0') {
        return strstr(word, substr) != NULL;
    }
    if (ch != '\0') {
        return strchr(word, ch) != NULL;
    }
    return 0;
}

char **remove_words(char **list, size_t size, const char *substr, char ch, size_t *out_size) {
    if (list == NULL || size == 0 || out_size == NULL) {
        if (out_size != NULL) *out_size = 0;
        return NULL;
    }

    char **result = malloc(size * sizeof(char *));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL && !contains_match(list[i], substr, ch)) {
            result[count] = list[i];
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *out_size = 0;
        return NULL;
    }

    char **shrunk = realloc(result, count * sizeof(char *));
    if (shrunk != NULL) {
        result = shrunk;
    }

    *out_size = count;
    return result;
}

int main(void) {
    char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    size_t size = sizeof(words) / sizeof(words[0]);
    size_t out_size = 0;

    char **filtered = remove_words(words, size, "an", '\0', &out_size);

    if (filtered != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s\n", filtered[i]);
        }
        free(filtered);
    }

    return 0;
}