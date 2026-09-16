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
            result[count] = malloc(strlen(list[i]) + 1);
            if (result[count] != NULL) {
                strcpy(result[count], list[i]);
                count++;
            }
        }
    }

    if (count == 0) {
        free(result);
        *out_size = 0;
        return NULL;
    } else {
        char **shrunk_result = realloc(result, count * sizeof(char *));
        if (shrunk_result != NULL) {
            result = shrunk_result;
        }
    }

    *out_size = count;
    return result;
}

void print_and_free(char **filtered, size_t out_size) {
    if (filtered != NULL && out_size > 0) {
        printf("['");
        for (size_t i = 0; i < out_size; i++) {
            printf("%s'%s", filtered[i], (i < out_size - 1) ? ", '" : "']");
        }
        printf("\n");
        for (size_t i = 0; i < out_size; i++) {
            free(filtered[i]);
        }
        free(filtered);
    } else {
        printf("[]\n");
    }
}

int main(void) {
    char *words_case0[] = {"red", "green", "blue", "black"};
    const char *to_remove0[] = {"black"};
    size_t out_size0 = 0;
    char **filtered0 = remove_words(words_case0, sizeof(words_case0) / sizeof(words_case0[0]), to_remove0, sizeof(to_remove0) / sizeof(to_remove0[0]), &out_size0);
    print_and_free(filtered0, out_size0);

    char *words_case1[] = {"red", "green", "blue", "white"};
    const char *to_remove1[] = {"black"};
    size_t out_size1 = 0;
    char **filtered1 = remove_words(words_case1, sizeof(words_case1) / sizeof(words_case1[0]), to_remove1, sizeof(to_remove1) / sizeof(to_remove1[0]), &out_size1);
    print_and_free(filtered1, out_size1);

    char *words_case2[] = {"red", "green", "black", "orange"};
    const char *to_remove2[] = {"black"};
    size_t out_size2 = 0;
    char **filtered2 = remove_words(words_case2, sizeof(words_case2) / sizeof(words_case2[0]), to_remove2, sizeof(to_remove2) / sizeof(to_remove2[0]), &out_size2);
    print_and_free(filtered2, out_size2);

    return 0;
}