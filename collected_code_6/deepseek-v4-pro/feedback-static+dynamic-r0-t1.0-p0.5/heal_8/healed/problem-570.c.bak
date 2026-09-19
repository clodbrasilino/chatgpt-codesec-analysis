#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(char **words, int word_count, const char *filter, int *new_count) {
    if (new_count == NULL) {
        return NULL;
    }

    *new_count = 0;

    if (words == NULL || filter == NULL || word_count <= 0) {
        return NULL;
    }

    int capacity = word_count;
    char **result = (char **)malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL && strstr(words[i], filter) == NULL) {
            size_t len = strlen(words[i]);
            result[count] = (char *)malloc((len + 1) * sizeof(char));
            if (result[count] == NULL) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            memcpy(result[count], words[i], len + 1);
            count++;
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
    }

    char **final_result = (char **)realloc(result, count * sizeof(char *));
    if (final_result == NULL) {
        for (int j = 0; j < count; j++) {
            free(result[j]);
        }
        free(result);
        return NULL;
    }
    result = final_result;

    *new_count = count;
    return result;
}

void free_words(char **words, int count) {
    if (words == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    char *words[] = {
        "apple",
        "banana",
        "cherry",
        "date",
        "elderberry",
        "fig",
        "grape"
    };
    int word_count = sizeof(words) / sizeof(words[0]);
    int new_count = 0;

    char **filtered = remove_words(words, word_count, "a", &new_count);

    if (filtered != NULL) {
        printf("Filtered words (%d):\n", new_count);
        for (int i = 0; i < new_count; i++) {
            printf("%s\n", filtered[i]);
        }
        free_words(filtered, new_count);
    } else {
        printf("No words remained after filtering.\n");
    }

    return 0;
}