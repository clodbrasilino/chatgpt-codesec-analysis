#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** remove_words_containing(char **list, int *size, const char *pattern) {
    int new_size = 0;
    for (int i = 0; i < *size; ++i) {
        if (strchr(list[i], pattern[0]) == NULL || (pattern[1] == '\0' && strchr(list[i], pattern[0]) != NULL)) {
            list[new_size++] = list[i];
        } else {
            free(list[i]);
        }
    }
    *size = new_size;
    return list;
}

int main() {
    int size = 5;
    char *words[] = {"hello", "world", "test", "data", "example"};
    char **dynamic_words = malloc(size * sizeof(char *));
    for (int i = 0; i < size; ++i) {
        dynamic_words[i] = strdup(words[i]);
    }

    printf("Original list:\n");
    for (int i = 0; i < size; ++i) {
        printf("%s\n", dynamic_words[i]);
    }

    dynamic_words = remove_words_containing(dynamic_words, &size, "e");

    printf("\nFiltered list:\n");
    for (int i = 0; i < size; ++i) {
        printf("%s\n", dynamic_words[i]);
    }

    for (int i = 0; i < size; ++i) {
        free(dynamic_words[i]);
    }
    free(dynamic_words);

    return 0;
}