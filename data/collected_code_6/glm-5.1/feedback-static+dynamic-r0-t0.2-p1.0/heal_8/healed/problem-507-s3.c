#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(char **list, size_t list_size, const char **remove_list, size_t remove_size, size_t *out_size) {
    if (list == NULL || list_size == 0 || remove_list == NULL || out_size == NULL) {
        if (out_size) *out_size = 0;
        return NULL;
    }

    char **result = malloc(list_size * sizeof(char *));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < list_size; i++) {
        if (list[i] == NULL) {
            continue;
        }

        int should_remove = 0;
        for (size_t j = 0; j < remove_size; j++) {
            if (remove_list[j] != NULL && strcmp(list[i], remove_list[j]) == 0) {
                should_remove = 1;
                break;
            }
        }

        if (!should_remove) {
            result[count] = strdup(list[i]);
            if (result[count] == NULL) {
                for (size_t k = 0; k < count; k++) {
                    free(result[k]);
                }
                free(result);
                *out_size = 0;
                return NULL;
            }
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *out_size = 0;
        return NULL;
    }

    char **shrunk_result = realloc(result, count * sizeof(char *));
    if (shrunk_result != NULL) {
        result = shrunk_result;
    }

    *out_size = count;
    return result;
}

int main(void) {
    char *words1[] = {"red", "green", "blue", "black", NULL};
    const char *to_remove1[] = {"blue"};
    size_t words_size1 = sizeof(words1) / sizeof(words1[0]) - 1;
    size_t remove_size1 = sizeof(to_remove1) / sizeof(to_remove1[0]);
    size_t out_size1 = 0;

    char **filtered1 = remove_words(words1, words_size1, to_remove1, remove_size1, &out_size1);
    if (filtered1 != NULL) {
        printf("[");
        for (size_t i = 0; i < out_size1; i++) {
            printf("'%s'", filtered1[i]);
            if (i < out_size1 - 1) printf(", ");
            free(filtered1[i]);
        }
        printf("]\n");
        free(filtered1);
    } else {
        printf("[]\n");
    }

    char *words2[] = {"red", "green", "blue", "white", NULL};
    const char *to_remove2[] = {"blue"};
    size_t words_size2 = sizeof(words2) / sizeof(words2[0]) - 1;
    size_t remove_size2 = sizeof(to_remove2) / sizeof(to_remove2[0]);
    size_t out_size2 = 0;

    char **filtered2 = remove_words(words2, words_size2, to_remove2, remove_size2, &out_size2);
    if (filtered2 != NULL) {
        printf("[");
        for (size_t i = 0; i < out_size2; i++) {
            printf("'%s'", filtered2[i]);
            if (i < out_size2 - 1) printf(", ");
            free(filtered2[i]);
        }
        printf("]\n");
        free(filtered2);
    } else {
        printf("[]\n");
    }

    char *words3[] = {"red", "green", "black", "orange", NULL};
    const char *to_remove3[] = {"orange"};
    size_t words_size3 = sizeof(words3) / sizeof(words3[0]) - 1;
    size_t remove_size3 = sizeof(to_remove3) / sizeof(to_remove3[0]);
    size_t out_size3 = 0;

    char **filtered3 = remove_words(words3, words_size3, to_remove3, remove_size3, &out_size3);
    if (filtered3 != NULL) {
        printf("[");
        for (size_t i = 0; i < out_size3; i++) {
            printf("'%s'", filtered3[i]);
            if (i < out_size3 - 1) printf(", ");
            free(filtered3[i]);
        }
        printf("]\n");
        free(filtered3);
    } else {
        printf("[]\n");
    }

    return 0;
}