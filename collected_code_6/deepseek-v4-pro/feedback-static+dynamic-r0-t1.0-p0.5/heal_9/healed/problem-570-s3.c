#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *safe_strdup(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = strlen(str);
    char *copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, str, len + 1);
    return copy;
}

int contains_substring(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) {
        return 0;
    }
    size_t str_len = strlen(str);
    size_t substr_len = strlen(substr);
    
    if (substr_len == 0) {
        return 0;
    }
    if (substr_len > str_len) {
        return 0;
    }
    
    for (size_t i = 0; i <= str_len - substr_len; i++) {
        if (memcmp(str + i, substr, substr_len) == 0) {
            return 1;
        }
    }
    return 0;
}

char **remove_words(char **words, int word_count, const char *filter, int *new_count) {
    if (words == NULL || filter == NULL || new_count == NULL || word_count <= 0) {
        if (new_count != NULL) {
            *new_count = 0;
        }
        return NULL;
    }

    size_t filter_len = strlen(filter);
    
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

        if (filter_len > 0 && contains_substring(words[i], filter)) {
            continue;
        }

        char *dup = safe_strdup(words[i]);
        if (dup == NULL) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            *new_count = 0;
            return NULL;
        }

        result[count] = dup;
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