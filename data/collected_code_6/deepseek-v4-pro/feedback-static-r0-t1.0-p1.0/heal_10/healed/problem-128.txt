#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char **shortlist_words(char **words, int word_count, int n, int *result_count) {
    if (words == NULL || word_count <= 0 || n < 0 || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    size_t max_len = (size_t)n;
    char **result = NULL;
    int count = 0;
    size_t alloc_count = 0;

    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL) {
            size_t len = strlen(words[i]);
            if (len > max_len) {
                if (count >= (int)alloc_count) {
                    size_t new_alloc = (alloc_count == 0) ? 4 : alloc_count * 2;
                    char **temp = (char **)realloc(result, new_alloc * sizeof(char *));
                    if (temp == NULL) {
                        for (int j = 0; j < count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        *result_count = 0;
                        return NULL;
                    }
                    result = temp;
                    alloc_count = new_alloc;
                }

                result[count] = (char *)malloc((len + 1) * sizeof(char));
                if (result[count] == NULL) {
                    for (int j = 0; j < count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *result_count = 0;
                    return NULL;
                }

                if (len > 0) {
                    memcpy(result[count], words[i], len);
                }
                result[count][len] = '\0';
                count++;
            }
        }
    }

    if (count == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    char **temp = (char **)realloc(result, count * sizeof(char *));
    if (temp == NULL) {
        for (int j = 0; j < count; j++) {
            free(result[j]);
        }
        free(result);
        *result_count = 0;
        return NULL;
    }

    *result_count = count;
    return temp;
}

int main(void) {
    char *words[] = {"apple", "banana", "cat", "dog", "elephant"};
    int word_count = sizeof(words) / sizeof(words[0]);
    int result_count = 0;
    int threshold = 3;

    char **result = shortlist_words(words, word_count, threshold, &result_count);

    if (result == NULL) {
        printf("No words longer than %d found or error occurred.\n", threshold);
        return 0;
    }

    printf("Words longer than %d:\n", threshold);
    for (int i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}