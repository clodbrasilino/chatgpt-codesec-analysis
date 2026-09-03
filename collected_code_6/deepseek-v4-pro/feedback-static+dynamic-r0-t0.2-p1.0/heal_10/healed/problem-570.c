#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(char **words, int word_count, const char *filter, int *new_count) {
    if (words == NULL || filter == NULL || new_count == NULL || word_count <= 0) {
        if (new_count != NULL) *new_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL && (filter[0] == '\0' || strstr(words[i], filter) == NULL)) {
            count++;
        }
    }

    if (count == 0) {
        *new_count = 0;
        return NULL;
    }

    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        *new_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL && (filter[0] == '\0' || strstr(words[i], filter) == NULL)) {
            result[index] = (char *)malloc((strlen(words[i]) + 1) * sizeof(char));
            if (result[index] == NULL) {
                for (int j = 0; j < index; j++) {
                    free(result[j]);
                }
                free(result);
                *new_count = 0;
                return NULL;
            }
            strcpy(result[index], words[i]);
            index++;
        }
    }

    *new_count = count;
    return result;
}

int main(void) {
    char *words[] = {
        "Red",
        "",
        "Green",
        "Orange",
        "White"
    };
    int word_count = sizeof(words) / sizeof(words[0]);
    int new_count = 0;

    char *test_filters[] = {"", "&", "#", "+", "color"};
    int test_count = sizeof(test_filters) / sizeof(test_filters[0]);

    for (int t = 0; t < test_count; t++) {
        char **filtered = remove_words(words, word_count, test_filters[t], &new_count);

        if (filtered != NULL && new_count > 0) {
            printf("Filtered words with \"%s\" (%d):\n", test_filters[t], new_count);
            for (int i = 0; i < new_count; i++) {
                if (filtered[i] != NULL) {
                    printf("%s\n", filtered[i]);
                    free(filtered[i]);
                }
            }
            free(filtered);
        } else {
            printf("No words remain after filtering with \"%s\".\n", test_filters[t]);
            if (filtered != NULL) {
                free(filtered);
            }
        }
    }

    return 0;
}