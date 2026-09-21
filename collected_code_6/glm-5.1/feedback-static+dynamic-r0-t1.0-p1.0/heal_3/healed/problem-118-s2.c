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

    size_t word_idx = 0;
    size_t start = 0;
    in_word = 0;

    for (size_t i = 0; i <= len; i++) {
        if (i < len && str[i] != ' ') {
            if (!in_word) {
                start = i;
                in_word = 1;
            }
        } else {
            if (in_word) {
                size_t word_len = i - start;
                list[word_idx] = malloc((word_len + 1) * sizeof(char));
                if (list[word_idx] == NULL) {
                    for (size_t j = 0; j < word_idx; j++) {
                        free(list[j]);
                    }
                    free(list);
                    return NULL;
                }
                memcpy(list[word_idx], str + start, word_len);
                list[word_idx][word_len] = '\0';
                word_idx++;
                in_word = 0;
            }
        }
    }

    list[word_idx] = NULL;
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
    const char *test_cases[] = {
        "python programming",
        "lists tuples strings",
        "write a program",
        "hello"
    };

    for (size_t t = 0; t < sizeof(test_cases) / sizeof(test_cases[0]); t++) {
        char **list = string_to_list(test_cases[t]);
        if (list == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; list[i] != NULL; i++) {
            printf("%s\n", list[i]);
        }
        printf("---\n");
        
        free_list(list);
    }

    return EXIT_SUCCESS;
}