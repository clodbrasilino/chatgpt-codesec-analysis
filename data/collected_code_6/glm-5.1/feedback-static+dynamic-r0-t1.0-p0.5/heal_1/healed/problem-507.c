#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_words(char **list, size_t list_size, const char **words_to_remove, size_t remove_size, size_t *out_size) {
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
            result[count] = list[i];
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
    char *test0_list[] = {"red", "green", "blue", "black", "yellow"};
    const char *test0_remove[] = {"yellow"};
    size_t test0_list_size = sizeof(test0_list) / sizeof(test0_list[0]);
    size_t test0_remove_size = sizeof(test0_remove) / sizeof(test0_remove[0]);
    size_t test0_out_size = 0;

    char **test0_result = remove_words(test0_list, test0_list_size, test0_remove, test0_remove_size, &test0_out_size);
    if (test0_result != NULL) {
        for (size_t i = 0; i < test0_out_size; i++) {
            printf("%s ", test0_result[i]);
        }
        printf("\n");
        free(test0_result);
    }

    char *test1_list[] = {"red", "green", "blue", "white", "purple"};
    const char *test1_remove[] = {"purple"};
    size_t test1_list_size = sizeof(test1_list) / sizeof(test1_list[0]);
    size_t test1_remove_size = sizeof(test1_remove) / sizeof(test1_remove[0]);
    size_t test1_out_size = 0;

    char **test1_result = remove_words(test1_list, test1_list_size, test1_remove, test1_remove_size, &test1_out_size);
    if (test1_result != NULL) {
        for (size_t i = 0; i < test1_out_size; i++) {
            printf("%s ", test1_result[i]);
        }
        printf("\n");
        free(test1_result);
    }

    char *test2_list[] = {"red", "green", "black", "orange", "cyan"};
    const char *test2_remove[] = {"cyan"};
    size_t test2_list_size = sizeof(test2_list) / sizeof(test2_list[0]);
    size_t test2_remove_size = sizeof(test2_remove) / sizeof(test2_remove[0]);
    size_t test2_out_size = 0;

    char **test2_result = remove_words(test2_list, test2_list_size, test2_remove, test2_remove_size, &test2_out_size);
    if (test2_result != NULL) {
        for (size_t i = 0; i < test2_out_size; i++) {
            printf("%s ", test2_result[i]);
        }
        printf("\n");
        free(test2_result);
    }

    char *list[] = {"apple", "banana", "cherry", "date", "elderberry"};
    const char *to_remove[] = {"banana", "date"};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t remove_size = sizeof(to_remove) / sizeof(to_remove[0]);
    size_t out_size = 0;

    char **filtered_list = remove_words(list, list_size, to_remove, remove_size, &out_size);

    if (filtered_list != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s\n", filtered_list[i]);
        }
        free(filtered_list);
    }

    return 0;
}