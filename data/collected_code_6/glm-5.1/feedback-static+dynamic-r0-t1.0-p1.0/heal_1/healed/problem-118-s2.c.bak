#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return NULL;
    }

    size_t word_count = 0;
    int in_word = 0;
    for (size_t i = 0; i < len; i++) {
        if (!isspace((unsigned char)str[i])) {
            if (!in_word) {
                word_count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }

    if (word_count == 0) {
        return NULL;
    }

    char **list = malloc((word_count + 1) * sizeof(char *));
    if (list == NULL) {
        return NULL;
    }

    size_t w_idx = 0;
    size_t start = 0;
    in_word = 0;

    for (size_t i = 0; i <= len; i++) {
        if (i < len && !isspace((unsigned char)str[i])) {
            if (!in_word) {
                start = i;
                in_word = 1;
            }
        } else {
            if (in_word) {
                size_t w_len = i - start;
                list[w_idx] = malloc((w_len + 1) * sizeof(char));
                if (list[w_idx] == NULL) {
                    for (size_t j = 0; j < w_idx; j++) {
                        free(list[j]);
                    }
                    free(list);
                    return NULL;
                }
                strncpy(list[w_idx], str + start, w_len);
                list[w_idx][w_len] = '\0';
                w_idx++;
                in_word = 0;
            }
        }
    }

    list[word_count] = NULL;
    return list;
}

void free_list(char **list) {
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; list[i] != NULL; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *test_strings[] = {
        "python programming",
        "lists tuples strings",
        "write a program",
        NULL
    };

    for (size_t n = 0; test_strings[n] != NULL; n++) {
        char **list = string_to_list(test_strings[n]);
        if (list == NULL) {
            return EXIT_FAILURE;
        }

        printf("Test %zu: [", n);
        for (size_t i = 0; list[i] != NULL; i++) {
            printf("'%s'%s", list[i], list[i + 1] != NULL ? ", " : "");
        }
        printf("]\n");

        free_list(list);
    }

    return EXIT_SUCCESS;
}