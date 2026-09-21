#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char **remove_words(char **words, int word_count, const char *filter, int *new_count) {
    if (words == NULL || filter == NULL || new_count == NULL || word_count <= 0) {
        if (new_count != NULL) {
            *new_count = 0;
        }
        return NULL;
    }

    size_t filter_len = strnlen(filter, SIZE_MAX);
    if (filter_len == 0) {
        *new_count = word_count;
        char **result = (char **)malloc((size_t)word_count * sizeof(char *));
        if (result == NULL) {
            *new_count = 0;
            return NULL;
        }
        int count = 0;
        for (int i = 0; i < word_count; i++) {
            if (words[i] == NULL) {
                continue;
            }
            size_t len = strnlen(words[i], SIZE_MAX);
            if (len >= SIZE_MAX) {
                continue;
            }
            result[count] = (char *)malloc((len + 1) * sizeof(char));
            if (result[count] == NULL) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *new_count = 0;
                return NULL;
            }
            memcpy(result[count], words[i], len);
            result[count][len] = '\0';
            count++;
        }
        if (count == 0) {
            free(result);
            *new_count = 0;
            return NULL;
        }
        char **final_result = (char **)realloc(result, (size_t)count * sizeof(char *));
        if (final_result == NULL) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            *new_count = 0;
            return NULL;
        }
        *new_count = count;
        return final_result;
    }

    char **result = (char **)malloc((size_t)word_count * sizeof(char *));
    if (result == NULL) {
        *new_count = 0;
        return NULL;
    }

    int count = 0;

    for (int i = 0; i < word_count; i++) {
        if (words[i] == NULL) {
            continue;
        }

        if (strstr(words[i], filter) != NULL) {
            continue;
        }

        size_t len = strnlen(words[i], SIZE_MAX);
        if (len >= SIZE_MAX - 1) {
            continue;
        }

        result[count] = (char *)malloc((len + 1) * sizeof(char));
        if (result[count] == NULL) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            *new_count = 0;
            return NULL;
        }

        memcpy(result[count], words[i], len);
        result[count][len] = '\0';
        count++;
    }

    if (count == 0) {
        free(result);
        *new_count = 0;
        return NULL;
    }

    char **final_result = (char **)realloc(result, (size_t)count * sizeof(char *));
    if (final_result == NULL) {
        for (int j = 0; j < count; j++) {
            free(result[j]);
        }
        free(result);
        *new_count = 0;
        return NULL;
    }

    *new_count = count;
    return final_result;
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
        "Red color",
        "Orange#",
        "Green",
        "Orange @",
        "White"
    };
    int word_count = (int)(sizeof(words) / sizeof(words[0]));

    char *filters[] = { "#", "&", "+", "@" };
    int filter_count = (int)(sizeof(filters) / sizeof(filters[0]));

    for (int f = 0; f < filter_count; f++) {
        int new_count = 0;
        char **filtered = remove_words(words, word_count, filters[f], &new_count);

        printf("Filter '%s':\n", filters[f]);
        if (filtered != NULL) {
            for (int i = 0; i < new_count; i++) {
                printf("  '%s'\n", filtered[i]);
            }
            free_words(filtered, new_count);
        } else {
            printf("  No words remained\n");
        }
        printf("\n");
    }

    return 0;
}