#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int should_remove(const char *word, const char *filter) {
    if (word == NULL || filter == NULL) return 0;
    return strstr(word, filter) != NULL;
}

char **remove_words(char **list, size_t size, const char *filter, size_t *out_size) {
    if (list == NULL || filter == NULL || out_size == NULL) {
        return NULL;
    }

    char **result = malloc(size * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL && !should_remove(list[i], filter)) {
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
    char *words[] = {"Red", "", "Green", "Orange", "White"};
    size_t size = sizeof(words) / sizeof(words[0]);
    const char *filter = "an";
    
    size_t out_size = 0;
    char **filtered = remove_words(words, size, filter, &out_size);
    
    if (filtered != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s\n", filtered[i]);
        }
        free(filtered);
    }
    
    return 0;
}