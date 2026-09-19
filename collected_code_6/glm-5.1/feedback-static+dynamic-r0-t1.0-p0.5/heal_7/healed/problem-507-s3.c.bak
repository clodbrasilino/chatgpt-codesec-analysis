#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(const char **list, size_t list_size, const char **words_to_remove, size_t remove_size, size_t *out_size) {
    if (list == NULL || words_to_remove == NULL || out_size == NULL) {
        return NULL;
    }

    char **result = malloc(list_size * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < list_size; i++) {
        if (list[i] == NULL) {
            continue;
        }

        int should_remove = 0;
        for (size_t j = 0; j < remove_size; j++) {
            if (words_to_remove[j] != NULL && strcmp(list[i], words_to_remove[j]) == 0) {
                should_remove = 1;
                break;
            }
        }

        if (!should_remove) {
            result[count] = malloc(strlen(list[i]) + 1);
            if (result[count] == NULL) {
                for (size_t k = 0; k < count; k++) {
                    free(result[k]);
                }
                free(result);
                *out_size = 0;
                return NULL;
            }
            strcpy(result[count], list[i]);
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
    const char *list[] = {"red", "green", "blue", "black", "white", "orange"};
    const char *to_remove1[] = {"blue", "white"};
    const char *to_remove2[] = {"blue", "orange"};
    const char *to_remove3[] = {"blue", "black"};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t out_size1 = 0, out_size2 = 0, out_size3 = 0;

    char **filtered1 = remove_words(list, list_size, to_remove1, 2, &out_size1);
    if (filtered1 != NULL) {
        for (size_t i = 0; i < out_size1; i++) {
            printf("'%s'", filtered1[i]);
            if (i < out_size1 - 1) {
                printf(", ");
            }
            free(filtered1[i]);
        }
        free(filtered1);
    }
    printf("\n");

    char **filtered2 = remove_words(list, list_size, to_remove2, 2, &out_size2);
    if (filtered2 != NULL) {
        for (size_t i = 0; i < out_size2; i++) {
            printf("'%s'", filtered2[i]);
            if (i < out_size2 - 1) {
                printf(", ");
            }
            free(filtered2[i]);
        }
        free(filtered2);
    }
    printf("\n");

    char **filtered3 = remove_words(list, list_size, to_remove3, 2, &out_size3);
    if (filtered3 != NULL) {
        for (size_t i = 0; i < out_size3; i++) {
            printf("'%s'", filtered3[i]);
            if (i < out_size3 - 1) {
                printf(", ");
            }
            free(filtered3[i]);
        }
        free(filtered3);
    }
    printf("\n");

    return 0;
}