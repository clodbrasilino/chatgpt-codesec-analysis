#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t word_count = 0;
    int in_word = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            in_word = 0;
        } else {
            if (!in_word) {
                word_count++;
                in_word = 1;
            }
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
        if (str[i] != ' ' && str[i] != '\0') {
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

    list[w_idx] = NULL;
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
    const char *test1 = "python programming";
    char **list1 = string_to_list(test1);
    if (list1 != NULL) {
        for (size_t i = 0; list1[i] != NULL; i++) {
            printf("%s\n", list1[i]);
        }
        free_list(list1);
    }

    const char *test2 = "lists tuples strings";
    char **list2 = string_to_list(test2);
    if (list2 != NULL) {
        for (size_t i = 0; list2[i] != NULL; i++) {
            printf("%s\n", list2[i]);
        }
        free_list(list2);
    }

    const char *test3 = "write a program";
    char **list3 = string_to_list(test3);
    if (list3 != NULL) {
        for (size_t i = 0; list3[i] != NULL; i++) {
            printf("%s\n", list3[i]);
        }
        free_list(list3);
    }

    return EXIT_SUCCESS;
}