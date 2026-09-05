#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **string_to_list(const char *str, size_t *list_len) {
    if (str == NULL || list_len == NULL) {
        return NULL;
    }

    *list_len = 0;

    size_t len = strlen(str);
    if (len == 0) {
        char **list = malloc(sizeof(char *));
        if (list == NULL) {
            return NULL;
        }
        list[0] = NULL;
        return list;
    }

    size_t capacity = len + 1;
    char **list = malloc(capacity * sizeof(char *));
    if (list == NULL) {
        return NULL;
    }

    size_t i = 0;
    while (i < len) {
        while (i < len && str[i] == ' ') {
            i++;
        }
        if (i >= len) {
            break;
        }

        const char *start = &str[i];
        size_t word_len = 0;
        while (i + word_len < len && str[i + word_len] != ' ') {
            word_len++;
        }

        char *word = malloc((word_len + 1) * sizeof(char));
        if (word == NULL) {
            for (size_t j = 0; j < *list_len; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }

        memcpy(word, start, word_len);
        word[word_len] = '\0';

        if (*list_len >= capacity) {
            capacity *= 2;
            char **new_list = realloc(list, capacity * sizeof(char *));
            if (new_list == NULL) {
                free(word);
                for (size_t j = 0; j < *list_len; j++) {
                    free(list[j]);
                }
                free(list);
                return NULL;
            }
            list = new_list;
        }

        list[*list_len] = word;
        (*list_len)++;
        i += word_len;
    }

    char **final_list = realloc(list, (*list_len + 1) * sizeof(char *));
    if (final_list != NULL) {
        list = final_list;
    }

    list[*list_len] = NULL;

    return list;
}

void free_list(char **list, size_t list_len) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list_len; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *str0 = "python programming";
    size_t list_len0 = 0;
    char **list0 = string_to_list(str0, &list_len0);
    if (list0 != NULL) {
        printf("[");
        for (size_t i = 0; i < list_len0; i++) {
            printf("'%s'", list0[i]);
            if (i < list_len0 - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_list(list0, list_len0);
    }

    const char *str1 = "lists tuples strings";
    size_t list_len1 = 0;
    char **list1 = string_to_list(str1, &list_len1);
    if (list1 != NULL) {
        printf("[");
        for (size_t i = 0; i < list_len1; i++) {
            printf("'%s'", list1[i]);
            if (i < list_len1 - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_list(list1, list_len1);
    }

    const char *str2 = "write a program";
    size_t list_len2 = 0;
    char **list2 = string_to_list(str2, &list_len2);
    if (list2 != NULL) {
        printf("[");
        for (size_t i = 0; i < list_len2; i++) {
            printf("'%s'", list2[i]);
            if (i < list_len2 - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_list(list2, list_len2);
    }

    return 0;
}