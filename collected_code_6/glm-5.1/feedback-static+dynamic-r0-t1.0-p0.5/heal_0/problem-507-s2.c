#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(char **list, size_t list_size, const char **remove_list, size_t remove_size, size_t *out_size) {
    if (list == NULL || remove_list == NULL || out_size == NULL) {
        return NULL;
    }

    char **result = malloc(list_size * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < list_size; i++) {
        int should_remove = 0;
        for (size_t j = 0; j < remove_size; j++) {
            if (remove_list[j] != NULL && strcmp(list[i], remove_list[j]) == 0) {
                should_remove = 1;
                break;
            }
        }
        if (!should_remove) {
            result[count] = list[i];
            count++;
        }
    }

    char **shrunk_result = realloc(result, count * sizeof(char *));
    if (shrunk_result != NULL) {
        result = shrunk_result;
    }

    *out_size = count;
    return result;
}

int main(void) {
    char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    const char *to_remove[] = {"banana", "date"};
    size_t words_size = sizeof(words) / sizeof(words[0]);
    size_t remove_size = sizeof(to_remove) / sizeof(to_remove[0]);
    size_t out_size = 0;

    char **filtered = remove_words(words, words_size, to_remove, remove_size, &out_size);

    if (filtered != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s\n", filtered[i]);
        }
        free(filtered);
    }

    return 0;
}