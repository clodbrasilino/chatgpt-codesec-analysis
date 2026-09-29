#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(char **words, int word_count, const char *filter, int *new_count) {
    if (words == NULL || filter == NULL || new_count == NULL || word_count <= 0) {
        if (new_count != NULL) {
            *new_count = 0;
        }
        return NULL;
    }

    if (filter[0] == '\0') {
        *new_count = 0;
        return NULL;
    }

    size_t filter_len = 0;
    while (filter[filter_len] != '\0') {
        filter_len++;
        if (filter_len > (size_t)word_count * 100) {
            *new_count = 0;
            return NULL;
        }
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

        size_t word_len = 0;
        while (words[i][word_len] != '\0') {
            word_len++;
            if (word_len > (size_t)word_count * 1000) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *new_count = 0;
                return NULL;
            }
        }

        int found = 0;

        if (word_len >= filter_len) {
            size_t remaining = word_len;
            const char *word_ptr = words[i];
            while (remaining >= filter_len) {
                size_t k;
                int match = 1;
                for (k = 0; k < filter_len; k++) {
                    if (word_ptr[k] != filter[k]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    found = 1;
                    break;
                }
                word_ptr++;
                remaining--;
            }
        }

        if (!found) {
            if (word_len + 1 > (size_t)(word_count * 1000)) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *new_count = 0;
                return NULL;
            }
            result[count] = (char *)malloc((word_len + 1) * sizeof(char));
            if (result[count] == NULL) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *new_count = 0;
                return NULL;
            }

            for (size_t m = 0; m <= word_len; m++) {
                result[count][m] = words[i][m];
                if (m >= word_len) break;
            }
            count++;
        }
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
    char *words1[] = {
        "Red",
        "",
        "Green",
        "Orange",
        "White"
    };
    int word_count = (int)(sizeof(words1) / sizeof(words1[0]));
    int new_count = 0;

    char **filtered = remove_words(words1, word_count, "a", &new_count);

    if (filtered != NULL) {
        printf("Filtered words (%d):\n", new_count);
        for (int i = 0; i < new_count; i++) {
            printf("%s\n", filtered[i]);
        }
        free_words(filtered, new_count);
    } else {
        printf("No words remained after filtering.\n");
    }

    char *words2[] = {
        "Red &",
        "Orange+",
        "Green",
        "Orange",
        "White"
    };
    word_count = (int)(sizeof(words2) / sizeof(words2[0]));
    new_count = 0;

    filtered = remove_words(words2, word_count, "a", &new_count);

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